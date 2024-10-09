import matplotlib.pyplot as plt
import numpy as np

# Load data from the files
edge_lengths = np.loadtxt('D:/C++study/homework5/assignment_statement/edge_lengths.txt')
vertex_areas = np.loadtxt('D:/C++study/homework5/assignment_statement/vertex_areas.txt')
triangle_areas = np.loadtxt('D:/C++study/homework5/assignment_statement/triangle_areas.txt')

# Calculate mean and standard deviation for edge lengths
mean_length = np.mean(edge_lengths)
std_dev_length = np.std(edge_lengths)
print(f"Mean edge length: {mean_length}")
print(f"Standard deviation of edge lengths: {std_dev_length}")

# Create histogram for edge lengths
plt.figure(figsize=(8, 6))
plt.hist(edge_lengths, bins=50, color='blue', alpha=0.7, edgecolor='black')
plt.axvline(mean_length, color='red', linestyle='dashed', linewidth=1, label=f'Mean: {mean_length:.2f}')
plt.axvline(mean_length + std_dev_length, color='green', linestyle='dashed', linewidth=1, label=f'+1 SD: {mean_length + std_dev_length:.2f}')
plt.axvline(mean_length - std_dev_length, color='green', linestyle='dashed', linewidth=1, label=f'-1 SD: {mean_length - std_dev_length:.2f}')
plt.text(mean_length, plt.gca().get_ylim()[1] * 0.8, f'Mean: {mean_length:.2f}', color='red')
plt.text(mean_length + std_dev_length, plt.gca().get_ylim()[1] * 0.7, f'+1 SD: {mean_length + std_dev_length:.2f}', color='green')
plt.text(mean_length - std_dev_length, plt.gca().get_ylim()[1] * 0.7, f'-1 SD: {mean_length - std_dev_length:.2f}', color='green')
plt.title('Histogram of Edge Lengths')
plt.xlabel('Edge Length')
plt.ylabel('Frequency')
plt.legend()
plt.show()

# Calculate mean and standard deviation for vertex areas
mean_vertex_area = np.mean(vertex_areas)
std_dev_vertex_area = np.std(vertex_areas)
print(f"Mean vertex area: {mean_vertex_area}")
print(f"Standard deviation of vertex areas: {std_dev_vertex_area}")

# Create histogram for vertex areas
plt.figure(figsize=(8, 6))
plt.hist(vertex_areas, bins=50, color='green', alpha=0.7, edgecolor='black')
plt.axvline(mean_vertex_area, color='red', linestyle='dashed', linewidth=1, label=f'Mean: {mean_vertex_area:.2f}')
plt.axvline(mean_vertex_area + std_dev_vertex_area, color='blue', linestyle='dashed', linewidth=1, label=f'+1 SD: {mean_vertex_area + std_dev_vertex_area:.2f}')
plt.axvline(mean_vertex_area - std_dev_vertex_area, color='blue', linestyle='dashed', linewidth=1, label=f'-1 SD: {mean_vertex_area - std_dev_vertex_area:.2f}')
plt.text(mean_vertex_area, plt.gca().get_ylim()[1] * 0.8, f'Mean: {mean_vertex_area:.2f}', color='red')
plt.text(mean_vertex_area + std_dev_vertex_area, plt.gca().get_ylim()[1] * 0.7, f'+1 SD: {mean_vertex_area + std_dev_vertex_area:.2f}', color='blue')
plt.text(mean_vertex_area - std_dev_vertex_area, plt.gca().get_ylim()[1] * 0.7, f'-1 SD: {mean_vertex_area - std_dev_vertex_area:.2f}', color='blue')
plt.title('Histogram of Vertex Areas')
plt.xlabel('Vertex Area')
plt.ylabel('Frequency')
plt.legend()
plt.show()

# Calculate mean and standard deviation for triangle areas
mean_triangle_area = np.mean(triangle_areas)
std_dev_triangle_area = np.std(triangle_areas)
print(f"Mean triangle area: {mean_triangle_area}")
print(f"Standard deviation of triangle areas: {std_dev_triangle_area}")

# Create histogram for triangle areas
plt.figure(figsize=(8, 6))
plt.hist(triangle_areas, bins=50, color='red', alpha=0.7, edgecolor='black')
plt.axvline(mean_triangle_area, color='red', linestyle='dashed', linewidth=1, label=f'Mean: {mean_triangle_area:.2f}')
plt.axvline(mean_triangle_area + std_dev_triangle_area, color='purple', linestyle='dashed', linewidth=1, label=f'+1 SD: {mean_triangle_area + std_dev_triangle_area:.2f}')
plt.axvline(mean_triangle_area - std_dev_triangle_area, color='purple', linestyle='dashed', linewidth=1, label=f'-1 SD: {mean_triangle_area - std_dev_triangle_area:.2f}')
plt.text(mean_triangle_area, plt.gca().get_ylim()[1] * 0.8, f'Mean: {mean_triangle_area:.2f}', color='red')
plt.text(mean_triangle_area + std_dev_triangle_area, plt.gca().get_ylim()[1] * 0.7, f'+1 SD: {mean_triangle_area + std_dev_triangle_area:.2f}', color='purple')
plt.text(mean_triangle_area - std_dev_triangle_area, plt.gca().get_ylim()[1] * 0.7, f'-1 SD: {mean_triangle_area - std_dev_triangle_area:.2f}', color='purple')
plt.title('Histogram of Triangle Areas')
plt.xlabel('Triangle Area')
plt.ylabel('Frequency')
plt.legend()
plt.show()
