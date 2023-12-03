/*
Code : Is Connected ?
Send Feedback
Given an undirected graph G(V,E), check if the graph G is connected graph or not.
Note:
1. V is the number of vertices present in graph G and vertices are numbered from 0 to V-1. 
2. E is the number of edges present in graph G.
Input Format :
The first line of input contains two integers, that denote the value of V and E.
Each of the following E lines contains two integers, that denote that there exists an edge between vertex a and b.
Output Format :
The first and only line of output contains "true" if the given graph is connected or "false", otherwise.
Constraints :
0 <= V <= 1000
0 <= E <= (V * (V - 1)) / 2
0 <= a <= V - 1
0 <= b <= V - 1
Time Limit: 1 second
Sample Input 1:
4 4
0 1
0 3
1 2
2 3
Sample Output 1:
true
Sample Input 2:
4 3
0 1
1 3 
0 3
Sample Output 2:
false 
Sample Output 2 Explanation
The graph is not connected, even though vertices 0,1 and 3 are connected to each other but there isn’t any path from vertices 0,1,3 to vertex 2. 
*/
#include <iostream>
#include <vector>
using namespace std;
void dfs(bool** graph, int V, vector<bool> &visited, int index)
{

	visited[index] = true;
	for (int i = 0; i < V; i++)
	{
		if (graph[index][i] == 1 && !visited[i])
			dfs(graph, V, visited, i);
	}
}
bool isConnected(){
    
    int V, E;
	cin >> V >> E;
    
    if(V == 0)
        return (E == 0 ? 1 : 0);
    
	bool ** graph = new bool*[V];
	// vector<vector<int>> graph(V); this way is giving error for 1 case don't know what
	// -> Q - why pass by value of graph / visited array (as vector) didn't worked in graph problems? (Runtime error or TLE)("CODINGNINJA" matrix search problem)
	// A - copying of large vector<vector> / vector in multiple function calls fills up the stack
	// use & in graph - will work. Reason, copying of huge graph in every function call
    for(int i=0; i<V; i++)
        graph[i] = new bool[V]();
	for (int i = 0; i < E; i++)
	{
		int u, v;
		cin >> u >> v;
        
		graph[u][v] = 1;
		graph[v][u] = 1;
	}
	vector<bool> visited(V, false);
	dfs(graph, V, visited, 0);
    
	for (int i = 0; i < V; i++)
	{
		if (!visited[i])
			return false;
	}
    return true;
}
int main()
{
	cout<<(isConnected() == 1 ? "true" : "false");
	return 0;
}
