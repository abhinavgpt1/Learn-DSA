Find more questions on:
https://takeuforward.org/interviews/strivers-sde-sheet-top-coding-interview-problems/

Complexity analysis
-------------------
1. Complexity of BFS in undirected graph
    * T(n) = O(V + 2E) ~ O(V + E)
    * S(n) = O(V)
    * how we got (V + 2*E) - https://stackoverflow.com/questions/26549140/breadth-first-search-time-complexity-analysis (it is actually 2E not E)
2. Complexity of DFS in undirected graph
    * T(n) = O(V + 2E) ~ O(V + E)
    * S(n) = O(V) - include recursion stack space too
3. cycle detection in undirected graph using BFS
    * https://www.youtube.com/watch?v=BPlrALf1LDU&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=11
    * BFS - O(V + 2E) + O(V)
    * 2E => summation of adj nodes = summation of edges w.r.t every node = summation of degree
    * O(V+2E) -> running for all vertices in a helper function i.e. while emptying the queue
    * O(V) -> running for loop in main function for component graph
    * space - O(V) - even in case of component graph - reason: comes from storage in queue
4. DFS directed graph - 2E changes to E since redirections are restricted

Is time complexity additive - https://stackoverflow.com/questions/25337687/what-is-the-difference-between-on-om-and-on-m-is-there-any