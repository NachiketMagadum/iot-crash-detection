#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#define ADXL345_ADDRESS (0x53) // ADXL345 sensor I2C address
#define buzzer 8 // Define the pin number for the buzzer
#define MIN_X -8   // Minimum threshold for x-axis
#define MAX_X 8    // Maximum threshold for x-axis
#define MIN_Y -8    // Minimum threshold for y-axis
#define MAX_Y 8    // Maximum threshold for y-axis
#define MIN_Z 4    // Minimum threshold for z-axis
#define MAX_Z 15    // Maximum threshold for z-axis

#define SIM800_TX_PIN 9
#define SIM800_RX_PIN 10
#define PHONE_NUMBER "<YOUR_PHONE_NUMBER>" // Change to your phone number

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(ADXL345_ADDRESS);
SoftwareSerial mySerial(SIM800_TX_PIN, SIM800_RX_PIN);

static const int RXPin = 2, TXPin = 3; // GPS module pins
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

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

  ss.begin(GPSBaud); // Start GPS module
}

void loop() {
  // Read accelerometer data
  sensors_event_t event;
  accel.getEvent(&event);

  float x = event.acceleration.x ;
  float y = event.acceleration.y ;
  float z = event.acceleration.z ;

  // Serial.print("Acceleration (X, Y, Z): ");
   Serial.print(x);
   Serial.print(", ");
   Serial.print(y);
   Serial.print(", ");
   Serial.println(z);

  // Check if accelerometer readings are out of range
  if (x < MIN_X || x > MAX_X || y < MIN_Y || y > MAX_Y || z < MIN_Z || z > MAX_Z) {
    Serial.println("Out of range! Buzzing the buzzer...");
    tone(buzzer, 1000); // Generate sound
    delay(1000); // Sound duration
    noTone(buzzer); // Stop sound
    delay(1000); // Pause before sending SMS
    sendSMSWithGPS();
  }

  // Check for GPS data
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      // Do nothing here, just read all available characters from GPS module
    }
    
  }
  

  // Check if GPS location is updated
  if (gps.location.isUpdated()) {
    Serial.println("GPS Location updated.");
    sendSMSWithGPS();
    
  }

  delay(1000); // Delay for stability
}

void sendSMSWithGPS() {
  if (gps.location.isValid()) {
    mySerial.println("AT+CMGF=1"); // Set SMS mode to text
    delay(100);
    mySerial.print("AT+CMGS=\""); // Start SMS sending command
    mySerial.print(PHONE_NUMBER); // Set the phone number
    mySerial.println("\"");
    delay(100);
    mySerial.println("EMERGENCY ALERT MESSAGE");
    mySerial.println("Vehicle owner- <OWNER_NAME>"); 
    mySerial.println("Vehicle number- <VEHICLE_PLATE>");
    mySerial.println("Accident Location");
    mySerial.print("Latitude: "); // Include latitude in SMS
    mySerial.println(gps.location.lat(), 6);
    delay(100);
    mySerial.print("Longitude: "); // Include longitude in SMS
    mySerial.println(gps.location.lng(), 6);
    delay(100);
    mySerial.println((char)26); // End SMS
    delay(1000); // Wait for SMS to send
  } else {
    Serial.println("GPS location is not valid.");
  }
}
void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  
  Serial.println();
}