/*
 * File:   clcd.c
 * Author: sheryas
 *
 * Created on 9 February, 2025, 11:19 AM
 * This file controls the 16x2 LCD, allowing the system to display text, numbers, and status messages. 
 * It includes:
? LCD Initialization ? Configures LCD in 8-bit mode.
? LCD Commands & Data Writing ? Sends commands and characters to LCD.
? Functions for Displaying Text & Characters ? Used in the Dashboard, Menu, and Password Entry screens.

 */

#include "clcd.h"
#include "main.h"
void init_clcd(void) {
    TRISD = 0x00;  // Configure PORTD as output
    __delay_ms(15);  // LCD power-on delay

    clcd_write(0x02, 0);  // Set 4-bit mode
    clcd_write(0x28, 0);  // 2-line display, 5x7 font
    clcd_write(DISPLAY_ON_CURSOR_OFF, 0);  // Display ON, Cursor OFF
    clcd_write(CLEAR_DISP_SCREEN, 0);  // Clear screen
    __delay_ms(2);  // Clear screen delay
}

void clcd_write(unsigned char byte, unsigned char mode) {
    RS = mode;  // RS = 0 for command, RS = 1 for data
    RW = 0;  // RW = 0 for write
    EN = 1;
    PORTD = (byte & 0xF0);  // Send higher nibble
    EN = 0;
    __delay_us(100);
    EN = 1;
    PORTD = ((byte << 4) & 0xF0);  // Send lower nibble
    EN = 0;
    __delay_ms(2);
}

void clcd_print(const char *str, unsigned char addr) {
    clcd_write(addr, 0);  // Set cursor position
    while (*str) {
        clcd_write(*str++, 1);  // Print each character
    }
}

void clcd_putch(char data, unsigned char addr) {
    clcd_write(addr, 0);  // Set cursor position
    clcd_write(data, 1);  // Print character
}
