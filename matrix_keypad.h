/*
 * ? Explanation of matrix_keypad.h (Keypad Header File)
This header file (matrix_keypad.h) is used to define keypad-related macros and function,
prototypes to make keypad handling easy in matrix_keypad.c.

? Why is matrix_keypad.h needed?

It defines PIC16F877A pin connections for the keypad.
It assigns numbers to each key (MK_SW1 to MK_SW12).
It declares functions needed for scanning and reading key presses.
 */

/*
 1 Prevent Multiple Inclusions
? Prevents multiple inclusions of this header file in the program.
? Ensures only one copy is included during compilation.
*/
#ifndef MATRIX_KEYPAD_H
#define MATRIX_KEYPAD_H

/*
2 Define Keypad Port
 ? Defines PORTB as the keypad interface data port.

All keys are connected to PORTB pins.
This allows reading key states from a single port.

 */ 
#define MATRIX_KEYPAD_PORT  PORTB

/*
3 Define Keypad Rows (Inputs)
 ? Defines which PIC16F877A pins are connected to the keypad:

Rows (RB5, RB6, RB7) ? Used as inputs (to detect pressed keys).
Columns (RB1, RB2, RB3) ? Used as outputs (to activate keypad rows).
*/

#define ROW1    PORTBbits.RB5
#define ROW2    PORTBbits.RB6
#define ROW3    PORTBbits.RB7

#define COL1    PORTBbits.RB1
#define COL2    PORTBbits.RB2
#define COL3    PORTBbits.RB3

/*
 4 Define Keypad Columns (Outputs)
 ? Defines two detection modes for read_switches() function:
LEVEL_CHANGE (0) ? Continuous detection (key remains active while held).
STATE_CHANGE (1) ? One-time detection (prevents repeated key reads).
 */
#define STATE_CHANGE  1
#define LEVEL_CHANGE  0

/*
 6 Key Mappings
 ? Assigns unique numbers to each key.
Makes it easy to refer to keys in the program using MK_SWx instead of raw numbers.
 */

#define MK_SW1   1
#define MK_SW2   2
#define MK_SW3   3
#define MK_SW4   4
#define MK_SW5   5
#define MK_SW6   6
#define MK_SW7   7
#define MK_SW8   8
#define MK_SW9   9
#define MK_SW10 10
#define MK_SW11 11
#define MK_SW12 12

/*
 7. Define NO Key press Condition
 */
#define ALL_RELEASED  0xFF  // No key is pressed


/*
 8. ? Declares the functions implemented in matrix_keypad.c:

init_matrix_keypad() ? Sets keypad PORTB pins as inputs.
scan_key() ? Scans the keypad for a pressed key and returns its number.
read_switches(detection_type) ? Reads the keypad input based on LEVEL_CHANGE or STATE_CHANGE.
 */
// Function Prototypes
void init_matrix_keypad(void);         // Initialize Keypad
unsigned char scan_key(void);          // Scan for pressed key
unsigned char read_switches(unsigned char detection_type); // Read Keypad with mode

#endif

/*
 Section                                       Purpose
Header Guards                  ->     Prevents multiple inclusions of the file
Keypad Port Definition         ->     Defines PORTB as the keypad port
Row & Column Definitions       ->	  Defines which PORTB pins handle rows & columns
Detection Modes                ->     Defines continuous vs single detection modes
Key Mappings                   ->     Assigns numbers to each key (MK_SW1 to MK_SW12)
No Key Pressed Macro           ->     Defines ALL_RELEASED (0xFF) when no key is pressed
Function Prototypes            ->     Declares keypad functions for matrix_keypad.c

 */