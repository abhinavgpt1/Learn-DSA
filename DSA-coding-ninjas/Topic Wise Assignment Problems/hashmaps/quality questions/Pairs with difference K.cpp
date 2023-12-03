/*
Pairs with difference K
Send Feedback
You are given with an array of integers and an integer K. Write a program to find and print all pairs which have difference K.
Take difference as absolute.
Input Format :
Line 1 : Integer n, Size of array
Line 2 : Array elements (separated by space)
Line 3 : K
Output format :
Print pairs in different lines (pair elements separated by space). In a pair, smaller element should be printed first.
(Order of different pairs is not important)
Constraints :
0 <= n <= 10^4
Sample Input 1 :
4 
5 1 2 4
3
Sample Output 1 :
2 5
1 4
Sample Input 2 :
4
4 4 4 4 
0
Sample Output 2 :
4 4
4 4
4 4
4 4
4 4
4 4
*/
//question's demand changed
#include <unordered_map>
int getPairsWithDifferenceK(int *arr, int n, int k)
{
    // Write your code here
    unordered_map<int, int> ump;
    for (int i = 0; i < n; i++)
    {
        ump[arr[i]]++;
    }
    int ans = 0;
    for (auto x : ump)
    {

        if (ump.count(x.first + k))
        {
            if (k == 0)
                ans += x.second * (x.second - 1) / 2;
            else
                ans += x.second * ump[x.first + k];
        }
    }
    return ans;
}
//efficient
int getPairsWithDifferencek(int *arr, int n, int k)
{
    unordered_map<int, int > freq;

    int pairCount = 0;

    for (int i = 0; i < n; ++i)
    {
        int complement = arr[i] + k;
        pairCount += freq[complement];

        if (k != 0)
        {
            complement = arr[i] - k;
            pairCount += freq[complement];
        }

        ++freq[arr[i]];
    }

    return pairCount;
}
//suggestion for below code...search for arr[i]+k and print arr[i], arr[i]+k ump[arr[i]+k] times...not need to erase
//OR in beginning keep check for ump.count(arr[i])

//works implicitly....there's a (technique) mistake eg. 5 5 1 2 4
// at i =0 5is deleted at we get 2 5 printed twice
// at i =1 ump[5] is created again as 0, then at the end it is deleted...so we could add ump.count(arr[i]) in beginning only
//better approach -> make count of arr[i] as 0 instead of erasing it
#include <unordered_map>
void printPairs(int *input, int n, int k)
{
    // Write your code here
    unordered_map<int, int> um;
    for (int i = 0; i < n; i++)
    {
        um[input[i]]++;
    }
    for (int i = 0; i < n; i++)
    {
        if (k == 0)
        {
            int count = (um[input[i]] - 1) * um[input[i]] / 2;
            while (count--)
            {
                cout << input[i] << " " << input[i] << endl;
            }
            um.erase(input[i]);
            continue;
        }
        int a = input[i] + k;
        int b = input[i] - k;
        int curr = input[i];
        if (um.count(a) > 0)
        {
            int count = um[curr] * um[a];
            while (count--)
            {
                cout << input[i] << " " << input[i] + k << endl;
            }
        }
        if (um.count(b) > 0)
        {
            int count = um[curr] * um[b];
            while (count--)
            {
                cout << input[i] - k << " " << input[i] << endl;
            }
        }
        um.erase(input[i]);
    }
}

/*
// can't handle if k == 0
#include<unordered_map>
void printPairs(int *input, int n, int k) {
	// Write your code here
	unordered_map<int, int> um;
    for(int i = 0; i < n; i++){
        if(um.count(input[i] - k) > 0){
            int count = um[input[i] - k];
            while(count--){
                cout<<input[i] - k<<" "<<input[i]<<endl;
            }
        }
        else if(um.count(input[i] + k) > 0){
            int count = um[input[i] + k];
            while(count--){
                cout<<input[i]<<" "<<input[i] + k<<endl;
            }
        }
        um[input[i]]++;        
    }
}
*/
