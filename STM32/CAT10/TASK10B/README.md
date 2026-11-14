# STM32–ESP8266 UART Communication and Wi-Fi Configuration

## Aim
To establish UART communication between an STM32 microcontroller and a Wemos D1 Mini (ESP8266) module using AT commands, configure the ESP8266 as a Wi-Fi station, and verify its network connection through UART responses.

## Hardware Requirements
- STM32F401RE development board
- Wemos D1 Mini (ESP8266)
- USB-to-Serial connection / ST-LINK
- Jumper wires
- Wi-Fi network

## Software Requirements
- STM32CubeIDE
- STM32 HAL Library
- Serial terminal (PuTTY or equivalent)

## Working Principle

The STM32 communicates with the ESP8266 using UART1 at a baud rate of 115200 bps. AT commands are transmitted to the ESP8266, and its responses are received byte by byte.

UART2 is used as a debugging interface to display the responses received from the ESP8266 on a serial terminal.

The program performs the following operations:

1. Initializes the STM32 HAL library and system clock.
2. Initializes USART1 and USART2, both configured at 115200 baud.
3. Introduces a 2-second delay to allow the ESP8266 module to boot.
4. Sends `AT` to check communication with the ESP8266.
5. Sends `AT+CWMODE=1` to configure the ESP8266 in Station mode.
6. Sends `AT+CWJAP` with the Wi-Fi SSID and password to connect to the wireless network.
7. Sends `AT+CIFSR` to retrieve the assigned IP address.
8. Sends `AT+CIPSTATUS` to check the current network connection status.
9. Displays the received responses through USART2.

## UART Configuration

| Parameter | USART1 | USART2 |
|---|---|---|
| Purpose | ESP8266 communication | Serial debugging |
| Baud Rate | 115200 | 115200 |
| Word Length | 8 bits | 8 bits |
| Stop Bits | 1 | 1 |
| Parity | None | None |
| Mode | TX/RX | TX/RX |

## AT Commands Used

| AT Command | Function |
|---|---|
| `AT` | Tests communication with ESP8266 |
| `AT+CWMODE=1` | Sets Wi-Fi Station mode |
| `AT+CWJAP` | Connects to the specified Wi-Fi network |
| `AT+CIFSR` | Retrieves the assigned IP address |
| `AT+CIPSTATUS` | Displays the current connection status |

## Hardware Connections

- STM32 USART1 TX → ESP8266 RX
- STM32 USART1 RX → ESP8266 TX
- STM32 GND → ESP8266 GND
- STM32 USART2 is connected to the serial debugging interface.

**Note:** Ensure compatible logic voltage levels and a suitable power supply for the ESP8266.

## Expected Output

The serial terminal displays the responses returned by the ESP8266, including:

- `OK` for successful AT command execution.
- Wi-Fi connection status.
- Assigned local IP address.
- Current TCP/IP connection status.


## Implementation Details

- Microcontroller: STM32F401RE
- Communication Protocol: UART
- ESP8266 Interface: AT Commands
- Programming Language: Embedded C
- Development Environment: STM32CubeIDE
- Peripheral Library: STM32 HAL
