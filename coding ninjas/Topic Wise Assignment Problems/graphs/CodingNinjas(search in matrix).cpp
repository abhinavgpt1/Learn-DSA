/*
Coding Ninjas
Send Feedback
Given a NxM matrix containing Uppercase English Alphabets only. Your task is to tell if there is a path in the given matrix which makes the sentence “CODINGNINJA” .
There is a path from any cell to all its neighbouring cells. For a particular cell, neighbouring cells are those cells that share an edge or a corner with the cell.
Input Format :
The first line of input contains two space separated integers N and M, where N is number of rows and M is the number of columns in the matrix. 
Each of the following N lines contain M characters. Please note that characters are not space separated.
Output Format :
Print 1 if there is a path which makes the sentence “CODINGNINJA” else print 0.
Constraints :
1 <= N <= 1000
1 <= M <= 1000
Time Limit: 1 second
Sample Input 1:
2 11
CXDXNXNXNXA
XOXIXGXIXJX
Sample Output 1:
1
*/

// Q - why pass by value of graph / visited array (as vector) didn't worked in graph problems? (Runtime error or TLE)("CODINGNINJA" matrix search problem)
// A - copying of large vector<vector> / vector in multiple function calls fills up the stack

// method 1: pass visited by reference and keep doing visitied[x][y] = false so as to reset it for next 'C'
// method 2: pass visited by reference and reinitialize it with false for next C's DFS

#include <iostream>
#include <vector>
using namespace std;

// method1: codingninjas help
bool dfs(vector<vector<char>> &board, vector<vector<bool>> &visited, int n, int m, int x, int y, string sentence) {
    if(sentence.length() == 0)
        return true;
    if(x < 0 || y < 0 || x == n || y == m || sentence[0] != board[x][y] || visited[x][y])
        return false;
    
    
    visited[x][y] = true;
    
    bool ans = ((sentence[0] == board[x][y]) &&
        (dfs(board, visited, n, m, x + 1, y, sentence.substr(1)) ||
        dfs(board, visited, n, m, x - 1, y, sentence.substr(1)) ||
        dfs(board, visited, n, m, x, y + 1, sentence.substr(1)) ||
        dfs(board, visited, n, m, x, y - 1, sentence.substr(1)) ||
        dfs(board, visited, n, m, x + 1, y - 1, sentence.substr(1)) ||
        dfs(board, visited, n, m, x + 1, y + 1, sentence.substr(1)) ||
        dfs(board, visited, n, m, x - 1, y - 1, sentence.substr(1)) ||
        dfs(board, visited, n, m, x - 1, y + 1, sentence.substr(1))));
    
    if(ans == false)
        visited[x][y] = false;
    return ans;
}
bool hasPath(vector<vector<char>> &board, int n, int m) {
    
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    string sentence = "CODINGNINJA";
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(board[i][j] == 'C' && dfs(board, visited, n, m, i, j, sentence))
                return true;            
        }
    }
    return false;
}
// method2 - still fails at one tc. creation and destruction of 2d vector m*n times
bool dfs(vector<vector<char>> &board, vector<vector<bool>> &visited, int n, int m, int x, int y, string sentence) {
    if(sentence.length() == 0)
        return true;
    if(x < 0 || y < 0 || x == n || y == m || sentence[0] != board[x][y] || visited[x][y])
        return false;
    
    visited[x][y] = true;
    
    return ((sentence[0] == board[x][y]) &&
        (dfs(board, visited, n, m, x + 1, y, sentence.substr(1)) ||
        dfs(board, visited, n, m, x - 1, y, sentence.substr(1)) ||
        dfs(board, visited, n, m, x, y + 1, sentence.substr(1)) ||
        dfs(board, visited, n, m, x, y - 1, sentence.substr(1)) ||
        dfs(board, visited, n, m, x + 1, y - 1, sentence.substr(1)) ||
        dfs(board, visited, n, m, x + 1, y + 1, sentence.substr(1)) ||
        dfs(board, visited, n, m, x - 1, y - 1, sentence.substr(1)) ||
        dfs(board, visited, n, m, x - 1, y + 1, sentence.substr(1))));
}
bool hasPath(vector<vector<char>> &board, int n, int m) {

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    string sentence = "CODINGNINJA";
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(board[i][j] == 'C'){
    			visited.assign(n, vector<bool>(m, false));
                if(dfs(board, visited, n, m, i, j, sentence))
                	return true;            
            }
        }
    }
    return false;
}