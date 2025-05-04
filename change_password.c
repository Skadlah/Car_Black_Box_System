/*
 * File:   change_password.c
 * Author: sheryas
 *
 * Created on 9 February, 2025, 8:38 PM
 * 
 ? Step 22: Setting Up change_password.c (Change Password Functionality)
This file (change_password.c) is responsible for:
? Allowing the user to change the system password.
? Storing the new password in EEPROM for future logins.
? Ensuring password confirmation to prevent errors.
 */

#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "ext_eep.h"
#include "matrix_keypad.h"

void change_pass(char key) 
{
    static char i = 0, npass = 0, rnpass = 0;
    
    if (i < 4) 
    {  // Enter new password
        clcd_print("ENTER NEW PASS", LINE1(0));
        if (key == MK_SW11) 
        {
            npass = npass << 1;
            clcd_putch('*', LINE2(i));
            i++;
        } 
        else if (key == MK_SW12) {
            npass = (npass << 1) | 1;
            clcd_putch('*', LINE2(i));
            i++;
        }
    } 
    else if (i < 8) 
    {  // Re-enter new password
        if (i == 4) CLEAR_DISP_SCREEN;
        clcd_print("RE-ENTER PASS", LINE1(0));
        if (key == MK_SW11) 
        {
            rnpass = rnpass << 1;
            clcd_putch('*', LINE2(i - 4));
            i++;
        } else if (key == MK_SW12) 
        {
            rnpass = (rnpass << 1) | 1;
            clcd_putch('*', LINE2(i - 4));
            i++;
        }
    } 
    else 
    {  // Verify and save
        if (npass == rnpass) 
        {
            write_ext_eep(200, npass);  // Store password in EEPROM
            clcd_print("CHANGE PASS", LINE1(0));
            clcd_print("SUCCESSFUL", LINE2(0));
        }
        else 
        {
            clcd_print("CHANGE PASS", LINE1(0));
            clcd_print("FAILED", LINE2(0));
        }
        __delay_ms(1000);
        i = 0;
        npass = 0;
        rnpass = 0;
        CLEAR_DISP_SCREEN;
        main_f = MENU;
    }
}

/*
 1 change_pass(char key) - Change Password Process

void change_pass(char key) {
    static char i = 0, npass = 0, rnpass = 0;
? Defines three static variables:

i ? Keeps track of password entry progress.
npass ? Stores the new password entered by the user.
rnpass ? Stores the re-entered password for verification.
2?? Enter New Password (First 4 Digits)

if (i < 4) {  // Enter new password
    clcd_print("ENTER NEW PASS", LINE1(0));
? Checks if the user is entering the first 4-digit password.

Displays "ENTER NEW PASS" on the LCD.

    if (key == MK_SW11) {
        npass = npass << 1;
        clcd_putch('*', LINE2(i));
        i++;
    } else if (key == MK_SW12) {
        npass = (npass << 1) | 1;
        clcd_putch('*', LINE2(i));
        i++;
    }
? Processes key input:

MK_SW11 (0 entered) ? Left shifts npass and appends 0.
MK_SW12 (1 entered) ? Left shifts npass and appends 1.
Displays * on the LCD to hide the entered digits.
Increments i to track entry progress.
? Example:
? If the user enters MK_SW11, MK_SW12, MK_SW11, MK_SW12, the stored npass will be:

} else if (i < 8) 
 * {  // Re-enter new password
    if (i == 4) CLEAR_DISP_SCREEN;
    clcd_print("RE-ENTER PASS", LINE1(0));
? Ensures user re-enters the same password for confirmation.

If i == 4, the screen is cleared to show "RE-ENTER PASS".

    if (key == MK_SW11) 
 * {
        rnpass = rnpass << 1;
        clcd_putch('*', LINE2(i - 4));
        i++;
    } else if (key == MK_SW12) 
 * {
        rnpass = (rnpass << 1) | 1;
        clcd_putch('*', LINE2(i - 4));
        i++;
    }
? Stores the re-entered password (rnpass) using the same logic as npass.

Displays * on the LCD for each digit entered.
? Example:
? If the user enters the same password again (0101), rnpass will store:
Binary:  0101
Decimal: 5
4?? Verify and Store Password

} else {  // Verify and save
    if (npass == rnpass) {
        write_ext_eep(200, npass);  // Store password in EEPROM
        clcd_print("CHANGE PASS", LINE1(0));
        clcd_print("SUCCESSFUL", LINE2(0));
    } else {
        clcd_print("CHANGE PASS", LINE1(0));
        clcd_print("FAILED", LINE2(0));
    }
? Checks if both passwords match (npass == rnpass).

If matched, stores npass in EEPROM at address 200 using write_ext_eep().
If mismatched, displays "CHANGE PASS FAILED".
? Example:

npass (New Password)	rnpass (Re-entered Password)    	Result
0101 (Decimal 5)	     0101 (Decimal 5)	               ? SUCCESSFUL
0101 (Decimal 5)	     1101 (Decimal 13)                  ? FAILED
5?? Reset and Return to Menu

    __delay_ms(1000);
    i = 0;
    npass = 0;
    rnpass = 0;
    CLEAR_DISP_SCREEN;
    main_f = MENU;
}
? After password verification:

Waits for 1 second (__delay_ms(1000)).
Resets all variables (i, npass, rnpass) for future password changes.
Clears the screen (CLEAR_DISP_SCREEN).
Returns to the menu (main_f = MENU).
? Summary of change_password.c
    Function                        Purpose
change_pass(key)        	Handles password change process
write_ext_eep(200, npass)	Saves new password in EEPROM
clcd_putch('*', LINE2(i))	Displays * instead of actual digits for security
CLEAR_DISP_SCREEN           Clears the LCD before new messages
 */