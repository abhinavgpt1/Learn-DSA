/**
 * Search insert position of K in a sorted array
 * ----------------------------------------------
 * Given a sorted array Arr[](0-index based) consisting of N distinct integers and an integer k, the task is to find the index of k, if its present in the array Arr[]. Otherwise, find the index where k must be inserted to keep the array sorted.
 * 
 * Expected Time Complexity: O(logN)
 * Expected Auxiliary Space: O(1)
 * 
 * 
 * Constraints:
 * 1 ≤ N ≤ 104
 * -103 ≤ Arr[i] ≤ 103
 * -103 ≤ k ≤ 103
 */

class Solution{
    public:
    int searchInsertK(vector<int>Arr, int N, int k)
    {
        // eqv. to find greatest element smaller than k, such that k can be inserted after that = floor
        int high = N - 1, low = 0;
        while(high >= low) {
            int mid = low + (high - low)/2;
            if(Arr[mid] == k)
                return mid;
            else if(k < Arr[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        return high + 1;
    }
};

// https://www.geeksforgeeks.org/search-insert-position-of-k-in-a-sorted-array/