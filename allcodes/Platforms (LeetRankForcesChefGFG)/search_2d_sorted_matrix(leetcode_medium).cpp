/*
240. Search a 2D Matrix II
Medium

Write an efficient algorithm that searches for a target value in an m x n integer matrix. The matrix has the following properties:

    Integers in each row are sorted in ascending from left to right.
    Integers in each column are sorted in ascending from top to bottom.

 

Example 1:

Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
Output: true

Example 2:

Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
Output: false

 

Constraints:

    m == matrix.length
    n == matrix[i].length
    1 <= n, m <= 300
    -109 <= matrix[i][j] <= 109
    All the integers in each row are sorted in ascending order.
    All the integers in each column are sorted in ascending order.
    -109 <= target <= 109


*/

//O(n)
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int i = 0, j = n-1;
        while(i<m && j>=0){
            if(matrix[i][j] == target)
                return true;
            else if(matrix[i][j] < target)
                i++;
            else
                j--;
        }
        return false;
    }
};
//O((logn)^2) : wrong approach : below example will fail it
// [[1,3,5,7,9],[2,4,6,8,10],[11,13,15,17,19],[12,14,16,18,20],[21,22,23,24,25]]
// 13

class Solution {
public:
    bool binary_search_column(vector<vector<int>>& matrix, int j, int st, int end, int target){
        int mid = (end+st)/2;
        if(st>end)
            return false;
        if(matrix[mid][j] == target)
            return true;
        if(matrix[mid][j] < target)
            return binary_search_column(matrix, j, mid+1, end, target);
        else
            return binary_search_column(matrix, j, st, mid-1, target);
    }
    bool solve(vector<vector<int>>& matrix, int st, int end, int m, int n, int target){
        int mid = (end+st)/2;
        if(st>end)
            return false;
        if(matrix[0][mid] == target)
            return true;
        if(binary_search_column(matrix,mid, 0, m-1, target))
            return true;
        if(matrix[0][mid] < target)
            return solve(matrix, mid+1, end, m, n, target);
        else
            return solve(matrix, st, mid-1, m, n, target);
    }
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        return solve(matrix, 0, n-1, m, n, target);
    }
};