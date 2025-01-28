# Cosmic Whisper 2.0
Cosmic Whisper 2.0 is an Arduino-based project that combines RF communication, Wi-Fi functionality, and a piezo buzzer to create an interactive system for transmitting musical notes. It supports wireless broadcasting of notes via RF and UDP and includes a web-based interface for easy interaction.

## Features
- **RF Transmission & Reception**
  - **Transmit Notes**: The system can transmit musical notes via an RF transmitter to other compatible devices.
  - **Receive Notes**: The system listens for incoming RF signals when idle and plays the received notes on a piezo buzzer.
- **Web Interface**
  - A Bootstrap-powered web interface allows users to trigger specific notes (A4, B4, etc.) remotely.
  - Notes triggered via the web interface are played locally and broadcast via RF.
- **UDP Broadcasting**
  - Notes played locally are also broadcast to all devices on the local network via UDP.
- **Visual Feedback**
  - An onboard LED provides visual feedback for both transmissions and receptions.
## Hardware Requirements
- **Arduino MKR WiFi 1010** (or any Wi-Fi-enabled Arduino compatible board).
- **RF Transmitter and Receiver Module**
- **Piezo Buzzer**
- **LED**

## Software Requirements
- **Libraries**: WiFiNINA, RH_ASK, SPI

## Setup
  - Wi-Fi credentials in ```arduino_secrets.h```:
    ```
    #define SECRET_SSID "YourWiFiNetwork"
    #define SECRET_PASS "YourWiFiPassword"
    ```
  - Local UDP port and broadcast IP address (if needed).

## Device
![CW-2 0](https://github.com/user-attachments/assets/daa1d957-4285-4a34-9e31-197d7a9b1a02)

## Interface
![interface](https://github.com/user-attachments/assets/0b4d766e-9b3c-41e0-a3d9-0cce68d6ca69)

## Future Improvements
- Add support for multiple simultaneous note transmissions.
- Integrate a real-time spectrum analyzer for received signals.
- Expand the web interface to include sliders for custom frequencies.
- Enable two-way UDP communication for note acknowledgment.
