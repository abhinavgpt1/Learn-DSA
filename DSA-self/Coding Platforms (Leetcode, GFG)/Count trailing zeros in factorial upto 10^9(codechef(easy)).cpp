/*
Count trailing zeros in factorial upto INT_MAX
For example, they defined the function Z. For any positive integer N, Z(N) is the number of zeros at the end of the decimal form of number N!. They noticed that this function never decreases. If we have two numbers N1<N2, then Z(N1) <= Z(N2). It is because we can never "lose" any trailing zero by multiplying by any positive number. We can only get new and new zeros. The function Z is very interesting, so we need a computer program that can determine its value efficiently.

Input
There is a single positive integer T on the first line of input (equal to about 100000). It stands for the number of numbers to follow. Then there are T lines, each containing exactly one positive integer number N, 1 <= N <= 1000000000.

Output
For every number N, output a single line containing the single non-negative integer Z(N).

Example
Sample Input:

6
3
60
100
1024
23456
8735373
Sample Output:

0
14
24
253
5861
2183837
*/
#include <iostream>
using namespace std;
int count_zero(int n){
    int count_2 = 0;
	int count_5 = 0;

	int count = 0;
	for(int i=2;i<=n;i++)
	{
		int cpy_i = i;
        if(cpy_i % 2 != 0 && cpy_i % 5 != 0)
            continue;


        while(cpy_i % 2 == 0 || cpy_i % 5 == 0){
                if(cpy_i % 2 == 0){
                    cpy_i = cpy_i / 2;
                    count_2++;
                }
                if(cpy_i % 5 == 0){
                    cpy_i = cpy_i / 5;
                    count_5++;
                }

        }

        if(count_2 !=0 && count_5 !=0){

        	if(count_2 > count_5){
        		count += count_5;
        		count_2 = count_2 - count_5;
        		count_5 = 0;
        	}
        	else{
        		count += count_2;
        		count_5 = count_5 - count_2;
        		count_2 = 0;
        	}

        }
	}
    return count;
}
int count_zero_very_efficient(int n)
{
    //in 5 running numbers, eg {1,2,3,4,5}, {11,12,13,14,15} there exist only one 10 i.e. one number of zero
    //unless we encounter a number i which has 2 or more 5, eg. 5*5 = 25
        int res = n/5;
        int d = 5*5;
        while(n>=d){
            res+=n/d;
            d*=5;
        }
    return res;
}

int main() {

	int t;
	cin>>t;
	while(t--){

	int n;
	cin>>n;

    cout<<"Answers:";
	cout<<count_zero(n);//my way, takes too much time for n = 1000000000 , approx 8 sec

	cout<<","<<count_zero_very_efficient(n)<<endl;

	}
	return 0;
}
