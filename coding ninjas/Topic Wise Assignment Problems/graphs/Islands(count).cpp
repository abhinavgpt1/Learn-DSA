/*
Islands
Send Feedback
An island is a small piece of land surrounded by water . A group of islands is said to be connected if we can reach from any given island to any other island in the same group . Given V islands (numbered from 1 to V) and E connections or edges between islands. Can you count the number of connected groups of islands.
Input Format :
The first line of input contains two integers, that denote the value of V and E.
Each of the following E lines contains two integers, that denote that there exists an edge between vertex a and b. 
Output Format :
Print the count the number of connected groups of islands
Constraints :
0 <= V <= 1000
0 <= E <= (V * (V-1)) / 2
0 <= a <= V - 1
0 <= b <= V - 1
Time Limit: 1 second
Sample Input 1:
5 8
0 1
0 4
1 2
2 0
2 4
3 0
3 2
4 3
Sample Output 1:
1 

*/
#include <iostream>
#include <vector>
using namespace std;

void dfs(bool **graph, int V, vector<bool> &visited, int index)
{
	visited[index] = true;
	for (int i = 0; i < V; i++)
	{
		if (graph[index][i] == 1 && !visited[i])
			dfs(graph, V, visited, i);
	}
}

int main() {
    int V, E;
	cin >> V >> E;
    if(V == 0)
    {
        cout<<0;
        return 0;
    }

    bool **graph = new bool *[V];
	for (int i = 0; i < V; i++)
		graph[i] = new bool[V]();
	for (int i = 0; i < E; i++)
	{
		int u, v;
		cin >> u >> v;

		graph[u][v] = 1;
		graph[v][u] = 1;
	}
	vector<bool> visited(V, false);
    int count = 0;    
	for (int i = 0; i < V; i++)
	{
		if (!visited[i]){
            dfs(graph, V, visited, i);
            count++;
        }
	}
    cout<<count<<endl;
}