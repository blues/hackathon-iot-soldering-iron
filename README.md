# Connected Soldering Iron - 2023 Nashville Hackathon

Gone are the days of soldering irons that are not connected to the internet. This is the future. This is the Connected Soldering Iron.

In just a few hours we created this wireless IoT proof of concept.

## Features

- Wireless detection of when the soldering iron is in use
- (Future opportunity) detection and control of parameters, like temperature,
  of the soldering iron

## Hardware

- [Pinecil] Soldering iron running open source IronOS 2.21 for BLE support
- Adafruit [Huzzah32] ESP32 Feather-compatible microcontroller for BLE support
- Blues [Notecard] IoT module for cellular or wifi support
- Blues [Notecarrier F] development board to connect the Notecard to the Huzzah32

## Firmware

- `src/main.c` is the main firmware file that runs on the Huzzah32

## Cloud Software

- Blues [Notehub] to securely receive and route data from the Notecard.
- [Datacake] Low-code IoT platform to visualize the data from the soldering iron.

## Architecture

The Pinecil is running IronOS 2.21, which supports BLE. The Huzzah32 is running
a BLE client that connects to the Pinecil. The Huzzah32 is also running a
Notecard client that sends data over serial to the Notecard through the Notecarrier. The Notecard is connected to Notehub, which is a cloud service that stores the data and routes it to Datacake. Datacake is a low-code IoT platform that visualizes the data.

### Firmware Development

- [Visual Studio Code](https://code.visualstudio.com/) IDE
- [PlatformIO](https://platformio.org/) VSCode extension to manage libraries, builds, programming, and serial monitoring.
- [Arduino](https://www.arduino.cc/) library for ESP32
- [Notecard Arduino Library] for Notecard communication
- [ArduinoBLE] library for Bluetooth Low Energy communication

[Pinecil]: https://wiki.pine64.org/wiki/Pinecil
[Huzzah32]: https://www.adafruit.com/product/3405
[Notecard]: https://blues.io/products/notecard/
[Notecarrier F]: https://blues.io/products/notecarrier/notecarrier-f/
[Notehub]: https://notehub.io/
[Datacake]: https://datacake.co/
[Notecard Arduino Library]: https://www.arduino.cc/reference/en/libraries/blues-wireless-notecard/
[ArduinoBLE]: https://www.arduino.cc/reference/en/libraries/arduinoble/
