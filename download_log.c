/*
 * File:   download_log.c
 * Author: sheryas
 *
 * Created on 9 February, 2025, 8:50 PM
 
 ? Step 24: Setting Up download_log.c (Download Log via UART)
This file (download_log.c) is responsible for:
? Transferring stored logs from EEPROM to a PC via UART.
? Sending log data in a structured format (Time, Event, Speed).
? Displaying "Downloading..." on the LCD during data transfer.
 */


#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "ext_eep.h"
#include "uart.h"

void download_log() 
{
    if (o == 0) 
    {
        CLEAR_DISP_SCREEN;
        clcd_print("Downloading...", LINE1(0));

        init_uart();
        puts("Logs:\n\r");
        puts("#  TIME  EVENT SPEED\n\r");

        o = 1;
        if (over_flow == 0) 
        {
            start = 0;
            end = val;
        } else {
            end = 10;
            start = val * 5;
        }

        for (i = 0; i < end; i++) 
        {
            putch(i + '0');
            putch(' ');

            putch((read_ext_eep(start) >> 4) + '0');
            putch((read_ext_eep(start) & 0x0F) + '0');
            putch(':');

            putch((read_ext_eep(start + 1) >> 4) + '0');
            putch((read_ext_eep(start + 1) & 0x0F) + '0');
            putch(':');

            putch((read_ext_eep(start + 2) >> 4) + '0');
            putch((read_ext_eep(start + 2) & 0x0F) + '0');
            putch(' ');

            puts(event[read_ext_eep(start + 3)]);
            putch(' ');

            putch((read_ext_eep(start + 4) >> 4) + '0');
            putch((read_ext_eep(start + 4) & 0x0F) + '0');
            puts("\n\r");

            start = (start + 5) % 50;
        }

        char temp = index;
        index = 8;
        save_log();
        index = temp;
    }

    clcd_print("Download Log", LINE1(0));
    clcd_print("Successfully", LINE2(0));

    if (--wait1 == 0) 
    {
        wait1 = 1000;
        o = 0;
        i = 0;
        main_f = MENU;
        CLEAR_DISP_SCREEN;
    }
}

/*1 - download_log() - Start Log Download Process

void download_log() {
    if (o == 0) {
        CLEAR_DISP_SCREEN;
        clcd_print("Downloading...", LINE1(0));
? Ensures the log download starts only once (o == 0).

CLEAR_DISP_SCREEN; ? Clears the LCD screen.
clcd_print("Downloading...", LINE1(0)); ? Displays a message on the LCD to inform the user.
2?? Initialize UART & Print Headers

 *         init_uart();
        puts("Logs:\n\r");
        puts("#  TIME  EVENT SPEED\n\r");
? Initializes UART communication and sends log headers to the PC.

init_uart(); ? Sets up the UART module for serial communication.
puts("Logs:\n\r"); ? Sends "Logs:\n\r" to the PC via UART.
puts("# TIME EVENT SPEED\n\r"); ? Sends column headers for the logs.
? PC Terminal Output Example:

makefile

Logs:
#  TIME  EVENT SPEED
3?? Determine Start & End Points for Log Retrieval

        o = 1;
        if (over_flow == 0) {
            start = 0;
            end = val;
        } else {
            end = 10;
            start = val * 5;
        }
? Calculates the range of stored logs to be sent.

over_flow == 0 ? Logs are within 50 entries, so we start from 0 and read until val (current log count).
over_flow == 1 ? More than 50 logs exist; reads the last 10 logs from the EEPROM.
4?? Loop Through Stored Logs & Send Data via UART

        for (i = 0; i < end; i++) {
            putch(i + '0');
            putch(' ');
? Loops through each stored log and sends it over UART.

Sends log index (i) followed by a space (' ').
? Sending Log Time (HH:MM:SS)

            putch((read_ext_eep(start) >> 4) + '0');
            putch((read_ext_eep(start) & 0x0F) + '0');
            putch(':');

            putch((read_ext_eep(start + 1) >> 4) + '0');
            putch((read_ext_eep(start + 1) & 0x0F) + '0');
            putch(':');

            putch((read_ext_eep(start + 2) >> 4) + '0');
            putch((read_ext_eep(start + 2) & 0x0F) + '0');
            putch(' ');
? Reads time from EEPROM and formats it as HH:MM:SS.

Converts binary-coded decimal (BCD) to ASCII.
Sends hours, minutes, and seconds over UART.
? Example:
? If stored values are:

Address	Data (BCD)	Decoded ASCII
0x00	0x12 (12)	12:
0x01	0x30 (30)	30:
0x02	0x45 (45)	45
? PC Terminal Output:
0  12:30:45  
? Sending Event Type

            puts(event[read_ext_eep(start + 3)]);
            putch(' ');
? Reads event type from EEPROM and sends it as text.

Uses event[] array (predefined event names: ON, GN, GR, G1, G2, G3, G4, C).
Sends the event description over UART.
? Example:
If event code is 2, then event[2] = "GR" (Gear Reverse).

? PC Terminal Output:

0  12:30:45  GR  
? Sending Speed

            putch((read_ext_eep(start + 4) >> 4) + '0');
            putch((read_ext_eep(start + 4) & 0x0F) + '0');
            puts("\n\r");
? Reads and sends speed value from EEPROM.

BCD-to-ASCII conversion for speed value.
Sends newline (\n\r) to move to the next log entry.
? Example:

Address	Data (BCD)	Decoded ASCII
0x04	0x40 (40)	40
? PC Terminal Output:

0  12:30:45  GR  40
5?? Move to Next Log Entry
c
Copy
Edit
            start = (start + 5) % 50;
        }
? Moves to the next log entry in EEPROM.

Each log entry occupies 5 bytes (HH MM SS EVENT SPEED).
Wraps around when it reaches 50 entries (circular logging).
6?? Save Log Index & Restore Original Index

        char temp = index;
        index = 8;
        save_log();
        index = temp;
? Temporarily updates index = 8 while saving the log status.

Saves current log index (save_log()).
Restores previous index (index = temp).
7?? Display "Download Successful" & Return to Menu

    clcd_print("Download Log", LINE1(0));
    clcd_print("Successfully", LINE2(0));

    if (--wait1 == 0) {
        wait1 = 1000;
        o = 0;
        i = 0;
        main_f = MENU;
        CLEAR_DISP_SCREEN;
    }
}
? Displays success message on the LCD and resets variables.

LCD Output:
mathematica

Download Log
Successfully
Waits before clearing the screen and returning to MENU.
 * 
 * 
? Summary of download_log.c
Function                      	Purpose
download_log()                Transfers logs from EEPROM to PC via UART
init_uart()             	  Initializes UART communication
puts("# TIME EVENT SPEED")	  Prints headers on the PC terminal
putch()                       Sends characters via UART
read_ext_eep(start + X)        Reads logs from EEPROM (time, event, speed)
 * 
 * 
? Final PC Terminal Output Example:

#  TIME  EVENT SPEED
0  12:30:45  GR  40
1  12:35:22  G2  55
2  12:40:11  G3  65*/