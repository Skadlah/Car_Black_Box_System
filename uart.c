/*
 * File:   uart.c
 * Author: sheryas
 *
 * Created on 9 February, 2025, 7:25 PM
 
? Step 10: Setting Up uart.c (UART Communication - Serial Data Transfer)
This file is responsible for:
? Initializing UART Communication ? Configures serial communication with a PC.
? Sending Data (Logs) via UART ? Sends event logs from EEPROM to a PC terminal.
? Receiving Data via UART (if needed) ? Allows receiving commands from a PC.

 */

#include <xc.h>
#include "uart.h"
#include "main.h"

void init_uart(void) {
    /* Serial initialization */
    RX_PIN = 1;  // Set RX as input
    TX_PIN = 0;  // Set TX as output

    TX9 = 0;     // 8-bit transmission
    TXEN = 1;    // Enable transmitter
    SYNC = 0;    // Set Asynchronous Mode
    BRGH = 1;    // High Baud Rate Select
    SPEN = 1;    // Enable Serial Port

    RX9 = 0;     // 8-bit reception
    CREN = 1;    // Enable receiver

    SPBRG = 129; // Set Baud Rate to 9600 for 20MHz Clock

    TXIE = 1;    // Enable TX Interrupt
    TXIF = 0;    // Clear TX Interrupt Flag
    RCIE = 1;    // Enable RX Interrupt
    RCIF = 0;    // Clear RX Interrupt Flag
}

void putch(unsigned char byte) 
{
    /* Output one byte */
    while (!TXIF);  // Wait until TX buffer is empty
    TXREG = byte;   // Load byte into TX register
}

int puts(const char *s) 
{
    while (*s) 
    {        
        putch(*s++);  // Send each character
    }
    return 0;
}

unsigned char getch(void) 
{
    /* Retrieve one byte */
    while (!RCIF);  // Wait until RX buffer is full
    return RCREG;   // Return received byte
}

/*
 1 init_uart() - Configuring UART

void init_uart(void) {
    Serial initialization 
    RX_PIN = 1;  // Set RX as input
    TX_PIN = 0;  // Set TX as output
? Configures TX (transmit) and RX (receive) pins:

RX_PIN = 1; ? Configures RX (Receive Pin - RC7) as an input.
TX_PIN = 0; ? Configures TX (Transmit Pin - RC6) as an output.
 */
/*
? Setting UART Transmission Mode

    TX9 = 0;     // 8-bit transmission
    TXEN = 1;    // Enable transmitter
    SYNC = 0;    // Set Asynchronous Mode
    BRGH = 1;    // High Baud Rate Select
    SPEN = 1;    // Enable Serial Port
? Configures UART for 8-bit, asynchronous, high-speed transmission:

TX9 = 0; ? Uses 8-bit transmission mode (standard for most applications).
TXEN = 1; ? Enables the UART Transmitter.
SYNC = 0; ? Sets UART to Asynchronous Mode (Standard Serial Communication).
BRGH = 1; ? Enables high-speed baud rate selection.
SPEN = 1; ? Enables the UART Serial Port (activates TX & RX).
? Setting UART Reception Mode

    RX9 = 0;     // 8-bit reception
    CREN = 1;    // Enable receiver
? Configures UART for 8-bit reception mode:

RX9 = 0; ? Uses 8-bit data format.
CREN = 1; ? Enables Continuous Reception (automatically receives data when available).
? Setting Baud Rate

    SPBRG = 129; // Set Baud Rate to 9600 for 20MHz Clock
 * 
? Configures the UART Baud Rate to 9600 (Standard for Serial Communication)

 * Baud Rate Formula for Asynchronous Mode
 
 * Baud Rate =  Fosc / 16(SPBRG+1)

 * Using Fosc = 20MHz and SPBRG = 129, we get:
 
 * BaudRate = 20,000,000 / 16×(129+1) = 9600

This matches the standard 9600 baud rate used for serial communication with a PC.
? Enabling UART Interrupts

    TXIE = 1;    // Enable TX Interrupt
    TXIF = 0;    // Clear TX Interrupt Flag
    RCIE = 1;    // Enable RX Interrupt
    RCIF = 0;    // Clear RX Interrupt Flag
}
? Configures Interrupts for UART Communication:

TXIE = 1; ? Enables Transmit Interrupts (Not used in this code, but ready for future use).
TXIF = 0; ? Clears the Transmit Interrupt Flag.
RCIE = 1; ? Enables Receive Interrupts (Not used in this code, but can be used for receiving commands).
RCIF = 0; ? Clears the Receive Interrupt Flag.
2?? putch() - Transmitting a Single Character
c
Copy
Edit
void putch(unsigned char byte) {
    /* Output one byte 
    while (!TXIF);  // Wait until TX buffer is empty
    TXREG = byte;   // Load byte into TX register
}
? This function sends a single character via UART.

while (!TXIF); ? Waits until the TX Buffer is empty before sending data.
TXREG = byte; ? Loads the character into the Transmit Register, which sends it over UART.
Example Usage:

c
Copy
Edit
putch('A');  // Sends the character 'A' via UART
3?? puts() - Transmitting a String
c
Copy
Edit
int puts(const char *s) {
    while (*s) {        
        putch(*s++);  // Send each character
    }
    return 0;
}
? This function sends a complete string via UART, character by character.

Uses putch() to send each letter in the string.
Stops sending when it reaches \0 (end of the string).
Example Usage:

c
Copy
Edit
puts("Hello, World!");
? Sends "Hello, World!" to the PC over UART.

4?? getch() - Receiving a Character
c
Copy
Edit
unsigned char getch(void) {
    /* Retrieve one byte 
    while (!RCIF);  // Wait until RX buffer is full
    return RCREG;   // Return received byte
}
? Receives a single character via UART.

Waits until the Receive Buffer (RCREG) is full (while (!RCIF)).
Returns the received character from RCREG.
Example Usage:

c
Copy
Edit
char received_char = getch();  // Wait for input from PC
? Receives a character from a serial terminal (e.g., PuTTY, Tera Term, Arduino Serial Monitor).

? Summary of uart.c
Function	Purpose
init_uart()	Initializes UART (9600 baud rate, TX/RX setup)
putch(byte)	Sends a single character via UART
puts(s)	Sends a string via UART
getch()	Receives a character from UART
*/