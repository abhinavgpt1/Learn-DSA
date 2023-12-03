#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isEdgeOk(int u, int v, vector<int> &parent)
{
  // top most parent checking

  while (parent[u] != u)
  {
    u = parent[u];
  }
  while (parent[v] != v)
  {
    v = parent[v];
  }
  if (u == v)
    return false;
  
  parent[u] = v;
  
  return true;
}
void printMST(vector<pair<int, pair<int, int>>> &edges, int V)
{
  sort(edges.begin(), edges.end());
  
  vector<int> parent(V);
  
  for (int i = 0; i < V; i++)
    parent[i] = i;
  
  int count = 0, i = 0;
  
  while (count != V - 1)
  {
    int u = edges[i].second.first;
    int v = edges[i].second.second;
    int w = edges[i].first;
   
    if (isEdgeOk(u, v, parent))
    {
      cout << min(u, v) << " " << max(u, v) << " " << w << endl;
      count++;
    }
    
    i++;
  }

}
int main()
{
  int V, E;
  cin >> V >> E;
  
  vector<pair<int, pair<int, int>>> edges;
  
  for (int i = 0; i < E; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    edges.push_back({w, {u, v}});
  }
  
  printMST(edges, V);
  
  return 0;
}

/*
Code : Kruskal's Algorithm

Given an undirected, connected and weighted graph G(V, E) with V number of vertices (which are numbered from 0 to V-1) and E number of edges.
Find and print the Minimum Spanning Tree (MST) using Kruskal's algorithm.

For printing MST follow the steps -
1. In one line, print an edge which is part of MST in the format -
v1 v2 w
where, v1 and v2 are the vertices of the edge which is included in MST and whose weight is w. And v1  <= v2 i.e. print the smaller vertex first while printing an edge.
2. Print V-1 edges in above format in different lines.

Note : Order of different edges doesn't matter.

Input Format :
Line 1: Two Integers V and E (separated by space)
Next E lines : Three integers ei, ej and wi, denoting that there exists an edge between vertex ei and vertex ej with weight wi (separated by space)
Output Format :
Print the MST, as described in the task.
Constraints :
2 <= V, E <= 10^5
Time Limit: 1 sec
Sample Input 1 :
4 4
0 1 3
0 3 5
1 2 1
2 3 8
Sample Output 1 :
1 2 1
0 1 3
0 3 5
*/