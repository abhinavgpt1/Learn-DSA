/*
Padovan Sequence
A Padovan Sequence is a sequence which is represented by the following recurrence
P(N) = P(N-2) + P(N-3)
P(0) = P(1) = P(2) = 1
Now given a number N your task is to find the Nth number in this sequence.

Note: Since the output could be very long take mod 1000000007

Input:
The first line of input contains an integer T denoting the number of test cases. Then T test cases follow. Each line contains an integer N.

Output:
For each test case, in a new line, print the nth no of the Padovan sequence.

Constraints:
1<=T<=100
1<=N<=100

Example:
Input:
2
12
4
Output:
21
2
*/
#include<iostream>
#include<cstring>
using namespace std;
long long int t[101];
long long int padovan(int n){
    
    if(n==0 || n==1 || n==2)
        return 1;
    
    if(t[n]!=0)
        return t[n];
    
    long long int ans=t[n]=(padovan(n-2)+padovan(n-3))%1000000007;
    return ans;
    
    
}
int main()
{
	//code
	memset(t,0,sizeof(t));
	t[0]=t[1]=t[2]=1;
	int z;
	cin>>z;
	while(z--){
	    int n;
	    cin>>n;
	    cout<<padovan(n)<<endl;
	}
	return 0;
}