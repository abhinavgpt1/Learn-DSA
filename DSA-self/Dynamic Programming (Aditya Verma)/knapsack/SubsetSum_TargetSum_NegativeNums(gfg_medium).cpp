/**
 * Target Sum
 * -----------
 * Given an array of integers A[] of length N and an integer target.
 * You want to build an expression out of A by adding one of the symbols '+' and '-' before each integer in A and then concatenate all the integers.
 * For example, if arr = {2, 1}, you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".
 * Return the number of different expressions that can be built, which evaluates to target and return your answer with modulo 10^9+7.
 * 
 * Expected Time Complexity: O(N*sum), where sum refers to the range of sum possible.
 * Expected Auxiliary Space: O(N).
 * 
 * Constraints:
 * 1 ≤ N ≤ 100
 * -1000 ≤ A[i] ≤ 1000
 * 0 <= sum(A[i]) <= 10^4
 * -1000 <= target <= 1000
 */

// link: https://www.geeksforgeeks.org/problems/target-sum-1626326450/1
// article: https://www.geeksforgeeks.org/number-of-ways-to-calculate-a-target-number-using-only-array-elements/

// Solution 1: Bottom-up: O(n*target), O(target)
class Solution{
    public:
    // refer 1D DP approach in SubsetSum_DP(gfg_medium).cpp
    long long findTargetSumWays(int n, vector<int> &arr, int target) {
        int abssum = 0; // a[i] >=-1000, n<=100 => abssum<=1e5
        for(int v: arr)
            abssum += abs(v);
        int MOD = 1e9+7;
        int normalsum = accumulate(arr.begin(), arr.end(), 0);
        int s1 = (normalsum + target)/2;
        
        if(target > abssum || target < -abssum || (normalsum+target)&1)
            return 0;
        
        vector<int> dp(2*abssum + 1, 0);
        dp[0+abssum] = 1; // arr[i] = 0 will take care of rest
        
        for(int pos=1; pos<=n; pos++){
            for(int sum=abssum; sum>=arr[pos-1]; sum--){
                dp[sum + abssum] = (dp[sum-arr[pos-1]+abssum] + dp[sum+abssum])%MOD;
            }
        }
        
        return dp[s1 + abssum];
    }
};
// Solution 2: Bottom-up: O(n*target), O(n*target)
class Solution{
    public:
    long long findTargetSumWays(int n, vector<int> &arr, int target) {
        int abssum = 0; // a[i] >=-1000, n<=100 => abssum<=1e5
        for(int v: arr)
            abssum += abs(v);
        int MOD = 1e9+7;
        int normalsum = accumulate(arr.begin(), arr.end(), 0);
        int s1 = (normalsum + target)/2;
        
        if(target > abssum || target < -abssum || (normalsum+target)&1)
            return 0;
        
        vector<vector<int>> dp(n+1, vector<int>(2*abssum + 1, 0));
        dp[0][0+abssum] = 1; // arr[i] = 0 will take care of rest
        
        for(int pos=1; pos<=n; pos++){
            for(int sum=-abssum; sum<=abssum; sum++){
                if(arr[pos-1] <= sum){
                    dp[pos][sum + abssum] = (dp[pos-1][sum-arr[pos-1]+abssum]%MOD + dp[pos-1][sum+abssum]%MOD)%MOD;
                } else{
                    dp[pos][sum + abssum] = dp[pos-1][sum+abssum];
                }
            }
        }
        
        return (dp[n][s1 + abssum])%MOD;
    }
};

// old code: index adjustment in bottom-up approach
class Solution {
    const int MOD = 1e9 + 7;
  public:
    int findTargetSumWays(int n, vector<int> &A,int target) {
        int maxsum = 0, sum = 0;
        for(int i=0; i<n; i++){
            maxsum += abs(A[i]);
            sum += A[i];
        }
        int S1 = (sum + target) / 2;
        if((sum + target) % 2) // 1 or -1 is unacceptable
            return 0;
        if(target > maxsum || target < -maxsum){
            return 0;
        }
            
        //putting all 0 at the bottom
        int i=0, j=n-1;
        while(i<j){
            if(A[i] != 0)
                i++;
            else if(A[j] == 0)
                j--;
            else{
                swap(A[i], A[j]);
                i++;
                j--;
            }
        }
        //based on constraints in the problem
        //one constraint is wrong in problem - N E [1, 1000] (by hit and trial)
        int dp[2][4002];
        memset(dp, 0, sizeof(dp));
        int shiftindex = 2001;
        for(int i=0; i<2; i++)
            dp[i][2001] = 1; // 0 sum can be achieved in 1 way
        for(int pos=1; pos<=n; pos++){
            for(int ls=-1000; ls<=1000; ls++){
                if(pos%2)
                    dp[1][ls + shiftindex] = (dp[0][ls - A[pos-1] + shiftindex] + dp[0][ls + shiftindex]) % MOD;
                else
                    dp[0][ls + shiftindex] = (dp[1][ls - A[pos-1] + shiftindex] + dp[1][ls + shiftindex]) % MOD;
                    
            }
        }
        return dp[n%2][S1 + shiftindex];
    }
};