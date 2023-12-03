// Solution 1
class Solution
{
    stack<int> ansStack;
	public:
	//Function to return list containing vertices in Topological order. 
	void dfsApproach(vector<int> adj[], int index, vector<bool> &visited) {
	    
	    visited[index] = true;
	    for(int i=0; i<adj[index].size(); i++){
	        int child = adj[index][i];
	        if(!visited[child])
	            dfsApproach(adj, child, visited);
	    }
	    ansStack.push(index);
	}
	vector<int> topoSort(int V, vector<int> adj[]) 
	{
	    vector<bool> visited(V, false); 
	    for(int i=0; i<V; i++){
	        if(!visited[i])    
	            dfsApproach(adj, i, visited);
	    }
	    vector<int> ans;
	    
	    while(!ansStack.empty()){
	        ans.push_back(ansStack.top());
	        ansStack.pop();
	    }
	    return ans;
	}
};

// Solution 2
class Solution
{
    // works for DAG only
    bool isCycle(int index, stack<int> &stk, vector<int> adj[], vector<int> &visited){
        visited[index] = 1;
        for(int x: adj[index]){
            if(visited[x] == -1)
                continue;
            if(visited[x] == 1 || isCycle(x, stk, adj, visited))
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
	    for(int i=0; i<V; i++){
	        if(!visited[i] && isCycle(i, stk, adj, visited))
	            return vector<int>();
	    }
	    vector<int> ans;
	    while(!stk.empty()){
	        ans.push_back(stk.top());
	        stk.pop();
	    }
	    
	    return ans;
	}
};

// Solution 3
class Solution
{
    void topoSort(vector<int> adj[], vector<bool> &visited, int index, vector<int> &ans) {
        visited[index] = true;
        for(int v: adj[index]){
            if(!visited[v])
                topoSort(adj, visited, v, ans);
        }
        ans.push_back(index);
    }
	public:
	//Function to return list containing vertices in Topological order. 
	vector<int> topoSort(int V, vector<int> adj[]) 
	{
	    vector<bool> visited(V, false);
	    vector<int> ans;
	    for(int i=0; i<V; i++){
	        if(!visited[i])
	            topoSort(adj, visited, i, ans);
	    }
	    reverse(ans.begin(), ans.end());
	    return ans;
	}
};

// isCyclic should be checked before or during topoSort
// For "during toposort" -> mark visited[i] with constants as per their traversal group -> check if cycle forms in the traversal of group
// i.e. pass a unique value to visited[i] and compare visited[i] in else block (after  line 77)