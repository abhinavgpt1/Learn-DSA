// Graph — Reference & Competitive Programming Cheatsheet
//
// Representations:
//   Adjacency List  → O(V+E) space  — best for sparse graphs (most CP problems)
//   Adjacency Matrix→ O(V^2) space  — best for dense graphs, fast edge lookup O(1)
//   Edge List       → O(E) space    — best for algorithms that iterate over all edges (Kruskal, BF)
//
// Terminology:
//   V = vertices, E = edges
//   Weighted / Unweighted
//   Directed (digraph) / Undirected
//   DAG = Directed Acyclic Graph
//
// When to use which algorithm (quick reference):
//   Unweighted shortest path                   → BFS                       O(V+E)
//   Weighted, non-negative edges               → Dijkstra                  O((V+E) log V)
//   Weighted, negative edges (no -ve cycle)    → Bellman-Ford              O(V*E)
//   All-pairs shortest path                    → Floyd-Warshall            O(V^3)
//   Minimum spanning tree (sparse)             → Kruskal + DSU             O(E log E)
//   Minimum spanning tree (dense)              → Prim                      O((V+E) log V)
//   Topological order                          → Kahn's (BFS) / DFS
//   Strongly connected components              → Kosaraju / Tarjan
//   Bridges / Articulation points              → Tarjan (single DFS pass)
//   Bipartite check                            → BFS / DFS 2-coloring
//   Max flow                                   → Dinic's                   O(V^2 * E)
//
// Classic CP Problems (pattern → algorithm):
//   Number of Islands (LC 200)                 → BFS/DFS grid, count unvisited '1' components
//   Shortest Path Grid w/ Obstacles (LC 1091)  → 0-1 BFS with deque (cost-0 front, cost-1 back)
//   Course Schedule (LC 207, 210)              → Kahn's topo sort; cycle check via BFS
//   Cheapest Flights K Stops (LC 787)          → Bellman-Ford, exactly K+1 rounds, copy dist[] each round
//   Critical Connections (LC 1192)             → Tarjan bridges; bridge if low[v] > disc[u]
//   Reconstruct Itinerary (LC 332)             → Hierholzer's Eulerian path; min-heap adj for lex order
//   Word Ladder (LC 127)                       → BFS on implicit graph; bidirectional BFS halves depth
// ============================================================

import java.util.*;

class Pair {
    int u, v;

    Pair(int u, int v) {
        this.u = u;
        this.v = v;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || getClass() != o.getClass())
            return false;
        Pair pair = (Pair) o;
        return u == pair.u && v == pair.v;
    }
}

// Undirected graph, stores graph as adjacency list
class MyUndirectedGraph {
    int V;
    List<List<Integer>> adj;

