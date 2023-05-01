#include "./include/originalgraph.hpp"
#include "./src/originalgraph.cpp"
#include "./include/residualgraph.hpp"
#include "./src/residualgraph.cpp"

#include <bits/stdc++.h>

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
    cout << "Inside maximum outflow" << endl;
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
            if (rg.adj_residual[j][i] != 0)
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

int main()
{
    // int n = 8; // number of vertices
    ifstream inputFile("t1_testcases/testcase7.txt");
    if (!inputFile.is_open())
    {
        cout << "Error in opening input file" << endl;
    }
    int n, numberofEdges;
    inputFile >> n >> numberofEdges;
    ResidualGraph rg(n);

    int src, dst, wt;
    // cout << "Printing important" << endl;
    for (int i = 0; i < numberofEdges; i++)
    {
        inputFile >> src >> dst >> wt;
        rg.add_edge(src - 1, dst - 1, wt);
        // cout << src << " " << dst << " " << wt << endl;
    }

    OriginalGraph og(n);

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

    cout << endl;
    int source = findSource(rg);
    cout << "Source " << source << endl;
    int sink = findDestionation(rg);
    cout << "Destination " << sink << endl;

    // Note : before running DFS or BFS we need to reinitialize the parent array and visited array
    // One optimization for finding paths is just running a BFS and storing all the paths inside a vector
    // So multiple BFS calls are not needed

    while (BFS(rg, rg.parent, source, sink, rg.visited))
    {
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