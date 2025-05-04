/*
? Step 12: Setting Up ds1307.h (RTC - Real-Time Clock Header File)
The RTC Header File (ds1307.h) is needed to:
? Define macros for DS1307 RTC communication.
? Declare function prototypes for ds1307.c.
? Enable timekeeping and time retrieval in the system.

*/

#ifndef DS1307_H
#define DS1307_H

#include <xc.h>

#define SLAVE_WRITE  0xD0  // DS1307 Write Address
#define SLAVE_READ   0xD1  // DS1307 Read Address

#define SEC_ADDR     0x00  // Register address for Seconds
#define MIN_ADDR     0x01  // Register address for Minutes
#define HOUR_ADDR    0x02  // Register address for Hours

// Renamed time variable to avoid conflicts with C99 standard library
extern char rtc_time[9];  

unsigned char read_ds1307(unsigned char address);
void write_ds1307(unsigned char address, unsigned char data);
void get_time(void);

#endif

 
/*#ifndef DS1307_H
#define DS1307_H

#include <xc.h>

extern unsigned char clock_reg[3];  // Declare global RTC registers
extern char time[9];  // Declare global time array


// DS1307 I2C Address
#define DS1307_I2C_ADDRESS  0xD0  // 11010000 (Write Mode)

// DS1307 Register Addresses
#define SEC_ADDR   0x00  // Seconds Register
#define MIN_ADDR   0x01  // Minutes Register
#define HOUR_ADDR  0x02  // Hours Register
#define DAY_ADDR   0x03  // Day Register
#define DATE_ADDR  0x04  // Date Register
#define MONTH_ADDR 0x05  // Month Register
#define YEAR_ADDR  0x06  // Year Register

// Function Prototypes
void init_ds1307(void);                        // Initialize DS1307 RTC
void write_ds1307(unsigned char, unsigned char); // Write Data to DS1307
unsigned char read_ds1307(unsigned char);      // Read Data from DS1307
void get_time(void);                           // Retrieve Current Time

#endif

/*
 
 * ? Explanation of ds1307.h (RTC - Real-Time Clock Header File)
This file (ds1307.h) provides function declarations and macros for communicating with the,
 *  DS1307 Real-Time Clock (RTC) module.

? Why is ds1307.h needed?

It defines the DS1307 I2C address and register locations.
It declares function prototypes so other files can access RTC functions.
It ensures modularity, separating time-related functions from other code.
 
1 - Prevent Multiple Inclusions
 
#ifndef DS1307_H
#define DS1307_H
? Prevents multiple inclusions of this file to avoid duplicate definitions.

Ensures the compiler only includes ds1307.h once during compilation.
 
2 - Define DS1307 I2C Address

#define DS1307_I2C_ADDRESS  0xD0  // 11010000 (Write Mode)
? Defines the I2C address of the DS1307 RTC:

0xD0 ? This is the 7-bit address shifted left (1101000X).
The last bit (X) determines Read (1) or Write (0) mode.
? For Communication:

Writing to DS1307 ? Use 0xD0.
Reading from DS1307 ? Use 0xD1.
 
3 - Define DS1307 Register Addresses

#define SEC_ADDR   0x00  // Seconds Register
#define MIN_ADDR   0x01  // Minutes Register
#define HOUR_ADDR  0x02  // Hours Register
#define DAY_ADDR   0x03  // Day Register
#define DATE_ADDR  0x04  // Date Register
#define MONTH_ADDR 0x05  // Month Register
#define YEAR_ADDR  0x06  // Year Register
? Defines memory locations for storing time in DS1307.

Seconds (0x00) ? Stores seconds value (0-59).
Minutes (0x01) ? Stores minutes value (0-59).
Hours (0x02) ? Stores hours value (0-23 for 24-hour format).
Day (0x03) ? Stores day of the week (1-7).
Date (0x04) ? Stores date (1-31).
Month (0x05) ? Stores month (1-12).
Year (0x06) ? Stores year (00-99) (only last two digits).
 
4 - Function Prototypes (Used in ds1307.c)

void init_ds1307(void);                        // Initialize DS1307 RTC
void write_ds1307(unsigned char, unsigned char); // Write Data to DS1307
unsigned char read_ds1307(unsigned char);      // Read Data from DS1307
void get_time(void);                           // Retrieve Current Time
? Declares functions that are implemented in ds1307.c:

init_ds1307() ? Initializes the DS1307 RTC (sets time if not configured).
write_ds1307(address, data) ? Writes data to the specified address in the RTC.
read_ds1307(address) ? Reads the stored time data from a given address.
get_time() ? Retrieves the current time (HH:MM:SS) from RTC and updates the display.
 
? Summary of ds1307.h
Section	Purpose
Header Guards	Prevents multiple inclusions of the file
I2C Address Definition	Sets DS1307 I2C address (0xD0) for communication
Register Definitions	Defines memory locations for storing time (HH:MM:SS, Date, Month, Year)
Function Prototypes	Declares time-related functions for ds1307.c*/