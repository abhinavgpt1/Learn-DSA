/*
1. Two Sum
Easy

Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

 

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]

 

Constraints:

    2 <= nums.length <= 104
    -109 <= nums[i] <= 109
    -109 <= target <= 109
    Only one valid answer exists.

*/
//O(n) solutions

//very good soln. - 100%
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> m;
        for(int i = 0;i<nums.size();i++){
            if(m.find(nums[i])==m.end()){
                m[target-nums[i]] = i;
            }
            else{
                return {m[nums[i]],i};
            }
        }
        return {};
    }
};

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<pair<int, int>> arr;
        
        int n = nums.size();
        for(int i=0; i<n; i++){
            arr.push_back({nums[i], i});
        }
        sort(arr.begin(), arr.end());
        
        int i = 0, j = n-1;
        while(i<j){
            if(arr[i].first + arr[j].first == target)
                return vector<int>{arr[i].second, arr[j].second};
            else if(arr[i].first + arr[j].first < target)
                i++;
            else 
                j--;
        }
        return vector<int>{0,n-1};
    }
};
