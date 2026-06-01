#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SoftwareSerial.h>

#define MIN_X -8   // Minimum threshold for x-axis
#define MAX_X 8    // Maximum threshold for x-axis
#define MIN_Y -8   // Minimum threshold for y-axis
#define MAX_Y 8    // Maximum threshold for y-axis
#define MIN_Z 4    // Minimum threshold for z-axis
#define MAX_Z 15   // Maximum threshold for z-axis

const int RXPin = 9; // Connect SIM800C TX pin to ESP8266 RX pin D5
const int TXPin = 10;  // Connect SIM800C RX pin to ESP8266 TX pin D4

SoftwareSerial sim800Serial(RXPin, TXPin); // RX, TX

// Initialize the ADXL345 using the Adafruit_ADXL345 class
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup(void) {
  Serial.begin(9600);
  Serial.println("ADXL345 test");

  if (!accel.begin()) {
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while (1);
  }

  // Set the range to whatever is appropriate for your project
  accel.setRange(ADXL345_RANGE_16_G);
}

void loop(void) {
  // Get a new sensor event
  sensors_event_t event;
  accel.getEvent(&event);
  float x, y, z;
  readAccelerometer(x, y, z);

  // if (isOutOfRange(x, y, z)) {
  //   Serial.println("Out of range! Buzzing the buzzer...");
  //   // buzzBuzzer(); // Assuming this function is defined elsewhere
  //   delay(1000); // Sound duration
  //   SendMessage(); // Send SMS
  // }
  // x=x+2.5;
  // y-=1.6;
  // Print the acceleration (in m/s^2) from the x, y, and z axes
  Serial.print("X: "); Serial.print(x);
  Serial.print(" Y: "); Serial.print(y);
  Serial.print(" Z: "); Serial.print(z );
  Serial.println(" m/s^2");

  delay(500); // Delay between measurements
  
if ((x < MIN_X || x > MAX_X )||( y < MIN_Y || y > MAX_Y) ||( z < MIN_Z || z > MAX_Z)) {
    Serial.println("Out of range! Buzzing the buzzer...");
    // tone(buzzer, 1000); // Generate sound
    // delay(1000); // Sound duration
    // noTone(buzzer); // Stop sound
    // delay(1000); // Pause before sending SMS
    SendMessage();
  }
}

void SendMessage() {
  Serial.println("Sending SMS...");
  sim800Serial.begin(9600); // Start SIM800C communication
  delay(500); // Wait for SIM800C to initialize
  sim800Serial.println("AT+CMGF=+919600504055"); // Set SMS mode to text
  delay(100);
  sim800Serial.println("AT+CMGS=\"+91\""); // Set the recipient phone number
  delay(100);
  sim800Serial.println("EMERGENCY ALERT MESSAGE");
  delay(100);
  sim800Serial.println("Vehicle Owner -XXXX");
  delay(100);
  sim800Serial.println("Vehicle Number-XX XX XX XXXX");
  delay(100);
  sim800Serial.println("Accident Location");
  delay(100);
  sim800Serial.println("Latitude-<LAT>");
  delay(100);
  sim800Serial.println("Longitude-<LNG>");
  delay(100);
  sim800Serial.println((char)26); // End SMS
  delay(1000); // Wait for SMS to send
  sim800Serial.end(); // End SIM800C communication
}

void readAccelerometer(float &x, float &y, float &z) {
  sensors_event_t event;
  accel.getEvent(&event);
  x = event.acceleration.x;
  y = event.acceleration.y;
  z = event.acceleration.z;
}