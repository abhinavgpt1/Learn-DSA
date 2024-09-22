/**
 * Minimum sum partition
 * ---------------------
 * Given an array arr of size n containing non-negative integers, 
 * the task is to divide it into two sets S1 and S2 
 * such that the absolute difference between their sums is minimum and find the minimum difference
 * 
 * Expected Time Complexity: O(N*|sum of array elements|)
 * Expected Auxiliary Space: O(N*|sum of array elements|)
 * 
 * 
 * Constraints:
 * 1 ≤ N*|sum of array elements| ≤ 10^6
 * 0 < arr[i] <= 10^5
 */

// link: https://www.geeksforgeeks.org/problems/minimum-sum-partition3317/1
// article: https://www.geeksforgeeks.org/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum/

#include <bits/stdc++.h>
using namespace std;
int minSubsetSumDiff(int arr[], int n, int localSum, int sumArr){
    if(n == 0)
    return abs(sumArr - 2*localSum);

    return min(minSubsetSumDiff(arr, n-1, localSum, sumArr), minSubsetSumDiff(arr, n-1, localSum + arr[n-1], sumArr));
}
int main(){
    int arr[] = {2,3,7,8,11};
    int sumArr = 0;
    sumArr = accumulate(arr, arr+sizeof(arr)/sizeof(int),0);
    cout<<minSubsetSumDiff(arr, sizeof(arr)/sizeof(int), 0, sumArr)<<endl;
}