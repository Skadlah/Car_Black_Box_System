/*
 * File:   ext_eep.c
 * Author: sheryas
 *
 * Created on 9 February, 2025, 8:00 PM
 ? Step 15: Setting Up ext_eep.c (External EEPROM Implementation)
This file implements functions to communicate with an external EEPROM using I2C communication.

? Stores important data like logs, passwords, and settings permanently.
? Reads previously stored values when needed.
? Uses I2C communication for data transfer.
 
 */
#include "ext_eep.h"
#include "i2c.h"

void write_ext_eep(unsigned char address, unsigned char data) 
{
    i2c_start();                     // Start I2C communication
    i2c_write(EEPROM_I2C_ADDRESS);    // Send EEPROM address with Write mode
    i2c_write(address);               // Send memory register address
    i2c_write(data);                  // Send data to be written
    i2c_stop();                        // Stop I2C communication
}

unsigned char read_ext_eep(unsigned char address) 
{
    unsigned char data;

    i2c_start();                      // Start I2C communication
    i2c_write(EEPROM_I2C_ADDRESS);    // Send EEPROM address with Write mode
    i2c_write(address);               // Send memory register address
    i2c_rep_start();                   // Restart I2C for reading
    i2c_write(EEPROM_I2C_ADDRESS | 1); // Send EEPROM address with Read mode
    data = i2c_read();                 // Read data from EEPROM
    i2c_stop();                        // Stop I2C communication

    return data;
}

/*
 1 - write_ext_eep() - Write Data to EEPROM

void write_ext_eep(unsigned char address, unsigned char data) 
{
    i2c_start();                      // Start I2C communication
    i2c_write(EEPROM_I2C_ADDRESS);    // Send EEPROM address with Write mode
    i2c_write(address);               // Send memory register address
    i2c_write(data);                  // Send data to be written
    i2c_stop();                        // Stop I2C communication
}
? Writes data to a specific address in EEPROM using I2C.

i2c_start(); ? Starts I2C communication.
i2c_write(EEPROM_I2C_ADDRESS); ? Sends the EEPROM device address (0xA0 for write mode).
i2c_write(address); ? Sends the specific memory register address to store data.
i2c_write(data); ? Writes the data value at that memory address.
i2c_stop(); ? Stops I2C communication.
? Example Usage:


write_ext_eep(0x10, 0x55);  // Store value 0x55 at memory address 0x10
? This stores the value 0x55 at EEPROM address 0x10.

2 - read_ext_eep() - Read Data from EEPROM

unsigned char read_ext_eep(unsigned char address) 
{
    unsigned char data;

    i2c_start();                      // Start I2C communication
    i2c_write(EEPROM_I2C_ADDRESS);    // Send EEPROM address with Write mode
    i2c_write(address);               // Send memory register address
    i2c_rep_start();                   // Restart I2C for reading
    i2c_write(EEPROM_I2C_ADDRESS | 1); // Send EEPROM address with Read mode
    data = i2c_read();                 // Read data from EEPROM
    i2c_stop();                        // Stop I2C communication

    return data;
}
? Reads stored data from a specific address in EEPROM.

i2c_start(); ? Starts I2C communication.
i2c_write(EEPROM_I2C_ADDRESS); ? Sends EEPROM device address (0xA0) in write mode.
i2c_write(address); ? Sends memory register address where data is stored.
i2c_rep_start(); ? Restarts I2C communication for reading.
i2c_write(EEPROM_I2C_ADDRESS | 1); ? Sends EEPROM device address in read mode (0xA1).
data = i2c_read(); ? Reads stored data from EEPROM.
i2c_stop(); ? Stops I2C communication.
Returns the retrieved data to the calling function.
? Example Usage:

unsigned char stored_value = read_ext_eep(0x10);
? This reads the value stored at EEPROM address 0x10.

? Summary of ext_eep.c
        Function                                      Purpose
write_ext_eep(address, data)  ->      Stores data in EEPROM at a specific address
read_ext_eep(address)         ->      Retrieves stored data from EEPROM*/

