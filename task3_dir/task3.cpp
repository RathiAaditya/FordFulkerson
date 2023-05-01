/**
 * @file task3.cpp
 * @author
 *  Aaditya Rathi (2020A7PS2191H)
 *  Sankalp Kulkarni (2020A7PS1097H)
 *  Shreyas Dixit (2020A7PS2079H)
 *  Chirag Gadia (2020A7PS1721H)
 * @brief Bipartite matching using Ford Fulkerson Algorithm
 * @version 0.1
 * @date 2023-05-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Implements Breadth First Search to find the augmented path
 *
 * @param flows flow or residual graph of the graph
 * @param parent vector to store the parent of each node in the augmented path
 * @param visited visited vector to keep track of visited nodes
 * @param numNodes total number of nodes in the graph
 * @param source index of the source node of the graph
 * @param sink index of the sink node of the graph
 * @return true if augmented path is found
 * @return false if augmented path is not found
 */
bool BFS(vector<vector<long long int>> &flows, vector<int> &parent, vector<bool> &visited, int numNodes, int source, int sink)
{

    queue<int> q;

    parent[source] = -1;
    q.push(source);

    while (!q.empty())
    {

        int u = q.front();
        q.pop();

        for (int i = 0; i < numNodes; ++i)
        {
            if (!visited[i] && flows[u][i] > 0)
            {
                q.push(i);
                parent[i] = u;
                visited[i] = true;
            }
        }
    }

    return visited[sink];
}

/**
 * @brief Implements Depth First Search to find the nodes reachable from source in final residual graph
 *
 * @param resGraph final residual graph for the given graph
 * @param source source node of the modified graph
 * @param vis boolean vector to keep track of visited nodes
 * @return vector<bool> boolean vectro with true for nodes reachable from source
 */
vector<bool> DFS(vector<vector<long long int>> &resGraph, int source, vector<bool> &vis)
{
    vis[source] = true;
    for (int i = 0; i < resGraph.size(); i++)
    {
        if (resGraph[source][i] and !vis[i])
        {
            // cout << "Visited " << i << endl;
            DFS(resGraph, i, vis);
        }
    }
    return vis;
}

/**
 * @brief Prints the edges in the min s-t cut
 *
 * @param resGraph final resdiual graph for the given graph
 * @param orgGraph modified version of the original graph
 * @param vis boolean vector with true for nodes reachable from source in the final residual graph
 */
void min_st_cut(vector<vector<long long int>> resGraph, vector<vector<long long int>> orgGraph, vector<bool> &vis)
{
    for (int i = 0; i < resGraph.size(); i++)
    {
        for (int j = 0; j < resGraph[i].size(); j++)
        {
            if (vis[i] and !vis[j] and orgGraph[i][j])
            {
                cout << i << " " << j << " " << orgGraph[i][j] << endl;
            }
        }
    }
}

/**
 * @brief Implements Ford Fulkerson algorithm to find the maximum flow
 *
 * @param orgGraph Modified version of the original graph
 * @param numNodes Total number of nodes in the graph
 * @param source Source node of the modified graph
 * @param sink Sink node of the modified graph
 * @param setA number of nodes in set A of the bipartite graph
 * @param setB number of nodes in set B of the bipartite graph
 * @return int maximum flow of the graph found using Ford Fulkerson algorithm
 */
int FordFulkerson(vector<vector<long long int>> &orgGraph, int numNodes, int source, int sink, int setA, int setB)
{

    vector<vector<long long int>> resGraph(numNodes, vector<long long int>(numNodes, 0));
    vector<int> parent(numNodes);
    vector<bool> visited(numNodes, false);

    // Replicate the graph for residual one
    for (int i = 0; i < numNodes; ++i)
    {
        for (int j = 0; j < numNodes; ++j)
        {
            resGraph[i][j] = orgGraph[i][j];
            // cout << resGraph[i][j] << " ";
        }
        // cout << endl;
    }
    long long int max_flow = 0;

    while (BFS(resGraph, parent, visited, numNodes, source, sink))
    {
        visited.assign(visited.size(), false);
        long long int path_flow = LLONG_MAX;
        for (int ver = sink; ver != source; ver = parent[ver])
        {
            int u = parent[ver];
            // cout << "ver: " << ver << endl;
            // cout << "Parent of ver: " << u << endl;
            path_flow = min(path_flow, resGraph[u][ver]);
            // path_flow = path_flow < resGraph[u][ver] ? path_flow : resGraph[u][ver];
            // cout << "Path Flow: " << path_flow << endl;
        }
        for (int ver = sink; ver != source; ver = parent[ver])
        {
            int u = parent[ver];
            resGraph[u][ver] -= path_flow;
            resGraph[ver][u] += path_flow;
        }
        // cout << "is it reaching" << endl;
        max_flow += path_flow;
    }
    // vector<bool> vis(numNodes, 0);

    // DFS(resGraph, source, vis);

    // // cout << "Printing s-t cut edges" << endl;
    // // min_st_cut(resGraph, orgGraph, vis);

    for (int src = 0; src < setA; ++src)
    {
        for (int dst = setA; dst < setA + setB; ++dst)
        {
            if (orgGraph[src][dst] == 1 and resGraph[src][dst] == 0)
            {
                cout << src << " " << dst << endl;
            }
        }
    }

    return max_flow;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Error: Invalid number of arguments." << endl;
        exit(0);
    }
    auto s = "./task3_dir/t3_testcases/testcase" + string(argv[1]) + ".txt";
    // cout << s << endl;
    ifstream inputFile(s);
    // ifstream inputFile("./testcases/testcase" + string(argv[1]) + ".txt");
    if (!inputFile.is_open())
    {
        cout << "Error in opening input file" << endl;
    }
    int setA, setB, numEdges;
    inputFile >> setA >> setB >> numEdges;
    vector<vector<long long int>> orgGraph(setA + setB + 2, vector<long long int>(setA + setB + 2, 0));
    int src, dst;
    for (int j = 0; j < numEdges; ++j)
    {
        inputFile >> src >> dst;
        orgGraph[src][dst] = 1;
        // cout << src << " " << dst << " " << wt << endl;
    }
    int source, sink;
    source = setA + setB;
    sink = setA + setB + 1;
    for (int dst = 0; dst < setA; dst++)
    {
        orgGraph[source][dst] = 1;
    }
    for (int src = setA; src < setA + setB; src++)
    {
        orgGraph[src][sink] = 1;
    }

    // if (!outputFile.is_open())
    // {
    //     cout << "Error in opening input file" << endl;
    // }

    long long int mxf = FordFulkerson(orgGraph, setA + setB + 2, source, sink, setA, setB);

    cout << "Maximum match for bipartite graph is: " << mxf << endl;
}