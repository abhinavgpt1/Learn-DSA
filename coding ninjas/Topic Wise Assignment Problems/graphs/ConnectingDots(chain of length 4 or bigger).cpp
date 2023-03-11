/*
Connecting Dots
Send Feedback
Gary has a board of size NxM. Each cell in the board is a coloured dot. There exist only 26 colours denoted by uppercase Latin characters (i.e. A,B,...,Z). Now Gary is getting bored and wants to play a game. The key of this game is to find a cycle that contain dots of same colour. Formally, we call a sequence of dots d1, d2, ..., dk a cycle if and only if it meets the following condition:
1. These k dots are different: if i ≠ j then di is different from dj.
2. k is at least 4.
3. All dots belong to the same colour.
4. For all 1 ≤ i ≤ k - 1: di and di + 1 are adjacent. Also, dk and d1 should also be adjacent. Cells x and y are called adjacent if they share an edge.
Since Gary is colour blind, he wants your help. Your task is to determine if there exists a cycle on the board.
Input Format :
The first line of input contains two space separated integers N and M, where N is number of rows and M is the number of columns of the board. 
Each of the following N lines contain M characters. Please note that characters are not space separated. Each character is an uppercase Latin letter.
Output Format :
Print true if there is a cycle in the board, else print false.
Constraints :
2 <= N <= 1000
2 <= M <= 1000
Time Limit: 1 second
Sample Input 1:
3 4
AAAA
ABCA
AAAA
Sample Output 1:
true
*/

// method1: pass the parent and keep count(redundant)
int dirX[] = {1, -1, 0, 0};
int dirY[] = {0, 0, 1, -1};

bool cycleDetected(vector<vector<char>> &board, vector<vector<bool>> &visited, int n, int m, int x, int y, int fromX, int fromY, char color) {
        
    if(x == n || x < 0 || y == m || y < 0 || board[x][y] != color)
        return false;
    
    //count >=4 is redundant since, when visited = true a loop of >=4 will be made for sure
    //would be beneficial if all 8 directions were opened and min count >= 4
    if(visited[x][y])
        return true;
    
    visited[x][y] = true;
    for(int i=0; i<4; i++){
        int newx = x + dirX[i];
        int newy = y + dirY[i];
        if(newx == fromX && newy == fromY)
            continue;
        if(cycleDetected(board, visited, n, m, newx, newy, x, y, color))
            return true;
    }
    // visited[x][y] = false; //this way all points of same color will be visited along dfs
    return false;
    	
}
bool hasCycle(vector<vector<char>> &board, int n, int m) {
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    
    for(int i=0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(!visited[i][j] && cycleDetected(board, visited, n, m, i, j, -1, -1, board[i][j]))
                return true;
        }
    }
    return false;
}

// method2: converge on the point of cycle initiation - inefficient than parent passing approach
bool cycleDetected(vector<vector<char>> &board, vector<vector<bool>>&visited, int n, int m, int i, int j, char color, int count, int x, int y) {
    
    if(i == x && j == y && count >= 4){
        return true;
    }
        
    if(i == n || i < 0 || j == m || j < 0 || visited[i][j] || board[i][j] != color)
        return false;
    count++;
    visited[i][j] = true;
    if(
    cycleDetected(board, visited, n, m, i + 1, j, color, count, x, y)||
    cycleDetected(board, visited, n, m, i - 1, j, color, count, x, y)||
    cycleDetected(board, visited, n, m, i, j + 1, color, count, x, y)||
    cycleDetected(board, visited, n, m, i, j - 1, color, count, x, y)){
        return true;
    }
    else{
        visited[i][j] = false;
        return false;
    }
    	
}
bool hasCycle(vector<vector<char>> &board, int n, int m) {
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    
    for(int i=0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(cycleDetected(board, visited, n, m, i, j, board[i][j], 0, i, j))
                return true;
        }
    }
    return false;
}