    MyUndirectedGraph(int V) {
        this.V = V;
        adj = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }
    }

    // O(1)
    private void addEdge(int u, int v) {
        adj.get(u).add(v);
        adj.get(v).add(u);
    }

    public void buildGraph(int[][] edges) {
        for (int i = 0; i < edges.length; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            addEdge(u, v);
        }
    }

    // ── Traversals ────────────────────────────────────────────────────────────

    // BFS from source - O(V+E)
    private List<Integer> bfs(int src, boolean[] visited) {
        Queue<Integer> pending = new LinkedList<>();
        List<Integer> result = new ArrayList<>();
        visited[src] = true;
        pending.add(src);
        while (!pending.isEmpty()) {
            int front = pending.remove();
            result.add(front);
            for (int v : adj.get(front)) {
                if (!visited[v]) {
                    visited[v] = true;
                    pending.add(v);
                }
            }
        }
        return result;
    }

    // BFS - visit all components (also called connected components) - O(V+E)
    public List<Integer> bfs() {
        List<Integer> result = new ArrayList<>();
        boolean[] visited = new boolean[V];
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                result.addAll(bfs(i, visited));
            }
        }
        return result;
    }

    // DFS (iterative) - O(V+E)
    private List<Integer> dfsIterative(int src, boolean[] visited) {
        List<Integer> result = new ArrayList<>();
        Deque<Integer> stack = new ArrayDeque<>();
        stack.push(src);
        visited[src] = true;
        while (!stack.isEmpty()) {
            int top = stack.pop(); // O(1)
            result.add(top);
            for (int v : adj.get(top)) { // O(Ev)
                if (!visited[v]) {
                    visited[v] = true;
                    stack.push(v);
                }
            }
        }
        // Time complexity: V(Constant + Ev) = O(V + E)
        return result;
    }

    // DFS (recursive) - O(V+E)
    private List<Integer> dfsRecursive(int src, boolean[] visited) {
        List<Integer> result = new ArrayList<>();
        visited[src] = true;
        result.add(src);
        for (int v : adj.get(src)) { // O(Ev)
            if (!visited[v]) {
                result.addAll(dfsRecursive(v, visited));
            }
        }
        return result;
    }

    // DFS - visit all components (also called connected components)
    // Time complexity - O(V+E)
    public List<Integer> dfs(boolean isRecursive) {
        List<Integer> result = new ArrayList<>();
        boolean[] visited = new boolean[V];
        for (int i = 0; i < V; i++) {
            if (!visited[i]) { // O(1)
                if (isRecursive) {
                    result.addAll(dfsRecursive(i, visited));
                } else {
                    result.addAll(dfsIterative(i, visited));
                }
            }
        }
        // Time complexity: V(Constant + Ev) = O(V + E)
        // PTR: this will be V + 2E since each edge is checked twice across all DFS calls
        return result;
    }

    // ── Cycle Detection ───────────────────────────────────────────────────────

    private boolean hasCycleUsingBFS(int src, boolean[] visited) {
        Queue<Pair> pending = new LinkedList<>();
        pending.add(new Pair(src, -1));
        visited[src] = true;
        while (!pending.isEmpty()) {
            Pair front = pending.remove();
            int u = front.u;
            int parent = front.v;
            for (int v : adj.get(u)) {
                if (!visited[v]) {
                    visited[v] = true;
                    pending.add(new Pair(v, u));
                } else if (v != parent) {
                    return true; // found a back edge → cycle
                }
            }
        }
        return false;
    }

    private boolean hasCycleUsingDFS(int src, boolean[] visited, int parent) {
        visited[src] = true;
        for (int v : adj.get(src)) {
            if (!visited[v]) {
                if (hasCycleUsingDFS(v, visited, src))
                    return true;
            } else if (v != parent) {
                return true; // found a back edge → cycle
            }
        }
        return false;
    }

    // Detect cycle in undirected graph for all connected components - O(V+E)
    public boolean hasCycle(boolean useDFS) {
        boolean[] visited = new boolean[V];
        for (int i = 0; i < V; i++) {
            if (!visited[i] && (useDFS ? hasCycleUsingDFS(i, visited, -1) : hasCycleUsingBFS(i, visited)))
                return true;
        }
        return false;
    }

    // ── Connected Components ──────────────────────────────────────────────────

    // Count connected components - O(V+E)
    public int connectedComponents() {
        boolean[] visited = new boolean[V];
        int count = 0;
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                bfs(i, visited); // or dfs(i, visited);
                count++;
            }
        }
        return count;
    }

    // ── Bipartite Check ───────────────────────────────────────────────────────
    private boolean isBipartiteUsingDFS(int src, int[] color, int srcColor) {
        color[src] = srcColor;
        for (int v : adj.get(src)) {
            if (color[v] == 0) {
                if (!isBipartiteUsingDFS(v, color, srcColor == 1 ? -1 : 1))
                    return false;
            } else if (color[v] == srcColor) {
                return false;
            }
        }
        return true;
    }

    private boolean isBipartiteUsingBFS(int src, int[] color, int srcColor) {
        Queue<Integer> pending = new LinkedList<>();
        pending.add(src);
        color[src] = srcColor;
        while (!pending.isEmpty()) {
            int front = pending.remove();
            for (int v : adj.get(front)) {
                if (color[v] == 0) {
                    color[v] = -color[front]; // assign opposite color
                    pending.add(v);
                } else if (color[v] == color[front]) {
                    return false; // neighbour has same color → not bipartite
                }
            }
        }
        return true;
    }

    // 2-coloring, covers connected components - O(V+E)
    // PTR: color[] = 0; assign -1/1 alternately; if neighbour has same color → not
    // bipartite.
    // Use: bipartite matching, graph coloring with 2 colors.
    public boolean isBipartite(boolean useDFS) {
        int[] color = new int[V]; // default 0 i.e. unvisited
        for (int i = 0; i < V; i++) {
            if (color[i] == 0 && (useDFS ? !isBipartiteUsingDFS(i, color, 1) : !isBipartiteUsingBFS(i, color, 1)))
                return false;
        }
        return true;
    }

    // ── Topological Sort ──────────────────────────────────────────────────────
    public List<Integer> topologicalSortKahnsAlgo() {
        throw new UnsupportedOperationException("Valid for Directed Graph");
    }

    // DFS-based topological sort. O(V+E)
    // PTR: post-order DFS; push to stack after all neighbours visited; reverse at
    // end.
    public List<Integer> topologicalSortDFS() {
        throw new UnsupportedOperationException("Valid for Directed Graph");
    }

    // ── Minimum Spanning Tree ─────────────────────────────────────────────────

    // Time complexity - O(ElogV)
    public int prim() {
        throw new UnsupportedOperationException("Valid for Weighted Undirected Graph");
    }
    
    // Time complexity — O(ElogE)
    public int kruskal() {
        throw new UnsupportedOperationException("Valid for Weighted Undirected Graph");
    }

    // ── Shortest Paths ────────────────────────────────────────────────────────

    // Dijkstra — find shortest path from source to all nodes, given non-negative weights. Very similar to Prim's in implementation.
    // Time complexity - O(ElogV)
    public int[] dijkstra(int src) {
        throw new UnsupportedOperationException("Valid for Weighted Directed/Undirected Graph");
    }

    // Bellman-Ford — find shortest path from source to all nodes. Gives correct answer in case of negative weight unless there's -ve cycle -> helps detects negative cycle.
    // Time complexity - O(EV)
    public int[] bellmanFord(int src) {
        throw new UnsupportedOperationException("Valid for Weighted Directed/Undirected Graph");
    }

    // Floyd-Warshall — find shortest path between all pairs of nodes. Gives correct answer in case of -ve weight unless there's -ve cycle -> helps detects negative cycle.
    // Time complexity - O(V^3), space complexity - O(V^2).
    public int[][] floydWarshall() {
        throw new UnsupportedOperationException("Valid for Weighted Directed/Undirected Graph");
    }

    // SPFA (Shortest Path Faster Algorithm) — BFS-based Bellman-Ford. O(V*E) worst,
    // O(E) average.
    // PTR: use queue instead of iterating all edges; only re-add node if it was
    // relaxed.
    // Not reliable for worst-case negative-weight graphs in CP; prefer Bellman-Ford
    // for safety.
    public int[] spfa(int src) {
        // TODO
        return new int[V];
    }

    // ── Strongly Connected Components ─────────────────────────────────────────
    // SCC are only valid for Directed graphs
    // Def: A strongly connected component (SCC) of a directed graph is a subgraph where there's a path from every node to every other node. SCCs are the directed graph analogue of connected components in undirected graphs.

    // Kosaraju's SCC - find/count strongly connected components in a directed graph.
    // Time complexity - O(V+E)
    public List<List<Integer>> kosarajuSCC() {
        throw new UnsupportedOperationException("SCCs are valid for Directed Graph only");
    }

    public List<List<Integer>> tarjanSCC() {
        throw new UnsupportedOperationException("SCCs are valid for Directed Graph only");
    }

    // ── Bridges & Articulation Points ────────────────────────────────
    // Def: Bridge (cut edge) is an edge whose removal increases the number of connected components (in undirected graph) or strongly connected components (in directed graph).
    // Def: Articulation point (cut vertex) is a node whose removal increases the number of connected components (in undirected graph) or strongly connected components (in directed graph).

    private void findBridgesDFS(int src, int parent, int discTime, int[] disc, int[] low, boolean[] visited, List<int[]> bridges) {
        visited[src] = true;
        disc[src] = low[src] = discTime;

        for (int v : adj.get(src)) {
            if (v == parent)
                continue; // skip the edge to parent
            
            if (!visited[v]) {
                findBridgesDFS(v, src, discTime + 1, disc, low, visited, bridges);
                
                low[src] = Math.min(low[src], low[v]); // **IMPORTANT**

                if (low[v] > disc[src]) { // no back edge from v or its subtree to src or its ancestors → bridge
                    bridges.add(new int[]{src, v});
                }

            } else {
                //  WHY disc[v] and not low[v]:
                // ----------------------------
                // - disc[v] is the standard implementation and semantically cleaner: "via this back edge, I can directly reach v at time disc[v]"
                // - low[v] also works (low[v] <= disc[v], so bridge detection is unaffected), but it smuggles in multi-hop reachability not established by this edge(src-v) alone.
                //
                // Looking at the condition in if(), low[src] = Math.min(low[src], low[v]);
                // It works and implies that anything reachable from v is also reachable from src, so low[v] is used instead of disc[v].
                // One can state same logic here. It isn't wrong but less intuitive.
                // 
                // Reason: The standard disc[v] doesn't leak extra information since using low[v] can propagate way upwards and make it seem like src can reach nodes that it can't directly reach via this back edge.
                // eg. 
                // 0/0  1/1   2/0   3/3    4/4
                // 0 --- 1 --- 2 --- 3 --- 4
                // |          / \          |
                // - - - - - -   - - - - - -
                // When at 4, and you see 2 visited, you're effectively saying:
                // Because 2 can reach 0 somehow, 4 can reach 0 too.
                // *** But that conclusion did not come from the back edge 4->2 or propagation.***
                // You can still say "because 2 can reach 0 somehow, 4 can reach 0 too" but it would be less intuitive. 
                // Check vid ref: https://youtu.be/j1QDfU21iZk?list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&t=596

                low[src] = Math.min(low[src], disc[v]); // back edge
            }
        }
    }

    // Time complexity (~DFS) - O(V+E)
    public List<int[]> findBridges() {
        // Algo:
        // - DFS with disc[] and low[]
        // - if descendant of src can't reach src or its ancestors (low[v] > disc[src]), then src-v is a bridge
        // Note: Intuition behind finding bridges is to check for an edge if the child node has a way to reach parent or its ancestor.

        // Note: it would be intuitive to keep a universal timer/discTime variable since we want to check back edge to ancestor of "src" while being at "v",
        // but it's not necessary since, initially, disc[v] and low[v] are both > disc[src] - guaranteed by discTime + 1.
        // Later, if a back edge to ancestor or src exists, then low[v] is sufficient to check src-v as bridge (low[v] > disc[src]).

        int[] disc = new int[V]; // discovery time of each node in DFS
        int[] low = new int[V]; // low[u] = min disc reachable from u (including itself and back edges)
        boolean[] visited = new boolean[V];
        List<int[]> bridges = new ArrayList<>();

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                findBridgesDFS(i, -1, 0, disc, low, visited, bridges);
            }
        }
        return bridges;
    }

    private List<Integer> findArticulationPointsDFS(int src, int parent, int discTime, int[] disc, int[] low, boolean[] visited) {
        List<Integer> apList = new ArrayList<>();
        visited[src] = true;
        disc[src] = low[src] = discTime;
        int children = 0; // to track number of unvisited children in DFS tree

        for (int v : adj.get(src)) {
            if (v == parent)
                continue; // skip the edge to parent
            
            if (!visited[v]) {
                children++;
                apList.addAll(findArticulationPointsDFS(v, src, discTime + 1, disc, low, visited));
                
                low[src] = Math.min(low[src], low[v]); // **IMPORTANT**

                if (parent != -1 && low[v] >= disc[src]) { // no back edge from v or its subtree to src or its ancestors → src is an AP
                    apList.add(src);
                }

            } else {
                low[src] = Math.min(low[src], disc[v]); // back edge - you'll understand the intuitiveness behind updating with disc[v] instead of low[v] 
                // in this eg. 1-0-2-3-0, 2-4-5-2, had you updated low[5] with low[2]=0 instead of disc[2]=2, low[5] would have become 0, and when you check low[5] >= disc[2], it would have been false and 2 would have been missed as an AP.
                // Hence, the updation shouldn't go beyond the direct back edge.
                // Check vid ref: https://youtu.be/j1QDfU21iZk?list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&t=596
            }
        }

        if (parent == -1 && children >= 2) { // root with 2+ unvisited children even after DFS on one of them → root is an AP
            apList.add(src);
        }
        return apList;
    }

    // Time complexity - O(V+E)
    public TreeSet<Integer> findArticulationPoints() {
        // My initial approach:
        // - find bridges via Tarjan
        // - both nodes of a bridge is an AP [WRONG]
        // Approach seems correct partially, but it isn't - AP removes the whole node and edges attached to it. Nodes next to bridges is a sub-answer [NOT ALWAYS]
        // eg. 1-0-2-3-0, 2-4-5-2. Above gives {0,1} as AP, but 2 is also an AP with no bridge attached to it. Also, 1 is not an AP.

        // Algo:
        // - DFS with disc[] and low[] like Tarjan
        // - if descendant of src can't reach src's ancestor, then src is an AP (low[v] >= disc[src]). fyi, if there's a back edge to src ancestor, then low[v] < disc[src].
        //  - Catch: this condition is valid only for non-root nodes. For root, check if it has 2+ *unvisited* children even after DFS on one of them. eg. 0-1-2, 1-3
        // Note: Intuition behind finding AP is to check for a node if its child has a back edge to its ancestor or not.

        // Note: It would be intuitive to keep a universal timer/discTime variable since we want to check back edge to ancestor of "src" while being at "v",
        // but it's not necessary since, initially, disc[v] and low[v] are both > disc[src] - guaranteed by discTime + 1.
        // Later, if a back edge to ancestor of src exists, then low[v] is sufficient to check src as AP (low[v] >= disc[src]).

        int[] disc = new int[V];
        int[] low = new int[V];
        boolean[] visited = new boolean[V];
        TreeSet<Integer> apList = new TreeSet<>();

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                apList.addAll(findArticulationPointsDFS(i, -1, 0, disc, low, visited));
            }
        }
        return apList;
    }

    // ── Network Flow ──────────────────────────────────────────────────────────

    // Dinic's Max Flow. O(V^2 * E) — practical performance much better.
    // PTR: alternates BFS (build level graph) and DFS (find blocking flow) until no
    // augmenting path.
    // Use: max-flow, min-cut, bipartite matching (O(E * sqrt(V)) via
    // Hopcroft-Karp).
    public int maxFlow(int source, int sink) {
        // TODO: use residual graph; capacity[u][v] and rCapacity[v][u] = -cap for
        // reverse edge.
        return 0;
    }
}

