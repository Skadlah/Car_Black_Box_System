/*
? Step 4: adc.h (ADC Header File)
This file (adc.h) is responsible for:
? Defining function prototypes for ADC operations.
? Enabling modularity by separating ADC-related functions.
*/

#ifndef ADC_H
#define ADC_H

#include <xc.h>

// Function Prototype
void init_adc(void);                  // Initialize ADC module
unsigned short read_adc(unsigned char channel);  // Read ADC value

#endif
