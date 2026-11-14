# Task 8C – Short Press and Long Press Detection (STM32)

## Aim
To interface a switch with an STM32 microcontroller and distinguish between short and long button presses to control an LED using different operations.

## Hardware Requirements
- STM32 development board
- LED connected to GPIO pin PC13
- Switch connected to GPIO pin PA3

## GPIO Configuration

| Pin | Configuration | Function |
|---|---|---|
| PA3 | Input with pull-up | Reads switch state |
| PC13 | Output push-pull | Controls LED |

## Working Principle

The program detects whether the switch is pressed briefly or held for a longer duration. It uses software debouncing to avoid false detections caused by mechanical switch bouncing.

A switch state is accepted only after remaining stable for **30 milliseconds**.

Two types of button presses are handled:

### 1. Short Press
- A press lasting less than 1000 milliseconds is treated as a short press.
- The LED toggles its current state once when the button is released.
- If blinking mode was active, a short press stops blinking and turns the LED OFF.

### 2. Long Press
- A press lasting 1000 milliseconds or longer is treated as a long press.
- When the button is released after a long press, blinking mode is activated.
- The LED continuously toggles at an interval of 300 milliseconds.

## Timing Configuration

| Constant | Value | Purpose |
|---|---:|---|
| `DEBOUNCE_MS` | 30 ms | Required switch stability period |
| `LONG_PRESS_MS` | 1000 ms | Threshold for detecting a long press |
| `BLINK_MS` | 300 ms | LED blinking interval |

## Variables Used

| Variable | Purpose |
|---|---|
| `lastRaw` | Stores the previous raw switch reading |
| `stableState` | Stores the debounced switch state |
| `blinking` | Indicates whether blinking mode is active |
| `lastChangeTick` | Stores the time of the last raw switch-state change |
| `pressStart` | Records the time at which a valid press begins |
| `lastBlink` | Records the time of the last LED toggle during blinking |

## Program Flow

1. Initialize the HAL library, system clock and GPIO peripherals.
2. Set PC13 HIGH to keep the active-low LED OFF initially.
3. Continuously read the switch connected to PA3.
4. Detect raw switch-state changes and restart the 30 ms debounce timer.
5. Accept a new switch state only after it remains stable for the debounce interval.
6. When a valid press is detected, record its starting time using `HAL_GetTick()`.
7. When the switch is released, calculate the press duration.
8. If the duration is less than 1000 ms, execute the short-press operation.
9. If the duration is 1000 ms or longer, activate blinking mode.
10. While blinking mode is active, toggle the LED every 300 ms.

## Clock Configuration

The system clock is configured using the external high-speed oscillator (HSE) and PLL.

- Oscillator source: HSE
- PLL source: HSE
- PLL multiplication factor: ×9
- AHB prescaler: 1
- APB1 prescaler: 2
- APB2 prescaler: 1

## Software Requirements
- STM32CubeIDE
- STM32 HAL Library
- STM32 development board

## Key Concepts Demonstrated
- GPIO input and output configuration
- Short-press and long-press detection
- Software switch debouncing
- Time measurement using `HAL_GetTick()`
- Non-blocking LED blinking
- State-based control using variables
- LED toggling using `HAL_GPIO_TogglePin()`
- Active-low LED operation

## Observation

The program distinguishes short and long button presses using their measured durations. A short press toggles the LED, while a long press activates LED blinking at 300 ms intervals. A subsequent short press stops blinking and turns the LED OFF.

The implementation uses non-blocking time checks instead of software delay loops, allowing switch monitoring and LED blinking to operate continuously.
