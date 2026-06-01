#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SoftwareSerial.h>

#define ADXL345_ADDRESS (0x53) // ADXL345 sensor I2C address
#define buzzer 9 // Define the pin number for the buzzer
#define MIN_X -8   // Minimum threshold for x-axis
#define MAX_X 8    // Maximum threshold for x-axis
#define MIN_Y -8    // Minimum threshold for y-axis
#define MAX_Y 8    // Maximum threshold for y-axis
#define MIN_Z 4    // Minimum threshold for z-axis
#define MAX_Z 15    // Maximum threshold for z-axis

#define SIM800_TX_PIN 2
#define SIM800_RX_PIN 3
#define PHONE_NUMBER "<YOUR_PHONE_NUMBER>" // Change to your phone number

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(ADXL345_ADDRESS);
SoftwareSerial mySerial(SIM800_TX_PIN, SIM800_RX_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  mySerial.begin(9600);
  Serial.println("Initializing SIM800C...");
  delay(1000);
  mySerial.println("AT");
  delay(1000);
  mySerial.println("SIM800C initialized.");

  Serial.println("Initializing ADXL345...");
  if (!accel.begin()) {
    Serial.println("Couldn't find ADXL345 sensor");
    while (1);
  }
  Serial.println("ADXL345 sensor found!");
  accel.setRange(ADXL345_RANGE_16_G);
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event);

  float x = event.acceleration.x + 2.59;
  float y = event.acceleration.y + 4.41;
  float z = event.acceleration.z - 22.4;

  Serial.print("Acceleration (X, Y, Z): ");
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(", ");
  Serial.println(z);

  if (x < MIN_X || x > MAX_X || y < MIN_Y || y > MAX_Y || z < MIN_Z || z > MAX_Z) {
    Serial.println("Out of range! Buzzing the buzzer...");
    tone(buzzer, 1000); // Generate sound
    delay(1000); // Sound duration
    noTone(buzzer); // Stop sound
    delay(1000); // Pause before sending SMS
    sendSMS();
  }
  delay(1000); // Delay for stability
}

void sendSMS() {
  mySerial.println("AT+CMGF=1"); // Set SMS mode to text
  delay(100);
  mySerial.print("AT+CMGS=\""); // Start SMS sending command
  mySerial.print(PHONE_NUMBER); // Set the phone number
  mySerial.println("\"");
  delay(100); 
  mySerial.println("test 123 test 123 "); // SMS content
  delay(100);
  mySerial.println((char)26); // End SMS
  delay(1000); // Wait for SMS to send
}
