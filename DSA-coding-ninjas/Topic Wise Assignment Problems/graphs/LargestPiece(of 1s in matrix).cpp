/*
Largest Piece
Send Feedback
It's Gary's birthday today and he has ordered his favourite square cake consisting of '0's and '1's . But Gary wants the biggest piece of '1's and no '0's . A piece of cake is defined as a part which consist of only '1's, and all '1's share an edge with each other on the cake. Given the size of cake N and the cake, can you find the count of '1's in the biggest piece of '1's for Gary ?
Input Format :
The first line of input contains an integer, that denotes the value of N. 
Each of the following N lines contain N space separated integers.
Output Format :
Print the count of '1's in the biggest piece of '1's, according to the description in the task.
Constraints :
1 <= N <= 1000
Time Limit: 1 sec
Sample Input 1:
2
1 1
0 1
Sample Output 1:
3
*/
int dfs(vector<vector<int>> &cake, vector<vector<int>> &dp, int x, int y, int n) {
 	
    if(x<0 || x == n || y < 0 || y == n || cake[x][y] == 0 || dp[x][y])
        return 0;
    dp[x][y] = 1;
    return 1 + 
        dfs(cake, dp, x + 1, y, n) + 
        dfs(cake, dp, x - 1, y, n) + 
        dfs(cake, dp, x, y + 1, n) + 
        dfs(cake, dp, x, y - 1, n);
}
int getBiggestPieceSize(vector<vector<int>> &cake, int n) {
    
    vector<vector<int>> dp(n, vector<int>(n, 0));
    int maxAns = 0;
    for(int i = 0; i<n; i++){
    	for(int j = 0; j<n; j++){
    	   if(!dp[i][j] && cake[i][j] == 1){
           		maxAns = max(maxAns, dfs(cake, dp, i, j, n));    
           }
    	}
    }
    return maxAns;
}