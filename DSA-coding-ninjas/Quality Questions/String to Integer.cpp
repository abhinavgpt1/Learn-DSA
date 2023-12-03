/*String to Integer
Send Feedback
Write a recursive function to convert a given string into the number it represents. That is input will be a numeric string that contains only numbers, you need to convert the string into corresponding integer and return the answer.
Major thing to notice is the behavior of pow() funtion
*/
#include <iostream> 
#include <string>
#include <cmath>  
using namespace std; 
int func(string str){
	if(str.length()==0)
		return -1;
	if(str.length()==1)
		return str[0]-'0';

	int first=str[0]-'0';
	int num=func(str.substr(1,str.length()-1));

	return first*(ceil(pow(10,str.length()-1)))+num;
}
int main() 
{ 
	string str="12353534";
	cout<<func(str);
	return 0; 
} 
