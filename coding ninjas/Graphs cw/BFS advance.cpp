/*
Code : BFS Traversal//hanles disconnected graph too
Send Feedback
Given an undirected and disconnected graph G(V, E), print its BFS traversal.
Here you need to consider that you need to print BFS path starting from vertex 0 only.
V is the number of vertices present in graph G and vertices are numbered from 0 to V-1.
E is the number of edges present in graph G.
Note : 1. Take graph input in the adjacency matrix.


2. Handle for Disconnected Graphs as well


Input Format :
Line 1: Two Integers V and E (separated by space)
Next 'E' lines, each have two space-separated integers, 'a' and 'b', denoting that there exists an edge between Vertex 'a' and Vertex 'b'.
Output Format :
BFS Traversal (separated by space)
Constraints :
2 <= V <= 1000
1 <= E <= 1000
Sample Input 1:
4 4
0 1
0 3
1 2
2 3
Sample Output 1:
0 1 3 2
*/

//approach: simpler
/*
// C++ implementation of modified BFS 
#include<bits/stdc++.h> 
using namespace std; 

// A utility function to add an edge in an 
// undirected graph. 
void addEdge(vector<int> adj[], int u, int v) 
{ 
  adj[u].push_back(v); 
} 

// A utility function to do BFS of graph 
// from a given vertex u. 
void BFSUtil(int u, vector<int> adj[], 
      vector<bool> &visited) 
{ 

  // Create a queue for BFS 
  list<int> q; 

  // Mark the current node as visited and enqueue it 
  visited[u] = true; 
  q.push_back(u); 

  // 'i' will be used to get all adjacent vertices 4 
  // of a vertex list<int>::iterator i; 

  while(!q.empty()) 
  { 
    // Dequeue a vertex from queue and print it 
    u = q.front(); 
    cout << u << " "; 
    q.pop_front(); 

    // Get all adjacent vertices of the dequeued 
    // vertex s. If an adjacent has not been visited, 
    // then mark it visited and enqueue it 
    for (int i = 0; i != adj[u].size(); ++i) 
    { 
      if (!visited[adj[u][i]]) 
      { 
        visited[adj[u][i]] = true; 
        q.push_back(adj[u][i]); 
      } 
    } 
  } 
} 

// This function does BFSUtil() for all 
// unvisited vertices. 
void BFS(vector<int> adj[], int V) 
{ 
  vector<bool> visited(V, false); 
  for (int u=0; u<V; u++) 
    if (visited[u] == false) 
      BFSUtil(u, adj, visited); 
} 

// Driver code 
int main() 
{ 
  int V = 5; 
  vector<int> adj[V]; 

  addEdge(adj, 0, 4); 
  addEdge(adj, 1, 2); 
  addEdge(adj, 1, 3); 
  addEdge(adj, 1, 4); 
  addEdge(adj, 2, 3); 
  addEdge(adj, 3, 4); 
  BFS(adj, V); 
  return 0; 
}

*/
#include <iostream>
#include<queue>
using namespace std;
void print_bfs(int ** edges, int V, int E, int sv){
    bool * visited = new bool[V]();
    queue<int> pending;
    pending.push(sv);
    visited[sv] = true;
  int count = 0;
    while(1){
        
      while(!pending.empty()){
        int front = pending.front();
        pending.pop();
        
        cout<<front<<" ";
        count++;
        
        for(int i = 0; i < V; i++){
          if(edges[front][i]){
            if(visited[i])
              continue;
            pending.push(i);
            visited[i] = true;
          }
        }
      }
      
      //check if there exists disconnected graph segments
      if(count != V){
        for(int i = 0; i < V; i++){
          if(visited[i] == false){
              pending.push(i);
              visited[i] = true;
              break;
          }
        }
      }
      else 
        break;

    }
}
int main() {
    int V, E;
    cin >> V >> E;

  /*

       Write Your Code Here
     Complete the Rest of the Program
     You have to take input and print the output yourself
   
  */
  int **edges = new int *[V];
    for(int i = 0; i < V; i++){
        edges[i] = new int[V];
    }
    for(int i = 0; i < E; i++){
        int f,s;
        cin >> f >> s;
        edges[f][s] = edges[s][f] = 1;
    }
    print_bfs(edges, V, E, 0);
  return 0;
}