# STM32 GPIO – Short Press and Long Press Detection

A button-controlled LED application using the STM32 HAL library. The firmware distinguishes between short and long button presses based on their duration, using software debouncing and non-blocking time tracking.

Different press types trigger different LED behaviours, implemented through a state-based control mechanism.

## Features

- Short-press and long-press detection.
- Software switch debouncing.
- Press-duration measurement using `HAL_GetTick()`.
- LED toggle control.
- Continuous LED blinking mode.
- Non-blocking timing without `HAL_Delay()`.
- State-based button and LED control.

## Hardware Configuration

| Pin | Configuration | Function |
|---|---|---|
| PA3 | Input with Pull-up | Reads switch state |
| PC13 | Output Push-Pull | Controls LED |

## Button Operations

The application supports two types of button interactions:

| Input | Duration | Behaviour |
|---|---|---|
| Short Press | Less than 1000 ms | Toggles LED state |
| Long Press | 1000 ms or longer | Activates blinking mode |

**Short press:**
- Toggles the LED once when the button is released.
- If blinking mode is already active, stops blinking and turns the LED OFF.

**Long press:**
- Activates continuous LED blinking when the button is released.
- The LED toggles at 300 ms intervals.

## Timing Configuration

| Parameter | Value | Purpose |
|---|---:|---|
| `DEBOUNCE_MS` | 30 ms | Input stability interval |
| `LONG_PRESS_MS` | 1000 ms | Long-press detection threshold |
| `BLINK_MS` | 300 ms | LED blinking interval |

## How It Works

### 1. Switch Debouncing

The firmware continuously reads PA3 and detects changes in its raw input state.

A new switch state is accepted only after remaining unchanged for 30 ms. This filters unwanted transitions caused by mechanical switch bouncing.

### 2. Press Duration Measurement

When a valid button press is detected, `HAL_GetTick()` records the starting timestamp in `pressStart`.

When the button is released, the elapsed duration is calculated and compared against the long-press threshold.

### 3. LED Control

The LED behaviour depends on the detected press type:

- **Short press:** Toggles the current LED state.
- **Long press:** Enables blinking mode.
- **Short press during blinking:** Disables blinking and turns the LED OFF.

### 4. Non-Blocking Blinking

Blinking is implemented using elapsed-time checks rather than blocking delays.

`HAL_GetTick()` tracks the time since the previous LED toggle. Once 300 ms has elapsed, the LED state is updated using `HAL_GPIO_TogglePin()`.

This allows the firmware to continue monitoring button input while blinking is active.

## State Variables

| Variable | Purpose |
|---|---|
| `lastRaw` | Previous raw switch reading |
| `stableState` | Last accepted debounced state |
| `blinking` | Indicates whether blinking mode is active |
| `lastChangeTick` | Timestamp of the most recent raw input change |
| `pressStart` | Starting timestamp of a valid button press |
| `lastBlink` | Timestamp of the previous LED toggle |

## Clock Configuration

The system clock uses an external High-Speed Oscillator (HSE) with PLL.

| Parameter | Configuration |
|---|---|
| Oscillator Source | HSE |
| PLL Source | HSE |
| PLL Multiplier | ×9 |
| AHB Prescaler | 1 |
| APB1 Prescaler | 2 |
| APB2 Prescaler | 1 |

## Requirements

- STM32 development board
- Push-button switch connected to PA3
- LED connected to PC13
- STM32CubeIDE
- STM32 HAL Library

## Circuit Diagram
<img width="1024" height="559" alt="image" src="https://github.com/user-attachments/assets/4de50365-9b53-4c26-b605-009ac6a3c3d0" />


## Behaviour

The application uses button press duration to select between two operating modes. Short presses toggle the LED, while long presses activate continuous blinking. A subsequent short press exits blinking mode and turns the LED OFF.

All timing operations are handled through system tick comparisons, allowing button detection and LED control to run concurrently without blocking delays.
