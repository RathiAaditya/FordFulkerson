/**
 * @file task1.cpp
 * @author
 *  Aaditya Rathi (2020A7PS2191H)
 *  Sankalp Kulkarni (2020A7PS1097H)
 *  Shreyas Dixit (2020A7PS2079H)
 *  Chirag Gadia (2020A7PS1721H)
 * @brief Implementation of Ford Fulkerson Algorithm and min s-t cut subroutine
 * @version 0.1
 * @date 2023-05-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <cstring>
#include <iostream>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Implements Breadth First Search to find augmented path from source to sink is flows graph
 *
 * @param flows flows in the residual graph
 * @param parent parent vector to store the parent of each node in the augmented path
 * from sink to source
 * @param visited visited vector to keep track of visited nodes in the graph
 * @param numNodes total number of nodes in the graph
 * @param source source node of the graph
 * @param sink sink node of the graph
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
 * @brief Implemts Depth First Search to find reachable nodes from source in final residual graph
 *
 * @param resGraph final residual graph of original graph
 * @param source source node of the graph
 * @param vis vector to keep track of visited nodes
 * @return vector<bool> visited vector to store reachable nodes from source in final residual graph
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
 * @brief Prints the min s-t cut edges and their capacities
 *
 * Min s-t cut edges are edges from reachable nodes in final residual graph to unreachable nodes
 *
 * @param resGraph final residual graph of original graph
 * @param orgGraph original graph
 * @param vis vector to keep track of visited nodes in final residual graph
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
 * @brief Implements Ford Fulkerson Algorithm
 *
 * @param orgGraph original graph
 * @param numNodes total number of nodes in the graph
 * @param source source node of the graph
 * @param sink sink node of the graph
 * @return int max flow in the graph using Ford Fulkerson Algorithm
 */
int FordFulkerson(vector<vector<long long int>> &orgGraph, int numNodes, int source, int sink)
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
    vector<bool> vis(numNodes, 0);

    DFS(resGraph, source, vis);

    cout << "Printing s-t cut edges" << endl;
    min_st_cut(resGraph, orgGraph, vis);

    return max_flow;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Please provide input file name" << endl;
    }
    ifstream inputFile("./task1_dir/t1_testcases/testcase" + string(argv[1]) + ".txt");
    if (!inputFile.is_open())
    {
        cout << "Error in opening input file" << endl;
    }
    int numNodes, numEdges;
    inputFile >> numNodes >> numEdges;
    vector<vector<long long int>> orgGraph(numNodes, vector<long long int>(numNodes, 0));
    int src, dst, wt;
    for (int j = 0; j < numEdges; ++j)
    {
        inputFile >> src >> dst >> wt;
        orgGraph[src - 1][dst - 1] = wt;
        // cout << src << " " << dst << " " << wt << endl;
    }

    int source, sink;
    source = 0;
    sink = numNodes - 1;
    long long int mxf = FordFulkerson(orgGraph, numNodes, source, sink);
    cout << "Max Flow in this graph is: " << mxf << endl;
}