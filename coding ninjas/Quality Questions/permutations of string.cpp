#include<iostream>
#include<string>
using namespace std;
int permStr(int fixed,int length, string s)//here length parameter can be avoided since we have s.length()
{
	static int count;//default 0 initialized
	if(fixed==length)
	{
		cout<<s<<endl;
		return count++;
	}
	int j=fixed;
	for( ;j<length;j++)
	{ 
		swap(s[fixed],s[j]);
		permStr(fixed+1,length,s);//here no increment of count can be done
		swap(s[fixed],s[j]);	 //necessary, since s[fixed] and s[j] were swapped once//although answer would come as a total same 
	}
	return count;
}
int main()
{
	string s="abcd";
	cout<<endl<<"COUNT:"<<permStr(0,4,s);
}


#include <string>
using namespace std;

int returnPermutations(string input, int fixed, string output[]){
    if(fixed==input.length())
    {
        output[0]="";
        return 1;
    }
    int size=returnPermutations(input, fixed+1, output);
    int top=size;

    for(int outer=0;outer<size;outer++)
    {
        string temp=output[outer];
        output[outer]=input[fixed]+output[outer];
        // cout<<"*outer*"<<output[outer]<<"*"<<endl;
        
        for(int inner=1;inner<=temp.length();inner++)
        {
            output[top]=temp.substr(0,inner)+input[fixed]+temp.substr(inner);
            // cout<<"*"<<output[top]<<"*"<<endl;
            top++;   
        }        
    }
    return top;
}
int returnPermutations(string input, string output[])
{
    return returnPermutations(input, 0, output);
}