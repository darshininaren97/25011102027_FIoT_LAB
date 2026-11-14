# STM32 GPIO – Debounced Switch-Controlled LED Toggle

A switch-driven LED control application using the STM32 HAL library. The firmware detects valid button presses and toggles an LED connected to PC13, using a software debounce mechanism to prevent multiple triggers caused by mechanical switch bouncing.

Unlike a simple switch-controlled LED, this implementation changes the LED state once per valid press rather than continuously following the switch state.

## Features

- GPIO-based switch input monitoring.
- Software debouncing with a 30 ms stability interval.
- Single toggle per valid button press.
- Non-blocking time tracking using `HAL_GetTick()`.
- LED state control using `HAL_GPIO_TogglePin()`.
- No blocking delay loops for debouncing.

## Hardware Configuration

| Pin | Configuration | Function |
|---|---|---|
| PA3 | Input with Pull-up | Reads switch state |
| PC13 | Output Push-Pull | Controls LED |

## How It Works

The application continuously monitors the switch connected to PA3 and validates input changes before accepting them.

Mechanical switches can produce rapid HIGH and LOW transitions during a press or release. These unwanted transitions are known as *switch bouncing*.

To handle this, the firmware requires the input to remain unchanged for at least **30 milliseconds** before accepting a new state.

### Debouncing Logic

The implementation uses the following variables:

| Variable | Purpose |
|---|---|
| `lastRaw` | Previous raw switch reading |
| `stableState` | Last accepted debounced state |
| `lastChangeTick` | Timestamp of the most recent raw state change |
| `DEBOUNCE_MS` | Required stability interval (30 ms) |

`HAL_GetTick()` provides the system tick count used to measure the stability interval without blocking program execution.

### Input Processing

1. Read the current raw switch state.
2. Detect changes by comparing it with `lastRaw`.
3. If a change occurs, update `lastRaw` and reset the stability timer.
4. Check whether the input has remained unchanged for 30 ms.
5. Accept the new state if the stability condition is satisfied.
6. If the accepted state represents a button press, toggle the LED.
7. Continue monitoring for subsequent presses.

### LED Logic

PC13 is connected to an active-low LED:

| GPIO Output | LED State |
|---|---|
| `GPIO_PIN_RESET` | ON |
| `GPIO_PIN_SET` | OFF |

The LED is toggled using:

```c
HAL_GPIO_TogglePin();
```

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
<img width="1024" height="559" alt="image" src="https://github.com/user-attachments/assets/6565a1da-bdab-4583-a3e2-46ff1efacf5f" />

## Behaviour

Each valid button press toggles the LED exactly once. The 30 ms stability check filters out rapid transitions caused by mechanical switch bouncing, while the non-blocking implementation allows the main loop to continue executing during the debounce interval.
