/*
 * File:   timer.c
 * Author: sheryas
 *
 * Created on 9 February, 2025, 6:11 PM
 */

/*
? Step 8: Setting Up timer.c (Timer & Interrupt Handling)
This file is responsible for:
? Setting up Timer1 ? Used for countdowns and timing events.
? Interrupt Handling ? Controls password timeout, blocking time, and dashboard updates.
*/

#include "main.h"

/*
 * 2 - init_timer1() - Configuring Timer1
 ? This function sets up Timer1 for periodic interrupts:

TMR1ON = 1; ? Turns ON Timer1.
TMR1IF = 0; ? Clears the Timer1 Interrupt Flag to prevent false triggers.
TMR1IE = 1; ? Enables interrupts for Timer1 (must also enable GIE and PEIE in main.c).
TMR1 = 3036; ? Preloads Timer1 with 3036, so it generates an interrupt every 50ms.

*/
void init_timer1(void) 
{
    TMR1ON = 1;   // Turn ON Timer1
    TMR1IF = 0;   // Clear Timer1 Interrupt Flag
    TMR1IE = 1;   // Enable Timer1 Interrupt
    TMR1 = 3036;  // Load Timer1 for a specific delay
}
/*
? Explanation of timer.c (Timer & Interrupt Handling Code)
This file is responsible for configuring Timer1 in the PIC16F877A microcontroller to manage:
? Password Timeout ? Gives 5 seconds to enter the password.
? Blocking System ? Counts 120 seconds if the user enters the wrong password multiple times.
? Real-time Event Updates ? Helps in time-based operations for logs and displays.

1?? Understanding Timer1 in PIC16F877A
? Timer1 is an internal 16-bit timer in PIC16F877A.
? It operates using a 4MHz clock frequency (assuming a 20MHz external crystal with a 4:1 division).
? Prescaler settings allow us to control the counting speed.

? Formula to Calculate Timer Delay:

 Timer Overflow Time = 4×(65536?Initial Timer Value) / Clock Frequency
 
For example, using a 3036 preload value results in 50ms delay per overflow.
*/
