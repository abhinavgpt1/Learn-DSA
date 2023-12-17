#include <bits/stdc++.h>
// Note: isCyclic should be checked before or during topoSort

// Solution 1
class Solution
{

	bool isCyclic(vector<int> adj[], vector<int> &visited, int index, vector<int> &ans)
	{

		visited[index] = 1;
		for (int v : adj[index])
		{
			if (visited[v] == 0)
			{
				if (isCyclic(adj, visited, v, ans))
					return true;
			}
			else if (visited[v] == 1)
				return true;
		}
		visited[index] = -1;
		ans.push_back(index);
		return false;
	}

public:
	// Function to return list containing vertices in Topological order.
	vector<int> topoSort(int V, vector<int> adj[])
	{
		// Topological sort DFS (inclusive of cycle detection (using single visited array))
		vector<int> visited(V, 0);
		vector<int> ans;
		for (int i = 0; i < V; i++)
		{
			if (!visited[i] && isCyclic(adj, visited, i, ans))
				return vector<int>();
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}
};

// Solution 2 - conventional way
class Solution
{
	bool isCyclic(vector<int> adj[], vector<bool> &visited, vector<bool> &pathVisited, int index, vector<int> &ans)
	{
		visited[index] = true;
		pathVisited[index] = true;

		for (int v : adj[index])
		{
			if (!visited[v])
			{
				if (isCyclic(adj, visited, pathVisited, v, ans))
					return true;
			}
			else if (pathVisited[v])
				return true;
		}
		pathVisited[index] = false;
		ans.push_back(index);
		return false;
	}

public:
	// Function to return list containing vertices in Topological order.
	vector<int> topoSort(int V, vector<int> adj[])
	{
		// Topological sort DFS (inclusive of cycle detection (in a conventional way))
		vector<bool> visited(V, false);
		vector<bool> pathVisited(V, false);
		vector<int> ans;
		for (int i = 0; i < V; i++)
		{
			if (!visited[i] && isCyclic(adj, visited, pathVisited, i, ans))
				return vector<int>();
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}
};

// Solution 3 - solution 1, but with stack and some changes in isCycle function
class Solution
{
	bool isCycle(int index, stack<int> &stk, vector<int> adj[], vector<int> &visited)
	{
		visited[index] = 1;
		for (int x : adj[index])
		{
			if (visited[x] == -1)
				continue;
			if (visited[x] == 1 || isCycle(x, stk, adj, visited))
				return true;
		}
		visited[index] = -1;
		stk.push(index);
		return false;
	}

public:
	vector<int> topoSort(int V, vector<int> adj[])
	{
		stack<int> stk;
		vector<int> visited(V, 0);
		for (int i = 0; i < V; i++)
		{
			if (!visited[i] && isCycle(i, stk, adj, visited))
				return vector<int>();
		}
		vector<int> ans;
		while (!stk.empty())
		{
			ans.push_back(stk.top());
			stk.pop();
		}

		return ans;
	}
};

// Another way to check visited
// -> mark all visited as 0 intially
// -> mark visited[i] with constants for all nodes traversed when topoSort is called
// -> check with this constant if visited[i] != 0

// Wrong Solution 1 - cycle in graph is not checked, works only for DAG
class WrongSolution
{
	stack<int> ansStack;

public:
	// Function to return list containing vertices in Topological order.
	void dfsApproach(vector<int> adj[], int index, vector<bool> &visited)
	{

		visited[index] = true;
		for (int i = 0; i < adj[index].size(); i++)
		{
			int child = adj[index][i];
			if (!visited[child])
				dfsApproach(adj, child, visited);
		}
		ansStack.push(index);
	}
	vector<int> topoSort(int V, vector<int> adj[])
	{
		vector<bool> visited(V, false);
		for (int i = 0; i < V; i++)
		{
			if (!visited[i])
				dfsApproach(adj, i, visited);
		}
		vector<int> ans;

		while (!ansStack.empty())
		{
			ans.push_back(ansStack.top());
			ansStack.pop();
		}
		return ans;
	}
};

// Wrong Solution 2 - cycle in graph is not checked, works only for DAG
class WrongSolution
{
	void topoSort(vector<int> adj[], vector<bool> &visited, int index, vector<int> &ans)
	{
		visited[index] = true;
		for (int v : adj[index])
		{
			if (!visited[v])
				topoSort(adj, visited, v, ans);
		}
		ans.push_back(index);
	}

public:
	// Function to return list containing vertices in Topological order.
	vector<int> topoSort(int V, vector<int> adj[])
	{
		vector<bool> visited(V, false);
		vector<int> ans;
		for (int i = 0; i < V; i++)
		{
			if (!visited[i])
				topoSort(adj, visited, i, ans);
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}
};