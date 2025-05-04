/*
 * File:   i2c.c
 * Author: sheryas
 *
 * Created on 9 February, 2025, 8:09 PM
 ? Step 17: Setting Up i2c.c (I2C Communication Implementation)
This file implements I2C communication functions for the PIC16F877A microcontroller, 
 * allowing it to communicate with external I2C devices like EEPROM and RTC.

? Initializes the I2C module on the PIC16F877A.
? Sends and receives data over the I2C bus.
? Handles start, stop, and restart conditions for communication.
*/

#include "i2c.h"

void init_i2c(void) 
{
    SSPCON = 0x28;    // Enable I2C in master mode
    SSPADD = 49;      // Set clock speed (100kHz for 20MHz system clock)
    SSPSTAT = 0x00;   // Standard speed
}

void i2c_start(void)
{
    SEN = 1;          // Initiate Start Condition
    while (SEN);      // Wait for completion
}

void i2c_rep_start(void) 
{
    RSEN = 1;         // Initiate Repeated Start Condition
    while (RSEN);     // Wait for completion
}

void i2c_stop(void) 
{
    PEN = 1;          // Initiate Stop Condition
    while (PEN);      // Wait for completion
}

void i2c_write(unsigned char data) 
{
    SSPBUF = data;    // Load data into buffer
    while (!SSPIF);   // Wait for transmission to complete
    SSPIF = 0;        // Clear interrupt flag
}

unsigned char i2c_read(void) 
{
    RCEN = 1;         // Enable Receive Mode
    while (!BF);      // Wait for data reception
    return SSPBUF;    // Return received data
}

/*
 1 - init_i2c() - Initialize I2C Module

void init_i2c(void) 
{
    SSPCON = 0x28;    // Enable I2C in master mode
    SSPADD = 49;      // Set clock speed (100kHz for 20MHz system clock)
    SSPSTAT = 0x00;   // Standard speed
}
? This function initializes I2C communication in Master Mode.

SSPCON = 0x28; ? Configures the Synchronous Serial Port (SSP) module for I2C Master Mode.
SSPADD = 49; ? Sets the baud rate for 100kHz I2C speed when using a 20MHz system clock.
Formula:

SSPADD = Fosc / 4×Baud Rate - 1
For Fosc = 20MHz, baud rate = 100kHz:
 
SSPADD = 20,000,000 / 4 x 100000 - 1 
 *     = 49;
 SSPSTAT = 0x00; ? Standard I2C speed settings.

? Example Usage:
init_i2c();  // Initializes I2C communication

2 - i2c_start() - Send I2C Start Condition

void i2c_start(void) 
{
    SEN = 1;          // Initiate Start Condition
    while (SEN);      // Wait for completion
}

? This function sends a Start Condition to begin I2C communication.

SEN = 1; ? Initiates the Start Condition (notifies connected I2C devices to prepare for communication).
while (SEN); ? Waits until the Start Condition is completed.
? Example Usage:

i2c_start();  // Begin I2C communication
3?? i2c_rep_start() - Send I2C Repeated Start Condition

void i2c_rep_start(void) 
{
    RSEN = 1;         // Initiate Repeated Start Condition
    while (RSEN);     // Wait for completion
}
? This function sends a Repeated Start Condition (used in reading data).

RSEN = 1; ? Sends a Repeated Start Condition to keep communication open.
while (RSEN); ? Waits until the Repeated Start is completed.
? Example Usage:

i2c_rep_start();  // Used before reading from EEPROM or RTC
4 - i2c_stop() - Send I2C Stop Condition

void i2c_stop(void) 
{
    PEN = 1;          // Initiate Stop Condition
    while (PEN);      // Wait for completion
}
? This function sends a Stop Condition to terminate I2C communication.

PEN = 1; ? Initiates the Stop Condition (signals end of communication).
while (PEN); ? Waits until Stop Condition is completed.
? Example Usage:
i2c_stop();  // End I2C communication
 
5 - i2c_write() - Send Data Over I2C
void i2c_write(unsigned char data) 
{
    SSPBUF = data;    // Load data into buffer
    while (!SSPIF);   // Wait for transmission to complete
    SSPIF = 0;        // Clear interrupt flag
}
? This function sends a byte of data to an I2C device.

SSPBUF = data; ? Loads data into the I2C buffer.
while (!SSPIF); ? Waits until data transmission is complete.
SSPIF = 0; ? Clears the Interrupt Flag to prepare for the next transfer.
? Example Usage:

i2c_write(EEPROM_I2C_ADDRESS);  // Send EEPROM address in write mode
6 - i2c_read() - Read Data Over I2C

unsigned char i2c_read(void) 
{
    RCEN = 1;         // Enable Receive Mode
    while (!BF);      // Wait for data reception
    return SSPBUF;    // Return received data
}
? This function reads a byte of data from an I2C device.

RCEN = 1; ? Enables Receive Mode (gets data from I2C bus).
while (!BF); ? Waits until data is received into the buffer.
return SSPBUF; ? Returns the received byte from the I2C buffer.
? Example Usage:

unsigned char data = i2c_read();  // Read a byte from EEPROM or RTC
? Summary of i2c.c
    Function                             Purpose
init_i2c()                  Initializes I2C Master Mode
i2c_start()             	Sends I2C Start Condition
i2c_rep_start()             Sends I2C Repeated Start Condition
i2c_stop()                  Sends I2C Stop Condition
i2c_write(data)             Writes data to an I2C device
i2c_read()                  Reads data from an I2C device
*/

