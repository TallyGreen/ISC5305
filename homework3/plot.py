import pandas as pd
import matplotlib.pyplot as plt

# Load the timing data from CSV
data = pd.read_csv("grid_timing.csv")

# Create the plot
plt.figure(figsize=(10, 6))

# Plot for Grid1
grid1_data = data[data["grid_type"] == "Grid1"]
plt.plot(grid1_data["n"], grid1_data["avg_time"], label="Grid1", marker="o")

# Plot for Grid2
grid2_data = data[data["grid_type"] == "Grid2"]
plt.plot(grid2_data["n"], grid2_data["avg_time"], label="Grid2", marker="o")

# Plot for Grid3
grid3_data = data[data["grid_type"] == "Grid3"]
plt.plot(grid3_data["n"], grid3_data["avg_time"], label="Grid3", marker="o")

# Add labels, title, and grid
plt.xlabel("Grid Size (n)")
plt.ylabel("Average Time (microseconds)")
plt.title("Grid Summation Time for Grid1, Grid2, and Grid3")
plt.grid(True)
plt.legend()

# Show the plot
plt.show()
