# Experiment: LCD Cursor Movement using Keypad and 8051

## Objective
To interface a 4-direction keypad with the 8051 microcontroller and control the movement of a character displayed on a 16×2 LCD using UP, DOWN, LEFT, and RIGHT inputs.

## Hardware Requirements
- AT89S52 (8051) Microcontroller
- 16×2 LCD Display
- 4-direction keypad
- Connecting wires
- Power supply

## Pin Connections

### LCD Connections

| LCD Pin | 8051 Connection |
|---|---|
| RS | P3.2 |
| E | P3.3 |
| D4–D7 | P3.4–P3.7 |
| RW | GND |
| VSS | GND |
| VDD | +5V |

### Keypad Connections

| Keypad Signal | 8051 Connection |
|---|---|
| UP | P2.3 |
| DOWN | P2.2 |
| LEFT | P2.1 |
| RIGHT | P2.0 |
| Common Column | P2.7 |

## Implementation

The program combines LCD interfacing with keypad input scanning to control the position of a character on the LCD.

The following functions are implemented:

- `lcd_send_nibble()` – Sends 4-bit data to the LCD.
- `lcd_cmd()` – Sends LCD control commands.
- `lcd_data()` – Displays individual characters.
- `lcd_init()` – Initializes the LCD in 4-bit mode.
- `lcd_goto()` – Positions the LCD cursor at a specified row and column.
- `lcd_puts()` – Displays strings.
- `check_button()` – Scans the four keypad directions and identifies the pressed button.

### Keypad Scanning Logic

The keypad is scanned using a polling technique.

- One direction line is made LOW at a time.
- The common column line is checked for a LOW signal.
- A short debounce delay is introduced to verify the button press.
- The program waits until the button is released.
- A direction code is returned based on the detected input.

| Direction | Return Value |
|---|---|
| UP | 1 |
| DOWN | 2 |
| LEFT | 3 |
| RIGHT | 4 |
| No key | 0 |

### Character Movement Logic

The character `A` is initially displayed at the first row and first column.

Two variables, `row` and `col`, maintain its current position.

When a direction button is pressed:

1. The current character position is cleared by displaying a space.
2. The row or column value is updated according to the selected direction.
3. Boundary conditions prevent movement outside the LCD dimensions.
4. The character `A` is displayed at the updated position.

The second row initially displays the text `HELLO`.

## Output

- Displays the character `A` on the LCD.
- Displays `HELLO` on the second row.
- Allows the character `A` to move in four directions using the keypad.
- Prevents movement beyond the 16×2 LCD boundaries.

