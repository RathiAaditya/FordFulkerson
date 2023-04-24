#include "../include/originalgraph.hpp"
#include <vector>

// Original Graph
OriginalGraph::OriginalGraph(int n)
{
    flow.assign(n, vector<int>(n, 0));
    capacity.assign(n, vector<int>(n, 0));
    // adj_original.resize(n);
    adj_original.assign(n, vector<int>(n, 0));
}
// if already an edge exists then just increase the capacity
void OriginalGraph::add_edge(int u, int v, int w)
{
    adj_original[u][v] = 1;
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