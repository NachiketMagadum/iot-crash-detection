# ML — Isolation Forest anomaly detection

Offline anomaly characterisation of accelerometer logs collected from the prototype.

## Setup

```bash
pip install pandas scikit-learn matplotlib openpyxl
```

## Scripts

| Script | What it does |
|--------|--------------|
| `isolation_forest_3axis.py` | Fit IF on x/y/z combined. Plots anomalies overlaid on raw signal. |
| `isolation_forest_single_axis.py` | Fit IF on x_acceleration only. Useful for low-compute targets. |
| `visualize_anomalies.py` | Replots `op2.xlsx` per-axis vs anomaly_number for inspection. |

## Run

```bash
cd ml
python isolation_forest_3axis.py   # reads ../data/dataset1.xlsx by default
```

> Update the `pd.read_excel(...)` path inside each script to point at the file in `../data/`.

## Data

See `../data/` for labelled event recordings. Each `.xlsx` has columns:

- `x_acceleration` (m/s²)
- `y_acceleration` (m/s²)
- `z_acceleration` (m/s²)

## Hyperparameters used

| Param | Value | Why |
|-------|-------|-----|
| `n_estimators` | 100 | Stable tree-count; runs in <1s on Pi-class hardware |
| `contamination` | 0.04 – 0.05 | Crashes are rare events |
| `random_state` | unset | Re-run for sensitivity check |

## Next-step ideas

- Compare IF vs One-Class SVM, LOF, Autoencoder
- Bayesian hyper-tuning (Optuna)
- Move from per-axis to feature-engineered windows (jerk, magnitude, FFT bands)
- Transformer-based time-series anomaly detector (planned for MSc dissertation extension)
