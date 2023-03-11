//distance from src = 0 to every other node is required

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int findMinDistIndex(vector<bool> &visited, vector<int> &distance, int V){
    int minIndex = -1;
    for(int i=0; i<V; i++){
        if(!visited[i] && (minIndex == -1 || distance[i] < distance[minIndex]))
            minIndex = i;
    }
    return minIndex;
}
void dijkstra(vector<vector<int>> &graph, int V, int src){
    vector<bool> visited(V, false);
    vector<int> distance(V ,INT_MAX);
    
    distance[src] = 0;
    
    for(int i=0; i<V-1; i++){
        int index = findMinDistIndex(visited, distance, V);
        visited[index] = true;
        for(int j=0; j<V; j++){
            if(graph[index][j] != 0 && !visited[j] && distance[j] > graph[index][j] + distance[index]){
                distance[j] = graph[index][j] + distance[index];
            }
		}
    }
    for(int i=0; i<V; i++){
        cout<<i<<" "<<distance[i]<<endl;
    }
}
int main() {
    int V, E;
    cin>>V>>E;
    vector<vector<int>>graph(V, vector<int>(V, 0));
    for(int i=0; i<E; i++){
        int u, v, w;
        cin>>u>>v>>w;
        graph[u][v] = graph[v][u] = w;
    }
    
    int src = 0;
    
//     print shortest distance from src to every other node
    dijkstra(graph, V, src);
}