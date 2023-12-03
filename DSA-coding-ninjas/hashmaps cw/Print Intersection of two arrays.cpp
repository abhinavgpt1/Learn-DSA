/*
Code : Print Intersection of two arrays
Send Feedback
Given two random integer arrays, print their intersection. That is, print all the elements that are present in both the given arrays.
Input arrays can contain duplicate elements.
Note : Order of elements are not important
Input format :
Line 1 : Integer N, Array 1 Size
Line 2 : Array 1 elements (separated by space)
Line 3 : Integer M, Array 2 Size
Line 4 : Array 2 elements (separated by space)
Output format :
Print intersection elements in different lines
Constraints :
0 <= M, N <= 5 * 10^7
Sample Input 1 :
6
2 6 8 5 4 3
4
2 3 4 7 
Sample Output 1 :
2 
4 
3
Sample Input 2 :
4
2 6 1 2
5
1 2 3 4 2
Sample Output 2 :
2 
2
1
*/

//this answer is of renewed question...here we were supposed to print elements in sorted order too
//soln. new
#include<unordered_map>
void intersection(int *arr1, int *arr2, int n, int m) 
{
    //Write your code here
    unordered_map<int, int> ump;
    for(int i=0; i<n; i++){
        ump[arr1[i]]++;
    }
    
    sort(arr2, arr2+m);
    for(int i=0; i<m; i++){
        if(ump.count(arr2[i]) && ump[arr2[i]] != 0){
            cout<<arr2[i]<<" ";
            ump[arr2[i]]--;
        }
    }
    cout<<endl;
}
//soln. old
#include<unordered_map>
#include<algorithm>
void intersection(int *arr1, int *arr2, int n, int m) 
{
    //Write your code here
    sort(arr1, arr1 + n);
    unordered_map<int, int> um;
    for(int i = 0 ; i < m; i++){
        um[arr2[i]]++;
    }
    for(int i = 0 ; i < n; i++){
        if(um.count(arr1[i]) > 0){
            
            if(um[arr1[i]])
            {
                cout<<arr1[i]<<" ";
                um[arr1[i]]--;
            }
        }
    }
}
/*
// input1 - first array
// input2 - second array
// size1 - size of first array
// size2 - size of second array
#include<unordered_map>
void intersection(int input1[], int input2[], int size1, int size2) {
    
    unordered_map<int,int> um;
    for(int i=0;i<size1;i++){
        um[input1[i]]++;
    }

    for(int i=0;i<size2;i++){
        if(um.empty())
            break;
        
        if(um.count(input2[i])>0){
            if(um[input2[i]] != 0){
                cout<<input2[i]<<endl;                
                um[input2[i]]--;
            }
            else
                um.erase(input2[i]);
        }
    }
}

*/