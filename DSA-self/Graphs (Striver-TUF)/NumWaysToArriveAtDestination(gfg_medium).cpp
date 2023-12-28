/*
 * Number of Ways to Arrive at Destination
 * ---------------------------------------
 * You are in a city that consists of n intersections numbered from 0 to n - 1 with bi-directional roads between some intersections. 
 * The inputs are generated such that you can reach any intersection from any other intersection and that there is at most one road between any two intersections.
 * 
 * You are given an integer n and a 2D integer array roads where roads[i] = [ui, vi, timei] means that there is a road between intersections ui and vi that takes timei minutes to travel. 
 * You want to know in how many ways you can travel from intersection 0 to intersection n - 1 in the shortest amount of time.
 * 
 * Return the number of ways you can arrive at your destination in the shortest amount of time. 
 * Since the answer may be large, return it modulo 109 + 7.
*/
// Solution 1: Dijkstra with set - ElogV
typedef long long int lli;
class Solution {
    const int MOD = 1e9 + 7;
  public:
    // caching minimum time to reach an intersection
    int countPaths(int n, vector<vector<int>>& roads) {
        int src = 0, dest = n-1;
        vector<vector<pair<int, int>>> graph(n);
        for(vector<int> road: roads){
            graph[road[0]].push_back({road[1], road[2]});
            graph[road[1]].push_back({road[0], road[2]});
        }
        
        vector<lli> dist(n, INT_MAX); //min. time to reach an intersection
        vector<int> ways(n, 0); //no. of paths leading to the intersection with min. dist
        dist[src] = 0; ways[src] = 1;
        set<pair<lli, int>> pending; //dist, intersection/node
        pending.insert({0, src});
        
        while(!pending.empty()){
            auto it = pending.begin();
            pending.erase(it);
            
            // NOTE: once a node is out, it'll not be visited minimally again 
            // - The whole point of Dijkstra
            lli currDist = it->first;
            int currNode = it->second;
            int waysCurrNode = ways[currNode];
            
            if(currNode == dest){
                return waysCurrNode;
            }
            
            for(pair<int, int> p: graph[currNode]){
                int nextNode = p.first;
                int edgeNextNode = p.second;
                if(dist[nextNode] > currDist + edgeNextNode){
                    if(dist[nextNode] != INT_MAX){
                        pending.erase({dist[nextNode], nextNode});
                    }
                    dist[nextNode] = currDist + edgeNextNode;
                    ways[nextNode] = waysCurrNode; //mistake in earlier solution
                    
                    pending.insert({dist[nextNode], nextNode});
                } else if(dist[nextNode] == currDist + edgeNextNode){
                    // the entry in pending will exist for sure, 
                    // since currDist < dist[nextNode] as edge weight>0
                    ways[nextNode] = (ways[nextNode]%MOD + waysCurrNode%MOD)%MOD;
                }
            }
        }

        return 0;
    }
};

// Solution 2: Breaking concerns : O(2*ElogV) -> better to use above solution
typedef long long int lli;
class Solution {
    const int MOD = 1e9 + 7;
    int getNumWaysToReachDestination(int n, vector<lli> &dist, vector<vector<pair<int, int>>> &graph, int src, int dest) {
        vector<int> ways(n, 0);
        ways[dest] = 1;
        
        // Queuing on the basis of ways was WRONG as it pops nodes which can be revisited in future. 
        // Re-inserting those nodes makes soln. complex
        // Comparator to pick greater distance first is necessary as lower distance nodes can be visited by higher distance nodes
        set<pair<lli, int>, greater<pair<lli, int>>> pending;//dist, node
        pending.insert({dist[dest], dest});

        // O(ElogV)
        while(!pending.empty()){
            auto it = pending.begin();
            pending.erase(it);
            
            int currNode = it->second;
            lli currDist = it->first;
            int waysCurrNode = ways[currNode];

            if(currNode == src){
                return waysCurrNode;
            }
            for(pair<int, int> p: graph[currNode]){
                int nextNode = p.first;
                int edgeNextNode = p.second;
                
                if(dist[nextNode] + edgeNextNode == currDist){
                    if(ways[nextNode] == 0)
                        pending.insert({dist[nextNode], nextNode});
                    ways[nextNode] = (ways[nextNode]%MOD + waysCurrNode%MOD)%MOD;
                }
            }
        }
        return 0;
    }
    
    //Approach: 
    // (1)Find min. time to reach each intersection
    // (2)Backtrack from dest to src to get total count
  public:
    int countPaths(int n, vector<vector<int>>& roads) {
        int src=0, dest=n-1;
        vector<vector<pair<int, int>>> graph(n);
        // O(E)
        for(vector<int> road: roads){
            graph[road[0]].push_back({road[1], road[2]});
            graph[road[1]].push_back({road[0], road[2]});
        }
        vector<lli> dist(n, INT_MAX); //min. time to reach an intersection/node
        dist[0] = 0;
        set<pair<lli, int>> pending; //dist, node
        pending.insert({0, 0});
        
        // O(ElogV)
        while(!pending.empty()){
            auto it = pending.begin();
            pending.erase(it);
            
            lli currDist = it->first;
            int currNode = it->second;
            
            if(currNode == dest){
                // There's no point to process nodes after dest is popped, 
                // as the dist to dest will increase after this
                break;
            }
            
            for(pair<int, int> p: graph[currNode]){
                int nextNode = p.first;
                int edgeNextNode = p.second;
                if(dist[nextNode] > currDist + edgeNextNode){
                    if(dist[nextNode] != INT_MAX){
                        pending.erase({dist[nextNode], nextNode});    
                    }
                    dist[nextNode] = currDist + edgeNextNode;
                    pending.insert({dist[nextNode], nextNode});
                }
            }
        }
        
        return getNumWaysToReachDestination(n, dist, graph, src, dest);
    }
};

// Use of lli wherever necessary
// Queue can't be used to push multiple {min.time, intersection} in queue everytime node is visited with min. time - Logically correct, but Time complexity exceeds
// Assuming that complexity to get all count from src to dest >> backtracking is WRONG
// Backtracking with dijkstra over num of visits is WRONG as the nodes can be visited again and defeats the purpose of Dijkstra
//// checking if node doesn't exists on min. dist visit and performing re-initalization of ways[nextNode] and push in set is just a blunder over blunder
    
