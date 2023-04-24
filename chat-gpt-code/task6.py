import matplotlib.pyplot as plt
import numpy as np

# function to plot the input points and fitted lines
def plot_lines(x, y, lines):
    plt.figure(figsize=(8, 6))
    plt.scatter(x, y, color='blue', label='input points')
    colors = ['red', 'green', 'orange', 'purple', 'brown', 'gray']
    for i in range(len(lines)):
        slope, intercept, start, end = lines[i]
        x_line = np.linspace(x[start], x[end], num=(end - start + 1) * 10)
        y_line = slope * x_line + intercept
        plt.plot(x_line, y_line, color=colors[i % len(colors)], label=f'line {i + 1}')
    plt.legend(loc='upper left')
    plt.title('Line Fitting Dynamic Programming Output')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.show()

# example input
n = 20 # number of points
k = 4 # number of lines
x = np.arange(n)
y = np.random.normal(loc=0, scale=10, size=n)

# run the algorithm
dpTable = np.zeros((n, k + 1))
for j in range(1, k + 1):
    for i in range(j, n):
        dpTable[i][j] = np.inf
        slope = 0
        intercept = 0
        for l in range(i, j - 1, -1):
            slope += x[l]
            intercept += y[l]
            errorL = np.sum(np.square(y[l:i+1] - slope / (i - l + 1) * x[l:i+1] - intercept / (i - l + 1)))
            dpTable[i][j] = min(dpTable[i][j], dpTable[l-1][j-1] + errorL)
minError = dpTable[n-1][k]

# find the lines that minimize the error
lines = []
j = k
i = n - 1
while j > 0:
    minErrorL = np.inf
    startL = i
    for l in range(i, j - 2, -1):
        slope = np.sum(x[l:i+1])
        intercept = np.sum(y[l:i+1])
        errorL = np.sum(np.square(y[l:i+1] - slope / (i - l + 1) * x[l:i+1] - intercept / (i - l + 1)))
        if dpTable[l-1][j-1] + errorL < minErrorL:
            minErrorL = dpTable[l-1][j-1] + errorL
            slopeL = slope / (i - l + 1)
            interceptL = intercept / (i - l + 1)
            startL = l
    lines.append((slopeL, interceptL, startL, i))
    i = startL - 1
    j -= 1

# plot the input points and fitted lines
plot_lines(x, y, lines)
