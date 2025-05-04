/*
 ? Step 11: Setting Up uart.h (UART Header File)
The UART Header File (uart.h) is needed to:
? Define macros for UART control pins.
? Declare function prototypes for uart.c.
? Ensure smooth communication between the PIC16F877A and external devices.

*/
#ifndef UART_H
#define UART_H

// Define UART Pins
#define RX_PIN  TRISC7  // RX (Receive) on RC7
#define TX_PIN  TRISC6  // TX (Transmit) on RC6

// Function Prototypes
void init_uart(void);             // Initialize UART
void putch(unsigned char byte);   // Send one character
int puts(const char *s);          // Send a string
unsigned char getch(void);        // Receive one character
unsigned char getch_with_timeout(unsigned short max_time);
unsigned char getche(void);

#endif

/*
 1 Prevent Multiple Inclusions

#ifndef UART_H
#define UART_H
 
? Prevents multiple inclusions of this file to avoid redefinitions.

This ensures the compiler only includes uart.h once during compilation.
 
2 Define UART Control Pins

#define RX_PIN  TRISC7  // RX (Receive) on RC7
#define TX_PIN  TRISC6  // TX (Transmit) on RC6
? Defines which microcontroller pins are used for serial communication:

RX_PIN = TRISC7 ? The Receive Pin (RC7) is set as an input.
TX_PIN = TRISC6 ? The Transmit Pin (RC6) is set as an output.
 
3 Function Prototypes (Used in uart.c)

void init_uart(void);             // Initialize UART
void putch(unsigned char byte);   // Send one character
int puts(const char *s);          // Send a string
unsigned char getch(void);        // Receive one character
unsigned char getch_with_timeout(unsigned short max_time);
unsigned char getche(void);
? Declares the UART functions implemented in uart.c:

init_uart() ? Initializes the UART hardware (9600 baud, TX/RX setup).
putch(byte) ? Sends one character via UART.
puts(s) ? Sends a complete string via UART.
getch() ? Receives one character via UART.
getch_with_timeout(max_time) ? Receives a character, but only waits for a limited time.
getche() ? Receives a character and echoes it back.
 * 

? Summary of uart.h
    Section                                     Purpose
Header Guards            ->  Prevents multiple inclusions of the file
UART Pin Definitions     ->   Assigns RX (RC7) and TX (RC6) pins
Function Prototypes      ->    Declares UART functions for uart.c
*/