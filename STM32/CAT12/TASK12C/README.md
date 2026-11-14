# STM32 GPIO – Short and Long Button Press Detection

This program uses the STM32F401RE GPIO input to detect short and long button presses and control an LED accordingly. A short press toggles the LED state, while a long press triggers five quick blinks and then restores the LED to its previous state.

## Implementation

- **Button Input:** PC13, configured as an input with an internal pull-up resistor.
- **LED Output:** PA5, configured as a push-pull output.
- **Debouncing:** A 50 ms delay is used to validate button presses and releases.
- **Press Duration:** `HAL_GetTick()` measures how long the button remains pressed.
- **Long Press Threshold:** 1000 ms.

## Button Behaviour

| Button Action | LED Behaviour |
|---|---|
| Short press (less than 1 second) | Toggles the LED and retains the new state |
| Long press (1 second or more) | Blinks the LED five times quickly, then restores its previous state |

## How It Works

1. The program continuously monitors PC13. The button is active-low, so a pressed button reads `GPIO_PIN_RESET`.
2. A 50 ms debounce delay is applied, followed by another read to confirm the press.
3. `HAL_GetTick()` records the time after the press is validated.
4. The program waits until the button is released and calculates the press duration.
5. Based on the duration:
   - A short press toggles PA5.
   - A long press toggles PA5 ten times with 100 ms intervals, producing five complete blink cycles.
6. After the blinking sequence, the LED is explicitly restored to its state before the sequence began.

## Clock Configuration

- Clock source: Internal High-Speed Oscillator (HSI)
- PLL enabled
- System clock: 84 MHz
- AHB prescaler: 1
- APB1 prescaler: 2
- APB2 prescaler: 1

## GPIO Configuration

| Pin | Configuration | Function |
|---|---|---|
| PC13 | Input, Pull-up | Push button |
| PA5 | Output, Push-pull | LED |

## Key HAL Functions

- `HAL_GPIO_ReadPin()` – Reads the button and LED states.
- `HAL_GPIO_TogglePin()` – Toggles the LED output.
- `HAL_GPIO_WritePin()` – Restores the LED to its previous state.
- `HAL_GetTick()` – Retrieves the system tick count for measuring press duration.
- `HAL_Delay()` – Implements debounce intervals and blink timing.

## Circuit Diagram 
![Diagram](diagram.png)

## Software & Hardware

- STM32CubeIDE
- STM32 HAL Library
- STM32F401RE Nucleo board
- Onboard user button (PC13)
- Onboard LED (PA5)
