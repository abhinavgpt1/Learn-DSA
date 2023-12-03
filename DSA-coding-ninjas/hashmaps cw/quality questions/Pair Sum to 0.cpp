/*
Code : Pair Sum to 0
Send Feedback
Given a random integer array A of size N. Find and print the pair of elements in the array which sum to 0.
Array A can contain duplicate elements.
While printing a pair, print the smaller element first.
That is, if a valid pair is (6, -6) print "-6 6". There is no constraint that out of 5 pairs which have to be printed in 1st line. You can print pairs in any order, just be careful about the order of elements in a pair.
Input format :
Line 1 : Integer N (Array size)
Line 2 : Array elements (separated by space)
Output format :
Line 1 : Pair 1 elements (separated by space)
Line 2 : Pair 2 elements (separated by space)
Line 3 : and so on
Constraints :
0 <= N <= 10^4
Sample Input:
5
2 1 -2 2 3
Sample Output :
-2 2
-2 2
*/

#include<unordered_map>
int pairSum(int *arr, int n) {
	// Write your code here
    unordered_map<int,int> ump;
    int ans = 0;
    for(int i=0; i<n; i++){
        ump[arr[i]]++;
        if(ump.count(-arr[i]))
            ans+=ump[-arr[i]];
    }
    int n0 = ump[0];
    ans-=n0;
    
    return ans;
}

// easier than above
#include<unordered_map>
int pairSum(int *arr, int n) {

    unordered_map<int,int> ump;
    int ans = 0;
    for(int i=0; i<n; i++){
        
        if(ump.count(-arr[i]))
            ans+=ump[-arr[i]];
            
        ump[arr[i]]++;
    }
    return ans;
}

//method 2
void pairSum(int *input, int n) 
{
    //Write your code here	 
    unordered_map<int,int> um;
    
    for(int i=0;i<n;i++){
        um[input[i]]++;
    }
    
    for(int i=0;i<n;i++){
        
        // works implictly because um[input[i]] will be 0 next time -> 1. do check um.count(input[i]) && um.count(-input[i]) 2. erase both input[i] and -input[i]
        if(um.count(-input[i])){
            int count;
            if(input[i] == 0){
                count = (um[input[i]] - 1) * um[input[i]] / 2;
            }
            else
            	count = um[-input[i]] * um[input[i]];
            
            while(count--)
            	cout<<-abs(input[i])<<" "<<abs(input[i])<<endl;          
            um.erase(input[i]);
        }
    }
}
//method 3: tactical: maintaining frequency and inserting at same time
// fails at input[i] = 0
void pairSum(int *input, int n) 
{
    //Write your code here	 
    unordered_map<int,int> um;
    
    for(int i=0;i<n;i++){
        
        if(um.count(-input[i])){
            int m = um[-input[i]];
            
            for(int t = 1 ; t <= m; t++)
            	cout<<-abs(input[i])<<" "<<abs(input[i])<<endl;          
        }
        um[input[i]]++;
    }
}
