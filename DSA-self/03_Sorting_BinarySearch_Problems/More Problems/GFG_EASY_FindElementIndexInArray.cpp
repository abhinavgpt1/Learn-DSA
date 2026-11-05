/**
 * Find element index in array using Binary Search 
 * - using recursion 
 * - using while loop
 * 
 */
// Sol1
class Solution {
  public:
    int binarysearch(int arr[], int n, int k) {
        int high = n - 1, low = 0;
        while(high >= low) {
            int mid = low + (high - low)/2;
            if(arr[mid] == k)
                return mid;
            else if(k < arr[mid]){
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return -1;
    }
};
// Sol2
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