/*
 * File:   LAB2_cas17169.c
 * Author: Josue Castillo Lou
 * Carné:  17169
 * LAB2_Interrupciones ADC, TMR0, Multiplexeo & Librerias
 * Created on 2 de febrero de 2020, 03:05 PM
 */

#include <xc.h>
#include <stdint.h>
#include "ADC_Library.h"                    //Librería de la Configuración del ADC 
#include "TMR0_InterruptMultiplex.h"        //Librería del Multiplexado para 7 Segmentos con el TMR0_Interrupción 
#define _XTAL_FREQ 4000000      // 4MHz

// CONFIG1 (DEBE IR DEBJO DEL #include <xc.h>)
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

//Definición de Variables Globales
uint8_t resultado_ADC_uni = 0;
uint8_t resultado_ADC_dec = 0;
uint8_t ADC_nibble_uni    = 0x0F; //0b00001111
//uint8_t ADC_nibble_dec  = 0xF0; //0b11110000
int     DISPLAY[16]       = {0b01111110, 0b00110000, 0b01101101, 0b01111001, 0b00110011, 0b01011011, 0b01011111, 0b01110000, 0b01111111, 0b01111011, 0b01110111, 0b00011111, 0b01001110, 0b00111101, 0b01001111, 0b11000111};

// Prototipos de Funciones 
void config(void);
void Show_7SEG(void);
//void initTMR0(void);


void __interrupt() ISR(void) {
    if (ADIF) {                                         //La bandera del ADC "ADIF" se enciende cada vez que hace una conversión!
        resultado_ADC_dec = ADRESH >> 4;                //(AND de los 4Bits LSB para el primer display_uni)
        resultado_ADC_uni = ADRESH & ADC_nibble_uni;    //(AND de los 4Bits MSB para el segundo display_dec + Corrimiento de bits)
        //PORTD = resultado_ADC_dec;                    //PRUEBA para verificar separacion de nibbles
        //PORTC = resultado_ADC_uni;
        Show_7SEG();                                    //ACA FIJO SIRVE EL MULTIPLEXEO!!
    }
    
    if (RBIF) {                                         //La bandera del IOCB "RBIF" se enciende cada vez que se presiona cualquier PushBotton en el PORTB
        if(PORTBbits.RB5 == 0){
            PORTD = PORTD++ ; 
        } 
        if(PORTBbits.RB7 == 0){
            PORTD = PORTD-- ; 
        }
        INTCONbits.RBIF  = 0 ; //APAGAMOS BANDERA DE IOCB ¡Con esto Funciono!
     }
    
    /*if (TMR0IF){            NOTA : SI HABLIITO EL TMR0 SE ARRUINAN LAS OTRAS DOS INTERRUPCIONES ( POR ESO EL MULTIPLEXEO LO PUSE EN OTRA PARTE)
        TMR0IF = 0;
        TMR0 = 100;
        
    }*/
    
}


//************************ Programa Principal **********************************

void main(void) {
    config ();
    config_ADC ();                  //Función en la Librería "ADC_Library"
    
    while(1){
    __delay_us(20);      
    ADCON0bits.GO_nDONE = 1;        // Enable ADC convertion
                                    // ACA NO SIRVE LLAMAR A LA FUNCION "Show_7SEG()"
    
    if (PORTD < ADRESH){            //Comparación del PORTD "Valor referencia" vs Valor ADC 
        PORTEbits.RE0 = 1;          //Si el ADC supera al Valor de referencia se activa la alarma!
    }
    else{
        PORTEbits.RE0 = 0;
        }
    
    }
   
    return;
}


void Show_7SEG(void){
        PORTEbits.RE2 = 0;
        PORTC = DISPLAY[resultado_ADC_uni];
        PORTEbits.RE1 = 1;
        __delay_us(100);
        PORTEbits.RE1 = 0;
        PORTC = DISPLAY[resultado_ADC_dec];
        PORTEbits.RE2 = 1;  
        PIR1bits.ADIF = 0;
}


/*
void Show_7SEG(void){
    if (FLAG == 1){
        PORTEbits.RE2 = 0;
        PORTC = DISPLAY[resultado_ADC_uni];
        PORTEbits.RE1 = 1; 
        FLAG = 0;
    }
    if (FLAG == 0){
        PORTEbits.RE1 = 0;
        PORTC = DISPLAY[resultado_ADC_dec];
        PORTEbits.RE2 = 1;  
    }
    
}
*/


// Funciones de Inicialización de Puertos 
void config(void){
    
    TRISC = 0x00; //Puerto OUT para 2 Displays de 7 SEGMENTOS
    TRISD = 0x00; //Puerto OUT para 8 Leds del Contador de Referencia
    TRISEbits.TRISE0 = 0; //PIN ALARMA 
    TRISEbits.TRISE1 = 0; //PINES MULTIPLEXEO
    TRISEbits.TRISE2 = 0; //PINES MULTIPLEXEO
    
     
//*********************** CONFIG PORTB con Interrupción *********************
    ANSELH = 0;             //YA SE APAGO EN EL ADC_Config
    INTCONbits.GIE   = 1;   //Se habilitan las Configuraciones Globales
    
    INTCONbits.RBIF  = 0 ; //APAGAMOS BANDERA DE IOCB 
    TRISBbits.TRISB7 = 1 ; //PUSH BOTTON 1 (RB0) PARA INCREMENTO CONTADOR Ref
    TRISBbits.TRISB5 = 1 ; //PUSH BOTTON 2 (RB1) PARA DECREMENTO CONTADOR Ref 
    
    OPTION_REGbits.nRBPU = 0;  //PUERTO B como entrada con PULL-UP 
    
    //IOCB_PORTB_Config
    INTCONbits.RBIE = 1;       //Habilita que PORTB tenga la interrupcion de cambio
  //INTCONbits.INTE = 1;       //Habilita la Interrupcion externa (IOCB PORTB)   ???? NOOOOOO SE HABILITA!
    IOCBbits.IOCB7  = 1;       //Se habilita la interrupción del PORTB del PUSH1
    IOCBbits.IOCB5  = 1;       //Se habilita la interrupción del PORTB del PUSH2
     
//****************************************************** *********************    
    
    PORTA = 0x00;          //Inicialización de Puertos
    PORTB = 0x00;
    PORTC = 0x00;  
    PORTD = 0x00;
    PORTE = 0x00;
}

/*void initTMR0(void){
    OPTION_REG = 0x85;   // Configuración para tener un desborde 
    TMR0 = 100;         // de 10 mS    
    INTCON = 0xA0;
}*/