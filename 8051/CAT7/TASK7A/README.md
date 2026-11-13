# Experiment: LCD Interfacing and String Display using 8051

## Objective
To interface a 16×2 LCD with the 8051 microcontroller using 4-bit communication mode and display individual characters and strings on both rows of the LCD.

## Hardware Requirements
- AT89S52 (8051) Microcontroller
- 16×2 LCD Display
- Connecting wires
- Power supply

## Pin Connections

| LCD Pin | 8051 Connection |
|---|---|
| RS | P3.2 |
| E | P3.3 |
| D4–D7 | P3.4–P3.7 |
| RW | GND |
| VSS | GND |
| VDD | +5V |

## Implementation

The LCD is interfaced using 4-bit mode, where only four data lines (D4–D7) are used to transmit data.

The program implements the following functions:

- `lcd_send_nibble()` – Sends a 4-bit data portion to the LCD.
- `lcd_cmd()` – Sends commands to configure and control the LCD.
- `lcd_data()` – Sends individual characters to the LCD.
- `lcd_init()` – Initializes the LCD in 4-bit mode with a two-line display.
- `lcd_puts()` – Displays a string character by character.

The program first displays an individual character and subsequently displays text on both rows.

## Output

- First row: `HELLO WORLD`
- Second row: `8051 LCD`

## Result

Successfully interfaced a 16×2 LCD with the AT89S52 microcontroller in 4-bit mode and displayed individual characters and strings on both rows.
