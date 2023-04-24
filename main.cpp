#include "./include/originalgraph.hpp"
#include "./src/originalgraph.cpp"
#include "./include/residualgraph.hpp"
#include "./src/residualgraph.cpp"
#include "./include/edge.hpp"
#include "./include/fordfulkerson.hpp"
#include <bits/stdc++.h>

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
    int n = 8; // number of vertices
    ResidualGraph rg(n);

    // add edges to the residual graph
    // rg.add_edge(0, 1, 16);
    // rg.add_edge(0, 2, 13);
    // rg.add_edge(1, 2, 10);
    // rg.add_edge(1, 3, 12);
    // rg.add_edge(2, 1, 4);
    // rg.add_edge(2, 4, 14);
    // rg.add_edge(3, 2, 9);
    // rg.add_edge(3, 5, 20);
    // rg.add_edge(4, 3, 7);
    // rg.add_edge(4, 5, 4);
    // int s = 0 t = 7;
    rg.add_edge(0, 1, 3);
    rg.add_edge(0, 4, 5);
    rg.add_edge(1, 2, 2);
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
    // ResidualGraph rg(n);
    OriginalGraph og(n);
    // intializeResidualGraph(); // this is what user is entering
    og.initializeOriginalGraph(og, rg);
    for (int i = 0; i < rg.adj_residual.size(); i++)
    {
        for (int j = 0; j < rg.adj_residual[i].size(); j++)
        {
            cout << rg.adj_residual[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < og.adj_original.size(); i++)
    {
        for (int j = 0; j < og.adj_original[i].size(); j++)
        {
            cout << og.adj_original[i][j] << " ";
        }
        cout << endl;
    }
    int source = 0;
    int sink = 7;
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
        for (int i = 0; i < rg.parent.size(); i++)
        {
            cout << rg.parent[i] << " ";
        }
        cout << endl;
        // parent and visited array need to be reinitialized here( by 0 and size n = any dimension of the graph)
        int bottleneckflow = bottleNeck(rg, rg.parent, source, sink);
        cout << bottleneckflow << endl;
        // cout << bottleneckflow << endl;
        og.updateOriginalGraph(og, bottleneckflow, rg.parent, source, sink);
        rg.updateResidualGraph(rg, og, rg.parent, source, sink);
        rg.visited.assign(n, 0);
        rg.parent.assign(n, 0);
        rg.parent[source] = -1; // as parent of source is -1
    }
    cout << "The maximum possible outflow from source s to sink t is " << maxOutFlow(rg, rg.parent, source) << endl;

    // DFS is better in Bipartite Graph
}