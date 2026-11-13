# Experiment: Interfacing Four LEDs, a 4×3 Matrix Keypad and a Seven-Segment Display Using 8051 Microcontroller

## 1. Aim

To interface four LEDs, a 4×3 matrix keypad, and a seven-segment display with the 8051 microcontroller and implement ten different LED operating modes (0–9) based on keypad input.

## 2. Experiment Overview

This experiment demonstrates the interfacing and control of multiple input and output devices using the 8051 microcontroller.

A 4×3 matrix keypad is used to select between ten different LED operating modes. The selected mode is displayed numerically on a seven-segment display, while four LEDs connected to Port 1 operate according to the selected mode.

The experiment involves GPIO programming, matrix keypad scanning, bitwise operations, sequential LED control, and seven-segment display interfacing using Embedded C.

## 3. Objectives

- To interface and control multiple LEDs using the 8051 microcontroller.
- To implement a 4×3 matrix keypad for user input.
- To understand row-column scanning techniques used in matrix keypad interfacing.
- To implement multiple LED operating patterns using bitwise operations.
- To interface a seven-segment display for numerical indication of the selected mode.
- To implement software-based switch debouncing.
- To develop a structured Embedded C program using functions, conditional statements, loops, and bit manipulation.

## 4. Hardware Requirements

| Component | Quantity |
|---|---:|
| 8051 Microcontroller | 1 |
| LEDs | 4 |
| Seven-Segment Display | 1 |
| 4×3 Matrix Keypad | 1 |
| Current-limiting resistors | As required |
| Breadboard | 1 |
| Connecting wires | As required |
| Power supply | 1 |

## 5. Software Requirements

- **Programming Language:** Embedded C
- **Microcontroller:** 8051
- **Header File:** `reg51.h`
- **Development Environment:** Keil µVision
- **Compiler:** Keil C51 Compiler
- **Simulation Software:** Proteus (optional)

## 6. Hardware Pin Configuration

### 6.1 LED Connections

| LED | 8051 Pin |
|---|---|
| LED1 | P1.0 |
| LED2 | P1.1 |
| LED3 | P1.2 |
| LED4 | P1.3 |

### 6.2 Seven-Segment Display Connections

| Segment | 8051 Pin |
|---|---|
| a | P0.0 |
| b | P0.1 |
| c | P0.2 |
| d | P0.3 |
| e | P0.4 |
| f | P0.5 |
| g | P0.6 |

The display uses active-HIGH segment control and assumes a common-cathode seven-segment display.

**Hardware consideration:** Port 0 of a standard 8051 requires external pull-up resistors when used as a general-purpose output port. Appropriate current-limiting resistors must also be provided.

### 6.3 Matrix Keypad Connections

| Keypad Pin | 8051 Pin | Configuration |
|---|---|---|
| Row 1 | P2.7 | Output |
| Row 2 | P2.6 | Output |
| Row 3 | P2.5 | Output |
| Row 4 | P2.4 | Output |
| Column 1 | P2.3 | Input |
| Column 2 | P2.2 | Input |
| Column 3 | P2.1 | Input |

## 7. Keypad Mapping

| Keypad Position | Key Value | Selected Mode |
|---|---:|---|
| Row 1, Column 1 | 1 | Mode 1 |
| Row 1, Column 2 | 2 | Mode 2 |
| Row 1, Column 3 | 3 | Mode 3 |
| Row 2, Column 1 | 4 | Mode 4 |
| Row 2, Column 2 | 5 | Mode 5 |
| Row 2, Column 3 | 6 | Mode 6 |
| Row 3, Column 1 | 7 | Mode 7 |
| Row 3, Column 2 | 8 | Mode 8 |
| Row 3, Column 3 | 9 | Mode 9 |
| Row 4, Column 2 | 0 | Mode 0 |

## 8. Operating Modes

The experiment implements ten different LED operating modes selected through the keypad.

| Mode | LED Operation | Description |
|---|---|---|
| 0 | All LEDs OFF | Resets LED patterns and internal counters |
| 1 | LED1 ON | Activates the first LED |
| 2 | LED2 ON | Activates the second LED |
| 3 | LED3 ON | Activates the third LED |
| 4 | LED4 ON | Activates the fourth LED |
| 5 | Running LED | LEDs turn ON sequentially |
| 6 | Alternate LED Pattern | Alternates between two LED combinations |
| 7 | Binary Counter | Displays a four-bit binary counting sequence |
| 8 | All LEDs Blinking | Switches all LEDs ON and OFF alternately |
| 9 | All LEDs OFF | Switches OFF all four LEDs |

### 8.1 Mode 0 – Reset

- Switches OFF all four LEDs.
- Resets the running LED index.
- Resets the binary counter.
- Resets the alternate pattern index.
- Resets the blinking state.

