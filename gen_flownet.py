import networkx as nx
import random
from matplotlib import pyplot as plt


# generate a random directed graph
G = nx.DiGraph()

num_nodes = 10
num_edges = 20

for i in range(num_nodes):
    G.add_node(i)

while num_edges > 0:
    source = random.randint(0, num_nodes-2)
    target = random.randint(1, num_nodes-1)
    while (source == target):
        target = random.randint(1, num_nodes-1)
    capacity = random.randint(1, 10)
    if ((source, target) not in G.edges()):
        G.add_edge(source, target, capacity=capacity)
        num_edges -= 1

file2 = open("t1_testcases/testcase2.txt", "w")

file2.write(num_nodes + "\n")
file2.write(len(G.edges()) + "\n")

for (u, v) in G.edges():
    file2.write(str(u) + " " + str(v) + " " + str(G[u][v]['capacity']) + "\n")

nx.draw_networkx(G, with_labels=True)
plt.show()
