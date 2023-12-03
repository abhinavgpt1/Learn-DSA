/*
15. 3Sum
Medium

15746

1511

Add to List

Share
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

 

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Example 2:

Input: nums = []
Output: []
Example 3:

Input: nums = [0]
Output: []
 

Constraints:

0 <= nums.length <= 3000
-105 <= nums[i] <= 105
*/

//simple implmentation - 100%
// This involves traversing through the array. For every element
// arr[i], find a pair with sum “-arr[i]”.
// NOW the problem is to find a pair with sum "-arr[i]" , HENCE
// using pairs sum problem we can solve the questions

// 	Algorithm:

//         Run a nested loop with two loops, outer loop from 0 to n-1
// 		and the inner loop from i+1 to n-1
//         Check if the sum of outer loop element multiplied with -1 is
// 		present or not.

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> ans;

        for (int i = 0; i < n; i++)
        {
            if (i > 0)
            {
                if (nums[i] == nums[i - 1])
                    continue;
            }
            int low = i + 1, high = n - 1;
            while (low < high)
            { //PREREQUISTE :PAIR SUM PROBLEM
                if (nums[low] + nums[high] < (-1 * nums[i]))
                {
                    low++;
                }
                else if (nums[low] + nums[high] > -1 * nums[i])
                {
                    high--;
                }
                else
                {

                    ans.push_back({nums[i], nums[low], nums[high]});

                    while (low + 1 < n && nums[low] == nums[low + 1])
                        low++;

                    while (high - 1 >= 0 && nums[high] == nums[high - 1])
                        high--;

                    low++;
                    high--;
                }
            }
        }
        return ans;
    }
};

//my soln. - same algo, just more thought
class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        int n = nums.size();
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < n; i++)
        {

            if (i != 0 && nums[i] == nums[i - 1])
                continue;

            int st = i + 1, en = n - 1;
            int localSum = -nums[i]; //2

            while (st < en)
            {
                bool isDuplicate = false;
                while (st < en && nums[st] == nums[st + 1])
                {
                    st++;
                    isDuplicate = true;
                }
                if (isDuplicate && nums[st] * 2 == localSum)
                {
                    ans.push_back({nums[i], nums[st], nums[st]});
                    st++;
                }

                isDuplicate = false;
                while (en > st && nums[en] == nums[en - 1])
                {
                    en--;
                    isDuplicate = true;
                }
                if (isDuplicate && nums[en] * 2 == localSum)
                {
                    ans.push_back({nums[i], nums[en], nums[en]});
                    en--;
                }

                if (st >= en)
                    break;

                if (nums[st] + nums[en] == localSum)
                {
                    ans.push_back({nums[i], nums[st], nums[en]});
                    st++;
                    en--;
                }
                else if (nums[st] + nums[en] > localSum)
                    en--;
                else
                    st++;
            }
        }
        return ans;
    }
};