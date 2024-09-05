import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file using pandas
data = pd.read_csv('tem_out.csv')

# Extract the 'x' and 'Temperature' columns
x = data['x']
T = data['temperature']

# Plot the temperature profile
plt.plot(x, T)
plt.xlabel('x')
plt.ylabel('Temperature')
plt.title('Temperature Profile')
plt.grid(True)
plt.show()