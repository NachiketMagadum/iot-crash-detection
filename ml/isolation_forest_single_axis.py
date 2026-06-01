import pandas as pd
from sklearn.ensemble import IsolationForest
import matplotlib.pyplot as plt

pd.set_option('display.max_rows', None)
pd.set_option('display.max_columns', None)


# Load the dataset from Excel
df = pd.read_excel('obstacles.xlsx')

# Extract the features
X = df[['x_acceleration']]

# Initialize Isolation Forest model
isolation_forest = IsolationForest(n_estimators=100, contamination=0.04) # Adjust parameters as needed

# Fit the model
isolation_forest.fit(X)

# Predict anomalies (-1 for anomalies, 1 for normal data points)
predictions = isolation_forest.predict(X)

# Add a new column to the DataFrame to number the anomalies
df['anomaly_number'] = 0  # Initialize all rows with 0

# Assign a unique number to each anomaly
anomaly_counter = 1
for idx, prediction in enumerate(predictions):
    if prediction == -1:
        df.loc[idx, 'anomaly_number'] = anomaly_counter
        anomaly_counter += 1

# Filter the DataFrame to show only anomalies
anomalies = df[df['anomaly_number'] != 0]

# Print or further process the anomalies
print(anomalies)

plt.plot(df['x_acceleration'], label='x_acceleration')
plt.plot(df['y_acceleration'], label='y_acceleration')
plt.plot(df['z_acceleration'], label='z_acceleration')

# Plot anomalies
anomalies_indices = df.index[predictions == -1]  # Indices of anomalies
#plt.scatter(anomalies_indices, df.loc[anomalies_indices, 'x_acceleration'], c='red', label='Anomalies (x_acceleration)')
#plt.scatter(anomalies_indices, df.loc[anomalies_indices, 'y_acceleration'], c='red', label='Anomalies (y_acceleration)')
#plt.scatter(anomalies_indices, df.loc[anomalies_indices, 'z_acceleration'], c='red', label='Anomalies (z_acceleration)')

# Add labels and title
plt.xlabel('Time(s)')
plt.ylabel('Acceleration(m/s^2)')
#plt.title('Acceleration Data with Anomalies')

#Add legend
plt.legend()

# Show the plot
plt.show()

accuracy = 100*list(data['anomaly_score']).count(-1)/(anomaly_count)
print("Accuracy of the model:", accuracy)
