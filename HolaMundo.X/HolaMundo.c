/*
 * File:   HolaMundo.c
 * Author: Josue
 *
 * Created on 22 de enero de 2020, 12:50 PM
 */


#include <xc.h>

//*****************************   CONFIGURATION BITIS   *****************************************************************************
// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2 
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// Prototipos de Funciones 
void init(void);
void delay_ms(unsigned int dms);

// Funci�n Principal del Programa

void main(void) {
    init();
    
    while(1){
        if (PORTAbits.RA3 == 1){
            PORTAbits.RA3 = 0;
        }  else {
            PORTAbits.RA3 = 1;
        } 
        delay_ms(500);
    }
    return;
}

// Funciones de Inicializaci�n de Puertos 
void init(void){
    TRISAbits.TRISA3 = 0 ;
    ANSEL  = 0;
    ANSELH = 0;
}

// Funcion para tiempo 
void delay_ms(unsigned int dms){
    for (int i=0; i<dms; i++) {
        for(int j=0; j<255; j++);
    }
}


