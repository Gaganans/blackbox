"# blackbox" 
# Black Box

## 📌 Project Overview
The Black Box project is a vehicle monitoring and safety system that detects accidents, monitors alcohol levels, records temperature, and sends real-time alerts via GSM. It utilizes GPS for location tracking and an LCD display for local monitoring. The system is designed to enhance road safety by providing automated alerts and emergency responses.

## 🚀 Features
- Alcohol level detection and alerts
- Temperature monitoring to detect overheating
- Accident detection using accelerometer data
- Real-time location tracking via GPS
- GSM-based emergency alert system
- LCD display for local status updates

## 🛠️ Technologies Used
- **Microcontroller:** Arduino
- **Sensors:** Vibration sensor, Alcohol sensor, Temperature sensor, Accelerometer
- **Communication Modules:** GPS, GSM
- **Display:** I2C LCD
- **Software:** Arduino IDE, Embedded C

## 📂 Installation & Setup
1. Clone the repository:
   ```sh
   git clone https://github.com/Gaganans/blackbox.git
   cd blackbox
   ```
2. Install necessary Arduino libraries:
   - `LiquidCrystal_I2C`
   - `SoftwareSerial`
   - `TinyGPS++`
3. Connect all hardware components as per the circuit diagram.
4. Upload the `blackbox.ino` code to the Arduino board using Arduino IDE.
5. Power the system and monitor real-time data on the LCD display.

## 📜 Usage
- The system continuously monitors alcohol levels, temperature, and vibrations.
- In case of an accident or alcohol detection, it sends an alert message via GSM.
- The GPS module retrieves the real-time location and sends it to emergency contacts.
- Data is displayed on the LCD for local monitoring.

## 🤝 Contribution
Contributions are welcome! Feel free to fork the repo and submit a pull request.

## 📞 Contact
For any queries or collaboration, reach out via [GitHub](https://github.com/Gaganans).

---
🛠 **Developed by Gagana** 🚀
