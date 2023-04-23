#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 100; // maximum number of nodes
const int INF = 1e9;  // infinity

int n, m;                 // n = number of nodes, m = number of edges
int capacity[MAXN][MAXN]; // capacity matrix
int residual[MAXN][MAXN]; // residual capacity matrix
bool visited[MAXN];       // visited array for BFS

bool bfs(int source, int sink, int parent[])
{
    // initialize visited array to false
    memset(visited, false, sizeof(visited));
    // create a queue for BFS
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        for (int next = 0; next < n; next++)
        {
            if (!visited[next] && residual[node][next] > 0)
            {
                q.push(next);
                visited[next] = true;
                parent[next] = node;
            }
        }
    }
    return visited[sink];
}

int fordFulkerson(int source, int sink)
{
    // initialize residual capacity matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            residual[i][j] = capacity[i][j];
        }
    }
    // find augmenting paths using BFS and update residual capacities
    int maxFlow = 0;
    int parent[MAXN];
    while (bfs(source, sink, parent))
    {
        int pathFlow = INF;
        for (int node = sink; node != source; node = parent[node])
        {
            int prev = parent[node];
            pathFlow = min(pathFlow, residual[prev][node]);
        }
        for (int node = sink; node != source; node = parent[node])
        {
            int prev = parent[node];
            residual[prev][node] -= pathFlow;
            residual[node][prev] += pathFlow;
        }
        maxFlow += pathFlow;
    }
    // find minimum cut using BFS and return its capacity
    bfs(source, sink, parent);
    int minCut = 0;
    for (int i = 0; i < n; i++)
    {
        if (visited[i])
        {
            for (int j = 0; j < n; j++)
            {
                if (!visited[j] && capacity[i][j] > 0)
                {
                    minCut += capacity[i][j];
                }
            }
        }
    }
    return minCut;
}

int main()
{
    cin >> n >> m;
    memset(capacity, 0, sizeof(capacity)); // set capacity matrix to 0
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        capacity[u][v] = w; // add edge to capacity matrix
    }
    int source, sink;
    cin >> source >> sink;
    int maxFlow = fordFulkerson(source, sink);
    int minCut = maxFlow; // initialize minimum cut to the maximum flow
    cout << "Maximum Flow: " << maxFlow << endl;
    cout << "Minimum Cut: " << minCut << endl;
    return 0;
}
