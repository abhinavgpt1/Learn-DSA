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