/*
Code : All connected components
Send Feedback
Given an undirected graph G(V,E), find and print all the connected components of the given graph G.
Note:
1. V is the number of vertices present in graph G and vertices are numbered from 0 to V-1. 
2. E is the number of edges present in graph G.
3. You need to take input in main and create a function which should return all the connected components. And then print them in the main, not inside function.
Print different components in new line. And each component should be printed in increasing order (separated by space). Order of different components doesn't matter.
Input Format :
The first line of input contains two integers, that denote the value of V and E.
Each of the following E lines contains two space separated integers, that denote that there exists an edge between vertex a and b.
Output Format :
Print different components in new line. And each component should be printed in increasing order of vertices (separated by space). Order of different components doesn't matter.
Constraints :
0 <= V <= 1000
0 <= E <= (V * (V - 1)) / 2
0 <= a <= V - 1
0 <= b <= V - 1
Sample Input 1:
4 2
0 1
2 3
Sample Output 1:
0 1 
2 3 
Sample Input 2:
4 3
0 1
1 3 
0 3
Sample Output 2:
0 1 3 
2
*/

**********************
// problem at one tc -> due to this form: vector<vector<int>> graph
// -> Q - why pass by value of graph / visited array (as vector) didn't worked in graph problems? (Runtime error or TLE)("CODINGNINJA" matrix search problem)
// A - copying of large vector<vector> / vector in multiple function calls fills up the stack
**********************

#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;
// use & in graph - will work. Reason, copying of huge graph in every function call
void dfs(vector<vector<int>> graph, vector<bool> &visited, int index, vector<int> &ans)
{

	visited[index] = true;
    ans.push_back(index);
	for (int i = 0; i < graph[index].size(); i++)
	{
		if (!visited[graph[index][i]])
			dfs(graph, visited, graph[index][i], ans);
	}
}
int main()
{
  int V, E;
  cin >> V >> E;

  vector<vector<int>> graph(V);
	for (int i = 0; i < E; i++)
	{
		int u, v;
		cin >> u >> v;
        
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	vector<bool> visited(V, false);
    vector<int> ans;
	for (int i = 0; i < V; i++)
	{
		if (!visited[i]){
            dfs(graph, visited, i, ans);
            sort(ans.begin(), ans.end());
            for(auto x: ans)
                cout<<x<<" ";
            cout<<endl;
            ans.clear();
        }
	}
  return 0;
}

// works - since multiple copies of graph isn't created.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void dfs(bool **graph, int V, vector<bool> &visited, int index, vector<int> &ans)
{

	visited[index] = true;
	ans.push_back(index);
	for (int i = 0; i < V; i++)
	{
		if (graph[index][i] == 1 && !visited[i])
			dfs(graph, V, visited, i, ans);
	}
}
int main()
{
	int V, E;
	cin >> V >> E;

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
	vector<int> ans;
	for (int i = 0; i < V; i++)
	{
		if (!visited[i])
		{
			dfs(graph, V, visited, i, ans);
			sort(ans.begin(), ans.end());
			for (auto x : ans)
				cout << x << " ";
			cout << endl;
			ans.clear();
		}
	}
	return 0;
}
