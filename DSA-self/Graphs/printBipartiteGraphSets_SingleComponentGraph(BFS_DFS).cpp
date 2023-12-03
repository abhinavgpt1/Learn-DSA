#include <bits/stdc++.h>
using namespace std;

// can be extended for multi-component graph
//  can use visited array only for setNo checking - see bipartiteGraphBFS(gfg_medium).cpp
bool bipartiteBFS(vector<vector<int>> &graph, int V)
{
  queue<pair<int, int>> pending;
  vector<int> visited(V, -1), red, blue;

  pending.push({0, 0});
  visited[0] = 0;

  while (!pending.empty())
  {
    pair<int, int> front = pending.front();
    pending.pop();

    int index = front.first, setNo = front.second;
    if (setNo)
      blue.push_back(index);
    else
      red.push_back(index);

    for (int i = 0; i < graph[index].size(); i++)
    {
      if (visited[graph[index][i]] == -1)
      {
        visited[graph[index][i]] = !setNo;
        pending.push({graph[index][i], !setNo});
      }
      else if (visited[graph[index][i]] == setNo)
        return false;
    }
  }

  for (int x : red)
  {
    cout << x << " ";
  }
  cout << endl;
  for (int x : blue)
  {
    cout << x << " ";
  }
  cout << endl;
  return true;
}
bool bipartiteDFSHelper(vector<vector<int>> &graph, int V, int index, vector<int> &visited, int parentSetNo, vector<int> &red, vector<int> &blue)
{
  visited[index] = !parentSetNo;
  if (visited[index])
    red.push_back(index);
  else
    blue.push_back(index);

  for (int i = 0; i < graph[index].size(); i++)
  {
    if (visited[graph[index][i]] == -1)
    {
      bool tmp = bipartiteDFSHelper(graph, V, graph[index][i], visited, visited[index], red, blue);
      if (!tmp)
        return tmp;
    }
    else if (visited[graph[index][i]] == visited[index])
      return false;
  }

  return true;
}
bool bipartiteDFS(vector<vector<int>> &graph, int V)
{
  vector<int> visited(V, -1), red, blue;

  bool ans = bipartiteDFSHelper(graph, V, 0, visited, 1, red, blue);

  if (ans)
  {
    for (int x : blue)
      cout << x << " ";
    cout << endl;
    for (int x : red)
      cout << x << " ";
  }
  cout << endl;
  return ans;
}
int main()
{
  int v, e;
  cin >> v >> e;
  vector<vector<int>> graph(v);
  for (int i = 0; i < e; i++)
  {
    int u, w;
    cin >> u >> w;
    graph[u].push_back(w);
    graph[w].push_back(u);
  }
  // can be extended for multi-component graph - just keep a visited array

  // if (bipartiteBFS(graph, v))
  //   cout << "Yes" << endl;
  // else
  //   cout << "No" << endl;
  if (bipartiteDFS(graph, v))
    cout << "Yes" << endl;
  else
    cout << "No" << endl;
}

// can use visited array only for setNo checking - see bipartiteGraphBFS(gfg_medium).cpp
bool isBipartiteBFS(vector<int> adj[], vector<int> &visited, int index)
{

  queue<int> pending;
  pending.push(index);
  visited[index] = 0;

  while (!pending.empty())
  {
    int front = pending.front();
    pending.pop();
    int setNo = visited[front];

    for (int i = 0; i < adj[front].size(); i++)
    {
      int child = adj[front][i];

      if (visited[child] == -1)
      {
        pending.push(child);
        visited[child] = !setNo;
      }
      else if (visited[child] == setNo)
        return false;
    }
  }
  return true;
}
