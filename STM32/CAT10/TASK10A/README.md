# Experiment: UART Communication Between STM32 and ESP8266 Using HAL

## Objective
To establish UART communication between an STM32 microcontroller and an ESP8266 Wi-Fi module using the STM32 HAL library. The STM32 transmits an AT command to the ESP8266, receives its response, and forwards the received data to a serial terminal through a second UART interface.

## Hardware Requirements
- STM32 microcontroller
- ESP8266 Wi-Fi module
- USB-to-Serial interface
- Jumper wires

## Software Requirements
- STM32CubeIDE
- STM32 HAL Library
- PuTTY (Serial Terminal)

## UART Configuration

| Parameter | USART1 | USART2 |
|---|---|---|
| Baud Rate | 115200 | 115200 |
| Word Length | 8 Bits | 8 Bits |
| Stop Bits | 1 | 1 |
| Parity | None | None |
| Mode | TX and RX | TX and RX |
| Hardware Flow Control | Disabled | Disabled |

## Connections

| STM32 | ESP8266 |
|---|---|
| USART1 TX | RX |
| USART1 RX | TX |
| GND | GND |

USART2 is used to forward received data to the serial terminal for monitoring.

## Working

1. Initialize the HAL library and configure the system clock.
2. Initialize GPIO, USART1 and USART2 peripherals.
3. Transmit the `AT\r\n` command to the ESP8266 through USART1.
4. Receive the ESP8266 response one character at a time using `HAL_UART_Receive()`.
5. Forward each received character through USART2 using `HAL_UART_Transmit()`.
6. Observe the ESP8266 response on the serial terminal.

## Expected Output

```text
AT

OK
```

The ESP8266 should return `OK` if the AT command is successfully received and processed.

## Circuit Diagram
<img width="1024" height="559" alt="image" src="https://github.com/user-attachments/assets/62b2cde7-442d-4569-941f-61761ed2a2c3" />
