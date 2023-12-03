/*
Given an integer N, count and return the number of zeros that are present in the given integer using recursion.
0 <= N <= 10^9
*/
//doesn't work for n=0
int countZeros(int n) {
    // Write your code here
    if(n==0)
        return 0;
    int count = 0;
    int r=n%10;
    if(r==0)
        count++;
	return count+countZeros(n/10);
}

//efficient
int countZeros(int n) {
    // Write your code here
    int count = 0;
    int r=n%10;
    if(r==0)
        count++;
    if(n/10==0)
        return count;//return 0 works fine if n!=0 (since most signinficant digit can't be zero(if n!=0))
    //count is written since 0<=n<=10^9
	return count+countZeros(n/10);
}

