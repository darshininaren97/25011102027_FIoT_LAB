# Task 9B – UART-Based LED Control using Serial Commands (STM32)

## Aim
To control an LED connected to an STM32 microcontroller using commands received through UART serial communication.

## Hardware Requirements
- STM32 development board
- LED connected to GPIO pin PC13
- Computer with a serial terminal application (such as PuTTY)

## GPIO Configuration

| Pin | Configuration | Function |
|---|---|---|
| PC13 | Output push-pull | Controls the LED |

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

The program receives commands from a serial terminal through USART2 and performs the corresponding LED operation.

Each incoming character is:
1. Received using `HAL_UART_Receive()`.
2. Echoed back to the serial terminal using `HAL_UART_Transmit()`.
3. Stored in a character buffer until a carriage return (`\r`) or newline (`\n`) is received.

Once a complete command is received, the program compares it with the supported commands using `strcmp()`.

## Supported Commands

| Command | Operation |
|---|---|
| `LED ON` | Turns the LED ON |
| `LED OFF` | Turns the LED OFF |
| `LED TOGGLE` | Continuously toggles the LED |
| Any other command | Displays `INVALID` |

### 1. LED ON
When `LED ON` is received, the program writes `GPIO_PIN_RESET` to PC13, turning the active-low LED ON. It then sends the confirmation message:

`LED IS TURNED ON`

### 2. LED OFF
When `LED OFF` is received, the program writes `GPIO_PIN_SET` to PC13, turning the LED OFF. It then sends:

`LED IS TURNED OFF`

### 3. LED TOGGLE
When `LED TOGGLE` is received, the program enters a continuous toggling loop.

- The LED changes state every 300 milliseconds using `HAL_GPIO_TogglePin()`.
- `HAL_Delay(300)` provides the blinking interval.
- The program checks for incoming UART data with a non-blocking receive timeout of zero.
- When a character is received, the toggling loop is exited.

The confirmation message is:

`LED IS TOGGLING`

### 4. Invalid Command
If the received command does not match any supported command, the program transmits:

`INVALID`

## Buffer Handling

The character buffer `c[20]` stores the incoming command.

- Characters are stored one at a time.
- A maximum of 19 characters is accepted, leaving space for the null terminator.
- When a carriage return or newline is received, the buffer is null-terminated.
- `strcmp()` compares the completed command with the supported command strings.
- The buffer index is reset after command processing.

## Program Flow

1. Initialize the HAL library.
2. Configure the system clock.
3. Initialize GPIO and USART2.
4. Receive characters from the serial terminal.
5. Echo each received character back.
6. Store characters in the command buffer.
7. Detect the end of a command using carriage return or newline.
8. Compare the command with the supported LED commands.
9. Perform the corresponding LED operation and transmit a status message.
10. Continue waiting for the next command.

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
- Command-based control
- Character buffering
- String comparison using `strcmp()`
- String transmission using `HAL_UART_Transmit()`
- UART reception using `HAL_UART_Receive()`
- Blocking and non-blocking UART reception
- GPIO output control
- LED toggling and delay-based blinking

## Observation

The STM32 receives commands through USART2 and controls the LED according to the command entered in the serial terminal. It also provides confirmation messages for valid commands and an invalid-command message for unsupported inputs.
