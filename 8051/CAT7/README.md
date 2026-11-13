# LCD and Keypad Interfacing using 8051 Microcontroller

## Overview

This set of experiments demonstrates the interfacing and control of a 16×2 LCD and a directional keypad using the AT89S52 (8051) microcontroller.

The experiments progressively implement basic LCD communication, cursor positioning, numerical data display, and interactive character movement using external keypad inputs.

## Experiments Covered

### 1. LCD Interfacing and String Display
- Interfaced a 16×2 LCD with the 8051 in 4-bit mode.
- Implemented LCD initialization and command/data transmission.
- Displayed individual characters and strings.
- Used both rows of the LCD for displaying text.

### 2. LCD Cursor Positioning and Integer Display
- Implemented row and column-based cursor positioning.
- Converted unsigned integer values into ASCII characters.
- Used division and modulus operations to extract individual digits.
- Displayed numerical values on the LCD.

### 3. LCD Cursor Movement using Keypad
- Interfaced a four-direction keypad with the 8051.
- Implemented polling-based keypad scanning.
- Added button debounce checking.
- Controlled character movement using UP, DOWN, LEFT, and RIGHT inputs.
- Implemented boundary checking to restrict movement within the LCD dimensions.



## Circuit Diagram
<img width="1024" height="559" alt="image" src="https://github.com/user-attachments/assets/e5d2911a-19a3-4fed-8cd5-653e5817f2e0" />
