# STM32 UART Echo – USART2

A basic UART communication implementation using the STM32 HAL library. The program continuously receives a byte through USART2 and transmits the same byte back to the sender, implementing a simple serial echo mechanism.

## Features

- UART communication using USART2.
- Single-byte data reception.
- Immediate echo of received data.
- Continuous receive-and-transmit operation.
- Blocking UART communication using STM32 HAL APIs.

## Configuration

| Parameter | Value |
|---|---|
| Peripheral | USART2 |
| Baud Rate | 115200 |
| Word Length | 8 Bits |
| Stop Bits | 1 |
| Parity | None |
| Mode | Transmit & Receive |
| Hardware Flow Control | None |
| Oversampling | 16 |

## How It Works

The application continuously executes a receive-and-echo cycle:

1. Waits for incoming data through USART2.
2. Receives one byte and stores it in `cmd`.
3. Transmits the received byte back through USART2.
4. Repeats the process indefinitely.

The implementation uses two STM32 HAL functions:

**Data Reception**
```c
HAL_UART_Receive(&huart2, &cmd, 1, HAL_MAX_DELAY);
```

**Data Transmission**
```c
HAL_UART_Transmit(&huart2, &cmd, 1, HAL_MAX_DELAY);
```

Both operations are blocking, meaning execution waits for the respective UART operation to complete.

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
- STM32CubeIDE
- STM32 HAL Library
- USB-to-UART interface (if required by the board setup)
- Serial terminal application such as PuTTY

## Circuit Diagram
<img width="1024" height="559" alt="image" src="https://github.com/user-attachments/assets/42eb53ef-684c-417b-884b-b092e946f92c" />


## Testing

The firmware can be tested using a serial terminal configured with the same UART settings (115200 baud, 8-N-1).

Sending characters through the terminal should result in the STM32 transmitting the same characters back.
