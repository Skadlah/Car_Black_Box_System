/*
 * File:   dashboard.c
 * Author: sheryas
 *
 * Created on 9 February, 2025, 8:32 PM
 
? Step 21: Setting Up dashboard.c (Dashboard Implementation)
This file (dashboard.c) is responsible for:
? Displaying real-time vehicle parameters (Speed, Gear, Time) on the LCD.
? Updating the dashboard with the latest values from sensors.
? Ensuring the data remains visible and easy to read while driving.
*/

#include "dashboard.h"
#include "clcd.h"
#include "main.h"

void display_dashboard(void) 
{
    CLEAR_DISP_SCREEN;  // Clear LCD screen
    clcd_print("TIME  SPD  GEAR", LINE1(0));  // Display header
    update_dashboard();  // Show initial values
}

void update_dashboard(void) 
{
    // Display Time
    get_time();  // Fetch time from RTC
    clcd_putch(time[0], LINE2(0));
    clcd_putch(time[1], LINE2(1));
    clcd_putch(':', LINE2(2));
    clcd_putch(time[3], LINE2(3));
    clcd_putch(time[4], LINE2(4));
    clcd_putch(':', LINE2(5));
    clcd_putch(time[6], LINE2(6));
    clcd_putch(time[7], LINE2(7));

    // Display Speed
    clcd_putch(speed / 10 + '0', LINE2(9));
    clcd_putch(speed % 10 + '0', LINE2(10));

    // Display Gear
    clcd_print(event[index], LINE2(14));
}

/*
 ? Explanation of dashboard.c (Dashboard Implementation)
This file (dashboard.c) controls how the vehicle?s real-time data 
 * (Time, Speed, Gear) is displayed on the LCD screen.

? Why is dashboard.c needed?

It displays essential driving information on the LCD.
It fetches real-time data from the RTC and sensors.
It ensures continuous updates of speed, time, and gear status.
1-  display_dashboard() - Initialize Dashboard Display

void display_dashboard(void) 
{
    CLEAR_DISP_SCREEN;  // Clear LCD screen
    clcd_print("TIME  SPD  GEAR", LINE1(0));  // Display header
    update_dashboard();  // Show initial values
}
? This function initializes the dashboard screen.

CLEAR_DISP_SCREEN; ? Clears the LCD to remove old data.
clcd_print("TIME SPD GEAR", LINE1(0)); ? Displays column labels for:
Time (HH:MM:SS)
Speed (SPD - Vehicle Speed)
Gear (Current Gear Position)
update_dashboard(); ? Calls update_dashboard() to display initial values.
? Example Display on LCD:
TIME  SPD  GEAR
12:30:45 40   G2


2 -  update_dashboard() - Update Real-Time Data

void update_dashboard(void) 
{
    // Display Time
    get_time();  // Fetch time from RTC
    clcd_putch(time[0], LINE2(0));
    clcd_putch(time[1], LINE2(1));
    clcd_putch(':', LINE2(2));
    clcd_putch(time[3], LINE2(3));
    clcd_putch(time[4], LINE2(4));
    clcd_putch(':', LINE2(5));
    clcd_putch(time[6], LINE2(6));
    clcd_putch(time[7], LINE2(7));
? This section updates the clock on the LCD.

Calls get_time(); ? Reads the current time from the RTC (DS1307).
Displays the time (HH:MM:SS) character by character using clcd_putch().
? Displaying Speed

    // Display Speed
    clcd_putch(speed / 10 + '0', LINE2(9));
    clcd_putch(speed % 10 + '0', LINE2(10));
? This section updates the speed display.

Speed is a two-digit number (00-99).
speed / 10 + '0' ? Extracts the tens place (e.g., 45 ? ?4?).
speed % 10 + '0' ? Extracts the ones place (e.g., 45 ? ?5?).
Speed appears at position (LINE2, column 9 & 10) on the LCD.
? Example Output:


TIME  SPD  GEAR
12:30:45 40   G2
? If speed = 40, it prints ?4? and ?0?.

? Displaying Gear Status

    // Display Gear
    clcd_print(event[index], LINE2(14));
}
? This section updates the gear position.

Gear data is stored in an array called event[].
index holds the current gear number, and the function displays the gear name from event[].
The gear is displayed at position (LINE2, column 14) on the LCD.
? Example Gear Values:

Index	Displayed Gear
0	ON (Ignition)
1	GN (Neutral)
2	GR (Reverse)
3	G1 (Gear 1)
4	G2 (Gear 2)
5	G3 (Gear 3)
6	G4 (Gear 4)
7	C (Clutch Pressed)
? Summary of dashboard.c
    Function                           Purpose
display_dashboard()     	Sets up the dashboard layout (Time, Speed, Gear)
update_dashboard()          Updates the values on the LCD in real-time
get_time()                  Reads current time from the RTC (DS1307)
clcd_putch()            	Displays single characters on LC*/

