/*
 * File:   LAB1_cas17169.c
 * Author: Josue
 * LAB1_Juego de Carreras 1.2
 * Created on 24 de enero de 2020, 12:11 PM
 */

#include <xc.h>
#define _XTAL_FREQ 4000000

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
unsigned char ESTADO  = 0x00;
unsigned char ESTADO2 = 0x00;
char          ESTADO3 = 0x00;
unsigned int  count   = 0x00;
unsigned int  count2  = 0x00;

unsigned char FLAG_ON = 0x00;

// Prototipos de Funciones 
void config(void);

// PROGRAMA PRINCIPL
void main(void) {
    config ();
    
    unsigned int TABLA7SEG [10] = {  //Array para secuencia de Inicio del Programa
        0b01111110, //0
        0b00110000, //1
        0b01101101, //2
        0b01111001, //3
        
        0b00110011, //4
        0b01011011, //5
        0b01011111, //6
        0b01110000, //7
        0b01111111, //8
        0b01111011, //9   
    };
    
    unsigned int jugador_uno [8] = {  //Array para secuencia de Inicio del Programa
        0b00000001,  
        0b00000010,  
        0b00000100,  
        0b00001000,  
        0b00010000,  
        0b00100000,  
        0b01000000,  
        0b10000000,    
    };
    
    unsigned int jugador_dos [8] = {  //Array para secuencia de Inicio del Programa
        0b00000001,  
        0b00000010,  
        0b00000100,  
        0b00001000,  
        0b00010000,  
        0b00100000,  
        0b01000000,  
        0b10000000,
    };
    
    while (1){
        
        if (PORTAbits.RA0 == 1){        //RUTINA INICIAL DEL JUEGO
            ESTADO = 1;
            __delay_us(250);
            
            if (ESTADO == 1 && PORTAbits.RA0 == 0) {
              
                PORTB = TABLA7SEG[3];
                PORTAbits.RA3 = 1; //Led VERDE
                __delay_ms(1000);

                PORTB = TABLA7SEG[2];
                PORTAbits.RA4 = 1; //Led AMARILLO
                __delay_ms(1000);

                PORTB = TABLA7SEG[1];
                PORTAbits.RA5 = 1; //Led ROJO
                __delay_ms(500);

                __delay_ms(500);
                PORTAbits.RA3 = 0; 
                PORTAbits.RA4 = 0; 
                PORTAbits.RA5 = 0; 
                PORTB = TABLA7SEG[0];   //SE PONE esta linea de ultimo para que conincidan los tiempos con los leds del 
                FLAG_ON =1;
            }
            ESTADO = 0;
        }
      
    
        
    while (FLAG_ON ==1){  
        if (PORTAbits.RA1 == 1 && ESTADO2 == 0) {                            //LECTURA DEL JUGADOR 1 
            ESTADO2 = 1;
            PORTC = jugador_uno[count]; 
            count++;
            __delay_us(250);
        }
        
        if (PORTAbits.RA2 == 1 && ESTADO3 == 0) {      //LECTURA DEL JUGADOR 1          PORTBbits.RB1 == 1
            ESTADO3 = 1;
            PORTD = jugador_dos[count2];  
            count2++;
            __delay_us(250);
        }
              
        //PORTC = jugador_uno[count];    //Corre bit del Puerto C con el contador del array
        //PORTD = jugador_dos[count2];          
        
                
        if (PORTCbits.RC7 == 1) {
            PORTC = 0x00; 
            PORTD = 0x00; 
            PORTEbits.RE0 = 1;
            PORTB = TABLA7SEG[1]; //SE MUESTRA EN EL DISPLAY QUE GANO EL JUGADOR 2!!!
            __delay_ms(1000);
            PORTEbits.RE0 = 0;
            PORTB = TABLA7SEG[0];
            __delay_ms(1000);
            PORTB = TABLA7SEG[1];
            PORTEbits.RE0 = 1;
            __delay_ms(1000);
            PORTB = TABLA7SEG[0];
            PORTEbits.RE0 = 0;
            __delay_ms(1000);
            PORTB = TABLA7SEG[1];
            PORTEbits.RE0 = 1;

            __delay_ms(5000);
            PORTB = 0x00; 
            PORTC = 0x00; 
            PORTD = 0x00; 
            PORTE = 0x00; 
            FLAG_ON = 0;
        }        
                
                
        if (PORTDbits.RD7 == 1) {
            PORTC = 0x00;
            PORTD = 0x00;
            PORTEbits.RE1 = 1;
            PORTB = TABLA7SEG[2]; //SE MUESTRA EN EL DISPLAY QUE GANO EL JUGADOR 2!!!
            __delay_ms(1000);
            PORTEbits.RE1 = 0;
            PORTB = TABLA7SEG[0];
            __delay_ms(1000);
            PORTB = TABLA7SEG[2];
            PORTEbits.RE1 = 1;
            __delay_ms(1000);
            PORTB = TABLA7SEG[0];
            PORTEbits.RE1 = 0;
            __delay_ms(1000);
            PORTB = TABLA7SEG[2];
            PORTEbits.RE1 = 1;

            __delay_ms(5000);
            PORTB = 0x00; 
            PORTC = 0x00; 
            PORTD = 0x00; 
            PORTE = 0x00; 
            FLAG_ON = 0;
        }
            
         
        if (PORTAbits.RA1 == 0) {       
           ESTADO2 = 0;
        }
        
        if (PORTAbits.RA2 == 0) {       
           ESTADO3 = 0;
        }
        
  
    }
  }   
    return;
}


// Funciones de Inicialización de Puertos 
void config(void){
    ANSEL = ANSELH = 0;
    TRISB = 0x00; //Puerto OUT para Displays 7 SEGMENTOS
    TRISC = 0x00; //Puerto OUT  para 8leds jugador 1
    TRISD = 0x00; //Puerto OUT  para 8leds jugador 2
    //TRISA = 0b00000111; //Puertos de ENTRADA (PUSH RA0,RA1,RA2) y Puertos de SALIDA (SEMAFORO Y LEDS GANADORES)
    TRISAbits.TRISA0 = 1 ;
    TRISAbits.TRISA1 = 1 ; // Puertos de entrada RA0-RA2 para PUSH BUTTONS
    TRISAbits.TRISA2 = 1 ;
    TRISAbits.TRISA3 = 0 ;
    TRISAbits.TRISA4 = 0 ; // Puertos de salida  RA3-RA5 para LED Semáforo
    TRISAbits.TRISA5 = 0 ;
    
    TRISEbits.TRISE0 = 0 ;
    TRISEbits.TRISE1 = 0 ; // Puertos de salida para LEDS ganadores
   
    PORTA = 0x00;          //Inicialización de Puertos
    PORTB = 0x00;
    PORTC = 0x00;  
    PORTD = 0x00;
    PORTE = 0x00;
}