import networkx as nx
import sys
from matplotlib import pyplot as plt

if __name__ == '__main__':
    if (len(sys.argv) < 2):
        print("Usage: python task3_vis.py <input_file_no> ")

    tno = sys.argv[1]
    # read the points from the file
    with open(f'./task3_dir/t3_testcases/testcase{tno}.txt', 'r') as f:
        lines = f.readlines()
        setA = int(lines[0].strip())
        setB = int(lines[1].strip())
        lines = lines[3:]
        points = [tuple(map(int, line.strip().split())) for line in lines]
    with open(f'./task3_dir/t3_answers/testcase{tno}.txt', 'r') as f:
        lines = f.readlines()
        lines = lines[:-1]
        pointsM = [tuple(map(int, line.strip().split())) for line in lines]
        # print(points)
    B = nx.Graph()
    B.add_nodes_from([i for i in range(setA)], bipartite=0)
    B.add_nodes_from([i for i in range(setA+1, setA+setB)], bipartite=1)
    B.add_edges_from(points)
    top = nx.bipartite.sets(B)[0]
    pos = nx.bipartite_layout(B, top)
    col_list = ['r' if i in pointsM else 'b' for i in points]
    nx.draw(B, pos, with_labels=True, edgelist=points, edge_color=col_list)
    # a = nx.maximal_matching(B)
    plt.savefig("./task3_dir/t3_plots/testcase"+tno+".png")
    plt.show()
