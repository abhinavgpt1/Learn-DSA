/*
Longest Consecutive Sequence
Send Feedback
You are given an array of unique integers that contain numbers in random order. Write a program to find the longest possible sequence of consecutive numbers using the numbers from given array.
You need to return the output array which contains consecutive elements. Order of elements in the output is not important.
Best solution takes O(n) time.
If two sequences are of equal length then return the sequence starting with the number whose occurrence is earlier in the array.
Input Format :
Line 1 : Integer n, Size of array
Line 2 : Array elements (separated by space)
Constraints :
0 <= n <= 10^6
Sample Input 1 :
13
2 12 9 16 10 5 3 20 25 11 1 8 6 
Sample Output 1 :
8 
9 
10 
11 
12
Sample Input 2 :
7
3 7 2 1 9 8 41
Sample Output 2 :
7
8
9
Explanation: Sequence should be of consecutive numbers. Here we have 2 sequences with same length i.e. [1, 2, 3] and [7, 8, 9], but output should be [7, 8, 9] because the starting point of [7, 8, 9] comes first in input array.
Sample Input 3 :
7
15 24 23 12 19 11 16
Sample Output 3 :
15 
16
*/

#include <vector>
#include<unordered_map>
using namespace std;

//O(n)
vector<int> longestConsecutiveIncreasingSequence(int *arr, int n) {
	
    //storing number: length of its sequence (in which number itself is at start)
    unordered_map<int, int> ump;
    for(int i=0; i<n; i++){
        ump[arr[i]] = 0;
    }

    int len_glob = 0, startValue;
    for(int i=0; i<n; i++){
        int len_local = 1, currElement = arr[i] + 1;
        
        while(ump.count(currElement)){
            if(ump[currElement] == 0)
            	len_local++;
            else
            {
                len_local += ump[currElement];
                break;//no need to process furthur as this currElement has already done it
            }
            
            // ump.erase(currElement); //irrelevant
            currElement++;
        }
        ump[arr[i]] = len_local;
        
        if(len_local > len_glob){
            len_glob = len_local;
            startValue = arr[i];
        }
    }
    
    //question's demand changed
    return {startValue, startValue + len_glob - 1};
        
}

//O(n)
vector<int> longestConsecutiveIncreasingSequence(int *arr, int n){

    unordered_map<int, bool> um;
    unordered_map<int, int> elementToIndex;
    for(int i = 0; i < n; i++){
        um[arr[i]] = true;
        elementToIndex[arr[i]] = i;
    }
    int finalStartValue;
    int maxLength = 0;
    for(int i = 0; i < n; i++){
        
        int curr = arr[i];
        int localLength = 1;
        int localStartVal = arr[i];
        if(um[curr] == true){
            
            //calculating sequence of which arr[i] / curr is part of
            //both in forward and backward direction
            int dup = curr + 1;
            while(um.count(dup) > 0){
                um[dup] = false;
            	localLength++;
                
            	dup++;
            }
            dup = curr - 1;
            while(um.count(dup) > 0){
                um[dup] = false;
                localLength++;
            	
            	dup--;
                localStartVal--;
            }
            
            //comparing lengths and assigning start
            if(localLength > maxLength){
                maxLength = localLength;
                finalStartValue = localStartVal;
            }
            else if(localLength == maxLength && elementToIndex[localStartVal] < elementToIndex[finalStartValue])//relevant because of the equal length criteria mentioned w.r.t. start of sequence
                finalStartValue = localStartVal;
        }
    }
    
    return {finalStartValue, finalStartValue + maxLength - 1};
}

//O(n^2)
#include<unordered_map>
#include<algorithm>
vector<int> longestConsecutiveIncreasingSequence(int *arr, int n) {
	
    unordered_map<int, int> ump;
    for(int i=0; i<n; i++){
        ump[arr[i]] = i;
    }
    int len_glob = 0, glob_index;
    for(int i=0; i<n; i++){
        int len_local = 0, el = arr[i];
        while(true){
            if(ump.count(el))
            {
                len_local++;
                el++;
            }
            else
                break;
        }
        if(len_local > len_glob){
            len_glob = len_local;
            glob_index = i;
        }
    }
    
    return {arr[glob_index], arr[glob_index]+ len_glob -1};
        
}