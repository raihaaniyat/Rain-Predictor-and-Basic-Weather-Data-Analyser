# 🌧️ Rainfall Prediction Using Arduino

This project predicts **rainfall** using an **Arduino-based weather station** by collecting real-time **temperature, humidity, and air pressure** data from sensors. It also integrates with **Blynk** for remote monitoring.

## 📌 Features
- Collects **temperature, humidity, and air pressure** data using sensors.
- Uses a **rainfall prediction algorithm** based on weather parameters.
- **Wi-Fi connectivity** for real-time data monitoring via **Blynk**.
- Displays sensor data on an **LCD screen (optional)**.

## 🛠️ Hardware Requirements
- **Arduino Board** (e.g., Arduino Uno, ESP8266, or ESP32)
- **DHT11/DHT22** (Temperature & Humidity Sensor)
- **BMP180/BMP280** (Barometric Pressure Sensor)
- **Wi-Fi Module** (ESP8266 or built-in ESP32 Wi-Fi)
- **LCD Display** (Optional, for local display)
- **Jumper Wires & Breadboard**
##NOTE: If you want to use blynk, ESP32 is your go-to soluton. Arduino Uno doesn't offer wifi facilities. 

## 💻 Software Requirements
- **Arduino IDE** (with necessary libraries installed)
- **Blynk App** (for remote monitoring)
- **GitHub** (for version control)

## 📜 Installation & Setup
1. **Clone this repository:**
   ```bash
   git clone https://github.com/your-username/rain-predictor-and-Basic-Weather-Data-Analyser.git
   cd rain-predictor-and-Basic-Weather-Data-Analyser
   ```
2. **Install required libraries in Arduino IDE:**
   - `Adafruit BMP280 Library`
   - `DHT sensor library`
   - `Blynk Library`
3. **Upload the code to Arduino** and configure Blynk settings.

## 📊 Data Monitoring via Blynk
- Set up a **Blynk project**.
- Add widgets for **temperature, humidity, and pressure**.
- Use a **chart widget** to visualize trends.

## 📈 Rainfall Prediction Algorithm
The algorithm analyzes **humidity**, **temperature**, and **pressure trends** to determine rainfall probability. Example logic:
- **High humidity (>80%)** + **Low pressure (<1000 hPa)** → High chance of rain 🌧️.
- **Stable pressure** + **Moderate humidity** → No rain ☀️.

## 🤝 Contributing
Feel free to **fork** this repository and contribute by improving the prediction algorithm or adding new features.

## 📜 License
This project is licensed under the **MIT License**.
