# import networkx as nx
from networkx.algorithms import bipartite
from networkx import draw_networkx
from networkx import maximal_matching
from networkx.generators.random_graphs import gnm_random_graph
from matplotlib import pyplot as plt

import random

# for biparite graph genration
nodeA = 50
nodeB = 45
numEdges = 900

bG = bipartite.gnmk_random_graph(nodeA, nodeB, numEdges)

file1 = open("t3_testcases/testcase2.txt", "w")

file1.write(str(nodeA) + "\n" + str(nodeB) + "\n" + str(numEdges) + "\n")

for (u, v) in bG.edges():
    file1.write(str(u) + " " + str(v) + "\n")

file2 = open("t3_ans/testcase2.txt", "r")

ans = maximal_matching(bG)
print(ans)
# file2.write(len(ans))
file2.write(str(len(ans)) + "\n")
for (i, j) in ans:
    file2.write(str(i) + " " + str(j) + "\n")
