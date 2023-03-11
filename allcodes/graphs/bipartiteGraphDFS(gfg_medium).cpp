class Solution {
public:
    bool isBipartiteDFS(vector<int>adj[], vector<int> &visited, int index, int groupNumber){
        
        visited[index] = groupNumber;
        
        for(int i=0; i<adj[index].size(); i++){
            int child = adj[index][i];
            
            if(visited[child] == -1){
                bool temp = isBipartiteDFS(adj, visited, child, !groupNumber);
                if(!temp)
                return false;    
            }
            //in simple terms - visited[child] != -1 && visited[child] == groupNumber
            else if(visited[child] == groupNumber)
                return false;
            
        }
        return true;
    }
	bool isBipartite(int V, vector<int>adj[]){
	    vector<int> visited(V, -1);
	   // need to do component wise checking also
	   // implemenation will change as visited[i] will be checked if == -1
	   for(int i=0; i<V; i++){
	       if(visited[i] == -1 && isBipartiteDFS(adj, visited, i, 0) == false){
	           return false;
	       }
	   }
	   return true;
	}

};