/*
Rotate Array(clockwise, anti by k times)
METHOD 3 (A Juggling Algorithm)
This is an extension of method 2. Instead of moving one by one, divide the array in different sets
where number of sets is equal to GCD of n and d and move the elements within sets.
If GCD is 1 as is for the above example array (n = 7 and d =2), then elements will be moved within one set only, we just start with temp = arr[0] and keep moving arr[I+d] to arr[I] and finally store temp at the right place.

Here is an example for n =12 and d = 3. GCD is 3 and

Let arr[] be {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}

a) Elements are first moved in first set – (See below 
   diagram for this movement)

ArrayRotation

          arr[] after this step --> {4 2 3 7 5 6 10 8 9 1 11 12}

b)    Then in second set.
          arr[] after this step --> {4 5 3 7 8 6 10 11 9 1 2 12}

c)    Finally in third set.
          arr[] after this step --> {4 5 6 7 8 9 10 11 12 1 2 3}
*/
//we run outer loop gcd times, because gcd gives us distinct/disjoint sets, shuffling in which goes until k==i comes
//{1,2,3,4,5,6} , d=2 -> {1,3,5} & {2,4,6} are the sets, in which shuffling occurs as many times you want(refer inner loop(while));
#include<iostream>
#include<algorithm>
using namespace std;
void leftRotate(int arr[], int n, int d){
    int gcd = __gcd(n,d);
    for(int i = 0; i < gcd; i++){
        
        int j = i;
        int temp = arr[j];
        while(1){
            
            // int k = j - d;
            int k = j + d;    
            
            // if(k<0)
            // k=n+k;
            if(k>=n)
            k=k-n;
            
            if(k==i)
            break;
            
            arr[j] = arr[k];
            j=k;
        }
        arr[j] = temp;
    }
}
int main()
{
	//code
	int z;
	cin>>z;
	while(z--){
	    int n,d;
	    cin>>n>>d;
	    int arr[n];
	    for(int i=0;i<n;i++)
	    cin>>arr[i];
	    
	    leftRotate(arr,n,d);
	    for(int i=0;i<n;i++)
	    cout<<arr[i]<<" ";
	    cout<<endl;
	    
	}
	return 0;
}