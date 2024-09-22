/**
 * Subset Sum Problem
 * ------------------
 * Given an array of non-negative integers, and a value sum, 
 * determine if there is a subset of the given set with sum equal to given sum. 
 * 
 * Expected Time Complexity: O(sum*n)
 * Expected Auxiliary Space: O(sum*n)
 * 
 * Constraints:
 * 1 <= n <= 100
 * 1<= arr[i] <= 100
 * 1<= sum <= 10^4
 */

// link: https://www.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1
// article: https://www.geeksforgeeks.org/subset-sum-problem-dp-25/

#include <bits/stdc++.h>
using namespace std;
// arr:[whatever], sum = 0 - true, as {} has sum = 0
bool checkSubsetSum(int arr[], int n, int sum, int index){
    if(index == n){
        return sum == 0;
    }
    return checkSubsetSum(arr, n, sum, index + 1) || checkSubsetSum(arr, n, sum - arr[index], index + 1);
}
int main(){
    int arr[] = {2,3,7,8,10};
    int sum = 11;
    if(checkSubsetSum(arr, sizeof(arr)/sizeof(int), sum, 0))
    cout<<"Present"<<endl;
    else
    cout<<"Not Present"<<endl;
}