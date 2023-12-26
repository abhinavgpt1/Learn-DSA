#include<utility>
#include<set>
#include<vector>
using namespace std;

// Solution with min heap (priority queue) is not certain to run once for every node -> hence it isn't an efficient soln. 
// T(n) = EVlogV and S(n) = O(heapsize) = O(E) ~ O(V^2)

// Solution 1: Using set
class Solution {
    // Using Set to pick and iterate over nodes
    // T(n) = O(ElogV)
    // S(n) = O(V) -> set and dist
	public:
    vector <int> dijkstra(int V, vector<vector<int>> adj[], int S)
    {
        set<pair<int, int>> pending;
        vector<int> dist(V, INT_MAX);
        
        pending.insert({0, S});
        while(!pending.empty()){ // O(V)
            set<pair<int, int>>::iterator it = pending.begin();
            pending.erase(it); //log(V)
            int node = it->second;
            int distNode = it->first;
            dist[node] = distNode;
            
            for(vector<int> vec: adj[node]){ //O(V) == Ea
                int adjNode = vec[0];
                int adjNodeEdgeWeight = vec[1];
                if(dist[adjNode] > distNode + adjNodeEdgeWeight){ //log(V)
                    if(dist[adjNode] != INT_MAX){
                        pending.erase({dist[adjNode], adjNode});
                    }
                    dist[adjNode] = distNode + adjNodeEdgeWeight;
                    pending.insert({dist[adjNode], adjNode});
                }
            }
        }
        return dist;
    }
};

// Solution 2: Using visited array and looping V times - Coding ninjas way
// T(n) = O(V^2 + E) ~ O(V^2) in worst case when E = V(V-1)
// S(n) = O(V) -> visited, dist