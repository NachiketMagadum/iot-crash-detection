import pandas as pd
import matplotlib.pyplot as plt

# Step 1: Read the data from the Excel file
# Replace 'your_file.xlsx' with the path to your Excel file
df = pd.read_excel('op2.xlsx')

# Step 2: Display the first few rows of the dataframe to understand its structure
print(df.head())

# Step 3: Plot the data
plt.figure(figsize=(15, 10))

# Plot x_acceleration vs anomaly_number
plt.subplot(3, 1, 1)
plt.plot(df['anomaly_number'], df['x_acceleration'], marker='o', linestyle='-', color='b')
plt.title('X Acceleration vs Anomaly Number')
plt.xlabel('Anomaly Number')
plt.ylabel('X Acceleration')
plt.grid(True)

# Plot y_acceleration vs anomaly_number
plt.subplot(3, 1, 2)
plt.plot(df['anomaly_number'], df['y_acceleration'], marker='o', linestyle='-', color='g')
plt.title('Y Acceleration vs Anomaly Number')
plt.xlabel('Anomaly Number')
plt.ylabel('Y Acceleration')
plt.grid(True)

# Plot z_acceleration vs anomaly_number
plt.subplot(3, 1, 3)
plt.plot(df['anomaly_number'], df['z_acceleration'], marker='o', linestyle='-', color='r')
plt.title('Z Acceleration vs Anomaly Number')
plt.xlabel('Anomaly Number')
plt.ylabel('Z Acceleration')
plt.grid(True)

# Adjust layout to prevent overlap
plt.tight_layout()

# Display the plot
plt.show()
