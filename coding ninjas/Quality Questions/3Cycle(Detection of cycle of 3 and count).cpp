/*
3 Cycle
Send Feedback
Given a graph with N vertices (numbered from 0 to N-1) and M undirected edges, then count the distinct 3-cycles in the graph. A 3-cycle PQR is a cycle in which (P,Q), (Q,R) and (R,P) are connected by an edge.
Input Format :
The first line of input contains two space separated integers, that denotes the value of N and M.
Each of the following M lines contain two integers, that denote the vertices which have an undirected edge between them. Let us denote the two vertices with the symbol u and v.
Output Format :
Print the count the number of 3-cycles in the given graph
Constraints :
0 <= N <= 100
0 <= M <= (N*(N-1))/2
0 <= u <= N - 1
0 <= v <= N - 1
Time Limit: 1 sec
Sample Input 1:
3 3
0 1
1 2
2 0
Sample Output 1:
1
*/

/*
// recursion solution will definitely require visited array
// loops won't require any
// 10 approaches in total - 5 listed
// ways possible - 8
// (2) multi count using loop - grid and list
// (2) multi count using recursion - grid and list

// these are bad - because it will use vec.assign(n, false)
// (2) single count using loop - grid and list
// (2) single count using recursion - grid and list

*/

#include <iostream>
#include <vector>
using namespace std;

// approach 0
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> graph(n, vector<bool>(n));
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u][v] = graph[v][u] = true;
    }
    // O(N^3), where N = vertices in graph
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (graph[i][j] && graph[j][k] && graph[k][i])
                    count++;
            }
        }
    }
    cout << count / 6;
}

// ninja's way - not looking back on previous vertices - just seeking nodes number increasingly
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> graph(n, vector<bool>(n));
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u][v] = graph[v][u] = true;
    }
    // O(N^3) but efficient than others
    int count = 0;
    for (int i = 0; i < n - 2; i++)
    {
        for (int j = i + 1; j < n - 1; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                if (graph[i][j] && graph[j][k] && graph[k][i])
                    count++;
            }
        }
    }
    cout << count;
}

// approach 1 - multiple count - using grid graph & loops
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> graph(n, vector<bool>(n, false));
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u][v] = graph[v][u] = true;
    }

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j])
            {
                for (int k = 0; k < n; k++)
                {
                    if (k == i)
                        continue;
                    if (graph[j][k] && graph[k][i])
                        count++;
                }
            }
        }
    }
    cout << count / 6;
}
// approach 2 - multi counting - using adj. list & recursion
int getCount(vector<vector<int>> &graph, vector<bool> &visited, int n, int index, int nodeCount, int parent)
{

    int count = 0;
    if (nodeCount == 3)
    {
        for (int i = 0; i < graph[index].size(); i++)
        {
            if (graph[index][i] == parent)
                count++;
        }
        return count;
    }
    visited[index] = true;
    for (int i = 0; i < graph[index].size(); i++)
    {
        if (visited[graph[index][i]])
            continue;
        count += getCount(graph, visited, n, graph[index][i], nodeCount + 1, parent);
    }
    visited[index] = false;
    return count;
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<bool> visited(n, false);
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        count += getCount(graph, visited, n, i, 1, i);
    }
    cout << count / 6;
    // for a node - clockwise and anti-clockwise
    // for all nodes in a cycle(of 3) = 2*3 = 6 times a count for same cycle
}

// approach 3 - single counting of loop - but not good if number of nodes are great (vec.assign(n, false) is used)
// although it passed on platform
int getCount(vector<vector<int>> &graph, vector<bool> &tempvisited, vector<bool> &visited, int n, int index, int nodeCount, int parent)
{

    int count = 0;
    if (nodeCount == 3)
    {
        for (int i = 0; i < graph[index].size(); i++)
        {
            if (graph[index][i] == parent)
                count++;
        }
        return count;
    }
    tempvisited[index] = true;
    for (int i = 0; i < graph[index].size(); i++)
    {
        if (tempvisited[graph[index][i]] || visited[graph[index][i]])
            continue;
        count += getCount(graph, tempvisited, visited, n, graph[index][i], nodeCount + 1, parent);
    }
    return count;
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<bool> visited(n, false);
    vector<bool> tempvisited(n, false);

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        count += getCount(graph, tempvisited, visited, n, i, 1, i);
        tempvisited.assign(n, false);
        visited[i] = true; // work over for this node
    }
    cout << count;
}