// ── Weighted Undirected Graph
// ──────────────────────────────────────────────────
class MyWeightedUndirectedGraph {
    int V;
    List<List<int[]>> adj; // or use List<List<Pair>>

    MyWeightedUndirectedGraph(int V) {
        this.V = V;
        adj = new ArrayList<>();
        for (int i = 0; i < V; i++)
            adj.add(new ArrayList<>());
    }

    // O(1)
    private void addEdge(int u, int v, int weight) {
        adj[u].add(new int[] { v, weight });
        adj[v].add(new int[] { u, weight });
    }

    public void buildGraph(int[][] edges) {
        // for (int[] e : edges) // can use this as well
        for(int i=0; i<edges.length; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];
            addEdge(u, v, w);
        }
    }

    // Following algos are same as in MyUndirectedGraph
    // ── Traversals ────────────────────────────────────────────────────────────
    // ── Cycle Detection ───────────────────────────────────────────────────────
    // ── Bipartite Check ───────────────────────────────────────────────────────

    // ── Minimum Spanning Tree ─────────────────────────────────────────────────

    private int findMinDistNode(int[] dist, boolean[] visited) {
        int minWeightNode = -1;
        for(int i=0; i<V; i++){
            if(!visited[i] && (minWeightNode == -1 || dist[minWeightNode] > dist[i])){
                minWeightNode = i;
            }
        }
        return minWeightNode;
    }
    // Prim's Algo — greedy, best for dense graphs.
    // Time complexity (iterative minNode find) - O(V^2 + E)
    public int primIterative() {
        boolean[] visited = new boolean[V]; // to track what all nodes are already in MST
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);

        int src = 0;
        dist[src] = 0;

        int minimumWeight = 0;

        for(int i=0; i<V; i++){ // O(V)
            int u = findMinDistNode(dist, visited); // O(V)
            visited[u] = true;
            minimumWeight += dist[u];
            // relax the nodes
            for(int[] e: adj.get(u)) { // O(Ev)
                int v = e[0];
                int w = e[1];
                if(visited[v])
                    continue;
                if(dist[v] > w) {
                    dist[v] = w;
                }
            }
        }
        // Time complexity: V * (V + Ev) = V^2 + E
        return minimumWeight;
    }

    // **Least efficient**
    // Time complexity with minHeap - O((V+E)logV + EV)
    public int primUsingMinHeap() {        
        PriorityQueue<Pair> minHeap = new PriorityQueue<>((a,b) -> a.v - b.v);
        int src = 0;
        boolean[] visited = new boolean[V];
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[src] = 0;
        minHeap.add(new Pair(src, dist[src]));

        int minimumWeight = 0;
        while(!minHeap.isEmpty()) { // O(V)
            int u = minHeap.peek().u;
            int uDist = minHeap.peek().v;
            minHeap.remove(); // O(log V)
            visited[u] = true;
            minimumWeight += uDist;

            for(int[] e: adj.get(u)) { // O(Ev)
                int v = e[0];
                int w = e[1];
                if(visited[v])
                    continue;
                if(dist[v] > w) { // O(V + logV)
                    if(dist[v] != Integer.MAX_VALUE) { // unnecessary check since remove() will simply return false if entry doesn't exist, but it doesn't harm either
                        // remove(Object o)
                        // - is O(n) and not O(logn) because it does a linear scan using equals() to find the object, then removes it and sifts.
                        // - uses .equals() and not comparator by definition.
                        minHeap.remove(new Pair(v, dist[v])); // fails if Pair doesn't override equals(). Reference based check fails by default for different memory addresses.
                    }
                    dist[v] = w;
                    minHeap.add(new Pair(v, dist[v]));
                }
            }
        }
        // Time complexity: V(log V + Ev*(V + logV)) = VlogV + E(V + logV) = O((V+E)logV + EV) ~ O(V(E + logV)) ~ O(VE)
        return minimumWeight;
    }

    // Time complexity with TreeSet - O((V+E)logV)
    public int primUsingTreeSet() {
        // TreeSet over PQ: comparator-based lookup lets remove(new int[]{w,v}) find entries by
        // value in O(log V); PQ.remove(Object) does a linear scan using equals() — O(n) — then
        // sifts in O(log n), so it's O(n) total and can't locate array entries by value anyway
        // (arrays use reference equality).
        //
        // **IMP**: Tie-break on node index is required for correctness: TreeSet uses the comparator as
        // its sole definition of equality (it never calls equals/hashCode). If the comparator
        // returns 0, the set treats the two entries as duplicates — add() silently drops the
        // second one and remove() can match the wrong node. Tie-breaking on node index ensures
        // every {weight, node} pair is distinct in the comparator's eyes, so all V entries
        // coexist in the set and targeted eviction always hits the right one.
        TreeSet<Pair> pending = new TreeSet<>((a, b) -> a.v != b.v ? a.v - b.v : a.u - b.u);
        int src = 0;
        boolean[] visited = new boolean[V];
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[src] = 0;
        pending.add(new Pair(src, dist[src]));
        int minimumWeight = 0;

        while (!pending.isEmpty()) { // O(V)
            Pair front = pending.removeFirst(); // O(logV)
            int u = front.u;
            visited[u] = true;
            minimumWeight += front.v;
            for (int[] e : adj.get(u)) { // O(Ev)
                int v = e[0];
                int w = e[1];
                if (visited[v])
                    continue;
                if (dist[v] > w) { // O(2logV) = O(logV)
                    // if (dist[v] != Integer.MAX_VALUE) // this check is unnecessary because TreeSet.remove() will simply return false if the entry doesn't exist, but it doesn't harm either
                    pending.remove(new Pair(v, dist[v])); // evict stale entry
                    dist[v] = w;
                    pending.add(new Pair(v, dist[v]));
                }
            }
        }
        // Time complexity: V(logV + Ev * logV) = O((V+E)logV) ~ O(ElogV)
        // Reason: 
        // For Prim's MST to be meaningful, the graph must be connected, which requires E ≥ V−1, meaning V = O(E). 
        // Therefore: O((V+E)logV) = O(ElogV)
        // FYI, Connected graph = graph where there's a path between every pair of nodes.
        return minimumWeight; 
    }

    private int findParentNaive(int n, int[] parent) { // O(V) worst case (degenerate chain)
        if(parent[n] == n)
            return n;
        return findParentNaive(parent[n], parent); 
    }

    // Time complexity - O(ElogE + EV)
    public int kruskalNaive() {
        // Algo:
        // - Make List<edges> / PQ<edges> from adjacency list
        // - Select min weight edge -> check if cycle forms -> accept / reject the edge
        // - Find optimisations in kruskalOptimised()
        
        List<int[]> edges = new ArrayList<>(); 
        // or use PriorityQueue<int[]> minHeap = new PriorityQueue<>((a,b) -> a[2] - b[2]);
        
        for(int u=0; u<V; u++) { // O(E)
            for(int[] e: adj.get(u)) {
                int v = e[0];
                int w = e[1];
                edges.add(new int[]{u, v, w});
            }
        }
        Collections.sort(edges, (a,b) -> a[2] - b[2]); // O(ElogE), actually 2Elog(2E)
        
        int minimumWeight = 0;
        int[] parent = new int[V];
        for(int i=0; i<V; i++) {
            parent[i] = i;
        }

        for(int[] e: edges) { // O(E)
            int u = e[0];
            int v = e[1];
            int w = e[2];
            int parentU = findParentNaive(u, parent); // O(V)
            int parentV = findParentNaive(v, parent); // O(V)
            
            if(parentU == parentV)
                continue; // cycle detected, reject edge
            
            minimumWeight += w;
            parent[parentV] = parentU; // union (unoptimised) - O(1)
        }
        // Time complexity: E + ElogE + E * 2V = O(E + ElogE + EV) = O(ElogE + EV)
        return minimumWeight;
    }

    // Path-compressed find: flattens the tree on every lookup → O(log* V) amortised ~ O(1)
    private int findParent(int n, int[] parent) {
        if (parent[n] == n)
            return n;
        return parent[n] = findParent(parent[n], parent);
    }

    private void unionByRank(int u, int v, int[] parent, int[] rank) {
        // making this function indepedent of whether u, v are actually parents or not, so that it can be used directly.
        int uParent = findParent(u, parent);
        int vParent = findParent(v, parent);
        if (uParent == vParent)
            return; // already in same set

        // Rule:
        // - attach smaller rank tree under root of higher rank tree
        // - if ranks are same, make one as root and increment its rank by one
        // Note: Rank is not a measure of depth but an upper bound on it. With path compression, rank can be thought of as an upper bound on the height of the tree, but it doesn't necessarily reflect the actual height due to the flattening effect of path compression.
        if (rank[uParent] < rank[vParent]) {
            parent[uParent] = vParent;
        } else if (rank[uParent] > rank[vParent]) {
            parent[vParent] = uParent;
        } else {
            parent[vParent] = uParent;
            rank[uParent]++; // PTR: increment rank of uParent, not vParent since uParent becomes the new root
        }
    }

    // Time complexity using optimisations — O(ElogE)
    public int kruskalOptimised() {
        // Optimisations:
        // 1. No need of duplicate edge - form List<edges> by comparing u < v -> saves O(E/2) ~O(E) space.
        // 2. Use path-compressed find → O(log* V) amortised ~ O(1) per union-find operation.
        // 3. Union by rank/size → keeps tree flat → find() becomes O(α(V)) amortised ~ O(1) which is better than O(log* V) of path compression alone. Note: with path compression, union by rank/size is not strictly necessary for O(1) find, but it helps keep the trees flatter and can improve practical performance.
        // 4. Early exit: once we have V-1 edges in MST, we can stop processing further edges.

        List<int[]> edges = new ArrayList<>();
        // or use PriorityQueue<int[]> minHeap = new PriorityQueue<>((a,b) -> a[2] - b[2]);
        for (int u = 0; u < V; u++) { // O(E)
            for (int[] e : adj.get(u)) {
                int v = e[0], w = e[1];
                if (u < v) // OPTIMISATION-1
                    edges.add(new int[]{u, v, w});
            }
        }
        Collections.sort(edges, (a, b) -> a[2] - b[2]); // O(ElogE)

        int[] parent = new int[V];
        int[] rank = new int[V];
        for (int i = 0; i < V; i++)
            parent[i] = i;

        int minimumWeight = 0, edgesUsed = 0;
        for (int[] e : edges) { // O(E)
            int u = e[0], v = e[1], w = e[2];
            int uParent = findParent(u, parent); // O(α(V)) amortised ~ O(1) :  OPTIMISATION-2 // this is called as inverse Ackermann function and is denoted as α(n). It grows extremely slowly, so for all practical purposes, it can be treated as a constant. In fact, for any value of n that can be written in the physical universe, α(n) ≤ 4.
            int vParent = findParent(v, parent);

            if (uParent == vParent)
                continue; // cycle detected, reject edge

            minimumWeight += w;
            unionByRank(uParent, vParent, parent, rank); // O(1) : OPTIMISATION-3 - helps achieve O(α(V)) from O(log* V) of path compression alone
            edgesUsed++;
            if (edgesUsed == V - 1) // OPTIMISATION-4
                break;
        }

        // Time complexity: O(E + ElogE + E * α(V)) = O(ElogE)
        return minimumWeight;
    }

    // extra
    private void unionBySize(int u, int v, int[] parent, int[] size) {
        int uParent = findParent(u, parent);
        int vParent = findParent(v, parent);
        if (uParent == vParent)
            return; // already in same set

        // Rule:
        // - attach smaller size tree under root of larger size tree
        // - update size of new root
        // Note: size increments everytime, so no need of else-if like in case of unionByRank
        // Note: use either union by rank or union by size, not both together. Both optimisations serve the same purpose of keeping the tree flat, so using both is redundant and doesn't provide additional asymptotic improvement.
        if (size[uParent] < size[vParent]) {
            parent[uParent] = vParent;
            size[vParent] += size[uParent];
        } else {
            parent[vParent] = uParent;
            size[uParent] += size[vParent];
        }
    }

    // ── Shortest Paths ────────────────────────────────────────────────────────

    // Dijkstra — find shortest path from source to all nodes, given non-negative weights. Very similar to Prim's in implementation.
    // Use Bellman-Ford if negative weights are present, or to check negative cycles. 
    // Dijkstra can give wrong answer in case of -ve weight, and loops in case of -ve cycle.
    // Time complexity - O(ElogV) with TreeSet, O((V+E)logV + EV) with minHeap, O(V^2 + E) with iterative minNode find.
    public int[] dijkstra(int src) {
        TreeSet<Pair> pending = new TreeSet<>((a, b) -> a.v != b.v ? a.v - b.v : a.u - b.u);
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[src] = 0;
        pending.add(new Pair(src, dist[src]));
        boolean[] visited = new boolean[V];
        while (!pending.isEmpty()) { // O(V)
            Pair front = pending.removeFirst(); // O(logV)
            int u = front.u;
            int uDist = front.v;
            visited[u] = true;
            for (int[] e : adj.get(u)) { // O(Ev)
                int v = e[0];
                int w = e[1];
                if (visited[v])
                    continue;
                if (dist[v] > uDist + w) { // O(2logV) ~ O(logV)
                    // if (dist[v] != Integer.MAX_VALUE) // this check is unnecessary because TreeSet.remove() will simply return false if the entry doesn't exist, but it doesn't harm either
                    pending.remove(new Pair(v, dist[v])); // evict stale entry
                    dist[v] = uDist + w;
                    pending.add(new Pair(v, dist[v]));
                }
            }
        }

        // Time complexity: V(logV + Ev * logV) = O((V+E)logV) ~ O(ElogV)
        // Reason: For Dijkstra's to be meaningful, the graph must be connected, which requires E ≥ V−1, meaning V = O(E). Therefore: O((V+E)logV) = O(ElogV)
        // FYI, Connected graph = graph where there's a path between every pair of nodes.
        return dist;
    }

    // Bellman-Ford — find shortest path from source to all nodes. Gives correct answer in case of negative weight unless there's -ve cycle -> helps detects negative cycle.
    // Time complexity - O(EV)
    public int[] bellmanFord(int src) {
        // Algo: Works for directed graph as well.
        // - Form a list of edges from adjacency list. IMP: for undirected graph, add both (u,v) and (v,u) to edge list.
        // - Iterate over all edges V-1 times, relax them. On V-th iteration, if any edge still relaxes → negative cycle.
        // Reason: Shortest simple path (no cycles) can have at most V-1 edges

        List<int[]> edges = new ArrayList<>();
        for (int u = 0; u < V; u++) { // O(E)
            for (int[] e : adj.get(u)) {
                int v = e[0];
                int w = e[1];
                edges.add(new int[]{u, v, w}); // no if (u < v) since we need both directions for undirected graph unlike kruskal
            }
        }

        // OPTIMISATION: early exit — if a full pass relaxes nothing, paths have converged; remaining rounds are no-ops. Best case: O(E), typical: O(kE) where k ≪ V
        boolean relaxed = true;

        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE); // unreachable
        dist[src] = 0;
        for (int i = 0; i < V - 1; i++) { // O(V)
            relaxed = false;
            for (int[] e : edges) { // O(E)
                int u = e[0], v = e[1], w = e[2];
                if(dist[u] == Integer.MAX_VALUE) // skip unreachable nodes
                    continue;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    relaxed = true;
                }
            }
            if (!relaxed) // early exit if no relaxation occurred
                break;
        }

        // Check for negative cycle on V-th iteration
        for (int[] e : edges) { // O(E)
            int u = e[0], v = e[1], w = e[2];
            if(dist[u] == Integer.MAX_VALUE) // skip unreachable nodes
                continue;
            if (dist[v] > dist[u] + w) {
                return new int[]{-1}; // negative cycle detected
            }
        }

        // Time complexity: O(E + EV) = O(EV)
        return dist;
    }

    // Floyd-Warshall — find shortest path between all pairs of nodes. Gives correct answer in case of -ve weight unless there's -ve cycle -> helps detects negative cycle.
    // Time complexity - O(V^3), space complexity - O(V^2).
    public int[][] floydWarshall() {
        // Algo:
        // - For each possible intermediate node k, check if going through k gives a shorter path from i to j
        // - dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
        int[][] dist = new int[V][V];
        for (int u = 0; u < V; u++) {
            Arrays.fill(dist[u], Integer.MAX_VALUE);
            for (int[] e : adj.get(u)) {
                int v = e[0];
                int w = e[1];
                dist[u][v] = w;
            }
        }

        for (int u = 0; u < V; u++) {
            if (dist[u][u] < 0)
                return new int[][]{{-1}}; // negative cycle detected

            if (dist[u][u] == Integer.MAX_VALUE) // there's no self-loop
                dist[u][u] = 0;
            // fyi, in case there's a +ve weighted self-loop, it won't affect the algo and we can still set dist[u][u] = 0 to maintain consistency.
        }

        for(int k=0; k<V; k++) {
            for(int u = 0; u < V; u++) {
                if(dist[u][k] == Integer.MAX_VALUE)
                    continue; // skip if k is unreachable from u. Better to put this check here than inside innermost loop to save more iterations since if k is unreachable from u, it can't possibly be part of a shorter path from u to any v.
                for(int v = 0; v < V; v++) {
                    if(dist[k][v] == Integer.MAX_VALUE)
                        continue; // skip if v is unreachable from k
                    if(dist[u][v] > dist[u][k] + dist[k][v]) {
                        dist[u][v] = dist[u][k] + dist[k][v];
                    }
                }
            }
        }

        // Note: If we know there are no negative cycles, we can solve this problem by running Dijkstra's from each node, which is O(VElogV)
        
        // Check for -ve cycle: if dist[i][i] < 0 for any i, then there's a negative cycle reachable from i
        for(int i=0; i<V; i++) {
            if(dist[i][i] < 0) {
                return new int[][]{{-1}}; // negative cycle detected
            }
        }

        // Time complexity: O(V^3)
        return dist;
    }

    // ── Strongly Connected Components ─────────────────────────────────────────
    // SCC are only valid for Directed graphs
    // Def: A strongly connected component (SCC) of a directed graph is a subgraph where there's a path from every node to every other node. SCCs are the directed graph analogue of connected components in undirected graphs.

    // Kosaraju's SCC - find/count strongly connected components in a directed graph.
    // Time complexity - O(V+E)
    public List<List<Integer>> kosarajuSCC() {
        throw new UnsupportedOperationException("Valid for Directed Graph");
    }

    // Time complexity - O(V+E)
    public List<List<Integer>> tarjanSCC() {
        throw new UnsupportedOperationException("Valid for Directed Graph");
    }

    // ── Bridges & Articulation Points ────────────────────────────────
    // Def: Bridge (cut edge) is an edge whose removal increases the number of connected components (in undirected graph) or strongly connected components (in directed graph).
    // Def: Articulation point (cut vertex) is a node whose removal increases the number of connected components (in undirected graph) or strongly connected components (in directed graph).

    // Time complexity (~DFS) - O(V+E)
    public List<int[]> findBridges() {
        throw new UnsupportedOperationException("Same as MyUndirectedGraph.findBridges() since no direction or weight info is used in the algo");
    }

    // Time complexity - O(V+E)
    public List<Integer> findArticulationPoints() {
        throw new UnsupportedOperationException("Same as MyUndirectedGraph.findArticulationPoints() since no direction or weight info is used in the algo");
    }
}

