/*
 * ? Step 20: Setting Up dashboard.h (Dashboard Header File)
This file (dashboard.h) is needed to:
? Declare function prototypes for the dashboard.
? Enable structured display of vehicle parameters (Speed, Gear, Time).

*/
#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <xc.h>

// Function Prototypes
void display_dashboard(void);  // Display vehicle status (speed, gear, time)
void update_dashboard(void);   // Update dashboard values in real-time

#endif


/*
 ? Explanation of dashboard.h (Dashboard Header File)
This file (dashboard.h) defines the function prototypes for the dashboard display, 
 * allowing the system to show real-time vehicle information such as speed, gear position, and time.

? Why is dashboard.h needed?

It declares function prototypes used in dashboard.c.
It ensures modularity, separating dashboard-related functions.
It allows real-time display updates for vehicle parameters.
1 - prevent Multiple Inclusions

#ifndef DASHBOARD_H
#define DASHBOARD_H
? Prevents multiple inclusions of this file to avoid duplicate definitions.

Ensures the compiler only processes dashboard.h once during compilation.
2 - Function Prototypes

void display_dashboard(void);  // Display vehicle status (speed, gear, time)
void update_dashboard(void);   // Update dashboard values in real-time
? Declares functions that will be implemented in dashboard.c:

display_dashboard() ? Displays vehicle parameters like speed, gear, and time on the LCD.
update_dashboard() ? Updates the displayed values in real-time based on sensor readings.
? Example Usage:


display_dashboard();  // Call this function to show vehicle data on LCD
? This displays speed, time, and gear status on the LCD screen.

? Summary of dashboard.h
    Section                     Purpose
Header Guards           	Prevents multiple inclusions of the file
Function Prototypes     	Declares dashboard display functions*/