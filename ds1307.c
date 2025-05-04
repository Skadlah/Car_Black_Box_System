/*
 * File:   ds1307.c
 * Author: sheryas
 *
 * Created on 9 February, 2025, 7:48 PM
 
? Step 13: Setting Up ds1307.c (RTC - Real-Time Clock Implementation)
This file implements functions to communicate with the DS1307 RTC using I2C protocol.

? Reads the current time (HH:MM:SS) from DS1307 RTC.
? Writes time data to DS1307 RTC (if needed).
? Uses I2C communication for data tran 
 */
#include <xc.h>
#include "ds1307.h"
#include "i2c.h"

char rtc_time[9] = "12:00:00";  // Renamed from time[] to rtc_time[]
unsigned char clock_reg[3];  // Stores raw values read from DS1307

unsigned char read_ds1307(unsigned char address) {
    i2c_start();
    i2c_write(SLAVE_WRITE);
    i2c_write(address);
    i2c_rep_start();
    i2c_write(SLAVE_READ);
    unsigned char data = i2c_read();
    i2c_stop();
    return data;
}

void write_ds1307(unsigned char address, unsigned char data) {
    i2c_start();
    i2c_write(SLAVE_WRITE);
    i2c_write(address);
    i2c_write(data);
    i2c_stop();
}

void get_time(void) {
    clock_reg[0] = read_ds1307(SEC_ADDR);  // Read Seconds
    clock_reg[1] = read_ds1307(MIN_ADDR);  // Read Minutes
    clock_reg[2] = read_ds1307(HOUR_ADDR); // Read Hours

    // Convert raw BCD values to ASCII for display
    rtc_time[0] = (clock_reg[2] >> 4) + '0';
    rtc_time[1] = (clock_reg[2] & 0x0F) + '0';
    rtc_time[2] = ':';
    rtc_time[3] = (clock_reg[1] >> 4) + '0';
    rtc_time[4] = (clock_reg[1] & 0x0F) + '0';
    rtc_time[5] = ':';
    rtc_time[6] = (clock_reg[0] >> 4) + '0';
    rtc_time[7] = (clock_reg[0] & 0x0F) + '0';
    rtc_time[8] = '\0';  // Null-terminate the string
}


/*
 ? Explanation of ds1307.c (RTC - Real-Time Clock Implementation)
This file implements functions to communicate with the DS1307 Real-Time Clock (RTC) using I2C communication.

? Why is ds1307.c needed?

It allows the system to read the current time (HH:MM:SS) from the DS1307.
It provides a way to write time values to the RTC if needed.
It ensures time synchronization for event logging and display updates.
 
1 - init_ds1307() - Initialize DS1307 RTC

void init_ds1307(void) 
{
    write_ds1307(SEC_ADDR, 0x00);  // Reset seconds to 00
}
? This function initializes the RTC.

Calls write_ds1307() to set the seconds register (0x00) to 00.
Ensures time starts correctly when the system powers on.

2 - write_ds1307() - Write Data to DS1307 RTC

void write_ds1307(unsigned char address, unsigned char data) 
{
    i2c_start();                     // Start I2C communication
    i2c_write(DS1307_I2C_ADDRESS);    // Send DS1307 address with Write mode
    i2c_write(address);               // Send memory register address
    i2c_write(data);                  // Send data
    i2c_stop();                        // Stop I2C communication
}
? Writes data to a specific register in the DS1307 RTC using I2C protocol.

Starts I2C communication using i2c_start().
Sends DS1307 address (0xD0) in write mode.
Sends register address (e.g., SEC_ADDR = 0x00 for seconds).
Sends data to write (e.g., 0x00 to reset seconds).
Stops communication using i2c_stop().
? Example Usage:

write_ds1307(HOUR_ADDR, 0x12);  // Set RTC Hours to 12
? This sets the time to 12:00:00 in the DS1307.

3 - read_ds1307() - Read Data from DS1307 RTC

unsigned char read_ds1307(unsigned char address) 
{
    unsigned char data;

    i2c_start();                      // Start I2C communication
    i2c_write(DS1307_I2C_ADDRESS);    // Send DS1307 address with Write mode
    i2c_write(address);               // Send memory register address
    i2c_rep_start();                   // Restart I2C for reading
    i2c_write(DS1307_I2C_ADDRESS | 1); // Send DS1307 address with Read mode
    data = i2c_read();                 // Read data from RTC
    i2c_stop();                        // Stop I2C communication

    return data;
}
? Reads data from a specific register in the DS1307 RTC.

Starts I2C communication using i2c_start().
Sends DS1307 address (0xD0) in write mode.
Sends register address (e.g., MIN_ADDR = 0x01 for minutes).
Restarts I2C communication for reading (i2c_rep_start()).
Sends DS1307 address (0xD1) in read mode.
Reads data from the specified register (i2c_read()).
Stops communication using i2c_stop().
Returns the received data.
? Example Usage:

unsigned char current_minutes = read_ds1307(MIN_ADDR);
? Reads the current minutes value from the RTC.

4 - get_time() - Read and Convert Time

void get_time(void) 
{
    clock_reg[0] = read_ds1307(SEC_ADDR);  // Read Seconds
    clock_reg[1] = read_ds1307(MIN_ADDR);  // Read Minutes
    clock_reg[2] = read_ds1307(HOUR_ADDR); // Read Hours

    time[0] = (clock_reg[2] >> 4) + '0';
    time[1] = (clock_reg[2] & 0x0F) + '0';
    time[3] = (clock_reg[1] >> 4) + '0';
    time[4] = (clock_reg[1] & 0x0F) + '0';
    time[6] = (clock_reg[0] >> 4) + '0';
    time[7] = (clock_reg[0] & 0x0F) + '0';
}
? Reads the current time and converts it to ASCII for display.

Calls read_ds1307() to get HH, MM, SS values.
Extracts the individual digits using bitwise operations:
>> 4 ? Extracts the tens place.
& 0x0F ? Extracts the ones place.
Stores the time as a string (time[]) for display.
? Example Usage:

get_time();
clcd_print(time, LINE1(0));  // Display time on LCD
? Displays the current HH:MM:SS on the LCD.

? Summary of ds1307.c
Function	Purpose
init_ds1307()	Initializes the DS1307 RTC
write_ds1307(address, data)	Writes data to a register in DS1307
read_ds1307(address)	Reads data from a register in DS1307
get_time()	Reads current time and formats it for display*/


