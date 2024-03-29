#include "./include/originalgraph.hpp"
#include "./src/originalgraph.cpp"
#include "./include/residualgraph.hpp"
#include "./src/residualgraph.cpp"

#include <bits/stdc++.h>

bool BFS(ResidualGraph &rg, vector<int> &parent, int s, int t, vector<bool> vis)
{
    queue<int> q;
    q.push(s);
    vis[s] = true;
    parent[s] = -1;
    while (!q.empty())
    {
        // cout << "I am here" << endl;
        int u = q.front();
        q.pop();
        for (int v = 0; v < rg.adj_residual.size(); v++)
        {
            if (!vis[v] && rg.adj_residual[u][v] > 0)
            {
                q.push(v);
                // cout << "pushing " << v << endl;
                parent[v] = u;
                vis[v] = true;
            }
        }
    }

    return vis[t]; // return true if there is a path from s to t
}

int bottleNeck(ResidualGraph &rg, vector<int> &parent, int s, int t)
{
    int bottleneckflow = INT_MAX;

    for (int y = t; parent[y] != -1; y = parent[y])
    {
        int x = parent[y];
        bottleneckflow = min(bottleneckflow, rg.get_forward_flow(x, y));
        // cout << "Min Flow uptil now " << bottleneckflow << endl;
    }

    return bottleneckflow;
}

int maxOutFlow(ResidualGraph &rg, int s) // only source is needed no need of the sink
{
    int maxoutflow = 0;
    // cout << "Inside maximum outflow" << endl;
    for (int i = 0; i < rg.adj_residual[s].size(); i++)
    {
        if (rg.adj_residual[i][s] > 0)
            maxoutflow += rg.get_backward_flow(s, i);
    }
    return maxoutflow;
}

int findDestionation(ResidualGraph &rg)
{
    for (int i = 0; i < rg.adj_residual.size(); i++)
    {
        int flag = 1;
        for (int j = 0; j < rg.adj_residual[i].size(); j++)
        {
            if (rg.adj_residual[i][j] == 1)
            {
                flag = 0;
                break;
            }
        }
        if (flag)
            return i;
    }
    return -1;
}

int findSource(ResidualGraph &rg)
{
    for (int i = 0; i < rg.adj_residual.size(); i++)
    {
        int flag = 1;
        int ctr = 0;
        for (int j = 0; j < rg.adj_residual[i].size(); j++)
        {
            if (rg.adj_residual[j][i] == 0)
            {
                flag = 0;
                break;
            }
            else
                ctr++;
        }
        if (flag)
            return i;
    }
    return -1;
}

void min_st_cut(vector<int> &parent, int temp, int source)
{
    stack<int> s;
    while (temp != source)
    {
        s.push(temp);
        temp = parent[temp];
    }

    cout << "The s-t cut is " << endl;
    while (!s.empty())
    {
        int cut = s.top();
        cout << cut << " ";
        s.pop();
    }
}
int main()
{
    // int n = 8; // number of vertices
    ifstream inputFile("t3_testcases/testcase1.txt");
    if (!inputFile.is_open())
    {
        cout << "Error in opening input file" << endl;
    }
    int setA, setB;
    int numberofEdges;
    inputFile >> setA >> setB >> numberofEdges;
    int n = setA + setB + 2;
    ResidualGraph rg(n); // cout << "Printing backward flow at the end" << endl;
    // for (int i = 0; i < rg.adj_residual.size(); i++)
    // {
    //     for (int j = 0; j < rg.adj_residual[i].size(); j++)
    //     {
    //         cout << rg.get_backward_flow(i, j) << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "Printing flow graph at the end" << endl;

    int src, dst, wt;
    cout << "Printing important" << endl;
    for (int i = 0; i < numberofEdges; i++)
    {
        inputFile >> src >> dst;
        rg.add_edge(src, dst, 1);
        cout << src << " " << dst << endl;
    }
    int source = setA + setB;
    int sink = setA + setB + 1;

    for (int j = 0; j < setA; j++)
    {
        rg.add_edge(source, j, 1);
    }

    for (int j = setA; j < setA + setB; j++)
    {
        rg.add_edge(j, sink, 1);
    }

    OriginalGraph og(n);

    og.initializeOriginalGraph(og, rg);

    // Note : before running DFS or BFS we need to reinitialize the parent array and visited array
    // One optimization for finding paths is just running a BFS and storing all the paths inside a vector
    // So multiple BFS calls are not needed

    while (BFS(rg, rg.parent, source, sink, rg.visited))
    {

        // parent and visited array need to be reinitialized here( by 0 and size n = any dimension of the graph)
        int bottleneckflow = bottleNeck(rg, rg.parent, source, sink);

        og.updateOriginalGraph(og, bottleneckflow, rg.parent, source, sink);

        rg.updateResidualGraph(rg, og, rg.parent, source, sink);

        rg.visited.assign(n, 0);
        int temp = rg.parent[sink];

        min_st_cut(rg.parent, temp, source);

        rg.parent.assign(n, 0);
    }

    cout << "The maximum possible outflow from source s to sink t is " << maxOutFlow(rg, source) << endl;

    // DFS is better in Bipartite Graph
}