/**
 * Floor in a Sorted Array
 * -----------------------
 * Given a sorted array arr[] of size N without duplicates, and given a value x. 
 * Floor of x is defined as the largest element K in arr[] such that K is smaller than or equal to x. 
 * Find the index of K(0-based indexing).
 * 
 * Expected Time Complexity: O(log N).
 * Expected Auxiliary Space: O(1).
 * 
 * Constraints:
 * 1 ≤ N ≤ 107
 * 1 ≤ arr[i] ≤ 1018
 * 0 ≤ X ≤ arr[n-1]
 */
class Solution {
  public:
    int helper(int arr[], int startIndex, int endIndex, int element){
        if(startIndex > endIndex)
            return -1;
        int mid = startIndex + (endIndex - startIndex) / 2;
        if(arr[mid] == element)
            return mid;
        else if(element < arr[mid])
            return helper(arr, startIndex, mid - 1, element);
        else
            return helper(arr, mid + 1, endIndex, element);
    }
    int binarysearch(int arr[], int n, int k) {
        return helper(arr, 0, n-1, k);
    }
};

// https://www.geeksforgeeks.org/floor-in-a-sorted-array/