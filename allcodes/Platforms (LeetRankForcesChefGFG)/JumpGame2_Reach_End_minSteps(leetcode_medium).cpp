/*
45. Jump Game II
Medium

7654

286

Add to List

Share
Given an array of non-negative integers nums, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

You can assume that you can always reach the last index.

 

Example 1:

Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: nums = [2,3,0,1,4]
Output: 2
 

Constraints:

1 <= nums.length <= 104
0 <= nums[i] <= 1000
*/
// 100%
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return 0;
        int currReach = nums[0], minSteps = 1, maxReach = nums[0];
        
        for(int i = 1 ; i < n ; i++) {
            if(currReach >= n-1) return minSteps;
            int potentialReach = i + nums[i];
            if(potentialReach > maxReach) {
                maxReach = potentialReach;
            }
            
            if(i == currReach) {
                currReach = maxReach;
                minSteps++;
            }
        }
        
        return minSteps;
    }
};

// mysoln.
class Solution {
    public:
        int jump(vector<int>& nums) {
            
            if(nums.size() == 1)
                return 0;
            int rangeIndex = nums[0], i = 0, jumps = 0;
            while(i < nums.size()){
                
                if(rangeIndex >= nums.size() - 1){
                    jumps++;
                    break;
                }
                    
                int maxRange = INT_MIN;
                
                while(i<=rangeIndex){
                    maxRange = max(maxRange, i + nums[i]);
                    i++;
                }
                
                jumps++;
                rangeIndex = maxRange;
                
            }
            
            return jumps;
        }
    };