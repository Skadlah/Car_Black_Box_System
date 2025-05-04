# Car Black Box System

## Overview
The **Car Black Box System** is a real-time data logging system developed using the **PIC16F877A** microcontroller. This system records event IDs, timestamps, and user inputs, displaying the data on a **Character LCD (CLCD)**. The data is stored permanently in an **external EEPROM** via the **I2C interface**. Data can be retrieved using **UART communication** for post-event analysis.

The system is designed to provide a reliable and easy-to-use mechanism to monitor critical events in a vehicle, such as sudden braking, acceleration, or any other user-defined event.

## Features
- **Event Logging**: Records event IDs, timestamps, and user actions in real-time.
- **CLCD Display**: Displays event details directly on a **Character LCD**.
- **External EEPROM Storage**: Data is permanently stored in an external EEPROM via the **I2C interface**.
- **UART Communication**: Retrieve the logged data using UART for post-event analysis.
- **User Input**: Allows users to mark and log specific events via buttons or switches.
- **Real-time Monitoring**: Provides real-time event monitoring through the CLCD.

## Components Used
- **Microcontroller**: PIC16F877A
- **Display**: Character LCD (CLCD)
- **Data Storage**: External EEPROM (I2C)
- **Communication**: UART (for data retrieval)
- **User Interface**: Push-buttons for event marking

## Project Structure
- **main.c**: The main program that controls the flow of the black box system, handles events, and updates the display.
- **eeprom.c**: Functions for interfacing with the external EEPROM for data storage and retrieval.
- **uart.c**: Functions for UART communication to send data to and receive data from an external device (e.g., PC).
- **clcd.c**: Functions to interface with and control the Character LCD for real-time display.
- **config.h**: Header file for configuration settings (e.g., I2C and UART settings).

## How to Use
### Hardware Setup
1. **Microcontroller**: The PIC16F877A is used as the central processing unit.
2. **LCD**: Connect a **16x2 Character LCD** to the microcontroller for real-time data display.
3. **External EEPROM**: Use an **I2C-compatible EEPROM** to store the logged data. Connect it to the microcontroller via the I2C bus.
4. **Push Buttons**: Use buttons to simulate event marking (e.g., sudden braking, system startup).
5. **UART**: Set up a serial communication interface (e.g., using a USB-to-serial adapter) for data retrieval.

### Software Setup
1. **MPLAB X IDE**:
   - Open the provided MPLAB X project in **MPLAB X IDE**.
   - Compile the code using the **XC8 compiler**.
   
2. **Upload the Program**: Use a compatible programmer (e.g., **PICkit 3**) to upload the compiled program to the **PIC16F877A** microcontroller.
   
3. **Monitor & Control**:
   - Use a **terminal program** (like **PuTTY** or **Tera Term**) to communicate with the system via UART.
   - The system will log events as they occur, displaying data on the CLCD and storing it in the EEPROM.
   
4. **Data Retrieval**: Use the UART interface to retrieve the logged event data for analysis.

## System Operation
1. On **power-up**, the system initializes and displays a welcome message on the CLCD.
2. As the car operates, the system listens for events (e.g., braking or acceleration). Each event is logged with a timestamp.
3. When an event occurs, it is displayed on the **CLCD** in real-time.
4. All event data is stored in **external EEPROM**.
5. Users can retrieve the event log by sending a specific command over UART, which displays the data on a terminal for post-event analysis.

## Pin Configuration
| Pin | Component         | Function               |
|-----|-------------------|------------------------|
| RA0 | Push-button        | Event Marker (Braking) |
| RA1 | Push-button        | Event Marker (Acceleration) |
| SCL  | External EEPROM    | I2C Clock Line         |
| SDA  | External EEPROM    | I2C Data Line          |
| TX   | UART               | Data Transmission      |
| RX   | UART               | Data Reception         |

## Code Description
- **`main.c`**: Manages event logging, handles user inputs, updates the display, and stores data in EEPROM.
- **`eeprom.c`**: Contains functions for writing to and reading from the external EEPROM.
- **`uart.c`**: Handles communication via UART, allowing external devices to retrieve stored data.
- **`clcd.c`**: Controls the LCD to display real-time information about the system's state.
- **`config.h`**: Configuration for the I2C, UART, and any other system-specific parameters.

## Setup Instructions
1. **Hardware Connections**:
   - Connect the **PIC16F877A** microcontroller to the **16x2 CLCD** using the appropriate data and control lines.
   - Connect the **external EEPROM** to the microcontroller’s **I2C bus**.
   - Attach push buttons to the microcontroller for marking events.
   - Set up UART communication for external data retrieval.

2. **MPLAB X IDE Setup**:
   - Download and install **MPLAB X IDE** and **XC8 compiler** if not already installed.
   - Open the provided MPLAB X project in the IDE.
   - Build and compile the project.
   - Upload the compiled program to the PIC16F877A using the **PICkit 3** programmer.

3. **Data Retrieval**:
   - Use a serial terminal program (such as **PuTTY**) to connect to the microcontroller via UART.
   - Send a command to retrieve the event log, and the data will be displayed in the terminal.

## License
This project is open-source and available under the [MIT License](LICENSE). You are free to use, modify, and distribute the code, provided you give appropriate credit.

## Acknowledgements
- **Microchip Technology** for the **PIC16F877A** microcontroller.
- Open-source libraries used for I2C, UART, and CLCD communication.
- The **MPLAB X IDE** and **XC8 Compiler** by **Microchip** for development.

