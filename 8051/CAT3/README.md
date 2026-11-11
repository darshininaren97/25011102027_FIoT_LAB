# Switch Polling – 8051 LED Control System

## Overview:

This program demonstrates a "switch polling mechanism" implemented on an **8051 microcontroller**, where each valid button press advances the system to a new operating state.

The objective of this exercise is to showcase our understanding of:
- Embedded C programming (compiled using **Keil C51**)
- GPIO pin configuration
- Direct memory-mapped register access
- State-based system design


## Requirements:

### Software
- Keil C51 Compiler

### Hardware
- Amotech 8051 Microcontroller Development Kit
- 4 LEDs
- 4 Resistors (1 kΩ each)
- Jumper cables (as required)
- Breadboard


## System States

Each button press advances the system to the next state.

### State 0 – Running LEDs
LEDs glow sequentially: LED1 -> LED2 -> LED3 -> LED4 -> repeat


### State 1 – Binary Counter
LEDs behave as a 4-bit counter: 0000 -> 0001 -> 0010 -> ... -> 1111


### State 2 – Alternating Pattern
LEDs toggle between: 1010 -> 0101 -> repeat


### State 3 – Full Flash
All LEDs blink together: 1111 -> 0000 -> repeat


## Software Implementation

### GPIO Configuration
LEDs are connected to Port 1 pins
Push button uses keypad mapping: P2.3 - ROW (output) and P2.7 - COL (input)


### Mode Tracking
We assigned a variable "mode" to keep track of the system state:

0 - Mode 1  
1 - Mode 2  
2 - Mode 3  
3 - Mode 4  

Mode increments on each valid button press and wraps back to 0.


### Core Functions

#### `delay()`
software delay to control LED speed.

#### `checkButton()`
- Implements switch polling with "debouncing"
- Detects button press using ROW and COL logic
- Waits until button release
- Increments Mode variable safely


#### `setLEDs(unsigned char val)`

Maps the lower 4 bits of the variable "val" to the LEDs.

Example:
LED2 = (val >> 1) & 0x01;
This ensures each LED reflects the specific bit of the value.


## Mode-wise Code Logic

### Mode 1 – Running LEDs

setLEDs(1 << m1_index);
m1_index = (m1_index + 1) % 4;

- Shifts a single ON bit across LEDs
- Creates a moving light effect


### Mode 2 – Binary Counter

setLEDs(m2_count);
m2_count = (m2_count + 1) % 16;

Displays numbers from 0 to 15 in binary


### Mode 3 – Alternating Pattern

pattern = {0x0A, 0x05}

Alternates between the binary patterns 1010 and 0101


### Mode 4 – Full Flash

if (m4_toggle)
    setLEDs(0x0F);
else
    setLEDs(0x00);
m4_toggle = !m4_toggle;

- Toggles all LEDs ON and OFF


## Main Design Issue we Encountered

### Problem

Initially, each mode was implemented as a continuous loop/function, meaning:
- Once a mode started executing,
- It completed its entire LED cycle before checking for button input

This caused:
- Delayed responsiveness
- User had to wait for the full pattern to finish before the modes switched


## Solution Implemented

To fix this, we modified the design so that:
- Each mode performs only one step per loop iteration
- Control returns to the main loop's switch case after every LED update
- checkButton() is called before every state update - so if the button hadn't been pressed it will return to the same mode's function and continue 

### Updated Execution Flow

while(1){
    checkButton();      //check for any changes in the input
    switch(mode){
        case 0: mode1(); break;
        case 1: mode2(); break;
        case 2: mode3(); break;
        case 3: mode4(); break;
    }
    delay();
}


## Key Improvement

This change ensures:
- Immediate response to button press
- Smooth and user-friendly behaviour


## Conclusion

This project helped us learn and demonstrate the clean implementation of:
- Gained understanding of the internal behaviour of mechanical switches, including signal bouncing, and implemented software debouncing along with GPIO-based
  logic control to ensure accurate and stable button input handling.
- Switch polling
- State machine design
- Bitwise LED control
- Modular embedded programming

---END---
