/*
 * File:   pass_menu.c
 * Author: sheryas
 *
 * Created on 9 February, 2025, 5:43 PM

 Step 7: Setting Up pass_menu.c (Password Handling & Menu System)
This file handles:
? Password Entry ? Required for menu access.
? Blocking Mechanism ? Blocks user for 120 seconds after failed attempts.
? Menu Navigation ? Allows the user to select View Logs, Set Time, Change Password, etc.
 */

/*
 1 - Global Variables & Setup
 * ? Defines global variables for password and menu handling:

o_pass         ? Stores the correct password (from EEPROM).
keycount       ? Tracks key presses for menu navigation.
wait1          ? Used as a delay counter for menu selection.
start, end     ? Used for log viewing and menu scrolling.
i, o           ? General counters for menu navigation.
 */
#include <xc.h>
#include "main.h"

char o_pass;
static int keycount = 0;
//static int wait1 = 1000;
//static signed char start, end;
// static char i, o;

/*
 2 - Password() - Handles User Authentication
 ? Resets variables when entering the password screen:

pass = 0  ? Clears any previously entered password.
tm = 5    ? Sets a 5-second timeout to enter the password.
attempt = 50 ? User has 50 chances to enter the correct password.
Clears the LCD screen using CLEAR_DISP_SCREEN.
*/
void password(void) 
{
    count = 0;
    pass = 0;
    tm = 5;
    char i = 0;
    unsigned char attempt = 50;
    CLEAR_DISP_SCREEN;
    unsigned char wait = 0;

    
/*
 ? Read Keypad Input for Password
 ? Detects Key Presses (MK_SW11 or MK_SW12) and Updates Password:

MK_SW11           ? Adds a '0' to the password.
MK_SW12           ? Adds a '1' to the password.
pass = pass << 1  ? Shifts password left (prepares for the next bit).
Prints * (hidden character) on LCD for each digit entered.
 */
    while (tm) 
    {
        key = read_switches(STATE_CHANGE);
        if (key >= MK_SW1 && key <= MK_SW3)
            gear_change(key);

        if (attempt >= '0' && wait == 0) 
        {
            clcd_print("  ENTER PASSWORD", LINE1(0));
            if (key == MK_SW11) 
            {
                pass = pass << 1;
                clcd_print("*", LINE2(i + 6));
                count = 0;
                tm = 5;
                i++;
            } else if (key == MK_SW12) 
            {
                pass = (pass << 1) | 1;
                clcd_print("*", LINE2(i + 6));
                count = 0;
                tm = 5;
                i++;
            }
        }

/*
 ? Password Validation
? Checks the entered password against stored EEPROM data:

If correct (pass == o_pass) ? Enter the Menu System.
If incorrect ?
Displays "Wrong Password".
Decreases remaining attempts.
Resets the password entry after 200 loops.
 */   
        if (i == 4) 
        {
            if (pass == (o_pass = read_ext_eep(200))) 
            {
                main_f = MENU; // Correct password ? Enter Menu
                CLEAR_DISP_SCREEN;
                return;
            } 
            else 
            {
                clcd_print(" Wrong password", LINE1(0));
                clcd_putch(attempt, LINE2(0));
                clcd_print(" ATTEMPTS LEFT", LINE2(1));

                if (wait++ == 200) 
                {
                    attempt--; // Reduce attempt
                    pass = 0;  // Reset password
                    i = 0;     // Reset input index
                    wait = 0;
                    CLEAR_DISP_SCREEN;
                }
            }
             
/*
 ? Security Lockout (Blocking for 120 Seconds)
 ? Locks user out for 120 seconds after too many wrong attempts:

Displays "You are blocked".
Shows a countdown timer.
Resets login after timeout expires.

 */
            if (attempt < '0') 
            {
                tm = 120;  // Block user for 120 seconds
                count = 0;
            }
        }
        if (attempt < '0') 
        {
            char blocks[4];
            blocks[0] = '0' + (tm / 100) % 10;
            blocks[1] = '0' + (tm / 10) % 10;
            blocks[2] = '0' + tm % 10;

            clcd_print("You are blocked", LINE1(0));
            clcd_print("Wait for", LINE2(0));
            clcd_print(blocks, LINE2(9));
            clcd_print(" sec", LINE2(12));
            
/*
 ? Checking If the Blocking Time (tm) is Over
 ? When tm reaches 0 (blocking time is over):

1) count = 0 ? Resets the countdown timer.
2) tm = 5 ? Allows 5 seconds for password entry again.
3) attempt = '2' ? Resets the attempt counter to '2' (ASCII value for 2).
4) CLEAR_DISP_SCREEN ? Clears the LCD screen before returning to the dashboard.

 */
            
            if (tm == 0) 
            {
                count = 0;
                tm = 5;
                attempt = '2';
                CLEAR_DISP_SCREEN;
            }
        }
    }
    
/*
 ? Returning to Dashboard Mode
? After handling the blocking mechanism:

Clears the LCD screen to remove any old messages.
Sets main_f = DASHBOARD ? The system returns to the Dashboard after unlocking.
*/
    CLEAR_DISP_SCREEN;
    main_f = DASHBOARD;
}


/*
 3 menu() - Handles Menu Navigation
 ? Detects keypresses and navigates menu options:

1) MK_SW11 (UP) ? Scrolls Up.
2) MK_SW12 (DOWN) ? Scrolls Down.
3) If a key is held for too long (keycount > 1000) ? It resets selection.
*/
void menu(char key) 
{
    static unsigned char i, sf;
    char *menu[5] = {"VIEW LOG", "DOWNLOAD LOG", "CLEAR LOG", "SET TIME", "CHANGE PASS"};

    if (key != ALL_RELEASED) 
    {
        if (keycount++ > 1000) 
        {
            keycount = 0;
            if (key == MK_SW11) 
            {
                CLEAR_DISP_SCREEN;
                main_f = MENU_ENTER;
                menu_f = sf ? i + 1 : i;
                i = 0;
                sf = 0;
                return;
            } else if (key == MK_SW12) 
            {
                main_f = DASHBOARD;
                i = 0;
                sf = 0;
                CLEAR_DISP_SCREEN;
                return;
            }
        }
    } else if (keycount > 0 && keycount < 1000) 
    {
        keycount = 0;
        if (p_key == MK_SW11) 
        {
            if (!sf && i-- == 0)
                i = 0;
            else
                sf = 0;
        } else if (p_key == MK_SW12) 
        {
            if (sf && i++ == 3)
                i = 3;
            else
                sf = 1;
        }
    }
    
    /*
? Displaying Menu Options on LCD
? Displays Menu Items & Highlights Selection:

Shows menu items on LCD (VIEW LOG, SET TIME, etc.).
Moves cursor (->) to the selected item.
     */

    if (!sf)
        clcd_print("->", LINE1(0));
    else
        clcd_print("->", LINE2(0));
    clcd_print(menu[i], LINE1(2));
    clcd_print(menu[i + 1], LINE2(2));
    p_key = key;
}

/*
 ? Summary of pass_menu.c
     Function                                Purpose
password()	              Handles password input & authentication
Password Check            Reads stored password from EEPROM
Blocking System           Locks user for 120 seconds after multiple failures
menu()                    Handles menu navigation & option selection
 */