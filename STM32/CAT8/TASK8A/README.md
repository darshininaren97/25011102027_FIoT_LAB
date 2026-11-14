# Task 8A – LED Follows Switch (STM32)

## Aim
To interface a switch with an STM32 microcontroller and control an LED based on the switch input using the STM32 HAL library.

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

The program continuously reads the state of the switch connected to PA3.

- **Switch pressed:** PA3 reads LOW (`GPIO_PIN_RESET`), so the LED is turned ON.
- **Switch released:** PA3 reads HIGH (`GPIO_PIN_SET`), so the LED is turned OFF.

The LED connected to PC13 is active-low. Therefore:
- Writing `GPIO_PIN_RESET` turns the LED ON.
- Writing `GPIO_PIN_SET` turns the LED OFF.

The LED is initialized to the OFF state before entering the infinite loop.

## Program Flow

1. Initialize the HAL library.
2. Configure the system clock.
3. Initialize GPIO pins.
4. Set PC13 HIGH to keep the LED OFF initially.
5. Continuously read the switch state at PA3.
6. Turn the LED ON when the switch is pressed and OFF when it is released.

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
- Reading digital input using `HAL_GPIO_ReadPin()`
- Controlling an LED using `HAL_GPIO_WritePin()`
- Internal GPIO pull-up configuration
- Active-low LED operation
- Continuous polling using an infinite loop

## Observation

The LED follows the state of the switch: it remains ON while the switch is pressed and turns OFF when the switch is released.
