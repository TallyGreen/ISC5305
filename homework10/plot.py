import matplotlib.pyplot as plt

# Provided data
threads = [1, 2, 4, 8, 16]

# Non-Adaptive Results
execution_times_non_adaptive = [0.0008471, 0.0003768, 0.0004757, 0.0009306, 0.0016714]  # n=1000, example data
execution_times_non_adaptive_10000 = [0.0003719, 0.000544, 0.0004746, 0.0007564, 0.0016953]  # n=10000
execution_times_non_adaptive_100000 = [0.0023142, 0.0021816, 0.0011967, 0.0012227, 0.0013177]  # n=100000

# Adaptive Results
execution_times_adaptive_001 = [0.0006574, 0.0000599, 0.000065, 0.0002045, 0.0001938]  # tol=0.001
execution_times_adaptive_1e6 = [0.0001722, 0.0002058, 0.0002142, 0.000256, 0.0002857]  # tol=1e-6

# Plot Execution Time vs Number of Threads for Non-Adaptive
plt.figure(figsize=(10, 5))
plt.plot(threads, execution_times_non_adaptive, marker='o', label='Non-Adaptive, n=1000')
plt.plot(threads, execution_times_non_adaptive_10000, marker='o', label='Non-Adaptive, n=10000')
plt.plot(threads, execution_times_non_adaptive_100000, marker='o', label='Non-Adaptive, n=100000')
plt.xlabel('Number of Threads')
plt.ylabel('Execution Time (s)')
plt.title('Non-Adaptive Execution Time vs Number of Threads')
plt.legend()
plt.grid(True)
plt.show()

# Plot Execution Time vs Number of Threads for Adaptive
plt.figure(figsize=(10, 5))
plt.plot(threads, execution_times_adaptive_001, marker='o', label='Adaptive, tol=0.001')
plt.plot(threads, execution_times_adaptive_1e6, marker='o', label='Adaptive, tol=1e-6')
plt.xlabel('Number of Threads')
plt.ylabel('Execution Time (s)')
plt.title('Adaptive Execution Time vs Number of Threads')
plt.legend()
plt.grid(True)
plt.show()
