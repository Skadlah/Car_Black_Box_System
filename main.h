#ifndef MAIN_H
#define MAIN_H

#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"
#include "adc.h"
#include "ds1307.h"
#include "ext_eep.h"
#include "i2c.h"
#include "uart.h"

 //2. Diffrant maccross
#define _XTAL_FREQ 20000000  // Define for 20MHz Crystal
#define DASHBOARD   0 // DASHBOARD (0) ? Shows speed, time, and gear position on LCD.
#define PASSWORD    1 // PASSWORD (1) ? User must enter a 4-digit binary password
#define MENU        2 //MENU (2) ? If the password is correct, the user enters the menu system.
#define MENU_ENTER  3 //MENU_ENTER (3) ? User selects a menu option.
#define VIEWLOG     0 //VIEWLOG (0) ? View event logs stored in EEPROM.
#define DOWNLOADLOG 1 //DOWNLOADLOG (1) ? Send logs to a PC via UART.
#define CLEARLOG    2 //CLEARLOG (2) ? Clear all stored logs in EEPROM.
#define SETTIME     3 //SETTIME (3) ? Set RTC Time using the keypad.
#define CHANGEPASS  4 //CHANGEPASS (4) ? Change the user password stored in EEPROM.



/* 3. This are Global variables
Current system state (main_f) ? Determines whether the system is in Dashboard, Password Entry, or Menu mode.
User Input (key, p_key) ? Stores the last pressed key.
RTC Time (time[], clock_reg[]) ? Stores current time and RTC registers.
Speed (speed, speeds[]) ? Stores car speed read from ADC.
EEPROM Logging (index, val, over_flow) ? Tracks stored logs and overflow conditions.
Security (pass, tm) ? Stores entered password and block time countdown.*/

unsigned char main_f = 0;  // Stores the current system state (Dashboard, Password, Menu)
unsigned char menu_f;       // Stores the selected menu option
char *event[] = {"ON", "GN", "GR", "G1", "G2", "G3", "G4", "C "};  // Event names
//char time[9] = "12:00:00";  // Stores the current time in HH:MM:SS format
unsigned char clock_reg[3]; // Stores RTC register values
char index;                 // Used for EEPROM log storage
char speeds[3];             // Stores speed values
unsigned char key;          // Stores the last pressed key
unsigned char p_key;        // Stores the previous keypress
unsigned char speed;        // Stores the current speed
unsigned char pass;         // Stores the entered password
unsigned char tm;           // Countdown timer variable
unsigned short count;       // Timer counter for ISR
unsigned char val;          // Stores log count
unsigned char over_flow;    // Used to track EEPROM overflow
extern unsigned short wait1;  // Declare wait1 globally
extern unsigned char i;      // Loop counter
extern unsigned char o;      // Flag for tracking download start
extern unsigned char start;  // Log start index
extern unsigned char end;    // Log end index
extern unsigned char clock_reg[3];  // Holds RTC time values
extern char time[9];  // Holds formatted time as a string

//extern unsigned short wait1; // Wait delay counter


//4. Function Prototypes
/*? These function prototypes ensure:
The compiler knows about functions before they are used.
Each module (dashboard.c, pass_menu.c, etc.) can call functions from other files.
Functions are defined separately in their respective files.*/

void display_dashboard(void);   // Show dashboard on LCD
void gear_change(unsigned char key); // Change gear when keypad key is pressed
void save_log(void);            // Save event logs to EEPROM
void password(void);            // Handle password entry
void init_timer1(void);         // Initialize Timer1 for countdowns
void menu(char key);            // Handle menu navigation
void view_log(char key);        // View logs stored in EEPROM
void download_log();            // Send logs via UART to PC
void clear_log(char key);       // Clear stored logs
void settime(char key);         // Set RTC time
void change_pass(char key);     // Change system password
void get_time(void);            // Read current time from RTC

#endif
/*? Summary of main.h

Header Includes   -> Includes all necessary files (LCD, RTC, EEPROM, UART, etc.)
State Definitions -> Defines system states (Dashboard, Password, Menu)
Menu Options	  -> Defines log management, time setting, and password change options
Global Variables  -> Stores key system data (time, speed, password, logs)
Function Prototypes	-> Declares all functions needed across different modules*/
