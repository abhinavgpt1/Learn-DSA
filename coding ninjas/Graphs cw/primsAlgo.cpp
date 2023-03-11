#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

int findMinWeightIndex(vector<int> &weight, vector<bool> &visited, int V)
{

    int minIndex = -1;
    for (int i = 0; i < V; i++)
    {
        if (!visited[i] && (minIndex == -1 || weight[i] < weight[minIndex]))
        {
            minIndex = i;
        }
    }
    return minIndex;
}
void prims(vector<vector<int>> &graph, int V)
{
    vector<bool> visited(V, false);
    vector<int> weight(V, INT_MAX);
    vector<int> parent(V, -1);

    weight[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < V-1; i++)
    {
        int index = findMinWeightIndex(weight, visited, V);
        visited[index] = true;

        
        for (int j = 0; j < V; j++)
        {
            if (graph[index][j] && !visited[j] && weight[j] > graph[index][j])
            {
                weight[j] = graph[index][j];
                parent[j] = index;
            }
        }
    }
    for (int i = 1; i < V; i++)
    {
        if (i < parent[i])
            cout << i << " " << parent[i] << " " << weight[i] << endl;
        else
            cout << parent[i] << " " << i << " " << weight[i] << endl;
    }
}
int main()
{
    int V, E;
    cin >> V >> E;

    vector<vector<int>> graph(V, vector<int>(V, 0));

    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = graph[v][u] = w;
    }

    prims(graph, V);

    return 0;
}
