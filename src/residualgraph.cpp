#include "../include/residualgraph.hpp"
#include <vector>

// Residual Graph
ResidualGraph::ResidualGraph(int n)
{
    forward_flow.assign(n, vector<int>(n, 0));
    backward_flow.assign(n, vector<int>(n, 0));
    // adj_residual.resize(n);
    adj_residual.assign(n, vector<int>(n, 0));
    parent.resize(n);
    visited.assign(n, 0);
}

void ResidualGraph::add_edge(int u, int v, int w)
{
    adj_residual[u][v] = 1;
    // adj_residual[v].push_back(u);
    forward_flow[u][v] += w;
}

void ResidualGraph::remove_edge(int u, int v)
{
    adj_residual[u][v] = 0;
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

void ResidualGraph::updateResidualGraph(ResidualGraph &rg, OriginalGraph &og, vector<int> &parent, int s, int t)
{
    for (int y = t; parent[y] != -1; y = parent[y])
    {
        int x = parent[y];
        rg.set_backward_flow(x, y, og.get_flow(x, y));
        rg.set_forward_flow(x, y, og.get_capacity(x, y) - og.get_flow(x, y));
        if (og.get_capacity(x, y) == og.get_flow(x, y))
        {
            rg.adj_residual[x][y] = 0;
        }
        if (rg.get_backward_flow(x, y) > 0)
            rg.adj_residual[y][x] = 1;
        if (og.get_flow(x, y) == 0)
        {
            rg.adj_residual[y][x] = 0; //  Not sure if this is right
        }
    }
}