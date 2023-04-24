#include "../include/originalgraph.hpp"
#include <vector>
using namespace std;
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

void OriginalGraph::updateOriginalGraph(OriginalGraph &og, int bn, vector<int> &parent, int s, int t)
{
    for (int y = t; parent[y] != -1; y = parent[y])
    {
        int x = parent[y];
        // bottleneckflow = min(bottleneckflow, rg.get_forward_flow(x, y));
        // cout << "Updated flow between x and y for original graph is " << endl;
        og.set_flow(x, y, og.get_flow(x, y) + bn);
    }
}

// already taken from the user
//  void initializeResidualGraph()
//  {
//  }

void OriginalGraph::initializeOriginalGraph(OriginalGraph &og, ResidualGraph &rg)
{
    for (int i = 0; i < rg.adj_residual.size(); i++)
    {
        for (int j = 0; j < rg.adj_residual[i].size(); j++)
        {
            if (rg.adj_residual[i][j] != -1)
            {
                og.set_flow(i, j, 0);
                og.set_capacity(i, j, rg.get_forward_flow(i, j));
            }
        }
    }
}