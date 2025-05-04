/*
 * File:   matrix_keypad.c
 * Author: sheryas
 *
 * Created on 9 February, 2025, 12:45 PM
 */
/*? Step 5: Setting Up matrix_keypad.c (Keypad Handling)
The 4x4 Matrix Keypad is used for:
? Password Entry (Login System)
? Menu Navigation (Selecting options like View Logs, Change Time)
? Gear Change Simulation (Using specific keys)

*/
#include <xc.h>
#include "matrix_keypad.h"

/*1 - init_matrix_keypad() - Initialize Keypad
 * 
 * ? Configures PORTB for keypad input:

MATRIX_KEYPAD_PORT = 0xFF ? Sets all PORTB pins as input (default HIGH).
Ensures keypad is ready to detect key presses.
*/

/*2- scan_key() - Detect Key Press
 
 * ? Scans the 4x4 matrix keypad:

1) Activates one row at a time (MATRIX_KEYPAD_PORT = ~(1 << (row + 4))).
2) Checks each column (if (!(MATRIX_KEYPAD_PORT & (1 << col)))):
3) If a key is pressed ? calculates its position ((row * 3) + col + 1).
4) Returns the detected key number immediately.
5) If no key is pressed, returns 0xFF (No Key).
 */
void init_matrix_keypad(void) 
{
    MATRIX_KEYPAD_PORT = 0xFF;  // Set all PORTB pins as input
}

unsigned char scan_key(void) {
    unsigned char key = 0xFF; // Default no key pressed

    for (unsigned char row = 0; row < 4; row++) {
        //MATRIX_KEYPAD_PORT = ~(1 << (row + 4)); // Activate row
        MATRIX_KEYPAD_PORT = (unsigned char) (~(1 << (row + 4)));


        for (unsigned char col = 0; col < 3; col++) {
            if (!(MATRIX_KEYPAD_PORT & (1 << col))) {
                key = (row * 3) + col + 1;  // Calculate key number
                return key;  // Return the detected key
            }
        }
    }
    return key;
}

/*3 - read_switches() - Detect Key Based on Press Type
 * 
 * ? Handles key press behavior based on detection_type:
1 - LEVEL_CHANGE Mode:

1) Returns the current key press status immediately.
2) STATE_CHANGE Mode:
3) Ensures a key is only detected once per press (ignores key holding).
4) Uses a once flag to prevent repeated detection.
5) Resets the flag when no key is pressed (once = 1)
*/

unsigned char read_switches(unsigned char detection_type) {
    static unsigned char once = 1;
    unsigned char key = scan_key();

    if (detection_type == LEVEL_CHANGE) {
        return key;
    } else if (detection_type == STATE_CHANGE && key != 0xFF) {
        if (once) {
            once = 0;
            return key;
        }
    } else if (key == 0xFF) {
        once = 1;
    }
    return 0xFF;
}
/*
     Function	                                Purpose
init_matrix_keypad()          ->	Sets keypad pins as inputs
scan_key()                    ->	Detects pressed key and returns its number
read_switches(detection_type) ->	Handles key press behavior (continuous vs single press)
 */