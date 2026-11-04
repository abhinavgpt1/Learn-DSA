#include <iostream>
using namespace std;

int subs(string input, string output[]) {
	if (input.empty()) {
		output[0] = "";
		return 1;
	}

	string smallString = input.substr(1);
	int smallOutputSize = subs(smallString, output);
	for (int i = 0; i < smallOutputSize; i++) {
		output[i + smallOutputSize] = input[0] + output[i];
	}
	return 2 * smallOutputSize;
}

int main() {
	string input;
	cin >> input;
	string* output = new string[1000];
	int count = subs(input, output);
	for (int i = 0; i < count; i++) {
		cout << output[i] << endl;
	}
}
#include <iostream>
using namespace std;
int subsequence(string input, string ouput[])
{
	if(input.size()==0)
	{
		ouput[0]="";
		return 1;
	}
	int n=subsequence(input.substr(1),output);
	for(int i=0;i<n;i++)
	{
		output[n+i]=input[0]+output[i];
	}
	return 2*n;
}
int main() {
	string input="abc";
	string *output=new string[pow(2,input.length())];
	int n=subsequence(input,ouput);
	for(int i=0;i<n;i++)
		cout<<output[i]<<endl;
}

