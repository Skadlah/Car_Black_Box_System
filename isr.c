/*
 * File:   isr.c
 * Author: sheryas
 *
 * Created on 9 February, 2025, 6:16 PM
 * 
 * 
 ? Step 9: Setting Up isr.c (Interrupt Service Routine - ISR Handling)
This file handles Timer1 interrupts, which are used for:
? Password Timeout Handling ? Resets the login screen if the user takes too long.
? Blocking Countdown ? Runs the 120-second lockout timer for incorrect password attempts.
? Real-Time Event Management ? Keeps track of time-based functions in the system.
 */

#include <xc.h>
#include "main.h"

void __interrupt() isr(void) {
    if (TMR1IF) {   // Check if Timer1 Interrupt Flag is set
        TMR1 = TMR1 + 3038;  // Reload Timer1 for next interrupt

        if (++count == 80) {  // 80 overflows = 4 seconds
            count = 0;
            tm--;   // Decrease timeout counter
        }
        
        TMR1IF = 0;  // Clear the Timer1 Interrupt Flag
    }
}
/*void __interrupt() isr(void) 
{
    if (TMR1IF) 
    {   // Check if Timer1 Interrupt Flag is set
        
? Re-initializes Timer1 for the next overflow.

Adds 3038 to the Timer1 register (TMR1) so that the next interrupt occurs in another 50ms.
This ensures periodic interrupts for countdown operations 
        TMR1 = TMR1 + 3038;  
        Reload Timer1 for next interrupt
*/
        
/*? Counting Timeouts & Blocking Mechanism
 ? This keeps track of time in seconds.

Every time Timer1 overflows (every 50ms), count increases.
After 80 overflows (50ms * 80 = 4 seconds), tm-- decreases.
tm is used for password timeout and lockout countdown.

        if (++count == 80) 
        {  // 80 overflows = 4 seconds
            count = 0;
            tm--;   // Decrease timeout counter
        }
        // Clearing the Interrupt Flag
        
        TMR1IF = 0;  // Clear the Timer1 Interrupt Flag
    }
}
*/

/*
 ? Explanation of isr.c (Interrupt Service Routine - ISR Handling)
This file handles Timer1 interrupts, which control:
? Password Timeout ? If the user doesn?t enter a password in time, it resets the login screen.
? Blocking Countdown ? When the system is locked, this ISR counts down from 120 seconds.
? Real-Time Event Updates ? Helps in timed operations like updating the dashboard and logs.

1 - Understanding Interrupts
? Interrupts allow the microcontroller to pause its normal execution and execute special functions (ISR) when an event occurs.
? In this case, Timer1 overflow triggers an interrupt, and the isr() function executes.
? The interrupt runs every 50ms (as set in timer.c).

2 - isr() - Interrupt Service Routine (ISR
? This function executes automatically when an interrupt occurs.

The __interrupt keyword tells the compiler this is an ISR function.
It is executed whenever Timer1 overflows.
 * 
 * 
 ? Summary of isr.c
        Function                                  Purpose
void __interrupt() isr(void)    	Executes on Timer1 interrupt
if (TMR1IF)                         Checks if Timer1 overflowed
TMR1 = TMR1 + 3038                  Reloads Timer1 for the next cycle
if (++count == 80) { tm--; }        Counts 4-second intervals
TMR1IF = 0;                         Clears interrupt flag
 
 */

