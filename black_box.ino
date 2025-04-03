#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


SoftwareSerial gpsSerial(4, 3);  
SoftwareSerial gsmSerial(7, 8);  
TinyGPSPlus gps;


#define VIBRATION_PIN 2
#define ALCOHOL_PIN A0
#define TEMP_PIN A1
#define ACC_X A2
#define ACC_Y A3
#define ACC_Z A4

// Thresholds
#define ALCOHOL_THRESHOLD 300
#define TEMP_THRESHOLD 50
#define ACCIDENT_THRESHOLD 400

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Vehicle Black Box");

  Serial.begin(9600);
  gpsSerial.begin(9600);
  gsmSerial.begin(9600);

  pinMode(VIBRATION_PIN, INPUT);

  delay(2000);
  lcd.clear();
}

void loop() {
  float temperature = getTemperature();
  int alcoholLevel = analogRead(ALCOHOL_PIN);
  bool vibration = digitalRead(VIBRATION_PIN);
  bool accident = detectAccident();

  displayData(temperature, alcoholLevel);
  readGPS();

  if (alcoholLevel > ALCOHOL_THRESHOLD) {
    sendAlert("Alcohol detected in vehicle!");
  }

  if (temperature > TEMP_THRESHOLD) {
    sendAlert("Vehicle overheating!");
  }

  if (vibration || accident) {
    sendAlert("Accident detected!");
    sendLocation();
  }

  delay(2000);
}


float getTemperature() {
  int tempReading = analogRead(TEMP_PIN);
  return (tempReading * 5.0 * 100.0) / 1024.0; 
}


bool detectAccident() {
  int x = analogRead(ACC_X);
  int y = analogRead(ACC_Y);
  int z = analogRead(ACC_Z);

  if (abs(x - 512) > ACCIDENT_THRESHOLD ||
      abs(y - 512) > ACCIDENT_THRESHOLD ||
      abs(z - 512) > ACCIDENT_THRESHOLD) {
    return true;
  }
  return false;
}


void displayData(float temp, int alcohol) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temp);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Alcohol:");
  lcd.print(alcohol);
}


void sendAlert(String message) {
  gsmSerial.println("AT+CMGF=1"); 
  delay(1000);
  gsmSerial.println("AT+CMGS=\"+91XXXXXXXXXX\"");  
  gsmSerial.println(message);
  gsmSerial.write(26);  
  delay(3000);
}


void sendLocation() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
    if (gps.location.isUpdated()) {
      String locationMsg = "Location: ";
      locationMsg += String(gps.location.lat(), 6);
      locationMsg += ",";
      locationMsg += String(gps.location.lng(), 6);
      sendAlert(locationMsg);
    }
  }
}


void readGPS() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }
}