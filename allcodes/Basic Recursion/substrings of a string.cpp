#include<iostream>
using namespace std;
void substring1(int fixed,int length,string s)//here length parameter can be avoided since we have s.length()
{
	if(fixed==length)
		return;
	for(int i=1;i<=length-fixed;i++)
	{
		cout<<s.substr(fixed,i)<<endl;
	}
	substring1(fixed+1,length,s);
}
int substring2(int fixed,int length,string s)
{
	if(fixed==length)
		return 0;
	int count=substring2(fixed+1,length,s);
	for(int i=1;i<=length-fixed;i++)
	{
		cout<<s.substr(fixed,i)<<endl;
		count++;
	}
	return count;

}
int main()
{
	string s="abcd";
	cout<<"Method1"<<endl;
	substring1(0,4,s);
	cout<<"Method2"<<endl;
	cout<<"NO. of substrings =n*(n+1)/2  :"<<substring2(0,4,s);

}