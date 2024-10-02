import matplotlib.pyplot as plt
import pandas as pd

# Load data
newton_data = pd.read_csv('D:/C++study/homework4/week04/homework4.1/homework_assignment/newton_iteration_data.csv', names=['Iteration', 'Root'])
secant_data = pd.read_csv('D:/C++study/homework4/week04/homework4.1/homework_assignment/secant_iteration_data.csv', names=['Iteration', 'Root'])

# Create the plot
plt.figure(figsize=(10, 6))

plt.plot(newton_data['Iteration'], newton_data['Root'], label="Newton's Method", marker='o')
plt.plot(secant_data['Iteration'], secant_data['Root'], label="Secant Method", marker='s')

plt.xlabel('Iteration Number')
plt.ylabel('Computed Root')
plt.title('Root as a Function of Iteration for Newton and Secant Methods')
plt.legend()
plt.grid(True)

# Save and show the plot
plt.savefig('root_vs_iterations.png')
plt.show()
