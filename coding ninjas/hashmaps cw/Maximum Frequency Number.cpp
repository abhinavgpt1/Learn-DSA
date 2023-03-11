/*
Code : Maximum Frequency Number
Send Feedback
You are given an array of integers that contain numbers in random order. Write a program to find and return the number which occurs the maximum times in the given input.


*********If two or more elements contend for the maximum frequency, return the element which occurs in the array first.*************


Input Format:
The first line of input contains an integer, that denotes the value of the size of the array. Let us denote it with the symbol N.
The following line contains N space separated integers, that denote the value of the elements of the array.
Output Format :
The first and only line of output contains most frequent element in the given array.
Constraints:
0 <= N <= 10^8
Time Limit: 1 sec
Sample Input 1 :
13
2 12 2 11 12 2 1 2 2 11 12 2 6 
Sample Output 1 :
2
Sample Input 2 :
3
1 4 5
Sample Output 2 :
1
*/
//short
#include<unordered_map>

int highestFrequency(int arr[], int n) {
    // Write your code here
    if(n == 0)
        return -1;
    unordered_map<int, pair<int, int>> ump;
    int maxFreq = 0, ans = 0;
    for(int i = 0; i<n; i++){
        if(ump.count(arr[i]))
            ump[arr[i]].first++;
        else
        	ump[arr[i]] = {1, i};
        
        if(maxFreq < ump[arr[i]].first || (maxFreq == ump[arr[i]].first && ump[arr[i]].second < ump[ans].second))
        {
            maxFreq = ump[arr[i]].first;
            ans = arr[i];
        }
        
    }
    return ans;
}
//long
#include<unordered_map>

int highestFrequency(int arr[], int n) {
    // Write your code here
    if(n == 0)
        return -1;
    unordered_map<int, pair<int, int>> ump;
    int maxAns = 1;
    for(int i = 0; i<n; i++){
        if(ump.count(arr[i]))
            ump[arr[i]].first++;
        else
        	ump[arr[i]] = {1, i};
        
        maxAns = max(maxAns, ump[arr[i]].first);
    }
    int index = -1, ans = -1;
    for(auto x: ump){
        int el = x.first;
        int freq = x.second.first;
        int index_local = x.second.second;
        if(freq == maxAns){
            if(index == -1 || index > index_local){
                index = index_local;
                ans = el;
            }                
        }
    }
    return ans;
}

//smae question - just tc's were dump enough to not check max.freq of 2 no.s
/*
Code : Maximum Frequency Number
Send Feedback
You are given an array of integers that contain numbers in random order. Write a program to find and return the number which occurs the maximum times in the given input.
If two or more elements contend for the maximum frequency, return the element which occurs in the array first.
Input Format :
Line 1 : An Integer N i.e. size of array
Line 2 : N integers which are elements of the array, separated by spaces
Output Format :
Most frequent element
Constraints :
0 <= N <= 10^8
Sample Input 1 :
13
2 12 2 11 12 2 1 2 2 11 12 2 6 
Sample Output 1 :
2
Sample Input 2 :
3
1 4 5
Sample Output 2 :
1
*/

#include<unordered_map>	
int highestFrequency(int *input, int n){	 
	
/* Don't write main().
 	* the input array is already passed as function argument.
 	* Taking input and printing output is handled automatically.
 	*/
    int maxFreq=0;
    int maxNum;
 	unordered_map<int, int> um;
 	for(int i=0;i<n;i++){
        um[input[i]]++;//we don't have problem if a key value pair generates first time
        if(um[input[i]]>maxFreq){
            maxFreq=um[input[i]];
            maxNum=input[i];
        }
    }
 	return maxNum;
}

