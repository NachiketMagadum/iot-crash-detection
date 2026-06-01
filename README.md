# IoT Crash Detection & Emergency Response System

> **Award-winning Final-Year Project** — Real-time vehicle crash detection on edge hardware with automatic GPS emergency SMS alerts and an Isolation Forest anomaly classifier to suppress false positives.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![Platform](https://img.shields.io/badge/platform-Arduino-blue)
![Language](https://img.shields.io/badge/language-Python%20%7C%20C%2B%2B-green)
![Status](https://img.shields.io/badge/status-Research%20prototype-orange)

---

## Overview

A low-cost embedded system that detects vehicle accidents in real time using an ADXL345 3-axis accelerometer, classifies events using an Isolation Forest anomaly-detection model, and automatically sends the vehicle's GPS location to a configured emergency contact via SMS over the SIM800C GSM module.

**Final-Year project at Gogte Institute of Technology, Belagavi (2024)** — awarded **Best Final-Year Project**.

## Key features

- Threshold + ML hybrid detection: hard accel thresholds gate the buzzer, Isolation Forest filters anomalies offline to characterise crash vs non-crash events
- Real-time SMS over GSM with GPS coordinates
- Multi-class event characterisation: crash, freefall, tumbling, side-push, explosion, obstacles, normal motion
- Modular firmware: ADXL, SIM800, GPS each tested independently before integration
- Sensor data logged to spreadsheets for offline ML analysis

## Architecture

```
+----------------+        +-----------+        +------------+
| ADXL345 (I2C)  | -----> | Arduino   | -----> | Buzzer     |
+----------------+        |   Uno     |        +------------+
                          |           |
+----------------+        |           |        +------------+
| Neo-6M / GPS   | -----> |           | -----> | SIM800C    | ---> SMS w/ GPS
+----------------+        |           |        | (GSM)      |
                          +-----------+        +------------+
                                |
                                v
                       sensor logs (xlsx)
                                |
                                v
                       Isolation Forest (Python)
                                |
                                v
                       Anomaly characterisation
```

## Repository structure

```
iot-crash-detection/
├── firmware/
│   ├── main/main.ino                       # Integrated ADXL + GSM + GPS
│   └── modules/                            # Subsystem test sketches
│       ├── adxl_sim800.ino                 # ADXL + SIM800 only
│       ├── adxl_sim800_basic.ino           # Bare ADXL+SIM800
│       ├── gps_test.ino                    # GPS standalone
│       └── sim800_test.ino                 # SIM800 standalone
├── ml/
│   ├── isolation_forest_single_axis.py    # IF on single axis (x_accel)
│   ├── isolation_forest_3axis.py          # IF on x/y/z combined
│   └── visualize_anomalies.py             # Anomaly visualisation
├── data/                                   # Labelled sensor recordings (xlsx)
│   ├── crash.xlsx
│   ├── freefall.xlsx
│   ├── normal_motion.xlsx
│   ├── obstacles.xlsx
│   ├── tumbling.xlsx
│   ├── explosion.xlsx
│   ├── side_push.xlsx
│   └── dataset1.xlsx                       # Combined master set
├── docs/                                   # Reports + IEEE paper draft + poster
├── images/                                 # Prototype + circuit photos
└── results/                                # Plots
```

## Hardware

| Component | Purpose |
|-----------|---------|
| Arduino Uno | MCU |
| ADXL345 | 3-axis accelerometer (I2C) |
| SIM800C | GSM module — sends SMS |
| Neo-6M / TinyGPS+ | GPS location |
| Buzzer | Audible alert |
| ESP32 (test bot) | Simulated crash bot for data collection |

## Firmware setup

1. Install **Arduino IDE** (1.8+ or 2.x)
2. Install libraries via Library Manager:
   - `Adafruit ADXL345`
   - `Adafruit Unified Sensor`
   - `TinyGPS++`
   - `SoftwareSerial` (built-in)
3. Open `firmware/main/main.ino`
4. **Configure your emergency contact**: search for `<YOUR_PHONE_NUMBER>` and `<OWNER_NAME>` / `<VEHICLE_PLATE>` placeholders and replace with your values
5. Wire as per circuit diagram (`images/circuit_diagram.jpg`)
6. Upload to Arduino Uno

### Accelerometer thresholds (defaults)

| Axis | Min | Max |
|------|-----|-----|
| X | -8 | 8 |
| Y | -8 | 8 |
| Z | 4 | 15 |

Tuning: collect baseline driving data, recompute via `ml/isolation_forest_3axis.py`.

## ML pipeline

```bash
cd ml
pip install pandas scikit-learn matplotlib openpyxl
python isolation_forest_3axis.py
```

### Data labels

| File | Event class |
|------|-------------|
| `crash.xlsx` | High-impact frontal/rear collision |
| `freefall.xlsx` | Free-fall (rollover) signature |
| `tumbling.xlsx` | Sustained chaotic motion |
| `side_push.xlsx` | Lateral impact |
| `explosion.xlsx` | Sudden, omnidirectional spike |
| `obstacles.xlsx` | Pothole / speed bump |
| `normal_motion.xlsx` | Baseline driving |

### Model

- **Algorithm:** Isolation Forest (sklearn)
- **Features:** x/y/z linear acceleration (m/s²)
- **Contamination:** 0.04 (single-axis) / 0.05 (3-axis)
- **Estimators:** 100 trees
- **Why this model:** unsupervised, no need for labelled crashes (rare), low compute footprint, fast inference

## Results

Per-class anomaly visualisation in `results/`. Hybrid threshold + IF pipeline meaningfully reduced false positives vs threshold-only baseline.

## Documents

- `docs/project_report.pdf` — full project report
- `docs/ieee_paper_draft.docx` — IEEE paper draft (2024)
- `docs/poster.pdf` — final presentation poster
- `docs/proposal.docx` — original proposal

## Limitations & future work

- Threshold tuning currently empirical — could use Bayesian optimisation
- IF runs offline; on-device inference (TFLite Micro) would enable real-time ML gating
- Single SMS recipient — multi-contact + cloud relay needed for production
- No driver-state inputs (heart rate, dashcam) — fusion would lift recall
- Move from IF → transformer-based time-series anomaly detection (planned in MSc dissertation extension)

## Authors

- **Nachiket Magadum** ([@NachiketMagadum](https://github.com/NachiketMagadum))
- Project team — Information Science & Engineering, Gogte Institute of Technology, Belagavi
- Faculty guide — GIT, ISE Department

## License

MIT — see [LICENSE](LICENSE).

## Citation

If this project helps your research, please cite:

```bibtex
@misc{magadum2024iotcrash,
  author = {Magadum, Nachiket and others},
  title  = {IoT Crash Detection \& Emergency Response System},
  year   = {2024},
  url    = {https://github.com/NachiketMagadum/iot-crash-detection},
  note   = {Final-Year Project, Gogte Institute of Technology}
}
```
