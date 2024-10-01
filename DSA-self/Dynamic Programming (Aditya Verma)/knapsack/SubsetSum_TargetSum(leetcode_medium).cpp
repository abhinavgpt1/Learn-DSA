/**
 * 494. Target Sum
 * -----------
 * You are given an integer array nums and an integer target.
 * You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.
 * For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".
 * Return the number of different expressions that you can build, which evaluates to target.
 * 
 * Constraints:
 * 1 <= nums.length <= 20
 * 0 <= nums[i] <= 1000
 * 0 <= sum(nums[i]) <= 1000
 * -1000 <= target <= 1000
 */

// link: https://leetcode.com/problems/target-sum/
// my article: https://leetcode.com/problems/target-sum/solutions/5821997/100-runtime-69-space/

/* 
    Note: here nums[i]>=0, it gets tough when nums[i]<0. 
    Refer: SubsetSum_TargetSum_NegativeNums(gfg_medium).cpp 

    No need to adjust index
    - article: https://www.geeksforgeeks.org/number-of-ways-to-calculate-a-target-number-using-only-array-elements/
    - article: https://leetcode.com/problems/target-sum/editorial/
*/

// Solution: Bottom-up: O(n*target), O(target)
class Solution {
public:
    int findTargetSumWays(vector<int> &nums, int target) {
        int n = nums.size(), sum = accumulate(nums.begin(), nums.end(), 0);
        target = abs(target); // {1,1,1,1,1}, -3 can be achieved if we know the ans for target=3
        if(target > sum || (sum + target)&1) //nums[i]>=0
            return 0;
        int s1 = (sum + target)/2;
        vector<int> dp(s1 + 1, 0);
        dp[0] = 1; //subject to change
        for(int i=0; i<n; i++){
            for(int j=s1; j>=nums[i]; j--){ //nums[i] = 0 is handled
                dp[j] += dp[j - nums[i]];
            }
        }
        return dp[s1];
    }
};