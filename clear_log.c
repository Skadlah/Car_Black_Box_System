/*
 * File:   clear_log.c
 * Author: sheryas
 *
 * Created on 9 February, 2025, 8:46 PM
 ? Step 23: Setting Up clear_log.c (Clear Log Functionality)
 his file (clear_log.c) is responsible for:
? Erasing all stored logs from EEPROM.
? Resetting event history to free up memory.
? Ensuring that logs are fully cleared before returning to the menu.
 */

#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "ext_eep.h"

void clear_log(char key) 
{
    clcd_print("CLEAR LOG", LINE1(0));

    if (wait1 == 1000) 
    {  // Prevents accidental multiple clears
        char temp = index;
        index = 9;
        over_flow = 0;
        val = 0;

        // Erase stored logs in EEPROM
        for (unsigned char i = 0; i < 50; i++) 
        {
            write_ext_eep(i, 0xFF);  // Set all log locations to 0xFF (erased)
        }

        save_log();
        index = temp;
    }

    clcd_print("LOG CLEARED", LINE2(0));

    // Wait before returning to menu
    if (--wait1 == 0) {
        wait1 = 1000;
        main_f = MENU;
        CLEAR_DISP_SCREEN;
    }
}

/*
 ? Explanation of clear_log.c (Clear Log Functionality)
This file (clear_log.c) clears all stored logs in the EEPROM memory to free up space for new event recordings.

? Why is clear_log.c needed?

It erases stored logs to free up EEPROM memory.
It ensures logs are completely removed before returning to the menu.
It prevents accidental multiple log deletions using a wait mechanism.
1?? clear_log(char key) - Start Log Clearing Process

void clear_log(char key) {
    clcd_print("CLEAR LOG", LINE1(0));
? Displays "CLEAR LOG" on the LCD screen to indicate the process is starting.

User is informed that the logs are being deleted.
2?? Prevent Accidental Log Clearing

if (wait1 == 1000) {  // Prevents accidental multiple clears
? Ensures the log is cleared only once when wait1 == 1000.

Prevents accidental multiple deletions if the function is triggered twice quickly.
3?? Backup Current Index & Reset Log Variables

char temp = index;
index = 9;
over_flow = 0;
val = 0;
? Temporarily stores index before clearing logs.

index = 9; ? Assigns a fixed index to identify log clearing.
over_flow = 0; ? Resets overflow tracking, preventing old logs from being read.
val = 0; ? Resets the log counter.
4?? Erase Stored Logs from EEPROM

for (unsigned char i = 0; i < 50; i++) {
    write_ext_eep(i, 0xFF);  // Set all log locations to 0xFF (erased)
}
? Deletes all stored logs in EEPROM.

Loops through the first 50 memory addresses (EEPROM log storage).
Writes 0xFF to each address to mark them as erased.
? EEPROM Before Clearing:

Address	Stored Log
0x00	0x45 (Event Data)
0x01	0x32 (Time Data)
0x02	0xA1 (Speed Data)
? EEPROM After Clearing:

Address	Stored Log
0x00	0xFF (Erased)
0x01	0xFF (Erased)
0x02	0xFF (Erased)
5?? Save Changes & Restore Index

save_log();
index = temp;
? Saves the cleared log status into EEPROM to ensure it remains deleted after a power cycle.

Restores index to its original value after clearing.
6?? Display "LOG CLEARED" Message

clcd_print("LOG CLEARED", LINE2(0));
? Displays confirmation on the LCD that the logs have been erased.

Ensures the user knows the operation was successful.
? LCD Output:

objectivec
Copy
Edit
CLEAR LOG
LOG CLEARED
7?? Delay Before Returning to Menu

if (--wait1 == 0) {
    wait1 = 1000;
    main_f = MENU;
    CLEAR_DISP_SCREEN;
}
? Prevents immediate return to the menu to allow the user to see the confirmation.

Waits before switching back to MENU.
Clears the screen to remove the message before returning.
? Summary of clear_log.c
    Function                                      Purpose
clear_log(key)                              Erases all logs stored in EEPROM
write_ext_eep(i, 0xFF)                      Writes 0xFF to each EEPROM address to mark it as erased
clcd_print("LOG CLEARED", LINE2(0))     	Displays success message after clearing logs
save_log()                                  Saves the cleared log state in EEPROM
*/
