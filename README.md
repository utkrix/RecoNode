
# RecoNode

Reconnaissance with NodeMCU and Ultrasonic Sensor (HC-SR04) with real time notifications from https://ntfy.sh

![Logo](https://docs.ntfy.sh/static/img/ntfy.png)


## Overview
This project utilizes an ESP8266 microcontroller and an ultrasonic sensor to detect nearby objects. When an object is detected within a specified range, it sends an alert message over Wi-Fi.

## Requirements
- Arduino IDE
- ESP8266WiFi library
- ESP8266HTTPClient library
- WiFiClientSecure library

## Circuit Diagram
  ![Circuit](https://i.imgur.com/42qE4FQ.png)

## Installation
1. Clone this repository.
2. Open the project in Arduino IDE / VS CODE.
3. Install the required libraries if not already installed:
   - ESP8266WiFi
   - ESP8266HTTPClient
   - WiFiClientSecure
4. Update the following variables in `main.cpp`(/src): 
   - `ssid`: Your Wi-Fi network name.
   - `password`: Your Wi-Fi password.
   - Adjust `echoPin` and `trigPin` if your sensor is connected to different GPIO pins.
   - Adjust `http.begin` and `payload` with your ntfy.sh topic and your message.

## Usage
1. Upload the sketch to your ESP8266 board.
2. Open the Serial Monitor to view sensor readings and debug messages.
3. Ensure the board connects to Wi-Fi successfully.
4. Observe the board's behavior when objects are detected within 20 cm of the sensor.