// Directed graph, stores graph as adjacency list
class MyDirectedGraph {
    int V;
    List<List<Integer>> adj;

    MyDirectedGraph(int V) {
        this.V = V;
        adj = new ArrayList<>();
        for (int i = 0; i < V; i++)
            adj.add(new ArrayList<>());
    }

    // O(1)
    private void addEdge(int u, int v) {
        adj.get(u).add(v);
    }

    public void buildGraph(int[][] edges) {
        for (int i = 0; i < edges.length; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            addEdge(u, v);
        }
    }

    // ── Traversals ────────────────────────────────────────────────────────────

    // BFS from source - O(V+E)
    private List<Integer> bfs(int src, boolean[] visited) {
        Queue<Integer> pending = new LinkedList<>();
        List<Integer> result = new ArrayList<>();
        visited[src] = true;
        pending.add(src);
        while (!pending.isEmpty()) {
            int front = pending.remove();
            result.add(front);
            for (int v : adj.get(front)) {
                if (!visited[v]) {
                    visited[v] = true;
                    pending.add(v);
                }
            }
        }
        return result;
    }

    public List<Integer> bfs() {
        List<Integer> result = new ArrayList<>();
        boolean[] visited = new boolean[V];
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                result.addAll(bfs(i, visited));
            }
        }
        return result;
    }

    private List<Integer> dfs(int src, boolean[] visited) {
        List<Integer> result = new ArrayList<>();
        visited[src] = true;
        result.add(src);
        for (int v : adj.get(src)) { // O(Ev)
            if (!visited[v]) {
                result.addAll(dfs(v, visited));
            }
        }
        return result;
    }
    
    // Check iterative version in MyUndirectedGraph; same logic applies here.
    // Time complexity: O(V + E)
    public List<Integer> dfs() {
        List<Integer> result = new ArrayList<>();
        boolean[] visited = new boolean[V];
        for (int i = 0; i < V; i++) {
            if (!visited[i]) { // O(1)
                result.addAll(dfs(i, visited)); // O(Ev)
            }
        }
        // Time complexity: V(Constant + Ev) = O(V + E)
        // PTR: this will be V + 2E since each edge is checked twice across all DFS calls
        return result;
    }

    // ── Cycle Detection ───────────────────────────────────────────────────────
    private boolean hasCycleDFS(int src, boolean[] visited, boolean[] inStackMem) {
        inStackMem[src] = true;
        for (int v : adj.get(src)) {
            if (visited[v])
                continue;
            if (inStackMem[v] || hasCycleDFS(v, visited, inStackMem))
                return true;
        }
        inStackMem[src] = false; // reset inStackMem for next connected component iteration; else do a
                                 // Arrays.fill in hasCycle
        visited[src] = true; // mark this src as "safe" to prevent redundant traversal in future
        return false;
    }

    // Detect cycle in directed graph - O(V+E)
    public boolean hasCycle(boolean useDFS) {
        if (useDFS) {
            boolean[] visited = new boolean[V];
            boolean[] inStackMem = new boolean[V]; // temporary memory for every traversal
            for (int i = 0; i < V; i++) {
                if (!visited[i] && hasCycleDFS(i, visited, inStackMem))
                    return true;
            }
            return false;
        } else {
            return topologicalSortKahnsAlgo().isEmpty(); // assuming V > 0
        }
    }

    // ── Topological Sort ──────────────────────────────────────────────────────

    // Kahn's algorithm (BFS-based) - O(V+E)
    // Use: task scheduling, course prerequisites, build order.
    public List<Integer> topologicalSortKahnsAlgo() {
        // Algo:
        // - Compute in-degree for all nodes
        // - Enqueue nodes with in-degree 0
        // - repeatedly dequeue and reduce in-degree of neighbours
        // - if any neighbour's in-degree becomes 0, enqueue it.
        int[] inDegree = new int[V];
        for (int u = 0; u < V; u++) {
            for (int v : adj.get(u)) {
                inDegree[v]++;
            }
        }
        Queue<Integer> pending = new LinkedList<>();
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0)
                pending.add(i);
        }
        List<Integer> topoSort = new ArrayList<>();
        while (!pending.isEmpty()) {
            int front = pending.remove();
            topoSort.add(front);
            for (int v : adj.get(front)) {
                inDegree[v]--;
                if (inDegree[v] == 0)
                    pending.add(v);
            }
        }
        if (topoSort.size() != V) // cycle detected, return empty list
            return new ArrayList<>();
        return topoSort;
    }

    private boolean dfsTopo(int src, int[] visited, List<Integer> topoSort) {
        visited[src] = 1;
        for (int v : adj.get(src)) {
            if (visited[v] == 1)
                return false; // cycle detected
            if (visited[v] == 0 && !dfsTopo(v, visited, topoSort))
                return false;
        }
        visited[src] = 2;
        topoSort.add(src); // post-order: add AFTER all descendants are finished
        return true;
    }

    // DFS-based topological sort - O(V+E)
    // TopoSort def: for every edge u→v, u appears before v in the ordering.
    public List<Integer> topologicalSortDFS() {
        // (EFFICIENT) Soln. 1 - during DFS, check cycle side-by-side and return the topoSort list
        // Soln. 2 - check isCycle, if yes, return empty list; else return dfs()

        // Performing cycle checking using a single visited array
        int[] visited = new int[V]; // 0 = unvisited, 1 = visiting, 2 = visited

        // Note on how to collect nodes:
        // -----------------------------
        // Context: postOrder fashion def:=> add node to container only after all its neighbours are visited
        // 1. Conventional Way of Topo - add node in postOrder fashion using dfs() in Stack<>. No reverse needed.
        //  - Tip: use ArrayDeque as Stack for better performance since Stack is synchronized and has more overhead.
        // 2. Alternate Way of Topo - add node in postOrder fashion using dfs() in ArrayList<>. Finally reverse the array.
        //  - used in this. Check kosaraju for 1.
        // 3. Custom Way - perform normal dfs(i, visited), but collected result in addFirst fashion from every unvisited node.
        List<Integer> topoSort = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            if (visited[i] == 0) {
                if (!dfsTopo(i, visited, topoSort)) {
                    return new ArrayList<>(); // cycle detected, return empty list
                }
            }
        }
        Collections.reverse(topoSort); // post-order gives reverse topo order
        return topoSort;
    }

    // ── Shortest Paths ────────────────────────────────────────────────────────

    // Dijkstra — find shortest path from source to all nodes, given non-negative weights. Very similar to Prim's in implementation. 
    // Time complexity - O(ElogV)
    public int[] dijkstra(int src) {
        throw new UnsupportedOperationException("Same as MyUndirectedGraph.dijkstra(), just works for directed graph as well");
    }

    // Bellman-Ford — find shortest path from source to all nodes. Gives correct answer in case of negative weight unless there's -ve cycle -> helps detects negative cycle.
    // Time complexity - O(EV)
    public int[] bellmanFord(int src) {
        throw new UnsupportedOperationException("Same as MyUndirectedGraph.bellmanFord(), just works for directed graph as well");
    }

    // Floyd-Warshall — find shortest path between all pairs of nodes. Gives correct answer in case of -ve weight unless there's -ve cycle -> helps detects negative cycle.
    // Time complexity - O(V^3), space complexity - O(V^2).
    public int[][] floydWarshall() {
        throw new UnsupportedOperationException("Same as MyUndirectedGraph.floydWarshall(), just works for directed graph as well");
    }

    // ── Strongly Connected Components ─────────────────────────────────────────
    // Def: A strongly connected component (SCC) of a directed graph is a subgraph where there's a path from every node to every other node. SCCs are the directed graph analogue of connected components in undirected graphs.

    private Deque<Integer> getOrderedNodesForKosaraju_TopoStyle(int src, boolean[] visited, Deque<Integer> orderedNodes) {
        visited[src] = true;
        for (int v : adj.get(src)) { // O(Ev)
            if (!visited[v]) {
                getOrderedNodesForKosaraju_TopoStyle(v, visited, orderedNodes);
            }
        }
        orderedNodes.push(src); // post-order: add AFTER all descendants are finished
        return orderedNodes;
    }

    // Kosaraju's SCC - find/count strongly connected components in a directed graph.
    // Time complexity - O(V+E)
    public List<List<Integer>> kosarajuSCC() {
        // Algo:
        // - DFS to get nodes in sorted order (~topoSort), such that for every edge u→v, u appears before v in the ordering. 
        // - Reverse the graph
        // - DFS on reversed graph, following the order from step 1. Each DFS call gives one SCC.

        // Intuition:
        /**
         * Say for a graph:
         *  1 -> 2 -> 5 -> 6 -> 7
         *  ^    |         ^    |
         *  |    v         |    v
         *  4 <- 3         9 <- 8
         * 
         * i.e.
         * SCC1 → SCC2 → SCC3
         * 
         * The sorted order after DFS would be [1,2,5,6,7,8,9,3,4] !== topological sort since there's cycles, but similar behavior
         * 
         * Now, when you reverse the graph, you get:
         *  1 <- 2 <- 5 <- 6 <- 7
         *  |    ^         |    ^
         *  v    |         v    |
         *  4 -> 3         9 -> 8
         * 
         * i.e.
         * SCC1 <- SCC2 <- SCC3
         * 
         * Now, if you do DFS on reversed graph, following the order from step 1, you get:
         * - Start with 1: DFS gives SCC1 = {1,4,3,2}
         * - Next is 2, but it's already visited in previous DFS, so skip
         * - Next is 5: DFS gives SCC2 = {5}, you don't visited 2 since it's already visited
         * - Next is 6: DFS gives SCC3 = {6,7,8,9}
         * - 7,8,9 are already visited in previous DFS, so skip
         * - 3,4 are already visited in first DFS, so skip
         */
        
        // List<Integer> orderedNodes = dfs(); // WRONG - dfs doesn't guarantee toposort like ordering. 
        // eg. dfs() starts from 0 by default and produces [0,4,3,2,1]. On reversing the graph, when dfs starts from 0, then no new SCC is detected
        /**
         *  1 -> 0 <- 2       1 <- 0 -> 2
         *       |    ^            ^    |
         *       v    |   ->       |    v
         *       4 -> 3            4 <- 3
         */
        // Soln.
        // Context: postOrder fashion def:=> add node to container only after all its neighbours are visited
        // 1. Conventional Way of Topo - add node in postOrder fashion using dfs() in Stack<>. No reverse needed.
        // 2. Alternate Way of Topo - add node in postOrder fashion using dfs() in ArrayList<>. Finally reverse the array.
        // 3. Custom Way - perform normal dfs(i, visited), but collected result in addFirst fashion from every unvisited node.
        Deque<Integer> orderedNodes = new ArrayDeque<>(); // not using Stack since it's synchronized and has more overhead
        boolean[] visited = new boolean[V];
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                getOrderedNodesForKosaraju_TopoStyle(i, visited, orderedNodes);
            }
        }

        MyDirectedGraph reversedGraph = new MyDirectedGraph(V);
        for (int u = 0; u < V; u++) { // O(E)
            for (int v : adj.get(u)) {
                reversedGraph.addEdge(v, u);
            }
        }

        boolean[] visited = new boolean[V];
        List<List<Integer>> sccs = new ArrayList<>();
        while(!orderedNodes.isEmpty()) { // O(V + E)
            int node = orderedNodes.pop();
            if(!visited[node]) {
                List<Integer> scc = reversedGraph.dfs(node, visited);
                sccs.add(scc);
            }
        }
        // Time complexity: (V+E) + E + (V+E) = O(V+E)
        return sccs;
    }

    class MyTarjanSCCInitialApproach_Wrong {
        private void tarjanSccDFS(int src, int parent, int discTime, int[] disc, int[] low, boolean[] visited,
                List<int[]> bridges) {
            visited[src] = true;
            disc[src] = low[src] = discTime;

            for (int v : adj.get(src)) {
                if (v == parent)
                    continue;

                if (!visited[v]) {
                    tarjanSccDFS(v, src, discTime + 1, disc, low, visited, bridges);
                    low[src] = Math.min(low[src], low[v]);
                    if (low[v] > disc[src]) {
                        bridges.add(new int[] { src, v });
                    }
                } else {
                    if (disc[v] == -1)
                        bridges.add(new int[] { src, v });
                    else
                        low[src] = Math.min(low[src], disc[v]);
                }
            }
        }

        // Tarjan's SCC - find/count strongly connected components in a directed graph.
        // Time complexity - O(V+E)
        public List<List<Integer>> tarjanSCC() {
            // process is same as finding bridges in UndirectedGraph
            // after a dfs gets over here, mark disc[] as -1 for all visited nodes.
            // In the following iteration, if you land on any v with disc[v] (aka
            // unreachable node from where there's no comeback practically), add that edge as bridge
            // Collect all bridges
            // remove temp from graph
            // run dfs over all nodes, and collect SCCs
            // re-establish bridges to maintain graph

            int[] disc = new int[V];
            int[] low = new int[V];
            boolean[] visited = new boolean[V];
            List<int[]> bridges = new ArrayList<>();
            for (int u = 0; u < V; u++) {
                if (!visited[u]) {
                    tarjanSccDFS(u, -1, 0, disc, low, visited, bridges);
                    // mark all visited nodes with disc[] = -1
                    for (int i = 0; i < V; i++) {
                        if (visited[i])
                            disc[i] = -1;
                    }
                    // **NEW LEARNING**
                    // alternate way using streams - fyi, no boolean[] stream
                    // - IntStream.range(0, V).filter(i -> visited[i]).forEach(i -> disc[i] = -1);
                    // - IntStream.range(0, V).forEach(i -> { if (visited[i]) disc[i] = -1; });
                }
            }

            // remove all bridges
            for (int[] e : bridges) {
                int u = e[0];
                int v = e[1];
                adj.get(u).remove(Integer.valueOf(v)); // not remove(index)
            }

            // dfs on all nodes to get scc
            List<List<Integer>> scc = new ArrayList<>();
            Arrays.fill(visited, false);
            for (int u = 0; u < V; u++) {
                if (!visited[u])
                    scc.add(dfs(u, visited));
            }

            // reinstate the bridges
            for (int[] e : bridges) {
                int u = e[0];
                int v = e[1];
                adj.get(u).add(v);
            }
            return scc;
        }

        // Problems:
        // 1. Loop between 2 nodes fails this algo due to presence of parent
        // - eg. 0->1->2->0, 2->3->4->3. In this case {0,1,2}, {3}, {4} will be answered as SCC whereas {3,4} is a single SCC
        // 2. Even if I remove parent check, it fails due to difference between reachability and STRONG connectivity.
        // - Tarjan's algo for finding bridge was based on reachability in undirected graph
        // - eg. 0->1->2, 0->2. In this above algo gives {0,2} and {1} as SCCs, whereas all three should be separate SCCs. This happened because we assumed if 0 can reach 2 (visited), then 2 must be having an alternate path to 0, which was true had it been undirected graph.
    }

    // @AI - should revise / code yourself next time
    private List<Integer> tarjanDFS(int src, int discTime, int[] disc, int[] low, boolean[] inStack, Deque<Integer> stack) {
        disc[src] = low[src] = discTime;
        stack.push(src);
        inStack[src] = true;

        for (int v : adj.get(src)) {
            if (disc[v] == -1) { // unvisited: tree edge
                tarjanDFS(v, discTime + 1, disc, low, inStack, stack);
                low[src] = Math.min(low[src], low[v]);
            } else if (inStack[v]) { // back edge: v is in current DFS path → same SCC
                low[src] = Math.min(low[src], disc[v]);
            }
            // visited but NOT in stack → v already belongs to a completed SCC; ignore.
            // (this is the key difference from bridge-finding, where all visited back edges are considered)
        }

        // src is the root of an SCC if no back edge can reach an ancestor of src
        List<Integer> scc = new ArrayList<>();
        if (low[src] == disc[src]) {
            while (true) { // intentional, since we gurantee to find src in stack - could have used while(!stack.isEmpty()) as well but that sets false expectation that src might not be found in stack
                int node = stack.pop();
                inStack[node] = false;
                scc.add(node);
                if (node == src) break; // src is the bottom of this SCC on the stack
            }
        }
        return scc;
    }

    // Tarjan's SCC - find/count strongly connected components in a directed graph.
    // Time complexity - O(V+E)
    public List<List<Integer>> tarjanSCC() {
        int[] disc = new int[V]; // discovery time of each node during DFS
        int[] low = new int[V]; // low-link values: lowest discovery time reachable from this node
        boolean[] inStack = new boolean[V]; // whether a node is currently in the stack
        Deque<Integer> stack = new ArrayDeque<>(); // stack to hold nodes in current DFS path
        
        Arrays.fill(disc, -1); // -1 = unvisited
        List<List<Integer>> sccs = new ArrayList<>();

        for (int i = 0; i < V; i++) {
            if (disc[i] == -1) {
                sccs.add(tarjanDFS(i, 0, disc, low, inStack, stack));
            }
        }
        // Time complexity: O(V+E) — each node and edge visited exactly once
        return sccs;

        // Small Alternative: You can keeping int[] visited with states like 0 = unvisited, 1 = visiting (in stack), 2 = visited (not in stack) instead of inStack[] arrays.
    }

    // ── Bridges & Articulation Points ────────────────────────────────────────
    // Def: Bridge (cut edge) is an edge whose removal increases the number of connected components (in undirected graph) or strongly connected components (in directed graph).
    // Def: Articulation point (cut vertex) is a node whose removal increases the number of connected components (in undirected graph) or strongly connected components (in directed graph).
    
    // In an undirected graph, a bridge is simply an edge whose removal increases the number of connected components.
    // In a directed graph, the equivalent concept is a Strong Bridge (an edge whose removal increases the number of SCCs). Standard Tarjan's algorithm fails here, 
    // so use Italiano’s Algorithm to find bridges and articulation points in directed graphs.

    public List<int[]> findBridges() {
        throw new UnsupportedOperationException("Use Italiano’s Algorithm for directed graphs. Tarjan's algo fails to find bridges in directed graphs ");
    }

    public List<Integer> findArticulationPoints() {
        throw new UnsupportedOperationException("Use Italiano’s Algorithm for directed graphs. The algo for undirected graphs does not apply here");
    }

    // ── Network Flow ──────────────────────────────────────────────────────────

    // Dinic's Max Flow. O(V^2 * E) — practical performance much better.
    // PTR: alternates BFS (build level graph) and DFS (find blocking flow).
    // PTR: use residual graph; reverse edge has capacity 0 initially.
    // Use: max-flow, min-cut, bipartite matching.
    public int maxFlow(int source, int sink) {
        throw new UnsupportedOperationException("TODO");
    }

    // ── DAG-specific Algorithms ───────────────────────────────────────────────

    // Longest path in a DAG. O(V+E)
    // PTR: only valid for DAGs (no negative-weight trick needed).
    // Topological sort + DP: dp[v] = max(dp[v], dp[u] + weight(u,v)).
    public int[] longestPath(int src) {
        throw new UnsupportedOperationException("TODO");
    }

    // Count all paths from src to dst in a DAG. O(V+E)
    // PTR: topological sort + DP: dp[dst] accumulates path counts.
    public long countPaths(int src, int dst) {
        throw new UnsupportedOperationException("TODO");
    }
}


