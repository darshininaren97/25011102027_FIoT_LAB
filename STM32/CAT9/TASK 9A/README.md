# Task 9A – UART Data Transmission and Reception using STM32

## Aim
To establish UART serial communication using the STM32 microcontroller, receive a single byte of data through USART2, and transmit the received byte back to the sender.

## Hardware Requirements
- STM32 development board
- USB-to-UART converter or serial communication interface
- Computer with a serial terminal (such as PuTTY)

## UART Configuration

| Parameter | Configuration |
|---|---|
| Peripheral | USART2 |
| Baud Rate | 115200 |
| Word Length | 8 bits |
| Stop Bits | 1 |
| Parity | None |
| Mode | Transmitter and Receiver |
| Hardware Flow Control | None |
| Oversampling | 16 |

## Working Principle

The program implements a UART echo operation.

1. The STM32 waits for one byte of data to arrive through USART2.
2. `HAL_UART_Receive()` receives the byte and stores it in the variable `cmd`.
3. `HAL_UART_Transmit()` sends the same byte back through USART2.
4. The process repeats continuously inside the infinite loop.

This allows any character received by the STM32 to be echoed back to the serial terminal.

## UART Functions Used

### `HAL_UART_Receive()`

```c
HAL_UART_Receive(&huart2, &cmd, 1, HAL_MAX_DELAY);
```

- Receives data through USART2.
- Stores the received byte in `cmd`.
- Receives one byte at a time.
- `HAL_MAX_DELAY` makes the function wait until data is received.

### `HAL_UART_Transmit()`

```c
HAL_UART_Transmit(&huart2, &cmd, 1, HAL_MAX_DELAY);
```

- Transmits the received byte through USART2.
- Sends one byte at a time.
- Uses blocking transmission until the operation is complete.

## Program Flow

1. Initialize the HAL library.
2. Configure the system clock.
3. Initialize GPIO and USART2.
4. Wait for a byte to be received through UART.
5. Store the received byte in `cmd`.
6. Transmit the same byte back to the sender.
7. Repeat the receive-and-transmit process continuously.

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
- PuTTY or another serial terminal application

## Key Concepts Demonstrated
- UART serial communication
- USART2 peripheral configuration
- UART data reception and transmission
- Byte-by-byte communication
- Blocking UART communication
- STM32 HAL UART functions
- Serial terminal interfacing

## Observation

The STM32 successfully receives a character through USART2 and transmits the same character back to the sender. This demonstrates basic two-way UART communication using a receive-and-echo mechanism.
