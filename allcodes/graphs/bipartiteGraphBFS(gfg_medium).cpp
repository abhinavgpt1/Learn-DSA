class Solution
{
public:
//can use pair<int, int> in pending for checking setNo
//see soln. at last - not implemented on GFG though
    bool isBipartiteBFS(vector<int> adj[], vector<int> &visited, int index)
    {

        queue<int> pending;
        pending.push(index);
        visited[index] = 0;

        while (!pending.empty())
        {
            int front = pending.front();
            pending.pop();
            int setNo = visited[front];

            for (int i = 0; i < adj[front].size(); i++)
            {
                int child = adj[front][i];

                if (visited[child] == -1)
                {
                    pending.push(child);
                    visited[child] = !setNo;
                }
                else if (visited[child] == setNo)
                    return false;
            }
        }
        return true;
    }
    bool isBipartite(int V, vector<int> adj[])
    {
        // deals with component wise checking of graph
        vector<int> visited(V, -1);
        for (int i = 0; i < V; i++)
        {
            if (visited[i] == -1 && isBipartiteBFS(adj, visited, i) == false)
                return false;
        }
        return true;
    }
};
//can use pair<int, int> in pending for checking setNo
bool bipartiteBFS(vector<vector<int>> &graph, int V)
{
    queue<pair<int, int>> pending;
    vector<int> visited(V, -1), red, blue;

    pending.push({0, 0});
    visited[0] = 0;

    while (!pending.empty())
    {
        pair<int, int> front = pending.front();
        pending.pop();

        for (int i = 0; i < graph[index].size(); i++)
        {
            if (visited[graph[index][i]] == -1)
            {
                visited[graph[index][i]] = !setNo;
                pending.push({graph[index][i], !setNo});
            }
            else if (visited[graph[index][i]] == setNo)
                return false;
        }
    }
    return true;
}