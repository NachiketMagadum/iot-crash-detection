# Data — labelled sensor recordings

Accelerometer logs (x/y/z in m/s²) collected from the ADXL345 over I2C, streamed via ThingSpeak and exported as spreadsheets.

| File | Class | Notes |
|------|-------|-------|
| `crash.xlsx` | Crash | High-impact frontal/rear collision profile |
| `freefall.xlsx` | Freefall | Rollover / drop profile |
| `tumbling.xlsx` | Tumbling | Sustained chaotic motion after impact |
| `side_push.xlsx` | Side impact | Lateral force |
| `explosion.xlsx` | Sudden burst | Omnidirectional spike |
| `obstacles.xlsx` | Obstacles | Potholes / speed bumps (non-crash) |
| `normal_motion.xlsx` | Baseline | Normal driving |
| `dataset1.xlsx` | Combined | Master set used by ML scripts |

## Columns

All files share the schema:

| Column | Unit |
|--------|------|
| `x_acceleration` | m/s² |
| `y_acceleration` | m/s² |
| `z_acceleration` | m/s² |

## Collection method

1. ADXL345 + Arduino mounted to a small ESP32-driven test platform
2. Manually-induced events (drop, push, etc.) on a soft surface
3. Live values streamed to ThingSpeak channel
4. Exported as `.xlsx` per event class

## License

Data released under MIT, same as code — see root LICENSE.
