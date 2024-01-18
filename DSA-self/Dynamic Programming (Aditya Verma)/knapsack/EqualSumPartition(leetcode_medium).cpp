/**
 * 416. Partition Equal Subset Sum
 * Given an integer array nums, return true if you can partition the array into two subsets 
 * such that the sum of the elements in both subsets is equal or false otherwise.
 * 
 * ref: https://leetcode.com/problems/partition-equal-subset-sum/description/
 */

// Solution 1: We can run for sum/2
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n=nums.size();
        int sum=0;
        for(int i=0;i<n;i++)sum+=nums[i];

        if(sum%2)return false;
         sum/=2; //Why for original sum, when we just need to check if sum/2 exists as a subset
        int dp[n+1][sum+1];
        for(int i=0;i<=sum;i++)dp[0][i]=0;
        for(int i=0;i<=n;i++)dp[i][0]=1;

        for(int i=1;i<=n;i++){
            for(int j=1;j<=sum;j++){
                if(nums[i-1]<=j){
                    dp[i][j]=dp[i-1][j-nums[i-1]]||dp[i-1][j];
                }
                else dp[i][j]=dp[i-1][j];
            }
        }
        return dp[n][sum];
    }
};

// Solution 2: Memoized code failed at leetcode because of below dp size
class Solution {
public:
    bool canPartition(vector<int> &arr) {
        // memoization didn't work due to function calls
        // Its the exact problem like "Subset sum problem", but we are checking the sum as arrSum/2
        int arrSum = accumulate(arr.begin(), arr.end(), 0);
        if(arrSum%2)
            return false;

        // It stores T/F whether elements from 0 to i can have a sum S (1->sum)
        // None among dp[200][j] or dp[i][0] is redundant
        bool dp[201][20001];
        memset(dp, 0, sizeof(dp));
        int n = arr.size();
        // base condition
        for(int i=0; i<n; i++)
            dp[i][0] = true;
        // bottom-up soln.
        for(int pos=1; pos <= n; pos++){
            for(int sum = 1; sum <= arrSum; sum++){
                if(arr[pos - 1] <= sum)
                    dp[pos][sum] = dp[pos-1][sum - arr[pos - 1]] || dp[pos-1][sum];
                else
                    dp[pos][sum] = dp[pos-1][sum];
            }
        }
        return dp[n][arrSum/2];
    }
};
 
// WRONG: https://www.geeksforgeeks.org/subset-sum-problem-osum-space/ which promises S(n) = O(sum)*1 
// We need to store w.r.t. element, eg. [1,2,5]

// Solution 3: Memoized soln.
class Solution {
    // Memoization will work in max. cases (odd case: Scrambled String)
    bool isSubsetHelper(int index, int n, vector<int> &arr, int sum, vector<vector<int>> &dp){
        if(index == n)
            return sum == 0;
        if(dp[index][sum] != -1)
            return dp[index][sum];
        
        if(arr[index] <= sum)
            return dp[index][sum] = isSubsetHelper(index + 1, n, arr, sum - arr[index], dp) || isSubsetHelper(index + 1, n, arr, sum, dp);
        else
            return dp[index][sum] = isSubsetHelper(index + 1, n, arr, sum, dp);
    }
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum%2)
            return false;
        sum /= 2;
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(sum + 1, -1));
        return isSubsetHelper(0, n, nums, sum, dp);
    }
};