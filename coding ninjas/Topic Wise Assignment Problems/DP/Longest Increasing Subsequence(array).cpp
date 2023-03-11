/*
Longest Increasing Subsequence
Send Feedback
Given an array with N elements, you need to find the length of the longest subsequence in the given array such that all elements of the subsequence are sorted in strictly increasing order.
Input Format
The first line of input contains an integer N. The following line contains N space separated integers, that denote the value of elements of array.
Output Format
The first and only line of output contains the length of longest subsequence.
Constraints
1 <= N <= 10^3
Time Limit: 1 second
Sample Input 1 :
6
5 4 11 1 16 8
Sample Output 1 :
3
Sample Output Explanation
Length of longest subsequence is 3 i.e. (5,11,16) or (4,11,16).
Sample Input 2 :
3
1 2 2
Sample Output 2 :
2
*/

// recursive
int helper(int* arr, int n, int index) {
    
    if(index == n)
        return 0;
    
    int ans = 1;
    for(int i=index+1; i<n; i++){
        if(arr[i] > arr[index]){
            int temp = helper(arr, n, i) + 1;
            ans = max(ans, temp);
        }
    }
    return ans;
}
int longestIncreasingSubsequence(int* arr, int n) {
	
    int ans = 0;
    
    for(int i=0; i<n; i++){
        int temp = helper(arr, n, i);
        ans = max(ans, temp);
    }
    return ans;
    
}

// memoization - n^2
int helper(int* arr, int n, int index, int *dp) {
    
    if(index == n)
        return 0;
    
    if(dp[index] != -1)
        return dp[index];
    
    int ans = 1;
    for(int i=index+1; i<n; i++){
        if(arr[i] > arr[index]){
            int temp = helper(arr, n, i, dp) + 1;
            ans = max(ans, temp);
        }
    }
    return dp[index] = ans;
}
int longestIncreasingSubsequence(int* arr, int n) {
	
    int ans = 0;
    int *dp = new int[n];
    for(int i=0; i<n; i++)
        dp[i] = -1;
    
    for(int i=0; i<n; i++){
        int temp = helper(arr, n, i, dp); //precalculated results are returned starightaway
        ans = max(ans, temp);
    }
    delete[] dp;
    return ans;   
}

// dp - time = O(n^2) and space = O(n^2)
int longestIncreasingSubsequence(int* arr, int n) {
	
    int *dp = new int[n];
    int result = 0;
    for(int i=0; i<n; i++){
        int localMax = 0;
     	for(int j = i-1; j>=0; j--){
            
            if(arr[j] < arr[i])
                localMax = max(dp[j], localMax);
        }   
        dp[i] = localMax + 1;
        result = max(result, dp[i]);
    }
    delete[] dp;
    return result;
    
}

// using LCS - GFG
// Method 3: Dynamic Programming 

// If we closely observe the problem then we can convert this problem to longest Common Subsequence Problem. Firstly we will create another array of unique elements of original array and sort it. Now the longest increasing subsequence of our array must be present as a subsequence in our sorted array. That’s why our problem is now reduced to finding the common subsequence between the two arrays.

// Eg. arr =[50,3,10,7,40,80]
//     // Sorted array
//     arr1 = [3,7,10,40,50,80]
//     // LIS is longest common subsequence between the two arrays
//     ans = 4
//     The longest increasing subsequence is {3, 7, 40, 80}

// -> inefficient since, space complexity = O(n^2) and time too.