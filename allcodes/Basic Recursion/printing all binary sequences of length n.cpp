#include<iostream>
using namespace std;
int binSeq(int start, int length, bool arr[])
{
	static int count;
	if(start==length)
	{
		for(int i=0;i<length;i++)
			cout<<arr[i];
		cout<<endl;
		count++;
		return count;
	}
	arr[start]=0;
	binSeq(start+1,length,arr);//nowhere here count can be incremented

	arr[start]=1;
	binSeq(start+1,length,arr);
}
int main()
{
	bool arr[4];
	cout<<endl<<binSeq(0,4,arr);
}