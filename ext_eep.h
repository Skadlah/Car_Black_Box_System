/*
 ? Step 14: Setting Up ext_eep.h (External EEPROM Header File)
This file (ext_eep.h) is required to:
? Define EEPROM I2C Address ? Allows communication with external EEPROM.
? Declare function prototypes ? Used in ext_eep.c for reading/writing data.
? Enable data storage for event logging ? Stores speed, gear shifts, and logs.

*/

#ifndef EXT_EEP_H
#define EXT_EEP_H

#include <xc.h>

// EEPROM I2C Address
#define EEPROM_I2C_ADDRESS  0xA0  // 10100000 (Write Mode)

// Function Prototypes
void write_ext_eep(unsigned char address, unsigned char data);  // Write data to EEPROM
unsigned char read_ext_eep(unsigned char address);  // Read data from EEPROM

#endif


/*
 1 - Prevent Multiple Inclusions

#ifndef EXT_EEP_H
#define EXT_EEP_H
? Prevents multiple inclusions of this file to avoid redefinitions.

Ensures that the compiler only processes ext_eep.h once during compilation.

2 - Define EEPROM I2C Address

#define EEPROM_I2C_ADDRESS  0xA0  // 10100000 (Write Mode)
? Defines the I2C address for the external EEPROM.

EEPROM chips typically have a base I2C address (0xA0).
The last bit determines Read (1) or Write (0) mode.

? For Communication:

Writing to EEPROM ? Use 0xA0.
Reading from EEPROM ? Use 0xA1.
3 - Function Prototypes (Used in ext_eep.c)

void write_ext_eep(unsigned char address, unsigned char data);  // Write data to EEPROM
unsigned char read_ext_eep(unsigned char address);  // Read data from EEPROM
? Declares functions implemented in ext_eep.c:

write_ext_eep(address, data) ? Stores data at the given address in EEPROM.
read_ext_eep(address) ? Retrieves stored data from the specified address.
? Example Usage:

write_ext_eep(0x10, 0x55);  // Store value 0x55 at memory address 0x10
unsigned char value = read_ext_eep(0x10);  // Read stored value from address 0x10
? This allows persistent storage for logs, passwords, and configurations.

? Summary of ext_eep.h
    Section                                         Purpose
Header Guards           ->        	Prevents multiple inclusions of the file
EEPROM I2C Address      ->        	Defines external EEPROM address (0xA0)
Function Prototypes     ->         	Declares read/write functions for EEPROM
 */