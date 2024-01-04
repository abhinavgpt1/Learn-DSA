/*
 * Floyd Warshall
 * --------------
 * The problem is to find the shortest distances between every pair of vertices in a given edge-weighted directed graph. The graph is represented as an adjacency matrix of size n*n.
 * Matrix[i][j] denotes the weight of the edge from i to j.
 * If Matrix[i][j]=-1, it means there is no edge from i to j.
 * Do it in-place.
 * 
 */

// Solution 1: unreachable distance is used as INT_MAX
class Solution {
    public:
	void shortest_distance(vector<vector<int>>&matrix){
	    int n = matrix.size();
	    
	    //marking no edge as INF
	    for(int i=0; i<n; i++){
	        for(int j=0; j<n; j++){
	            if(matrix[i][j] == -1)
	                matrix[i][j] = INT_MAX;
	        }
	    }
	    
	    //Floyd-Warshall logic
	    for(int k=0; k<n; k++){
	        for(int i=0; i<n; i++){
	            for(int j=0; j<n; j++){
	                if(matrix[i][k] == INT_MAX || matrix[k][j] == INT_MAX)
	                    continue;
                    matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
	            }
	        }
	    }
	    
	    // If there's no -ve negative cycle known beforehand, 
	    // then dijkstra n times can be implemented in VElogV > O(V^3)
	    
	    //Check for negative cycle
	    for(int i=0; i<n; i++){
	        if(matrix[i][i] < 0){
	            // negative cycle detected
	            assert(1 == -1);
	        }
	    }
	    
	    //resetting 1e9 to -1 to mark as unreachable
	    for(int i=0; i<n; i++){
	        for(int j=0; j<n; j++){
	            if(matrix[i][j] == INT_MAX)
	                matrix[i][j] = -1;
	        }
	    }
	}
}

// Solution 2: unreachable dist is used as -1.
class Solution {
  public:
	void shortest_distance(vector<vector<int>>&matrix){
	    int n = matrix.size();
	    
        //Floyd-Warshall logic
	    for(int i=0; i<n; i++){
	        for(int j=0; j<n; j++){
	            for(int k=0; k<n; k++){
	                if(matrix[j][i] == -1 || matrix[i][k] == -1)
	                    continue;
	                if(matrix[j][k] == -1)
                        matrix[j][k] = matrix[j][i] + matrix[i][k];
                    else
                        matrix[j][k] = min(matrix[j][k], matrix[j][i] + matrix[i][k]);
	            }
	        }
	    }
        // If there's no -ve negative cycle known beforehand, 
	    // then dijkstra n times can be implemented in VElogV > O(V^3)
	    
	    //Check for negative cycle
	    for(int i=0; i<n; i++){
	        if(matrix[i][i] < 0){
	            // negative cycle detected
	            assert(1 == -1);
	        }
	    }
	}
};