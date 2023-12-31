# ESP32 ChatGPT Implementation

Welcome to the ESP32 ChatGPT Implementation project! This project enables you to create an ESP32 device that interacts with the ChatGPT server, delivering an intuitive touch interface experience on an LCD screen. Dive into the world of AI communication through a user-friendly setup.

*Warning: Messy codebase ahead, proceed with caution! :)*

<p align="center">
<img src="/images/overview.jpg" alt="Project overview" width="800"> <img src="/images/chatgpt.png" alt="GPT icon" width="300">
</p>

## Features

- Utilizes ESP32 and LCD for a tactile ChatGPT experience.
- Customizable configurations via `configs.h`.
- Seamless interactions through a touch-enabled interface.

## Hardware Requirements

- ESP32 development board (I used Waveshare ESP32 S3-Pico).
- LCD display (I am currently using a 2.4inch touch TFT display with driver ILI9341).

 ### LCD (2.4 inch TFT touch ILI9341)

<p align="center">
<img src="/images/lcd.jpg" alt="LCD Close-up" width="300">
</p>

 ### ESP32 S3-PICO

<p align="center">
<img src="/images/esp32_front.jpg" alt="ESP32 Controller" width="370"> <img src="/images/esp32_pinout.jpg" alt="ESP32 Pinout" width="300">
</p>

## Schematic

  Follow this schematic to wire up the LCD with the ESP32.

  <p align="center">
  <img src="/images/schematicc.png" alt="Schematic" width="500">
  </p>

## Setup Instructions

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/kevinjacb/esp32-chatgpt_llama.git
   cd esp32-chatgpt_llama
   ```

2. **Configure `configs.h`:**
   Modify the `configs.h` file according to your hardware setup:
   - Adjust LCD parameters (width, height, pins).
   - Set up Wi-Fi SSID and password.
   - Define ChatGPT server details.

3. **Build and Flash:**
   Use ESP-IDF tools to build and flash the project to your ESP32 device.
   (for Windows)
   - idf.py build
   - idf.py -p COMX flash 
   - idf.py monitor

5. **Interacting with the Device:**
    Once flashed and all connections are done, the system is ready for use. Queries can be entered using the touchscreen.

## Folder Structure

- `main/`: Contains project source files.
- `main/ui/`: Includes UI files generated by Squareline Studio and modified to fit our use.

## Screenshots / Visuals

  <p align="center">
<img src="/images/demo.jpg" alt="Demo" width="800">
</p>

### YouTube Video

https://www.youtube.com/shorts/8u8_6w0_Zd8


Click the link above to watch the YouTube video demonstrating the project.

## Softwares used:

  - Squareline Studio
