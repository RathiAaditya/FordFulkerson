#include "./include/originalgraph.hpp"
#include "./src/originalgraph.cpp"
#include "./include/residualgraph.hpp"
#include "./src/residualgraph.cpp"
#include "./include/edge.hpp"
#include "./include/fordfulkerson.hpp"
#include <bits/stdc++.h>

// FordFulkerson::FordFulkerson(const OriginalGraph &original, const ResidualGraph &residual)

// bool BFS(ResidualGraph &rg, vector<int> &parent, int s, int t, vector<bool> vis)
// {
//     queue<int> q;
//     parent[s] = -1;
//     q.push(s);

//     while (!q.empty())
//     {
//         int x = q.front();
//         q.pop();
//         for (int k = 0; k < rg.adj_residual[x].size; k++)
//             cout << rg.adj_residual[x][k] << " ";
//         // vector<int> adjacency_list = rg.adj_residual;
//         for (auto y : rg.adj_residual[x])
//         {
//             cout << y << endl;
//             if (y and !vis[y] and rg.get_forward_flow(x, y) > 0)
//             {
//                 q.push(y);
//                 parent[y] = x;
//                 vis[y] = true;
//             }
//         }
//     }

//     return vis[t];
// }

bool BFS(ResidualGraph &rg, vector<int> &parent, int s, int t, vector<bool> vis)
{
    cout << "Parent array before entering BFS" << endl;
    for (int i = 0; i < parent.size(); i++)
    {
        cout << parent[i] << " ";
    }
    cout << endl;
    queue<int> q;
    q.push(s);
    vis[s] = true;
    parent[s] = -1;
    while (!q.empty())
    {
        cout << "I am here" << endl;
        int u = q.front();
        q.pop();
        for (int v = 0; v < rg.adj_residual.size(); v++)
        {
            if (!vis[v] && rg.adj_residual[u][v] > 0)
            {
                q.push(v);
                cout << "pushing " << v << endl;
                parent[v] = u;
                vis[v] = true;
            }
        }
    }
    cout << "Parent array after  BFS" << endl;
    for (int i = 0; i < parent.size(); i++)
    {
        cout << parent[i] << " ";
    }
    cout << endl;
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
    cout << "Finding bottleneck" << endl;
    for (int i = 0; i < rg.parent.size(); i++)
    {
        cout << rg.parent[i] << " ";
    }
    cout << endl;
    for (int y = t; parent[y] != -1; y = parent[y])
    {
        int x = parent[y];
        bottleneckflow = min(bottleneckflow, rg.get_forward_flow(x, y));
        cout << "Min Flow uptil now " << bottleneckflow << endl;
    }

    return bottleneckflow;
}

int maxOutFlow(ResidualGraph &rg, int s) // only source is needed no need of the sink
{
    int maxoutflow = 0;
    // vector<int> v = rg.adj_residual[s];
    cout << "Inside maximum outflow" << endl;
    // for (auto i : v)
    // {
    //     cout << i << endl;
    //     maxoutflow += rg.get_forward_flow(s, i);
    // }
    for (int i = 0; i < rg.adj_residual[s].size(); i++)
    {
        if (rg.adj_residual[i][s] > 0)
            maxoutflow += rg.get_backward_flow(s, i);
    }
    return maxoutflow;
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
    // ResidualGraph rg(n);
    OriginalGraph og(n);
    // intializeResidualGraph(); // this is what user is entering
    og.initializeOriginalGraph(og, rg);
    cout << "Initialized original capacity" << endl;
    for (int i = 0; i < rg.adj_residual.size(); i++)
    {
        for (int j = 0; j < rg.adj_residual[i].size(); j++)
        {
            cout << og.get_capacity(i, j) << " ";
        }
        cout << endl;
    }

    cout << "Initialized original flow" << endl;
    for (int i = 0; i < rg.adj_residual.size(); i++)
    {
        for (int j = 0; j < rg.adj_residual[i].size(); j++)
        {
            cout << og.get_flow(i, j) << " ";
        }
        cout << endl;
    }
    cout << endl;
    // for (int i = 0; i < og.adj_original.size(); i++)
    // {
    //     for (int j = 0; j < og.adj_original[i].size(); j++)
    //     {
    //         cout << og.adj_original[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    cout << endl;
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
    cout << "Flow between 6 and 7 is " << rg.get_forward_flow(6, 7) << endl;
    while (BFS(rg, rg.parent, source, sink, rg.visited))
    {
        // cout << "Hi" << endl;
        // cout << rg.parent.size() << endl;
        // for (int i = 0; i < rg.parent.size(); i++)
        // {
        //     cout << rg.parent[i] << " ";
        // }
        cout << "Printing path in reverse order" << endl;
        for (int k = rg.parent.size() - 1; k >= 0; k = rg.parent[k])
        {
            cout << k << " ";
        }
        cout << endl;

        // parent and visited array need to be reinitialized here( by 0 and size n = any dimension of the graph)
        int bottleneckflow = bottleNeck(rg, rg.parent, source, sink);
        cout << "Bottleneck flow " << bottleneckflow << endl;
        // till this right
        //  cout << bottleneckflow << endl;
        og.updateOriginalGraph(og, bottleneckflow, rg.parent, source, sink);
        // cout << og.adj_original.size() << endl;
        cout << "Updated original graph flow " << endl;
        for (int i = 0; i < og.adj_original.size(); i++)
        {
            for (int j = 0; j < og.adj_original[i].size(); j++)
            {
                cout << og.get_flow(i, j) << " ";
            }
            cout << endl;
        }

        rg.updateResidualGraph(rg, og, rg.parent, source, sink);
        // cout << "Flow between 6 and 7 is " << rg.get_forward_flow(6, 7) << endl;
        // cout << "Residual graphs backward flow" << endl;
        // cout << rg.get_backward_flow(1, 7) << endl;
        // cout << "Residual graphs forward flow" << endl;
        // cout << rg.get_forward_flow(1, 7) << endl;
        cout << "Printing backward flow after updating residual graph" << endl;
        for (int i = 0; i < rg.adj_residual.size(); i++)
        {
            for (int j = 0; j < rg.adj_residual[i].size(); j++)
            {
                cout << rg.get_backward_flow(i, j) << " ";
            }
            cout << endl;
        }

        cout << "Updated residual graph flow " << endl;
        for (int i = 0; i < rg.adj_residual.size(); i++)
        {
            for (int j = 0; j < rg.adj_residual[i].size(); j++)
            {
                cout << rg.get_forward_flow(i, j) << " ";
            }
            cout << endl;
        }
        rg.visited.assign(n, 0);
        rg.parent.assign(n, 0);
    }
    cout << "Printing backward flow at the end" << endl;
    for (int i = 0; i < rg.adj_residual.size(); i++)
    {
        for (int j = 0; j < rg.adj_residual[i].size(); j++)
        {
            cout << rg.get_backward_flow(i, j) << " ";
        }
        cout << endl;
    }
    cout << "Printing flow graph at the end" << endl;

    cout << "The maximum possible outflow from source s to sink t is " << maxOutFlow(rg, source) << endl;

    // DFS is better in Bipartite Graph
}