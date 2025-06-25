# 🤖 Voice-Enabled Smart Glove for Assistive Communication

A wearable IoT-based glove that detects hand gestures using **flex sensors** and an **MPU6050** IMU and converts them into **real-time speech** using **Python Text-to-Speech (TTS)**. This glove is aimed at enhancing communication for speech-impaired individuals and can also be used in gesture-based control systems.

---

## 🛠️ Features

- 🔍 Real-time gesture recognition using flex sensors (bending detection)
- 🎯 Orientation tracking using MPU6050 (pitch & roll angles)
- 📢 Text-to-speech voice output using Python and `pyttsx3`
- ⚡ Shake detection using accelerometer data
- 💬 Recognizes gestures like:
  - Hello
  - Water
  - OK
  - Good
  - Washroom
  - Peace
  - Medicine
  - Stop
  - Hungry
  - Sleep
  - Shake

---

## 🧰 Components Used

| Component           | Description                             |
|--------------------|-----------------------------------------|
| Flex Sensors (x4)   | Detect finger bending                   |
| MPU6050            | Accelerometer + Gyroscope for motion sensing |
| Arduino UNO/Nano   | Microcontroller                         |
| Python + pyttsx3   | For speech output via PC                |
| Jumper wires, glove| For mounting and connections            |

---

## 🔌 Circuit Diagram

📷 *[Insert image of your schematic or physical setup here]*

---

## 📋 How It Works

1. **Flex sensors** measure the bend in fingers and output analog values.
2. **MPU6050** provides pitch and roll data to enhance gesture accuracy.
3. Arduino reads all sensor data and sends gesture information via serial.
4. A **Python script** reads the serial output and uses **TTS** to speak the gesture aloud.

---

## 🚀 Getting Started

### ✅ Arduino Side

1. Upload the Arduino code from [`gesture_glove.ino`](gesture_glove.ino).
2. Connect the flex sensors to A0–A3 and MPU6050 to SDA/SCL.

### ✅ Python Side

1. Install Python 3 and required library:
   ```bash
   pip install pyttsx3 pyserial
