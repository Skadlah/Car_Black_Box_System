#ifndef CLCD_H
#define CLCD_H

#include <xc.h>

// Define LCD Control Pins
#define RS RD2  // Register Select (Command/Data)
#define RW RD3  // Read/Write
#define EN RD4  // Enable

// Define LCD Commands
#define CLEAR_DISP_SCREEN  0x01  // Clear LCD screen
#define DISPLAY_ON_CURSOR_OFF  0x0C  // Turn ON display, cursor OFF
#define DISPLAY_ON_CURSOR_ON   0x0E  // Turn ON display, cursor ON

// Define LCD Line Addresses
#define LINE1(x) (0x80 + x)  // Line 1 Start Address
#define LINE2(x) (0xC0 + x)  // Line 2 Start Address

// Function Prototypes
void init_clcd(void);                      // Initialize LCD
void clcd_write(unsigned char, unsigned char);  // Write command or data
void clcd_print(const char *, unsigned char);  // Print string on LCD
void clcd_putch(char, unsigned char);      // Print single character

#endif

/*1 Prevent Multiple Inclusions

#ifndef CLCD_H
#define CLCD_H
Prevents multiple inclusions of the header file to avoid redefinitions.
Ensures the compiler processes this file only once during compilation.
 
2 LCD Port & Control Pins Definition

#define CLCD_PORT   PORTD   // LCD Data Port
#define CLCD_EN     RC2     // LCD Enable
#define CLCD_RW     RC1     // LCD Read/Write
#define CLCD_RS     RC0     // LCD Register Select
? Defines which PIC pins are connected to the LCD:

PORTD (CLCD_PORT) ? Used as the data port for LCD.
RC2 (CLCD_EN) ? Enable (E) pin ? Triggers LCD to read data.
RC1 (CLCD_RW) ? Read/Write (RW) pin ? 0 for write, 1 for read.
RC0 (CLCD_RS) ? Register Select (RS) pin ?
0 ? Command Mode (Send LCD settings like cursor position).
1 ? Data Mode (Send characters to display).
 
3 LCD Command Types
#define INSTRUCTION_COMMAND 0
#define DATA_COMMAND        1
? Defines command types for clcd_write() function:

INSTRUCTION_COMMAND = 0 ? Used to send LCD commands (e.g., clear screen, move cursor).
DATA_COMMAND = 1 ? Used to send characters (e.g., "HELLO" on LCD).
4 Function Prototypes (Used in clcd.c)
void init_clcd(void);                         // Initialize LCD
void clcd_write(unsigned char, unsigned char);// Write Command/Data to LCD
void clcd_print(const char *, unsigned char); // Print String on LCD
void clcd_putch(char, unsigned char);         // Print Single Character on LCD
? Declares the LCD functions defined in clcd.c:

init_clcd() ? Initializes LCD in 8-bit mode, clears display, sets cursor.
clcd_write(byte, mode) ? Sends commands (mode = 0) or data (mode = 1) to LCD.
clcd_print(data, addr) ? Displays a string at a given position.
clcd_putch(data, addr) ? Displays a single character at a given position.
 *
? Summary of clcd.h

Header Guards           -> Prevents multiple inclusions of the file
LCD Port Definitions    -> Defines which PIC pins are connected to LCD
Command Type Macros     -> Specifies command mode vs data mode
Function Prototypes     -> Declares LCD functions for use in clcd.c & main.c*/