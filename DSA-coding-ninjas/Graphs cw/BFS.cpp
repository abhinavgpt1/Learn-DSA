/*
Code : (Basic)BFS Traversal
*/
#include<iostream>
using namespace std;
void print(int ** edges, int n, int sv, bool * visited){
	cout<<sv<<endl;
	visited[sv] = true;

	for(int i = 0; i < n; i++){

		if(edges[sv][i]){
			if(visited[i])
				continue;
			print(edges, n, i, visited);
		}
	}
}
void print_bfs(int ** edges, int V, int E, int sv){
    bool * visited = new bool[V]();
    queue<int> pending;
    pending.push(sv);
    visited[sv] = true;
    //commenting line 23, 52 and  uncommenting line 46 will cause errors
   
   	/*
    eg.
    5 8
	0 1
	0 4
	1 2
	2 0
	2 4
	3 0
	3 2
	4 3
	
	your o/p:012342344 something
	correct o/p: 01234
    */
    while(!pending.empty()){
        int front = pending.front();
  		pending.pop();

  		cout<<front<<" ";
  		// visited[front] = true;  	
  		for(int i = 0; i < V; i++){
  			if(edges[front][i]){
  				if(visited[i])
  					continue;
  				pending.push(i);
  				visited[i] = true;
  			}
  		}
    }
}

int main(){
  int n,e;
  cin >> n >> e;
  int **edges = new int[n];
  for(int i = 0; i < n; i++){
  	edges[i] = new int[n]();
  }
  for(int i = 0; i < e; i++){
  	int f,s;
  	cin>>f>>s;
  	edges[f][s] = edges[s][f] = 1;
  }
  bool *visited = new bool[n]();
  // print(edges, n, 0, visited);
  print_bfs(edges, n, 0);
  for(int i = 0; i < n; i++)
  	delete[] edges[i];
  delete[] edges;
}