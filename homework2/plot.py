import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Function to plot 2D trajectory from a file
def plot_2d_trajectory(filename):
    time = []
    x = []
    y = []

    with open(filename, 'r') as file:
        for line in file:
            t, pos_x, pos_y = map(float, line.split())
            time.append(t)
            x.append(pos_x)
            y.append(pos_y)

    plt.figure()
    plt.plot(x, y, label='2D Trajectory')
    plt.xlabel('X Position')
    plt.ylabel('Y Position')
    plt.title('2D Particle Trajectory')
    plt.legend()
    plt.show()

# Function to plot 3D trajectory from a file
def plot_3d_trajectory(filename):
    time = []
    x = []
    y = []
    z = []

    with open(filename, 'r') as file:
        for line in file:
            t, pos_x, pos_y, pos_z = map(float, line.split())
            time.append(t)
            x.append(pos_x)
            y.append(pos_y)
            z.append(pos_z)

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot(x, y, z, label='3D Trajectory')
    ax.set_xlabel('X Position')
    ax.set_ylabel('Y Position')
    ax.set_zlabel('Z Position')
    ax.set_title('3D Particle Trajectory')
    plt.legend()
    plt.show()

# Call the plotting functions for 2D and 3D trajectories
plot_2d_trajectory('traject_2d.txt')
plot_3d_trajectory('traject_3d.txt')
