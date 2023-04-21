#include "./include/original.hpp"
#include "./include/residual.hpp"
#include "./include/edge.hpp"
#include "./include/fordfulkerson.hpp"
#include <bits/stdc++.h>

// Original Graph
OriginalGraph::OriginalGraph(int n)
{
    flow.assign(n, vector<int>(n, 0));
    capacity.assign(n, vector<int>(n, 0));
    adj_original.resize(n);
}

void OriginalGraph::add_edge(int u, int v, int w)
{
    adj_original[u].push_back(v);
    // adj_original[v].push_back(u);
    capacity[u][v] += w;
}

int OriginalGraph::get_flow(int u, int v) const
{
    return flow[u][v];
}

int OriginalGraph::get_capacity(int u, int v) const
{
    return capacity[u][v];
}

void OriginalGraph::set_flow(int u, int v, int f)
{
    flow[u][v] = f;
}

void OriginalGraph::set_capacity(int u, int v, int c)
{
    capacity[u][v] = c;
}

// Residual Graph
ResidualGraph::ResidualGraph(int n)
{
    forward_flow.assign(n, vector<int>(n, 0));
    backward_flow.assign(n, vector<int>(n, 0));
    adj_residual.resize(n);
    parent.resize(n);
    visited.assign(n, 0);
}

void ResidualGraph::add_edge(int u, int v, int w)
{
    adj_residual[u].push_back(v);
    // adj_residual[v].push_back(u);
    forward_flow[u][v] += w;
}

int ResidualGraph::get_forward_flow(int u, int v) const
{
    return forward_flow[u][v];
}

int ResidualGraph::get_backward_flow(int u, int v) const
{
    return backward_flow[u][v];
}

void ResidualGraph::set_forward_flow(int u, int v, int f)
{
    forward_flow[u][v] = f;
}

void ResidualGraph::set_backward_flow(int u, int v, int f)
{
    backward_flow[u][v] = f;
}

// FordFulkerson::FordFulkerson(const OriginalGraph &original, const ResidualGraph &residual)

bool BFS(ResidualGraph &rg, vector<int> &parent, int s, int t, vector<bool> vis)
{
    queue<int> q;
    parent[s] = -1;
    q.push(s);

    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        // vector<int> adjacency_list = rg.adj_residual;
        for (int y : rg.adj_residual[x])
        {
            if (!vis[y] and rg.get_forward_flow(x, y) > 0)
            {
                q.push(y);
                parent[y] = x;
                vis[y] = true;
            }
        }
    }

    return vis[t];
}

bool DFS(ResidualGraph &rg, vector<int> &parent, int s, int t, vector<bool> vis)
{
    if (s == t)
        return true;
    int n = rg.forward_flow.size();
    vis[s] = true;
    for (int i = 0; i < n; i++)
    {
        if (!vis[i] and rg.get_forward_flow(s, i) > 0)
        {
            parent[i] = s;
            if (DFS(rg, parent, i, t, vis))
                return true;
        }
    }
    return false;
}

int bottleNeck(ResidualGraph &rg, vector<int> &parent, int s, int t)
{
    int bottleneckflow = INT_MAX;
    for (int y = t; y != s; y = parent[t])
    {
        int x = parent[y];
        bottleneckflow = min(bottleneckflow, rg.get_forward_flow(x, y));
    }

    return bottleneckflow;
}

int maxOutFlow(ResidualGraph &rg, vector<int> &parent, int s) // only source is needed no need of the sink
{
    int maxoutflow = 0;
    vector<int> v = rg.adj_residual[x];

    for (auto i : v)
    {
        maxoutflow += rg.get_forward_flow(s, i);
    }
    return maxoutflow;
}

int main()
{
    // cout << "Hello" << endl;
    // Edge e;
    ResidualGraph rg(5);
    OriginalGraph og(5);
    // int source;
    // int sink;
    // // all flows will be updated based upon the input
    // while (BFS(rg, parent, source, sink, visited) ) // this is to run FordFulkerson till we keep getting paths using BFS or DFS in residual graph
    // {
    // FordFulkerson(og, rg);
    // }

    // Note : before running DFS or BFS we need to reinitialize the parent array
}