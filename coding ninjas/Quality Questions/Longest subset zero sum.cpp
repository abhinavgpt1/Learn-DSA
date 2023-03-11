/*
Longest subset zero sum
Send Feedback
Given an array consisting of positive and negative integers, find the length of the longest subarray whose sum is zero.
NOTE: You have to return the length of longest subarray .
Input Format :
Line 1 : Contains an integer N i.e. size of array

Line 2 : Contains N elements of the array, separated by spaces
Output Format
 Line 1 : Length of longest subarray 
Constraints:
0 <= N <= 10^8
Sample Input :
10 
 95 -97 -387 -435 -5 -70 897 127 23 284
Sample Output :
5
*/

#include<unordered_map>
int lengthOfLongestSubsetWithZeroSum(int* arr, int n) {
    
    unordered_map<int, int> ump;
    int localSum = 0, maxLength = 0;
    int k = 0;//sum demanded
    
    for(int i=0; i<n; i++){
            
        localSum += arr[i];
        if(localSum == k)
        {
            maxLength = i+1;
            continue;
        }
        if(ump.count(localSum - k))
        {
            maxLength = max(maxLength, i - ump[localSum]);
        }
        else//imp. : we need to track only the occurence when it appeared first
        	ump[localSum] = i;
    }
    return maxLength;
}

//ninja's soln.
#include <unordered_map>
int lengthOfLongestSubsetWithZeroSum(int *arr, int n)
{
    unordered_map<int, int> freq;
    for (int i = 1; i < n; i++)
    {
        arr[i] += arr[i - 1];
    }

    int m = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 0)
        {
            if (m < i + 1)
                m = i + 1;
        }
        else if (freq.count(arr[i]) > 0)
        {
            if (m < i - freq[arr[i]])
                m = i - freq[arr[i]];
        }
        else
            freq[arr[i]] = i;
    }
    return m;
}

//has couple of mistakes - 
// 2 -2 0 2 -2 - inclusion of zero in beginning/ end/ in between
// no handling if localSum = 0 -> (i - um[localSum]) won't work if subarray includes index 0.
// (i - um[localSum]) is useful in case we want to exclude elements from start
#include<unordered_map>
using namespace std;
int lengthOfLongestSubsetWithZeroSum(int* arr, int size){
  
  // Write your code here
	unordered_map<int, int> um;
    int localSum = 0;
    int maxLength = 0;
    um[0] = 0;
    for(int i = 0; i < size; i++){
        if(arr[0] == 0)
        {
            maxLength = 1;
            continue;
        }
        
        localSum += arr[i];
        if(um.count(localSum) > 0){
            if(i - um[localSum] > maxLength){
                maxLength = i - um[localSum];
            }
        }
        else
        	um[localSum] = i;
    }
    return maxLength;
}

