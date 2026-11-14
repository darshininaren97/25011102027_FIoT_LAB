# Hyper-Local Moisture Advisory and Mold Prevention System

## Overview

This implementation combines an STM32-based environmental sensing system with a Node-RED dashboard to monitor indoor atmospheric conditions and compare them with real-time outdoor weather data.

A BME280 sensor connected to the STM32 collects indoor temperature, humidity and atmospheric pressure. The STM32 processes the sensor readings, formats them into a JSON payload and transmits them through an ESP8266 Wi-Fi module using MQTT.

Node-RED receives the MQTT data and retrieves outdoor weather information from the OpenWeatherMap API. By comparing indoor and outdoor atmospheric conditions, the system generates moisture-related recommendations to help reduce indoor dampness, condensation and potential mold development.

The dashboard presents the measurements, derived parameters, environmental risk indicators and ventilation recommendations through a dynamically updating web interface.

## System Architecture

The implementation consists of two interconnected sections:

### 1. STM32-Based Environmental Data Acquisition

**Hardware and technologies:**
- STM32 microcontroller
- BME280 environmental sensor
- ESP8266 Wi-Fi module
- I2C communication
- UART communication
- MQTT protocol
- STM32 HAL

**Working:**

1. The BME280 sensor communicates with the STM32 through I2C1.
2. The STM32 initializes the sensor using the BME280 Sensor API.
3. Temperature, humidity and pressure measurements are periodically acquired.
4. The pressure measurement is converted from Pa to hPa.
5. The readings are formatted into a JSON payload.
6. The ESP8266 establishes a Wi-Fi connection and opens a TCP connection to the MQTT broker.
7. An MQTT connection is established, and the sensor data is published to the configured topic at one-second intervals.

**MQTT Configuration:**

| Parameter | Configuration |
|---|---|
| Broker | broker.emqx.io |
| Port | 1883 |
| Protocol | MQTT |
| Client ID | STM32_da |
| Topic | stm32/da |
| QoS | 0 |
| Publishing interval | 1000 ms |

**JSON Payload Format:**

```json
{
  "temperature": 27.45,
  "pressure": 1008.23,
  "humidity": 55.12
}
```

### 2. Node-RED Moisture Advisory Dashboard

Node-RED acts as the data processing and visualization layer. It receives indoor sensor readings through MQTT and retrieves outdoor weather information using the OpenWeatherMap API.

**Technologies:**
- Node-RED
- MQTT
- OpenWeatherMap Current Weather API
- OpenWeatherMap Forecast API
- JavaScript
- HTML and CSS
- HTTP endpoints

**Data Acquisition:**

- Indoor sensor readings are received through the `stm32/da` MQTT topic.
- Only the latest valid indoor sensor reading is retained.
- Outdoor current weather data is retrieved every 10 minutes.
- Outdoor forecast data is retrieved every 30 minutes.
- The forecast contains eight three-hourly time steps, covering approximately 24 hours.

The dashboard retrieves processed information through HTTP endpoints and refreshes its displayed data every 10 seconds.

**Dashboard URL:**

`http://localhost:1880/board`

## Environmental Analysis

The system uses indoor sensor measurements and outdoor weather information to derive additional parameters for environmental assessment.

### 1. Absolute Humidity

Absolute humidity estimates the actual mass of water vapour present in a unit volume of air.

It is used to compare indoor and outdoor moisture content more meaningfully than relative humidity alone.

The calculation uses temperature and relative humidity to estimate water vapour content in g/m³.

### 2. Dew Point

The dew point is calculated for indoor and outdoor air conditions.

It helps estimate the temperature at which water vapour begins condensing into liquid water.

### 3. Indoor and Outdoor Moisture Comparison

The difference between indoor and outdoor absolute humidity is used to determine whether introducing outdoor air is likely to reduce or increase indoor moisture.

This forms the basis of the ventilation recommendation.

### 4. Condensation Assessment

The dashboard estimates condensation risk by comparing the indoor dew point with an adjustable assumed surface temperature.

The surface temperature can be modified through the dashboard to observe how the condensation margin changes.

### 5. Wood Equilibrium Moisture Content

The implementation also estimates the equilibrium moisture content of wood using the Hailwood-Horrobin equation.

This provides an additional environmental indicator for assessing whether prolonged humidity conditions may affect wooden furniture and musical instruments.

### 6. Outdoor Pressure Trend

Outdoor atmospheric pressure changes are examined using forecast data to identify significant predicted pressure rises or drops.

## Mold Risk Assessment

A rule-based scoring mechanism evaluates indoor environmental conditions using a maximum score of 6.

The scoring considers:

