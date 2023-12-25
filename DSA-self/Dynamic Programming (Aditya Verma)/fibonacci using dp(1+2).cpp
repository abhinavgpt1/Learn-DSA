//using memoization
//find nth fibonacci
#include<iostream>
using namespace std;
int t[85];//n was constraint with n<=84
int fib(int n){
    if(n==1 || n==2)
    {
        return 1;
    }
    if(t[n]!=0)
        return t[n];
    
    int ans=t[n]=(fib(n-1)+fib(n-2));
    return ans;
}
int main()
{
	//code
	memset(t,0,sizeof(t));
	t[1]=1;
	t[2]=1;
	int t;
	cin>>t
	while(t--){
	    int n;
	    cin>>n;
	    fib(n);
	}
	return 0;
}



//now printing till n
#include<iostream>
#include<cstring>
using namespace std;
long int t[85];
long int fib(int n){
    if(n==1 || n==2)
    {
        return 1;
    }
    if(t[n]!=0)
        return t[n];
    
    long int ans=t[n]=(fib(n-1)+fib(n-2));
    return ans;
}
int main()
{
	//code
	memset(t,0,sizeof(t));
	t[1]=1;
	t[2]=1;
	int t;
	cin>>t;
	while(t--){
	    int n;
	    cin>>n;
	    for(int i=1;i<=n;i++)
	        cout<<fib(i)<<" ";
	    cout<<endl;
	}
	return 0;
}

//using top-down approach
#include<iostream>
#include<cstring>//for memset
using namespace std;
long int t[85];

int main()
{
	//code
	memset(t,0,sizeof(t));
	t[1]=1;
	t[2]=1;
	for(int i=3;i<85;i++){
	    t[i]=t[i-1]+t[i-2];
	}
	int z;
	cin>>z;
	while(z--){
	    int n;
	    cin>>n;
	    for(int i=1;i<=n;i++)
	        cout<<t[i]<<" ";
	    cout<<endl;
	}
	return 0;
}