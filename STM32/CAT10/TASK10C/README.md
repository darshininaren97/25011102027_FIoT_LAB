# Experiment: STM32 UART Communication with ESP8266 Using AT Commands

## Aim
To establish UART communication between an STM32 microcontroller and a Wemos D1 Mini (ESP8266) module, configure the ESP8266 to connect to a Wi-Fi network using AT commands, and retrieve its assigned IP address and connection status.

## Hardware Requirements
- STM32F401RE Development Board
- Wemos D1 Mini (ESP8266)
- USB-to-Serial Interface
- Jumper Wires

## Software Requirements
- STM32CubeIDE
- STM32 HAL Library
- PuTTY (Serial Terminal)

## Communication Configuration

| Parameter | USART1 | USART2 |
|---|---|---|
| Purpose | STM32–ESP8266 communication | Serial debugging |
| Baud Rate | 115200 | 115200 |
| Data Bits | 8 | 8 |
| Stop Bits | 1 | 1 |
| Parity | None | None |
| Mode | TX/RX | TX/RX |

## Working Principle

The STM32 communicates with the ESP8266 through USART1 using AT commands. The responses received from the ESP8266 are forwarded byte by byte through USART2 and displayed on a serial terminal.

A `send()` function is implemented to transmit AT commands and receive responses with a specified timeout.

The program performs the following operations:

1. Initializes the HAL library and configures the system clock.
2. Initializes USART1 and USART2.
3. Waits for 2 seconds to allow the ESP8266 module to boot.
4. Transmits the `AT` command to verify communication.
5. Configures the ESP8266 in Station mode using `AT+CWMODE=1`.
6. Connects to the specified Wi-Fi network using `AT+CWJAP`.
7. Retrieves the assigned IP address using `AT+CIFSR`.
8. Checks the network connection status using `AT+CIPSTATUS`.
9. Forwards the ESP8266 responses to the serial terminal through USART2.

## AT Commands Used

| Command | Description |
|---|---|
| `AT` | Tests communication with the ESP8266 |
| `AT+CWMODE=1` | Configures Wi-Fi Station mode |
| `AT+CWJAP` | Connects to a specified Wi-Fi network |
| `AT+CIFSR` | Retrieves the assigned IP address |
| `AT+CIPSTATUS` | Checks the current network connection status |

## Hardware Connections

**STM32 to ESP8266**

| STM32 | Wemos D1 Mini |
|---|---|
| USART1 TX | RX |
| USART1 RX | TX |
| GND | GND |

USART2 is used for serial debugging through the STM32 serial interface.

**Note:** Ensure that the ESP8266 receives a suitable 3.3 V supply and that UART logic levels are compatible.

## Expected Output

The serial terminal displays the responses returned by the ESP8266, including:

- `OK` responses for successful AT commands.
- Wi-Fi connection confirmation.
- Local IP address assigned by the router.
- Current network connection status.


## Technical Specifications

- **Microcontroller:** STM32F401RE
- **Wi-Fi Module:** ESP8266 (Wemos D1 Mini)
- **Communication Protocol:** UART
- **Command Interface:** ESP8266 AT Commands
- **Programming Language:** Embedded C
- **Peripheral Library:** STM32 HAL
- **Development Environment:** STM32CubeIDE
