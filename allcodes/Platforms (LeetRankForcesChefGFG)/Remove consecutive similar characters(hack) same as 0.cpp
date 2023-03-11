/*
Remove consecutive similar characters
Steve has a string of lowercase characters in range ascii[‘a’..’z’]. He wants to reduce the string to its shortest length by doing a series of operations. In each operation he selects a pair of adjacent lowercase letters that match, and he deletes them. For instance, the string aab could be shortened to b in one operation.

Steve’s task is to delete as many characters as possible using this method and print the resulting string. If the final string is empty, print Empty String

Function Description

Complete the superReducedString function in the editor below. It should return the super reduced string or Empty String if the final string is empty.

superReducedString has the following parameter(s):

s: a string to reduce
Input Format

A single string, .

Constraints

Output Format

If the final string is empty, print Empty String; otherwise, print the final non-reducible string.

Sample Input 0

aaabccddd
Sample Output 0

abd
Explanation 0

Steve performs the following sequence of operations to get the final string:

aaabccddd → abccddd → abddd → abd
Sample Input 1

aa
Sample Output 1

Empty String
Explanation 1

aa → Empty String
Sample Input 2

baab
Sample Output 2

Empty String
Explanation 2

baab → bb → Empty String
*/
#include <bits/stdc++.h>

using namespace std;

string mydelete(string n, int i, int j){

    string ans;
    if(i<n.length() && j< n.length())
        ans=n.substr(0,i)+n.substr(j+1);
    // else
    //     ans="";
    return ans;
}

// Complete the superReducedString function below.
string helper(string s) {

    if(s.length()==0)
    return "";

    if(s[0]==s[1])
    {
        s=helper(s.substr(2));
    }
    else
        s=s[0]+helper(s.substr(1));
        if(s[0]==s[1])
        {
            s=s.substr(2);
        }
    
    return s;
}
string superReducedString(string s) {

    string ans=helper(s);
    if(ans=="")
    return "Empty String";
    return ans;
}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = superReducedString(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
