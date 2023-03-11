#include <iostream>
using namespace std;

//Solution 2: alternate solution
bool solve(char input[], int start, int end)
{
    if(start>=end)
        return true;
    if(input[start]==input[end])
    {
        return solve(input,start+1,end-1);
    }
    return false;
}
bool checkPalindrome2(char input[]) 
{
    int length=0;
    for(int i=0;input[i]!='\0';i++)
        length++;
    return solve(input,0,length-1);

}


//Solution 1: alters the input
bool checkPalindrome(char input[]) 
{
    int length=0;
    for(int i=0;input[i]!='\0';i++)
        length++;
    if(length==0)
        return true;
    
    if(input[0]==input[length-1])
    {
        input[length-1]='\0';
        return checkPalindrome(input+1);
    }
    return false;

}
int main() {
    char input[50];
    cin >> input;
    
    if(checkPalindrome(input)) {
        cout << "true" << endl;
    }
    else {
        cout << "false" << endl;
    }
}