### 8.2 Modes 1–4 – Individual LED Control

Each mode activates one specific LED while keeping the remaining LEDs OFF.

- Mode 1: LED1 ON.
- Mode 2: LED2 ON.
- Mode 3: LED3 ON.
- Mode 4: LED4 ON.

### 8.3 Mode 5 – Running LED Pattern

One LED is activated at a time in sequential order.

Sequence:

`0001 → 0010 → 0100 → 1000 → Repeat`

The `run_index` variable determines the LED position. A left-shift operation generates the required LED pattern, and modulo 4 resets the index after the fourth LED.

### 8.4 Mode 6 – Alternate LED Pattern

This mode alternates between two complementary LED combinations.

Sequence:

`1010 → 0101 → Repeat`

The patterns are stored in an array:

- `0x0A` activates LED2 and LED4.
- `0x05` activates LED1 and LED3.

The `alt_index` variable selects the pattern, and modulo 2 ensures continuous alternation.

### 8.5 Mode 7 – Binary Counter

This mode implements a four-bit binary counter using the four LEDs.

The counter progresses from decimal 0 to 15, representing all possible combinations of four binary bits.

| Decimal | Binary |
|---:|---|
| 0 | 0000 |
| 1 | 0001 |
| 2 | 0010 |
| 3 | 0011 |
| 4 | 0100 |
| 5 | 0101 |
| ... | ... |
| 15 | 1111 |

The `binary_count` variable is incremented after each iteration and wraps around after reaching 15 using modulo 16.

### 8.6 Mode 8 – All LEDs Blinking

All four LEDs are switched ON and OFF alternately.

- When `blink_toggle` is 1, all LEDs are switched ON.
- When `blink_toggle` is 0, all LEDs are switched OFF.

The toggle variable changes state after every iteration to produce continuous blinking.

### 8.7 Mode 9 – All LEDs OFF

This mode switches OFF all four LEDs without resetting the internal pattern variables.

It provides a separate LED OFF operation, distinct from Mode 0, which also resets the pattern counters.

## 9. Function Description

The program is divided into individual functions to improve modularity and readability.

| Function | Purpose |
|---|---|
| `delay()` | Generates software delay for timing control and keypad debouncing |
| `setLEDs()` | Controls four LEDs according to a supplied binary pattern and updates the display |
| `running_led()` | Generates the sequential LED pattern |
| `binary_counter()` | Generates the four-bit binary counting sequence |
| `alternate_led()` | Alternates between two LED patterns |
| `blink_all()` | Controls simultaneous ON/OFF blinking |
| `led_control()` | Updates the selected operating mode based on keypad input |
| `display_digit()` | Displays the selected digit on the seven-segment display |
| `keypad_scan()` | Scans keypad rows and detects key presses |

## 10. Working Methodology

1. The microcontroller initializes the output pins and internal variables.
2. The system starts in Mode 0 with all LEDs switched OFF.
3. The matrix keypad is scanned continuously.
4. When a key is pressed, the corresponding mode number is identified.
5. The `mode` variable is updated.
6. The seven-segment display shows the selected mode number.
7. A switch-case statement executes the corresponding LED operation.
8. The selected operation continues until another valid key is pressed.
9. The process repeats continuously.

## 11. Program Execution

The `main()` function initializes the LEDs and seven-segment display and sets the default operating mode to zero.

The program then enters an infinite loop consisting of two major operations:

**1. Keypad Scanning:** The keypad is scanned continuously to identify user input and update the selected mode.

**2. Mode Execution:** A switch-case statement executes the LED behavior associated with the current mode.

A software delay is introduced after each execution cycle to control the speed of LED transitions.

## 12. Expected Output

- Pressing keys 1–4 activates the corresponding individual LEDs.
- Pressing key 5 initiates a running LED sequence.
- Pressing key 6 generates alternating LED combinations.
- Pressing key 7 initiates a four-bit binary counting sequence.
- Pressing key 8 makes all four LEDs blink simultaneously.
- Pressing key 9 switches OFF all LEDs.
- Pressing key 0 switches OFF all LEDs and resets the pattern variables.

The seven-segment display indicates the currently selected operating mode.

## Circuit Diagram
<img width="1024" height="559" alt="image" src="https://github.com/user-attachments/assets/4f9aa5db-69d3-436b-94b0-3ca48cc71e2c" />

## 14. Limitations and Considerations

- The delay function uses software loops, so its duration depends on the microcontroller clock frequency and compiler configuration.
- Keypad scanning is polling-based and does not use hardware interrupts.
- The seven-segment display uses active-HIGH operation and assumes a common-cathode display.
- Port 0 requires suitable external pull-up resistors on a standard 8051.
- The program uses blocking delays and waits for key release, temporarily preventing other operations from executing.
- Only one operating mode can be selected at a time.

