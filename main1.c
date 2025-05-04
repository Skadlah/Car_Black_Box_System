/*
 * File:   main1.c
 * Author: sheryas
 *
 * Created on 9 February, 2025, 10:44 AM
 */

#include <xc.h>
#include "main.h"


// ? Global Variable Definitions (Place them at the top of `main.c`)
//unsigned char clock_reg[3];  // Stores RTC (DS1307) time values
//char time[9] = "12:00:00";   // Stores formatted time (HH:MM:SS)
extern unsigned char clock_reg[3];  // Declare global RTC registers
extern char time[9];  // Declare global time array

void init_config(void)
{
    GIE = 1; //Enable Global Interrupt
    PEIE = 1; // Enable Peripheral Interrupt
    
    init_clcd(); //Initialized LCD Display
    init_matrix_keypad(); //Initialized 4x4 Keypad
    init_adc();            // Initialize ADC for speed sensor
    init_timer1();         // Initialize Timer1 for countdown
    init_i2c();            // Initialize I2C for EEPROM & RTC
    init_ds1307();         // Initialize Real-Time Clock (RTC)
    write_ext_eep(200, 10); // Store default password (10) in EEPROM
}

void main(void) 
{
    init_config(); // Call init_config() to set up everything
    
    while(1) //Infinite loop (Runs forever)
    {
        get_time(); //Fetch the current time from RTC
        key = read_switches(STATE_CHANGE);
        if (main_f == DASHBOARD)
        {
            display_dashboard();
        }
        else if (main_f == PASSWORD)
        {
            password();
        }
        else if (main_f == MENU)
        {
            menu(key);
        }
    }
}
