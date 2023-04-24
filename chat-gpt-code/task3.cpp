#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 100; // maximum number of nodes
const int INF = 1e9;  // infinity

int n, m;                       // n = number of nodes, m = number of edges
int capacity[MAXN][MAXN];       // capacity matrix
int residual[MAXN][MAXN];       // residual capacity matrix
bool visited[MAXN];             // visited array for DFS
int matchL[MAXN], matchR[MAXN]; // matching arrays

bool dfs(int node)
{
    if (visited[node])
        return false;
    visited[node] = true;
    for (int next = 0; next < n; next++)
    {
        if (residual[node][next] > 0)
        {
            if (matchR[next] == -1 || dfs(matchR[next]))
            {
                matchL[node] = next;
                matchR[next] = node;
                return true;
            }
        }
    }
    return false;
}

int fordFulkerson()
{
    // initialize residual capacity matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            residual[i][j] = capacity[i][j];
        }
    }
    // initialize matching arrays
    memset(matchL, -1, sizeof(matchL));
    memset(matchR, -1, sizeof(matchR));
    // find maximum matching using DFS
    bool foundPath = true;
    while (foundPath)
    {
        foundPath = false;
        memset(visited, false, sizeof(visited)); // set visited array to false
        for (int i = 0; i < n; i++)
        {
            if (matchL[i] == -1 && dfs(i))
            {
                foundPath = true;
            }
        }
    }
    // count number of matched vertices
    int matchedVertices = 0;
    for (int i = 0; i < n; i++)
    {
        if (matchL[i] != -1)
        {
            matchedVertices++;
        }
    }
    return matchedVertices;
}

int main()
{
    cin >> n >> m;
    memset(capacity, 0, sizeof(capacity)); // set capacity matrix to 0
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        capacity[u][v] = 1; // add edge to capacity matrix
    }
    int maxMatching = fordFulkerson();
    cout << "Maximum Bipartite Matching: " << maxMatching << endl;
    return 0;
}
