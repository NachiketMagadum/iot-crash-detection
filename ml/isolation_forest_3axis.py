import pandas as pd
import matplotlib.pyplot as plt
from sklearn.ensemble import IsolationForest

# Load the dataset from Excel
df = pd.read_excel('dataset1.xlsx')

# Extract the features
X = df[['x_acceleration', 'y_acceleration', 'z_acceleration']]

# Initialize Isolation Forest model
isolation_forest = IsolationForest(n_estimators=100, contamination=0.05)  # Adjust parameters as needed

# Fit the model
isolation_forest.fit(X)

# Predict anomalies (-1 for anomalies, 1 for normal data points)
predictions = isolation_forest.predict(X)

# Plot the data points
plt.plot(df['x_acceleration'], label='x_acceleration')
plt.plot(df['y_acceleration'], label='y_acceleration')
plt.plot(df['z_acceleration'], label='z_acceleration')

# Plot anomalies
anomalies_indices = df.index[predictions == -1]  # Indices of anomalies
plt.scatter(anomalies_indices, df.loc[anomalies_indices, 'x_acceleration'], c='red', label='Anomalies (x_acceleration)')
plt.scatter(anomalies_indices, df.loc[anomalies_indices, 'y_acceleration'], c='red', label='Anomalies (y_acceleration)')
plt.scatter(anomalies_indices, df.loc[anomalies_indices, 'z_acceleration'], c='red', label='Anomalies (z_acceleration)')

# Add labels and title
plt.xlabel('Time(s)')
plt.ylabel('Acceleration(m/s^2)')
plt.title('Acceleration Data with Anomalies')

# Add legend
#plt.legend()

# Show the plot
plt.show()