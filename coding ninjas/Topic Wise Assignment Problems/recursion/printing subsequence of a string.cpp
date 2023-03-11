#include <iostream>
using namespace std;

void printSubseq(string input, string output)
{
	if(input.empty())
	{
		cout<<output<<endl;
		return;
	}
	printSubseq(input.substr(1),output);
	printSubseq(input.substr(1),output+input[0]);
}

void printSubsequence1(string input, string output)
{
	if(input.empty())
	{
		cout<<output<<endl;
		return;
	}
	output=output+input[0];//since it is inserted at last so, it'll be popped from back
	printSubsequence1(input.substr(1),output);
	// output.pop_back();//hence this works fine
	printSubsequence1(input.substr(1),output);
}
void printSubsequence2(string input, string output)
{
	if(input.empty())
	{
		cout<<output<<endl;
		return;
	}
	output=input[0]+output;
	printSubsequence2(input.substr(1),output);
	output=output.substr(1);
	printSubsequence2(input.substr(1),output);
}
int main() {
	string input="abc";
	string output;
	// printSubsequence2(input,output);
	// printSubsequence2(input,output);
	printSubseq(input,output);

}
