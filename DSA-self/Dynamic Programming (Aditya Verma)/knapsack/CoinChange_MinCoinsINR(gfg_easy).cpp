/**
 * Minimum number of Coins
 * -----------------------
 * Given an infinite supply of each denomination of
 * Indian currency { 1, 2, 5, 10, 20, 50, 100, 200, 500, 2000 } and a target value N.
 * Find the minimum number of coins and/or notes needed to make the change for Rs N.
 * You must return the list containing the value of coins required.
 *
 * Expected Time Complexity: O(N)
 * Expected Auxiliary Space: O(N)
 * 
 * Constraints:
 * 1 ≤ N ≤ 10^6
 */
// link: https://www.geeksforgeeks.org/problems/-minimum-number-of-coins4426/1
// article: https://www.geeksforgeeks.org/greedy-algorithm-to-find-minimum-number-of-coins/

/**
 * @brief Note in editorial
 * Note: The above approach may not work for all denominations. 
 * For example, it doesn't work for denominations {9, 6, 5, 1} and V = 11. 
 * The above approach would print 9, 1 and 1. But we can use 2 denominations 5 and 6. 
 * For general input, below dynamic programming approach can be used: 
 * - https://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/
 * - CoinChange_MinCoinCount(leetcode_medium).cpp
 */

// Solution: Greedy-approach: O(sum), O(sum)
class Solution{
public:
    vector<int> minPartition(int sum)
    {
        // its because of the denominations that a greedy approach can be applied
        // for general denominations, it would have become unbounded knapsack

        vector<int> den = {2000, 500, 200, 100, 50, 20, 10, 5, 2, 1}; 
        // S(sum) = O(sum) -> O(1) if we use if-else ladder
        // https://www.geeksforgeeks.org/greedy-algorithm-to-find-minimum-number-of-coins/
        
        vector<int> notes; int i = 0;
        while(sum!= 0 && i<den.size()){
            int notecnt = sum / den[i];
            for(int x=0; x<notecnt; x++)
                notes.push_back(den[i]);
            sum = sum%den[i];
            i++;
        }
        return notes;
    }
};

// old soln
class Solution
{
public:
    vector<int> minPartition(int sum)
    {
        // its because of the denominations that a greedy approach can be applied
        // for general denominations, it would have become unbounded knapsack
        vector<int> den = {1, 2, 5, 10, 20, 50, 100, 200, 500, 2000};
        int n = den.size();
        vector<int> ans;
        while (sum > 0)
        {
            int notes = sum / den[n - 1]; // or coins
            sum = sum % den[n - 1];
            if (notes > 0)
            {
                for (int i = 0; i < notes; i++)
                    ans.push_back(den[n - 1]);
            }
            n--;
        }
        return ans;
    }
};