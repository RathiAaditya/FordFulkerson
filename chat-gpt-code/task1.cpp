#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 100; // maximum number of nodes
const int INF = 1e9;  // infinity

int n, m;                 // n = number of nodes, m = number of edges
int capacity[MAXN][MAXN]; // capacity matrix
int residual[MAXN][MAXN]; // residual capacity matrix
int parent[MAXN];         // parent vector for BFS
int maxFlow;              // maximum flow

bool bfs(int source, int sink)
{
    memset(parent, -1, sizeof(parent)); // set parent vector to -1
    queue<int> q;
    q.push(source);
    parent[source] = -2;
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        for (int next = 0; next < n; next++)
        {
            if (parent[next] == -1 && residual[cur][next] > 0)
            {
                parent[next] = cur;
                if (next == sink)
                    return true;
                q.push(next);
            }
        }
    }
    return false;
}

void fordFulkerson(int source, int sink)
{
    // initialize residual capacity matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            residual[i][j] = capacity[i][j];
        }
    }
    maxFlow = 0;
    while (bfs(source, sink))
    {
        int pathFlow = INF;
        // find bottleneck capacity
        for (int cur = sink; cur != source; cur = parent[cur])
        {
            int prev = parent[cur];
            pathFlow = min(pathFlow, residual[prev][cur]);
        }
        // update residual capacity
        for (int cur = sink; cur != source; cur = parent[cur])
        {
            int prev = parent[cur];
            residual[prev][cur] -= pathFlow;
            residual[cur][prev] += pathFlow;
        }
        maxFlow += pathFlow;
    }
}

int main()
{
    cin >> n >> m;
    memset(capacity, 0, sizeof(capacity)); // set capacity matrix to 0
    for (int i = 0; i < m; i++)
    {
        int from, to, c;
        cin >> from >> to >> c;
        capacity[from][to] += c; // add edge to capacity matrix
    }
    int source, sink;
    cin >> source >> sink;
    fordFulkerson(source, sink);
    cout << maxFlow << endl;
    return 0;
}
