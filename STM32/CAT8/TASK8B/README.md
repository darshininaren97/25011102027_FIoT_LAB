# Task 8B – Debounced LED Toggle (STM32)

## Aim
To interface a switch with an STM32 microcontroller and toggle an LED whenever a valid switch press is detected, using software debouncing to eliminate unwanted multiple triggers caused by switch bouncing.

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

The program continuously monitors the switch connected to PA3.

Mechanical switches may produce multiple rapid HIGH and LOW transitions when pressed or released. This is known as switch bouncing. To avoid registering these transitions as multiple presses, the program implements a software debounce mechanism.

A switch state is accepted only when it remains unchanged for **30 milliseconds**.

- **Valid press:** The LED toggles its current state once.
- **Switch release:** The stable switch state is updated, but the LED does not toggle.
- **Repeated bouncing:** The stability timer restarts whenever a raw switch-state change is detected.

The LED connected to PC13 is active-low:
- `GPIO_PIN_RESET` – LED ON
- `GPIO_PIN_SET` – LED OFF

## Debouncing Logic

The program uses the following variables:

| Variable | Purpose |
|---|---|
| `lastRaw` | Stores the previous raw switch reading |
| `stableState` | Stores the debounced switch state |
| `lastChangeTick` | Stores the tick count when the raw state last changed |
| `DEBOUNCE_MS` | Defines the required stability period (30 ms) |

`HAL_GetTick()` is used to obtain the current system tick count.

The program follows these steps:

1. Read the current switch state.
2. Compare it with the previous raw reading.
3. If a change is detected, update `lastRaw` and restart the stability timer.
4. Check whether the raw state has remained unchanged for at least 30 ms.
5. If the stable state has changed, update `stableState`.
6. If the accepted state represents a press, toggle the LED using `HAL_GPIO_TogglePin()`.

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
- Software switch debouncing
- Non-blocking time-based delay using `HAL_GetTick()`
- Edge/state-change detection
- LED toggling using `HAL_GPIO_TogglePin()`
- Active-low LED operation
- Continuous polling using an infinite loop

## Observation

The LED changes its state exactly once for every valid switch press. The 30 ms debounce interval prevents mechanical switch bouncing from causing multiple unwanted toggles. The program does not use blocking delay functions for debouncing.
