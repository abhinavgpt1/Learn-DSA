/**
 * Partitions with Given Difference
 * --------------------------------
 * Given an array arr, partition it into two subsets(possibly empty) such that their union is the original array.
 * Let the sum of the element of these two subsets be S1 and S2.
 * Given a difference d, count the number of partitions in which S1 is greater than or equal to S2
 * and the difference S1 and S2 is equal to d. since the answer may be large return it modulo 10^9 + 7.
 *
 * Expected Time Complexity: O( n*sum(arr))
 * Expected Space Complexity: O( sum(arr))
 * 
 * Constraint:
 * 1 <= n <= 500
 * 0 <= d  <= 25000
 * 0 <= arr[i] <= 50
 */

// link: https://www.geeksforgeeks.org/problems/partitions-with-given-difference/1
// article: https://www.geeksforgeeks.org/count-of-subsets-with-given-difference/

// Solution 1: Bottom-up: O(n*d), O(d)
// combination of Solution1@SubsetSum_DP(gfg_medium).cpp [dp 1D soln.] and SubsetSum_PerfectSum(gfg_medium).cpp [count when arr[i] = 0]
class Solution{
    public:
    int countPartitions(int n, int d, vector<int> &arr) {
        const int MOD = 1e9 + 7;
        int sum = accumulate(arr.begin(), arr.end(), 0);
        int s1 = (sum + d)/2; // s2 = sum - s1
        if(d > sum || (sum+d)&1)
            return 0;

        vector<int> dp(sum + 1, 0); // dp[i] = subset count when sum=i
        dp[0] = 1;
        
        for(int i=0; i<n; i++){
            for(int j=s1; j>=arr[i]; j--){ // this covers arr[i]=0. arr[i]->s1 will be unbounded knapsack scenario
                dp[j] = (dp[j] + dp[j - arr[i]]) % MOD;
            }
        }
        return dp[s1];
    }
};

// Solution 2: Bottom-up: O(n*d), O(n*d)
class Solution
{
    public:
    int countPartitions(int n, int d, vector<int> &arr) {
        // refer: Solution2: https://www.geeksforgeeks.org/problems/perfect-sum-problem5633/1
        // NOTE: arr[i] >= 0
        // d E [0, S] => so no S/=2
        const int MOD = 1e9 + 7;
        int S = accumulate(arr.begin(), arr.end(), 0);
        if((S + d) % 2 || d > S) // if S + d is odd => S1 is floating number, which is not possible as all elements are integers
            return 0;
        int S1 = (S + d) / 2;
        sort(arr.begin(), arr.end(), greater<int>()); // applied learning from https://www.geeksforgeeks.org/count-of-subsets-with-sum-equal-to-x/#:~:text=So%20just%20sort%20the%20array%20in%20descending%20order%20to%20achieve%20the%20correct%20output.
        vector<vector<int>> dp(n + 1, vector<int>(S + 1, 0));
        for(int i=0; i<=n; i++)
            dp[i][0] = 1;
        
        for(int pos=1; pos<=n; pos++){
            for(int ls=0; ls<=S; ls++){ //it is important to run from 0 eg. S1=0 and arr={0,0,0}
                if(arr[pos - 1] <= ls)
                    dp[pos][ls] = (dp[pos - 1][ls - arr[pos - 1]] + dp[pos - 1][ls]) % MOD;
                else
                    dp[pos][ls] = dp[pos - 1][ls];
            }
        }
        return dp[n][S1];
    }
}