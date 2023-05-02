import networkx as nx
import sys
from matplotlib import pyplot as plt

if __name__ == '__main__':
    if (len(sys.argv) < 2):
        print("Usage: python t1_vis.py <input_file_no> ")

    tno = sys.argv[1]
    # read the points from the file
    with open(f'./task1_dir/t1_testcases/testcase{tno}.txt', 'r') as f:
        lines = f.readlines()
        nodes, edges = map(int, lines[0].strip().split())
        lines = lines[1:]
        points = [tuple(map(int, line.strip().split())) for line in lines]
        # print(points)
    with open(f'./task1_dir/t1_answers/testcase{tno}.txt', 'r') as f:
        lines = f.readlines()
        lines = lines[1:-1]
        pointsM = [tuple(map(int, line.strip().split())) for line in lines]
        # print(pointsM)
    B = nx.DiGraph()
    el = [(i, j) for i, j, k in points]
    elM = [(i+1, j+1) for i, j, k in pointsM]
    wt = [k for i, j, k in points]
    B.add_edges_from(el, capacity=wt)
    # top = nx.bipartite.sets(B)[0]
    # pos = nx.bipartite_layout(B, top)
    col_list = ['r' if i in elM else 'b' for i in el]
    pos = nx.spring_layout(B)
    nx.draw_networkx_nodes(B, pos, node_size=nodes)
    nx.draw_networkx_edges(B, pos, edgelist=el,
                           edge_color=col_list)
    nx.draw_networkx_labels(B, pos, font_size=20, font_family="sans-serif")
    edge_labels = {(i, j): k for i, j, k in points}
    nx.draw_networkx_edge_labels(B, pos, edge_labels)
    ax = plt.gca()
    ax.margins(0.08)
    plt.axis("off")
    plt.tight_layout()
    # nx.draw(B, with_labels=True, edgelist=points,
    #         edge_color=col_list)
    # a = nx.maximal_matching(B)
    plt.savefig("./task1_dir/t1_plots/testcase"+tno+".png")
    plt.show()
