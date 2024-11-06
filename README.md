# Temperature, Humidity, Gas, and Real-Time Wi-Fi Check System

This project uses an Arduino board with a DHT11 sensor, a gas sensor, and real-time Wi-Fi status monitoring. The system reads temperature, humidity, and gas levels and transmits the data to an MQTT broker for real-time monitoring.

## Features

- **Temperature and Humidity**: Measures temperature and humidity using a DHT11 sensor.
- **Gas Detection**: Monitors the gas levels using a gas sensor.
- **Real-Time Wi-Fi Check**: Checks the status of the Wi-Fi connection and transmits the connection status.
- **MQTT Communication**: Sends all sensor data and Wi-Fi status to an MQTT broker.

## Requirements

### Hardware

- Arduino board (e.g., ESP32 or ESP8266)
- DHT11 sensor (for temperature and humidity)
- Gas sensor (e.g., MQ-2 or any other gas sensor)
- Wi-Fi access point
- MQTT Broker (e.g., [broker.emqx.io](https://broker.emqx.io))

### Libraries

- **WiFi.h**: Used for Wi-Fi connection.
- **PubSubClient.h**: MQTT client library.
- **DHT.h**: DHT sensor library.

## Wiring

1. **DHT11 Sensor**:
   - VCC to 3.3V or 5V on the Arduino
   - GND to GND
   - Data pin to digital pin 4 on the Arduino (`DHTPIN`)

2. **Gas Sensor (e.g., MQ-2)**:
   - VCC to 5V
   - GND to GND
   - Output pin to analog pin A0 (`capF`)

3. **Button/Switch (for motion detection, optional)**:
   - VCC to 5V
   - GND to GND
   - Input pin to digital pin 12 (`capm`)

## MQTT Topics

- `t`: Temperature data (Celsius)
- `h`: Humidity data
- `capm`: Motion sensor data
- `wc`: Wi-Fi connection status
- `ip`: Device IP address
- `capF`: Gas sensor data

## How It Works

1. **Wi-Fi Connection**: The system connects to a Wi-Fi network and checks the status.
2. **Sensor Readings** : The DHT11 sensor reads temperature and humidity, while the gas sensor (capF) monitors gas levels.
3. **MQTT Communication** : The system sends the temperature, humidity, gas data, and Wi-Fi status to an MQTT broker in real-time.
4. **Real-Time Monitoring**: The data can be accessed through an MQTT client connected to the same broker.

## Usage

1. **Setup**: Ensure the hardware is properly wired and the Arduino is connected to the Wi-Fi network.
2.**Monitor**: Open an MQTT client to subscribe to the topics and view the data in real-time.
3.**Custom Configuration**: Modify the Wi-Fi credentials and MQTT broker settings as needed.

## Acknowledgments
1. Arduino Community for providing resources for Wi-Fi, MQTT, and sensor interfacing.
2. DHT11 and Gas Sensor Libraries for sensor data handling.
