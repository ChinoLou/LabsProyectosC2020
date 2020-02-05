/*
 * File:   ADC_Library.c
 * Author: Josue
 *
 * Created on 3 de febrero de 2020, 06:01 PM
 */
#include <pic16f887.h>
#include "ADC_Library.h"

//**************************************************************
// Función para configurar el ADC con Interrupciones
// Ver pág. 99 del Manual PIC16F887
//**************************************************************

void config_ADC(void){
    ADCON0bits.ADON  = 1;   // Habilitamos el Módulo ADC en general
    
    ANSELH = 0;             //Apagamos el ANSEL_H "Puerto B"
    ANSELbits.ANS0   = 1;   //Encendemos el ANSEL_L para ANALOG_INPUT en RA0 (El módulo ADC tiene 4 registros: ADRESH,ADRESL. ADCON0 Y ADCON registros de control)
    TRISAbits.TRISA0 = 1;   //Entrada Analógica Asociada (RA0) para la conversión ADC
    
    ADCON0bits.CHS0  = 0;   //Seleccionamos el CANAL para usar el RA0    
    ADCON0bits.CHS0  = 0;   // CHS<3:0> 4 Bits de selección de canal ya que son 14 puertos analogicos 
    ADCON0bits.CHS0  = 0;
    ADCON0bits.CHS0  = 0;
    
    ADCON1bits.ADFM  = 0;   //Justificación a la izquierda << para usar ANSEL_L
    ADCON1bits.VCFG0 = 0;   //VDD COMO REFERENCIA VREF+ (5V)
    ADCON1bits.VCFG1 = 0;   //GND COMO REFERENCIA VREF- (0v)
    
    ADCON0bits.ADCS1 = 1;   //Seleccionamos el FOSC/8 correspondiente a los 4MHz del XTAL_FREQ (2uS)
    ADCON0bits.ADCS0 = 0; 
    
    //Config_Interrupcion ADC 
    INTCONbits.GIE   = 1;   //Se habilitan las Configuraciones Globales
    INTCONbits.PEIE  = 1;   //Interrupción Periférica del ADC (ON)
    PIE1bits.ADIE    = 1;   //Habilita la Interrupción del ADC
    PIR1bits.ADIF    = 0;   //InterruptADC_Flag (Se enciende cada vez que termina una conversión)
}