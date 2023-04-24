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
            if (y and !vis[y] and rg.get_forward_flow(x, y) > 0)
            {
                q.push(y);
                parent[y] = x;
                vis[y] = true;
            }
        }
    }

    return vis[t];
}

// Not sure whether this is correct ..... Parent array needs to be backtracked in the for loop from i =0 to n
//  bool DFS(ResidualGraph &rg, vector<int> &parent, int s, int t, vector<bool> vis)
//  {
//      if (s == t)
//          return true;
//      int n = rg.forward_flow.size();
//      vis[s] = true;
//      for (int i = 0; i < n; i++)
//      {
//          if (!vis[i] and rg.get_forward_flow(s, i) > 0)
//          {
//              parent[i] = s;
//              if (DFS(rg, parent, i, t, vis))
//                  return true;
//          }
//      }
//      return false;
//  }

int bottleNeck(ResidualGraph &rg, vector<int> &parent, int s, int t)
{
    int bottleneckflow = INT_MAX;
    for (int y = t; y != -1; y = parent[y])
    {
        int x = parent[y];
        bottleneckflow = min(bottleneckflow, rg.get_forward_flow(x, y));
    }

    return bottleneckflow;
}

int maxOutFlow(ResidualGraph &rg, vector<int> &parent, int s) // only source is needed no need of the sink
{
    int maxoutflow = 0;
    vector<int> v = rg.adj_residual[s];

    for (auto i : v)
    {
        maxoutflow += rg.get_forward_flow(s, i);
    }
    return maxoutflow;
}

void OriginalGraph::updateOriginalGraph(OriginalGraph &og, int bn, vector<int> &parent, int s, int t)
{
    for (int y = t; y != -1; y = parent[t])
    {
        int x = parent[y];
        // bottleneckflow = min(bottleneckflow, rg.get_forward_flow(x, y));
        og.set_flow(x, y, og.get_flow(x, y) + bn);
    }
}

void ResidualGraph::updateResidualGraph(ResidualGraph &rg, OriginalGraph &og, vector<int> &parent, int s, int t)
{
    for (int y = t; y != -1; y = parent[t])
    {
        int x = parent[y];
        rg.set_backward_flow(x, y, og.get_flow(x, y));
        rg.set_forward_flow(x, y, og.get_capacity(x, y) - og.get_flow(x, y));
        if (og.get_capacity(x, y) - og.get_flow(x, y))
        {
            rg.adj_residual[x][y] = 0;
        }
        // if(og.get_flow(x,y)==0)
        // {
        //     rg.adj_residual[y][x]=0;   Not sure if this is right
        // }
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
int main()
{
    // cout << "Hello" << endl;
    // Edge e;
    int n = 6; // number of vertices
    ResidualGraph rg(n);

    // add edges to the residual graph
    rg.add_edge(0, 1, 16);
    rg.add_edge(0, 2, 13);
    rg.add_edge(1, 2, 10);
    rg.add_edge(1, 3, 12);
    rg.add_edge(2, 1, 4);
    rg.add_edge(2, 4, 14);
    rg.add_edge(3, 2, 9);
    rg.add_edge(3, 5, 20);
    rg.add_edge(4, 3, 7);
    rg.add_edge(4, 5, 4);
    // ResidualGraph rg(n);
    OriginalGraph og(n);
    // intializeResidualGraph(); // this is what user is entering
    og.initializeOriginalGraph(og, rg);

    int source = 0;
    int sink = 5;
    // visited array to be declared here
    //  int bottleneck;
    //  // all flows will be updated based upon the input
    //  while (BFS(rg, parent, source, sink, visited) ) // this is to run FordFulkerson till we keep getting paths using BFS or DFS in residual graph
    //  {
    //  FordFulkerson(og, rg);
    //  }

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
        rg.parent.assign(n, 0);
        rg.parent[source] = -1; // as parent of source is -1
    }
    cout << "The maximum possible outflow from source s to sink t is " << maxOutFlow(rg, rg.parent, source) << endl;

    // DFS is better in Bipartite Graph
}