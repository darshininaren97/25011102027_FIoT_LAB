# STM32 BME280 – Environmental Data Acquisition and MQTT Publishing

This program interfaces a BME280 environmental sensor with an STM32F401RE through I2C1 and publishes the measured temperature, atmospheric pressure and relative humidity to an MQTT broker using an ESP8266 module connected over USART1. Sensor readings are formatted as JSON and transmitted to the MQTT topic at one-second intervals.

## Implementation

The system uses three main components:

- **BME280:** Measures temperature, atmospheric pressure and relative humidity.
- **STM32F401RE:** Handles sensor communication, data processing, JSON formatting and MQTT publishing.
- **ESP8266:** Provides Wi-Fi connectivity and a TCP connection to the MQTT broker.

## Communication Configuration

| Interface | Configuration | Purpose |
|---|---|---|
| I2C1 | 100 kHz, 7-bit addressing | BME280 communication |
| USART1 | 115200 baud, 8-N-1 | STM32–ESP8266 communication |
| MQTT | TCP, port 1883 | Data publishing |

## BME280 Configuration

The sensor is configured using the Bosch BME280 Sensor API.

| Parameter | Configuration |
|---|---|
| I2C Address | `0x76` |
| Temperature Oversampling | 1x |
| Pressure Oversampling | 1x |
| Humidity Oversampling | 1x |
| Filter | Disabled |
| Standby Time | 1000 ms |
| Operating Mode | Normal |

The STM32 HAL I2C functions are connected to the BME280 API through custom read, write and delay callback functions.

## JSON Data Formatting

The sensor measurements are converted into a JSON payload containing three fields:

```json
{
  "temperature": 27.45,
  "pressure": 1008.23,
  "humidity": 55.12
}
```

- Temperature is represented in °C.
- Pressure is converted from Pa to hPa.
- Humidity is represented as relative humidity (%RH).
- Measurements are formatted to two decimal places.

The `formatFixed2()` function handles decimal formatting using integer arithmetic, avoiding the need to enable floating-point support in `printf`.

## MQTT Configuration

| Parameter | Value |
|---|---|
| Broker | `broker.emqx.io` |
| Port | `1883` |
| Client ID | `STM32_da` |
| Topic | `stm32/da` |
| QoS | 0 |
| Publish Interval | 1000 ms |
| Keep Alive | 500 seconds |
| Session | Clean Session |

The ESP8266 is initialized in station mode, connected to the configured Wi-Fi network and then connected to the MQTT broker through TCP.

The MQTT connection is established using the MQTT functions provided by `ESPLib.h`.

## How It Works

1. Initializes the STM32 HAL, system clock, GPIO, I2C1 and USART1.
2. Initializes the BME280 sensor and configures its measurement settings.
3. Initializes the ESP8266 in station mode.
4. Connects the ESP8266 to the Wi-Fi network.
5. Establishes a TCP connection to the MQTT broker.
6. Performs the MQTT connection handshake using the configured client ID and keep-alive settings.
7. Uses `HAL_GetTick()` to maintain a one-second publishing interval.
8. Reads temperature, pressure and humidity from the BME280.
9. Formats the measurements into a JSON payload.
10. Publishes the payload to the configured MQTT topic using QoS 0.

## Key Functions

| Function | Purpose |
|---|---|
| `user_i2c_read()` | Reads BME280 registers through I2C1 |
| `user_i2c_write()` | Writes to BME280 registers through I2C1 |
| `user_delay_us()` | Provides the delay callback required by the BME280 API |
| `formatFixed2()` | Formats numerical values to two decimal places |
| `buildJson()` | Constructs the JSON payload |
| `ESP8266_Init()` | Initializes the ESP8266 |
| `ESP8266_wifiConnect()` | Connects to the Wi-Fi network |
| `ESP8266_portConnect()` | Establishes the TCP connection to the broker |
| `MQTT_connectBroker()` | Performs the MQTT connection handshake |
| `MQTT_publishTopic()` | Publishes sensor data to the MQTT topic |
| `HAL_GetTick()` | Maintains the periodic publishing interval |

## Hardware Connections

| Module | Pin | STM32F401RE |
|---|---|---|
| BME280 | VCC | 3.3V |
| BME280 | GND | GND |
| BME280 | SCL | PB8 (I2C1_SCL, if configured in CubeMX) |
| BME280 | SDA | PB9 (I2C1_SDA, if configured in CubeMX) |
| ESP8266 | TX | PA10 (USART1_RX) |
| ESP8266 | RX | PA9 (USART1_TX) |
| ESP8266 | GND | GND |

The ESP8266 requires a suitable 3.3V power supply capable of handling its current demand.

## Software & Tools

- STM32CubeIDE
- STM32 HAL Library
- Bosch BME280 Sensor API
- ESP8266 library (`ESPLib.h`)
- MQTT protocol
- Public MQTT broker: EMQX
- STM32F401RE Nucleo board

## Notes

- The MQTT payload is published with QoS 0, so delivery is not acknowledged at the MQTT application level.
- The publishing interval is controlled using `HAL_GetTick()` rather than a blocking one-second delay.
- The code depends on the external `ESPLib.h` implementation for ESP8266 and MQTT operations.
- Replace the Wi-Fi credentials with your own configuration before running the program. Avoid committing real Wi-Fi passwords to a public repository.
