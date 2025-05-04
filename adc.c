/*
 * File:   adc.c
 * Author: sheryas
 *
 * Created on 9 February, 2025, 9:02 PM

? Step 5: adc.c (ADC Implementation File)
This file (adc.c) is responsible for:
? Configuring the ADC module on the PIC16F877A.
? Reading values from the selected ADC channel. */


#include "adc.h"
#include "main.h"

void init_adc(void) 
{
    ADCON0 = 0x00;  // ADC OFF initially
    ADCON1 = 0x0E;  // Configure all pins as digital except AN0
    ADCON0 = 0x01;  // Enable ADC module
    __delay_ms(2);  // Wait for ADC stabilization
}

unsigned short read_adc(unsigned char channel) 
{
    ADCON0 &= 0xC3;  // Clear channel selection bits
    ADCON0 |= (channel << 2);  // Select ADC channel
    GO = 1;  // Start ADC conversion
    while (GO);  // Wait for conversion to complete
    //return ((ADRESH << 8) | ADRESL);  // Combine high and low bytes
    return (((unsigned short)ADRESH << 8) | ADRESL);
}
