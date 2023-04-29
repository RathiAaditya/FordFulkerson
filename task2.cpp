#include "./include/originalgraph.hpp"
#include "./src/originalgraph.cpp"
#include "./include/residualgraph.hpp"
#include "./src/residualgraph.cpp"
#include "./include/edge.hpp"
#include "./include/fordfulkerson.hpp"
#include <bits/stdc++.h>

bool BFS(ResidualGraph &rg, vector<int> &parent, int s, int t, vector<bool> vis, int delta)
{
    queue<int> q;
    q.push(s);
    vis[s] = true;
    parent[s] = -1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < rg.adj_residual.size(); v++)
        {
            if (!vis[v] && rg.adj_residual[u][v] > 0 and rg.get_forward_flow(u, v) >= delta)
            {
                q.push(v);
                parent[v] = u;
                vis[v] = true;
            }
        }
    }
    return vis[t]; // return true if there is a path from s to t
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
    for (int y = t; parent[y] != -1; y = parent[y])
    {
        int x = parent[y];
        bottleneckflow = min(bottleneckflow, rg.get_forward_flow(x, y));
    }

    return bottleneckflow;
}

int maxOutFlow(ResidualGraph &rg, int s) // only source is needed no need of the sink
{
    int maxoutflow = 0;
    cout << "Inside maximum outflow" << endl;
    for (int i = 0; i < rg.adj_residual[s].size(); i++)
    {
        if (rg.adj_residual[i][s] > 0)
            maxoutflow += rg.get_backward_flow(s, i);
    }
    return maxoutflow;
}

int getdeltaflow(ResidualGraph &rg, int s)
{
    int maxdelta = 0;
    for (int i = 0; i < rg.adj_residual.size(); i++)
    {
        if (rg.adj_residual[s][i])
        {
            maxdelta += rg.get_forward_flow(s, i);
        }
    }
    return maxdelta;
}
int binexpo(int a, int b)
{
    int t = 1;
    while (b > 0)
    {
        if (b & 1)
            t = t * a;
        a = a * a;
        b >>= 1;
    }
    return t;
}
int findDestionation(ResidualGraph &rg)
{
}
int main()
{
    int n = 8; // number of vertices
    ResidualGraph rg(n);
    // Adding Edges initializing residual graph with it
    rg.add_edge(0, 1, 3);
    rg.add_edge(0, 4, 5);
    rg.add_edge(0, 2, 2);
    rg.add_edge(3, 1, 5);
    rg.add_edge(4, 3, 4);
    rg.add_edge(4, 2, 3);
    rg.add_edge(2, 6, 4);
    rg.add_edge(6, 3, 2);
    rg.add_edge(1, 5, 2);
    rg.add_edge(5, 3, 2);
    rg.add_edge(1, 7, 4);
    rg.add_edge(5, 7, 3);
    rg.add_edge(6, 7, 3);
    OriginalGraph og(n);
    og.initializeOriginalGraph(og, rg);
    int source = 0;
    int sink = 7;
    int delta = getdeltaflow(rg, source);
    delta = binexpo(2, (int)log2(delta));
    cout << "The delta flow is " << delta << endl;

    // Note : before running DFS or BFS we need to reinitialize the parent array and visited array
    // One optimization for finding paths is just running a BFS and storing all the paths inside a vector
    // So multiple BFS calls are not needed
    while (delta >= 1)
    {
        while (BFS(rg, rg.parent, source, sink, rg.visited, delta))
        {

            // parent and visited array need to be reinitialized here( by 0 and size n = any dimension of the graph)
            int bottleneckflow = bottleNeck(rg, rg.parent, source, sink);
            og.updateOriginalGraph(og, bottleneckflow, rg.parent, source, sink);

            rg.updateResidualGraph(rg, og, rg.parent, source, sink);
            rg.visited.assign(n, 0);
            rg.parent.assign(n, 0);
        }
        delta = delta / 2;
        cout << delta << endl;
    }
    cout << "The maximum possible outflow from source s to sink t is " << maxOutFlow(rg, source) << endl;
}