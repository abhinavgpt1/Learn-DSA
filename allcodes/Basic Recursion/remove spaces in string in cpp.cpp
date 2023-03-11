//remove spaces in string in c++
#include <iostream>
#include <string>
#include<queue>
using namespace std;
int main() 
{
	string s;
	queue<int> space_queue;
	getline(cin,s);
	
	for(int i=0;i<s.size();i++)
	{
	   if(s[i]==' ')
	        space_queue.push(i);
	   else
	   {
	       if(!space_queue.empty())
	       {
	           swap(s[space_queue.front()],s[i]);
	           space_queue.pop();
	           
	           space_queue.push(i);
	       }
	   }
	}
	cout<<s;
}
//approach 2

#include <iostream> 
using namespace std; 

char *removeSpaces(char *str) 
{ 
	int i = 0, space_index = 0; 
	while (str[i]) 
	{ 
		if (str[i] != ' ') 
		str[space_index++] = str[i]; 
		i++; 
	} 
	str[space_index] = '\0'; 
	return str; 
} 

// Driver program to test above function 
int main() 
{ 
	char str1[] = "gee k "; 
	cout << removeSpaces(str1) << endl; 

	char str2[] = " g e e k "; 
	cout << removeSpaces(str2); 
	return 0; 
}
