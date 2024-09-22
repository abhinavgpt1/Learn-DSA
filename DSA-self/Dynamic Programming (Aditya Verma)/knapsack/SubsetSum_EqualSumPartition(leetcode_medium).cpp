/**
 * 416. Partition Equal Subset Sum
 * -------------------------------
 * Given an integer array nums, return true if you can partition the array into two subsets 
 * such that the sum of the elements in both subsets is equal or false otherwise.
 * 
 * Constraints:
 * 1 <= nums.length <= 200
 * 1 <= nums[i] <= 100
 */
// link: https://leetcode.com/problems/partition-equal-subset-sum/description/
// link: https://www.geeksforgeeks.org/problems/subset-sum-problem2014/1
// article : https://www.geeksforgeeks.org/partition-problem-dp-18/

// Solution 1: Bottom-up: O(N*sum/2), O(sum/2)
class Solution{
    public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum%2)
            return false;
        sum /= 2;
        int n = nums.size();
        vector<bool> dp(sum + 1, false);
        dp[0] = true;
        for(int pos=1; pos<=n; pos++){
            // IMP: it is from sum to 1. In case of confusion, just use 2 arrays (curr, prev) and code conventionally. 
            // It isn't unbounded knapsack, and going from left to right will consider same element twice, hence this is a unique technique where we go from right to left just to avoid double element counting.
            for(int ls=sum; ls>=j >= arr[i]; ls--){// ls>=1 is unnecessary
                if(nums[pos - 1] <= ls)
                    dp[ls] = dp[ls - nums[pos-1]] || dp[ls];
                // optimization by https://medium.com/@ayundaywhea/leetcode-416-partition-equal-subset-sum-dynamic-programming-1d-array-solution-with-python-928569928064
                if(dp[sum])
                    return dp[sum];
            }
        }
        return dp[sum];
    }
};

// Solution 2: Bottom-up: O(N*sum/2), O(sum/2)
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n=nums.size();
        int sum=0;
        for(int i=0;i<n;i++)sum+=nums[i];

        if(sum%2)return false;
        sum/=2; //Why take original sum, when we just need to check if dp at sum/2 exists or not.
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

// Solution 3: Memoization: O(N*sum/2), O(N*sum/2)
class Solution {
    // Memoization will work in max. cases (odd case: Scrambled String)
    bool isSubsetHelper(int index, int n, vector<int> &arr, int sum, vector<vector<int>> &dp){
        if(sum == 0)
            return true;
        if(index == n)
            return false;
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

// Solution 4: Memoized code failed at leetcode because of below dp size
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