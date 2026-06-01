# Firmware

Arduino sketches for the IoT crash-detection prototype.

## Sketches

| File | Purpose |
|------|---------|
| `main/main.ino` | **Integrated build** — ADXL345 + SIM800C + GPS + buzzer. Production sketch. |
| `modules/adxl_sim800.ino` | Accelerometer + SMS only (no GPS) |
| `modules/adxl_sim800_basic.ino` | Bare ADXL + SIM800 minimal sketch |
| `modules/gps_test.ino` | TinyGPS++ standalone — print lat/lng |
| `modules/sim800_test.ino` | SIM800 standalone — send a test SMS |

## Configure before flashing

Open `main/main.ino` and replace these placeholders:

```cpp
#define PHONE_NUMBER "<YOUR_PHONE_NUMBER>"   // e.g. "+44XXXXXXXXXX"
// also update Vehicle owner / Vehicle plate strings in sendSMSWithGPS()
```

**Never commit your real phone number or vehicle plate.** Use placeholders before pushing.

## Wiring (Arduino Uno)

| Component | Pin |
|-----------|-----|
| ADXL345 SDA | A4 |
| ADXL345 SCL | A5 |
| GPS TX | D2 (RX on Uno) |
| GPS RX | D3 (TX on Uno) |
| SIM800 TX | D9 |
| SIM800 RX | D10 |
| Buzzer | D8 |
| Power | 5V / 3.3V per module spec |

## Required libraries

Install via Arduino Library Manager:

- Adafruit ADXL345
- Adafruit Unified Sensor
- TinyGPS++
- SoftwareSerial (built-in)