// ── Main — Usage Documentation
// ────────────────────────────────────────────────
public class _19_GraphImpl {
    public static void main(String[] args) {

        // ── Adjacency list graph ───────────────────────────────────────────────
        //
        // 0 → 1 (w=4)
        // 0 → 2 (w=1)
        // 2 → 1 (w=2)
        // 1 → 3 (w=1)
        // 2 → 3 (w=5)
        //
        Graph g = new Graph(4);
        g.addEdge(0, 1, 4);
        g.addEdge(0, 2, 1);
        g.addEdge(2, 1, 2);
        g.addEdge(1, 3, 1);
        g.addEdge(2, 3, 5);

        // BFS — unweighted distances from 0
        int[] bfsDist = g.bfs(0);
        // bfsDist = [0, 1, 1, 2] (hop count)

        // Dijkstra — weighted shortest paths from 0
        int[] dist = g.dijkstra(0);
        // dist = [0, 3, 1, 4] (0→2→1→3 is cheapest at 4)

        // Bellman-Ford — same graph, handles negative edges
        int[] bfDist = g.bellmanFord(0);

        // Floyd-Warshall — all-pairs
        int[][] allPairs = g.floydWarshall();

        // Topological sort (only valid for DAGs)
        int[] topoKahn = g.topologicalSortKahn();
        int[] topoDFS = g.topologicalSortDFS();

        // Cycle detection
        System.out.println(g.hasCycleDirected()); // false for the example above
        System.out.println(g.hasCycleUndirected()); // depends on interpretation

        // Bipartite check
        System.out.println(g.isBipartite());

        // Bridges and articulation points
        List<int[]> bridges = g.findBridges();
        List<Integer> aps = g.findArticulationPoints();

        // SCCs
        List<List<Integer>> sccKos = g.kosarajuSCC();
        List<List<Integer>> sccTar = g.tarjanSCC();

        // Max flow
        int flow = g.maxFlow(0, 3);

        // Prim's MST
        int mstWeight = g.prim();

        // ── DSU ───────────────────────────────────────────────────────────────
        DSU dsu = new DSU(5);
        dsu.union(0, 1);
        dsu.union(1, 2);
        System.out.println(dsu.connected(0, 2)); // true
        System.out.println(dsu.connected(0, 3)); // false

        // ── Kruskal MST ───────────────────────────────────────────────────────
        // edges: {weight, u, v}
        int[][] edges = { { 1, 0, 2 }, { 2, 2, 1 }, { 4, 0, 1 }, { 1, 1, 3 }, { 5, 2, 3 } };
        Kruskal kruskal = new Kruskal();
        System.out.println(kruskal.mst(4, edges)); // 4 (edges: 0-2 w1, 2-1 w2, 1-3 w1)

        // ── Key Patterns (no code, just notes) ────────────────────────────────
        //
        // Pattern 1: Multi-source BFS
        // → Push all sources into queue at distance 0 before BFS starts.
        // → Use: "nearest exit", "rotting oranges", "walls and gates".
        //
        // Pattern 2: 0-1 BFS (deque)
        // → Cost 0 edges → deque.addFirst(); cost 1 edges → deque.addLast().
        // → Use: grid problems where moves have cost 0 or 1.
        //
        // Pattern 3: Dijkstra on implicit graph (no explicit edge list)
        // → State = (cost, node_state); encode node_state as single integer.
        // → Use: "minimum cost to reach target with constraints" problems.
        //
        // Pattern 4: Bidirectional BFS
        // → Run BFS from both source and target simultaneously.
        // → Stop when frontiers meet; halves search depth → O(b^(d/2)) instead of
        // O(b^d).
        // → Use: word ladder, shortest transformation sequence.
        //
        // Pattern 5: Topological sort + DP (DAG DP)
        // → Process nodes in topological order; propagate values forward.
        // → Use: longest path in DAG, number of paths, critical path (project
        // scheduling).
        //
        // Pattern 6: SCC → Condensation DAG
        // → Contract each SCC to a single node; result is always a DAG.
        // → Use: 2-SAT, reachability in directed graphs, strongly connected
        // sub-problems.
        //
        // Pattern 7: 2-SAT
        // → Model implications as directed graph; variable x and ¬x are nodes.
        // → Run Tarjan's SCC; if x and ¬x are in the same SCC → unsatisfiable.
        //
        // Pattern 8: Bipartite Matching (Hopcroft-Karp)
        // → O(E * sqrt(V)); use when matching left to right nodes optimally.
        // → Min vertex cover = Max matching (König's theorem for bipartite graphs).
        //
        // Pattern 9: Minimum cut = Maximum flow (Max-flow Min-cut theorem)
        // → Run Dinic's; BFS on residual graph from source; reachable nodes = S-side.
        //
        // Pattern 10: Virtual / Super source-sink node
        // → Add a super-source connected to all real sources (weight = INF or supply).
        // → Use: multi-source Dijkstra, multi-sink flow problems.
        //
        // Pattern 11: Negative cycle detection
        // → Bellman-Ford: V-th relaxation round still relaxes → negative cycle.
        // → Floyd-Warshall: dist[i][i] < 0 → node i is on a negative cycle.
        //
        // Pattern 12: Euler path / circuit
        // → Undirected: Euler circuit exists iff all degrees even & graph connected.
        // Euler path exists iff exactly 2 odd-degree vertices.
        // → Directed: circuit iff in-degree == out-degree for all nodes.
        // path iff one node has out-in=1 (start), one has in-out=1 (end).
        // → Algorithm: Hierholzer's DFS; push node after exhausting its edges.
    }
}
