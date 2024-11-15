import pandas as pd
import matplotlib.pyplot as plt

# Load CSV file
csv_file = "benchmark_results.csv"
df = pd.read_csv(csv_file)

# Plotting benchmark results
plt.figure(figsize=(15, 10))

# Plot execution time for each method
plt.subplot(2, 1, 1)
for method in df['method_name'].unique():
    method_data = df[df['method_name'] == method]
    plt.plot(method_data['nb_intervals_or_max_depth'], method_data['execution_time'], label=method)

plt.xlabel('Number of Intervals or Max Depth')
plt.ylabel('Execution Time (s)')
plt.title('Execution Time for Different Integration Methods')
plt.legend()

# Plot absolute error for each method
plt.subplot(2, 1, 2)
for method in df['method_name'].unique():
    method_data = df[df['method_name'] == method]
    plt.plot(method_data['nb_intervals_or_max_depth'], method_data['absolute_error'], label=method)

plt.xlabel('Number of Intervals or Max Depth')
plt.ylabel('Absolute Error')
plt.title('Absolute Error for Different Integration Methods')
plt.legend()

plt.tight_layout()
plt.show()