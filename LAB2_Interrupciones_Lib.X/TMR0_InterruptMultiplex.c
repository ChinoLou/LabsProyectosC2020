/*
 * File:   TMR0_InterruptMultiplex.c
 * Author: Steven Josué Castillo Lou
 * Comments: (Librería TMR0 desborde de 10ms Para Multiplexeo Displays)
 * Created on 5 de febrero de 2020, 12:15 AM
 */

#include <stdint.h>
#include <pic16f887.h>
#include "TMR0_InterruptMultiplex.h"

void TMR0_InterruptMultiplex(uint8_t resultado_ADC_uni) {
    switch (resultado_ADC_uni){             //TABLA VALORES DISPLA7 DE 0 A 15 EN HEXADECIMAL (CÁTODO COMÚN)
        case 0: 
            PORTC =  0b01111110;
            break;
        case 1: 
            PORTC =  0b00110000;
            break;
        case 2: 
            PORTC =  0b01101101;
            break;
        case 3: 
            PORTC =  0b01111001;
            break;
        case 4: 
            PORTC =  0b00110011;
            break;
        case 5: 
            PORTC =  0b01011011;
            break;
        case 6: 
            PORTC =  0b01011111;
            break;
        case 7: 
            PORTC =  0b01110000;
            break;
        case 8: 
            PORTC =  0b01111111;
            break;
        case 9: 
            PORTC =  0b01111011;
            break;
        case 10: 
            PORTC =  0b01110111;
            break;
        case 11: 
            PORTC =  0b00011111;
            break;
        case 12: 
            PORTC =  0b01001110;
            break;
        case 13: 
            PORTC =  0b00111101;
            break;
        case 14: 
            PORTC =  0b01001111;
            break;
        case 15: 
            PORTC =  0b11000111;
            break;
    }
     
    return;
}






 

 


 
 
  
 
 

 