| Parameter | Condition | Score |
|---|---|---|
| Relative humidity | 60%–69% | +1 |
| Relative humidity | 70%–79% | +2 |
| Relative humidity | 80% or higher | +3 |
| Dew point | 22°C or higher | +1 |
| Condensation margin | Below 2°C | +1 |
| Condensation margin | 0°C or lower | +2 |

The resulting score is mapped to four advisory levels:

- Low mold risk
- Worth watching
- Mold risk is rising
- Mold conditions are present

A hysteresis mechanism is incorporated into the risk-level transitions to reduce unnecessary fluctuations when measurements are close to scoring thresholds.

The score is an environmental advisory indicator, not a direct measurement or prediction of mold growth.

## Ventilation Recommendations

The system generates recommendations based on indoor and outdoor moisture conditions.

Examples include:

- **Open the windows:** When outdoor air contains significantly less moisture than indoor air and it is not raining.
- **Keep windows closed:** When outdoor air contains more moisture or rain is detected.
- **Ventilation changes little:** When indoor and outdoor absolute humidity are approximately equal.
- **Mechanical dehumidification:** When indoor humidity is elevated and outdoor ventilation is unsuitable.
- **Best time to ventilate:** Identifies a suitable upcoming forecast interval when outdoor air is expected to contain less moisture.

## Dashboard Features

The web dashboard provides:

- Live indoor and outdoor sensor status.
- Indoor and outdoor temperature and relative humidity.
- Absolute humidity comparison.
- Dew point comparison.
- Mold risk score and contributing factors.
- Ventilation recommendations.
- Adjustable surface-temperature assessment.
- Condensation margin analysis.
- Wood equilibrium moisture assessment.
- Outdoor weather forecast visualization.
- Forecast-based ventilation opportunities.
- Outdoor atmospheric pressure trend.
- Detailed numerical comparison table.
- Mathematical explanations of derived parameters.
- Dynamic weather-responsive backgrounds and visual elements.
- Automatic data refresh every 10 seconds.
- Sensor and API connectivity status indicators.

## Software and Dependencies

**STM32 Firmware**
- STM32CubeIDE
- STM32 HAL Drivers
- BME280 Sensor API
- ESPLib
- ESP8266 AT-command-compatible firmware

**Node-RED**
- Node-RED
- MQTT input node
- HTTP request node
- Function node
- Template node
- HTTP input and response nodes

**External Service**
- OpenWeatherMap API

## Setup and Execution

### STM32 Firmware

1. Open the STM32 project in STM32CubeIDE.
2. Configure the BME280 sensor on I2C1.
3. Connect the ESP8266 to USART1.
4. Include the required BME280 Sensor API and ESPLib files.
5. Configure the Wi-Fi credentials and MQTT broker details in the firmware.
6. Build and flash the firmware onto the STM32.
7. Verify that sensor readings are being published to the MQTT topic.

### Node-RED Dashboard
<img width="847" height="507" alt="Screenshot 2026-11-14 140139" src="https://github.com/user-attachments/assets/257a7442-29bf-486b-8f9e-02b787770b1b" />


1. Install and run Node-RED.
2. Import the provided Node-RED flow JSON.
3. Configure the MQTT broker connection.
4. Open the Moisture Advisory flow tab.
5. Navigate to **Properties → Environment variables**.
6. Set `OWM_KEY` to your OpenWeatherMap API key.
7. Set `OWM_CITY` to the desired city (default: Chennai).
8. Deploy the flow.
9. Open the dashboard in a browser:

   `http://localhost:1880/board`

## Notes

- The STM32 and Node-RED must connect to the same MQTT broker.
- The MQTT topic configured in the firmware and Node-RED must match.
- The OpenWeatherMap API key must be configured separately in Node-RED.
- Indoor sensor readings are considered offline if no new reading is received for more than three minutes.
- Outdoor weather data has its own freshness validation.
- The assumed surface temperature is adjustable and is not directly measured by the BME280.
- The system provides environmental guidance based on measured and retrieved atmospheric conditions; it does not directly detect mold or measure wall moisture.

## Learning Outcomes

- Interfacing an environmental sensor with an STM32 microcontroller using I2C.
- Implementing UART communication with an ESP8266 Wi-Fi module.
- Establishing MQTT communication and publishing structured JSON data.
- Integrating embedded sensor data with Node-RED.
- Retrieving external environmental data through REST APIs.
- Processing and comparing indoor and outdoor environmental parameters.
- Implementing rule-based environmental assessment and recommendation logic.
- Developing a dynamic web dashboard using HTML, CSS and JavaScript.
- Understanding the practical integration of embedded systems, networking and IoT-based data visualization.
