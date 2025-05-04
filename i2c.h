/*
? Step 16: Setting Up i2c.h (I2C Communication Header File)
This file (i2c.h) is needed to:
? Define function prototypes for I2C communication.
? Enable data transfer between the PIC16F877A and external devices (EEPROM, RTC).
? Ensure modularity by keeping I2C functions separate from other code.
*/

#ifndef I2C_H
#define I2C_H

#include <xc.h>

// Function Prototypes
void init_i2c(void);               // Initialize I2C communication
void i2c_start(void);              // Send I2C Start Condition
void i2c_rep_start(void);          // Send I2C Repeated Start Condition
void i2c_stop(void);               // Send I2C Stop Condition
void i2c_write(unsigned char data); // Write data to I2C bus
unsigned char i2c_read(void);      // Read data from I2C bus

#endif

/*
 1 - Prevent Multiple Inclusions

#ifndef I2C_H
#define I2C_H
? Prevents multiple inclusions of this file to avoid duplicate definitions.

Ensures that the compiler only includes i2c.h once during compilation.

2 - Function Prototypes for I2C Communication

void init_i2c(void);               // Initialize I2C communication
void i2c_start(void);              // Send I2C Start Condition
void i2c_rep_start(void);          // Send I2C Repeated Start Condition
void i2c_stop(void);               // Send I2C Stop Condition
void i2c_write(unsigned char data); // Write data to I2C bus
unsigned char i2c_read(void);      // Read data from I2C bus
? Declares functions that will be implemented in i2c.c:

init_i2c() ? Initializes I2C module (sets up clock and control registers).
i2c_start() ? Sends a Start Condition (begins communication).
i2c_rep_start() ? Sends a Repeated Start Condition (used in reading data).
i2c_stop() ? Sends a Stop Condition (ends communication).
i2c_write(data) ? Sends a byte of data to an I2C device.
i2c_read() ? Receives a byte of data from an I2C device.
? Example Usage:


i2c_start();                     // Start I2C Communication
i2c_write(EEPROM_I2C_ADDRESS);   // Send EEPROM address in write mode
i2c_write(0x10);                 // Send memory address
i2c_write(0x55);                 // Write data (0x55)
i2c_stop();                      // Stop I2C Communication
? This writes the value 0x55 to EEPROM address 0x10.

? Summary of i2c.h
     Section                             Purpose
Header Guards           ->	  Prevents multiple inclusions of the file
Function Prototypes     ->    Declares I2C functions for i2c.c
I2C Operations          ->    Supports Start, Stop, Write, Read*/