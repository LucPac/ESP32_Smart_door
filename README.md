<div align="center">
  <h1>🚪✨ Smart Door with ESP32 and Blynk ✨🚪</h1>
  <p>
    <img src="https://img.shields.io/badge/Microcontroller-ESP32-blueviolet?style=for-the-badge&logo=espressif&logoColor=white" alt="ESP32 Badge">
    <img src="https://img.shields.io/badge/Platform-Blynk-brightgreen?style=for-the-badge&logo=blynk&logoColor=white" alt="Blynk Badge">
    <img src="https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++ Badge">
  </p>

  ---

  <p>
    <a href="#🚀-overview">Overview</a> •
    <a href="#🛠️-installation-and-usage-guide">Installation and Usage Guide</a> •
    <a href="#⚙️-blynk-setup">Blynk Setup</a> •
    <a href="#🚩-final-product">Final Product</a>
  </p>

  ---
</div>

<br>

## 🚀 Overview

Welcome to the **`ESP32_Smart_door`** repository!

This project provides a complete solution for building a smart door system that allows you to control the opening/closing and monitor the door status from anywhere through the Blynk mobile app. Using the powerful ESP32 microcontroller, this project combines hardware and software to bring convenience and security to your home.

<br>

## 🛠️ Installation and Usage Guide

To set up this project, you need the following software and hardware components:

### Software Requirements:
* VS Code
* PlatformIO IDE Extension
* Blynk App (Android/iOS)

### Hardware Requirements:
* ESP32
* Servo SG90 (Door simulator)
* 4x4 Keypad Matrix
* Breadboard, jumper wires or design PCB and solder the circuit

### Basic Steps:

* Install VS Code and PlatformIO IDE Extension
* Clone or download the repository
    ```bash
    git clone https://github.com/your-username/ESP32_Smart_door.git
    ```
* Open the project in VS Code with PlatformIO
* Configure Blynk and WiFi information (see below)
* Compile and upload the code
* Set up the Blynk app
* Connect the hardware

   ![Image](https://github.com/user-attachments/assets/11b66dff-b35e-4c9a-ab23-a85c969d9280)
<br>

## ⚙️ Blynk Setup

To make the project work, you need to configure your Blynk account and project.

### 1. Create a new project on Blynk Console
* Go to [Blynk Console](https://blynk.cloud/) and create an account (if you don't have one).
* Create a **New Template** for the "Smart Door" project.
* Write down the **Template ID** and **Template Name**.
* When creating a new device from this Template, you will receive an **Auth Token**.

### 2. Update the information in the source code
In the `src/main.cpp` file, you need to replace the following placeholders with your information:
* Enter your Blynk information in the blank spaces.
* Next, enter your WiFi name and password.
```cpp
#define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_DEVICE_NAME "YOUR_BLYNK_TEMPLATE_NAME" // Your device name
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

char ssid[] = "YOUR_WIFI_SSID";     // Your WiFi network name
char pass[] = "YOUR_WIFI_PASSWORD"; // Your WiFi password
```

### 3. Set up Datastreams on Blynk app
* Set up a virtual switch Control Pass to allow or deny password entry.
* Set up a virtual switch Control Door to open/close the door remotely.
* You need to create corresponding Datastreams on the Blynk app to control and monitor the door

**Control Door**: Used to control door opening/closing.  
**Control Pass**: Used to allow or deny password entry.

![Image](https://github.com/user-attachments/assets/fcbd7521-018a-412e-ab2a-13345259e6de)

### 4. Set up Events & Notifications on Blynk
* Set up to receive notifications when the door opens and when the wrong password is entered too many times.
  
**door_warning**: Receive notification when wrong password is entered too many times.  
**infor_log**: Receive notification when the door opens.

![Image](https://github.com/user-attachments/assets/4ab1b57e-5ace-4121-b9c9-64a33b7e6cba)
<br>

## 🚩 Final Product  

* PCB

![image](https://github.com/user-attachments/assets/8b5fd353-5e9b-4ee1-b4e6-18378d0c0ba5)

![image](https://github.com/user-attachments/assets/e3680863-935d-402b-8ed2-0ffe2a3997a8)

* Product Images  
  
![Image](https://github.com/user-attachments/assets/4d81e4d7-fea2-4c3e-aadd-f5422bfd31a5)  

![Image](https://github.com/user-attachments/assets/b90fe5ab-9323-43b3-8db6-f412df51777b)  

![Image](https://github.com/user-attachments/assets/1ec14359-2239-489c-9ed6-a1922a23d178)  

* Product Demo Video  

[![Image](https://github.com/user-attachments/assets/3ac83cd1-7f86-4c51-a952-ec393e816f73)](https://youtu.be/4SuPDmZ4MYU)

<br>

---

<div align="center">
  <br>
  <p>Thank you for visiting! I hope this repository is useful for your learning and research. 😊</p>
  </div>
