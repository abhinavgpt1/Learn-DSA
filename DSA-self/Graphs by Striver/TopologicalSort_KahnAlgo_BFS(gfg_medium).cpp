#include <bits/stdc++.h>
using namespace std;

// Solution 1
class Solution
{
public:
	// Function to return list containing vertices in Topological order.
	vector<int> topoSort(int V, vector<int> adj[])
	{
		// Kahn's Algo
		vector<int> indegree(V, 0), ans;
		for (int i = 0; i < V; i++)
		{
			for (int x : adj[i])
				indegree[x]++;
		}

		queue<int> pending;

		for (int i = 0; i < V; i++)
		{
			if (indegree[i] == 0)
				pending.push(i);
		}
		while (!pending.empty())
		{
			int front = pending.front();
			pending.pop();
			for (int x : adj[front])
			{

				if (indegree[x] == 0) // redundant check, but avoids decrement operation
					continue;
				indegree[x]--;
				if (indegree[x] == 0)
					pending.push(x);
			}
			ans.push_back(front);
		}
		return ans;
	}
};

// Solution 2
class Solution
{
public:
	// Function to return list containing vertices in Topological order.
	vector<int> topoSort(int V, vector<int> adj[])
	{
		// Kahn's Algo
		vector<int> indegree(V, 0), visited(V, 0), ans;
		for (int i = 0; i < V; i++)
		{
			for (int x : adj[i])
				indegree[x]++;
		}

		queue<int> pending;

		for (int i = 0; i < V; i++)
		{
			if (indegree[i] == 0)
			{
				pending.push(i);
				visited[i] = 1;
			}
		}
		while (!pending.empty())
		{
			int front = pending.front();
			pending.pop();
			for (int x : adj[front])
			{

				if (visited[x])
					continue;
				indegree[x]--;
				if (indegree[x] == 0)
				{
					pending.push(x);
					visited[x] = 1;
				}
			}
			ans.push_back(front);
		}
		return ans;
	}
};

// Wrong Solution 1 - simple BFS can't be used
class WrongSolution
{
public:
	// Function to return list containing vertices in Topological order.
	// WRONG - eg 0 1, 1 2, 2 3, 0 3 -> ans should be 0 1 2 3 but this algo will give - 0 1 3 2
	vector<int> bfsApproach(vector<int> adj[], int index, vector<bool> &visited)
	{
		vector<int> ans;
		queue<int> pending;
		pending.push(index);
		visited[index] = true;
		while (!pending.empty())
		{
			int front = pending.front();
			pending.pop();
			ans.push_back(front);
			for (int i : adj[front])
			{
				if (!visited[i])
				{
					pending.push(i);
					visited[i] = true;
				}
			}
		}
		return ans;
	}
	vector<int> topoSort(int V, vector<int> adj[])
	{
		vector<bool> visited(V, false);
		vector<int> ans;
		for (int i = 0; i < V; i++)
		{
			if (!visited[i])
			{

				vector<int> tempAns = bfsApproach(adj, i, visited);
				for (int x : ans)
					tempAns.push_back(x);
				ans = tempAns;
			}
		}
		return ans;
	}
};
class Solution
{
public:
	vector<int> topoSort(int V, vector<int> adj[])
	{
		// kahn algo
	}
};

int main()
{
	Solution sol;
	int v, e;
	cin >> v >> e;
	vector<int> adj[v];
	for (int i = 0; i < e; i++)
	{
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
	}

	vector<int> ans = sol.topoSort(v, adj);
	for (int i : ans)
		cout << i << " ";
	cout << endl;
}
