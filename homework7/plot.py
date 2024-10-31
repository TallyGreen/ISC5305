import matplotlib.pyplot as plt
import numpy as np

# Load data from the file
filename = 'polynomial_evaluation.txt'
data = np.loadtxt(filename, skiprows=1)

# Extract x values and polynomial/derivative values
x_values = data[:, 0]
p_values = data[:, 1:]

# Plot the polynomial and its derivatives
plt.figure(figsize=(10, 6))
labels = ["P(x)", "P'(x)", "P''(x)", "P'''(x)", "P''''(x)", "P'''''(x)"]

for i in range(p_values.shape[1]):
    plt.plot(x_values, p_values[:, i], label=labels[i])

# Add grid, labels, title, and legend
plt.grid(True)
plt.xlabel('x')
plt.ylabel('Value')
plt.title('Polynomial and Its Derivatives')
plt.legend()

# Save the plot as a PDF
plt.savefig('polynomial_derivatives_plot.pdf')

# Save the plot as a JPG
plt.savefig('polynomial_derivatives_plot.jpg')

# Show the plot
plt.show()
