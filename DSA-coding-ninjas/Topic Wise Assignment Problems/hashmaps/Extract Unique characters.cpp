/*
Extract Unique characters
Send Feedback
Given a string, you need to remove all the duplicates. That means, the output string should contain each character only once. The respective order of characters should remain same.
Input format :
String S
Output format :
Output String
Constraints :
0 <= Length of S <= 10^8
Sample Input 1 :
ababacd
Sample Output 1 :
abcd
Sample Input 2 :
abcde
Sample Output 2 :
abcde
*/
#include<cstring>
string uniqueChar(string str) {
	// Write your code here
    int alpha[26];
    memset(alpha, 0, sizeof(alpha));
    string strNew = "";
    for(int i=0; i<str.length(); i++){
        if(alpha[str[i]-'a'])
            continue;
        alpha[str[i]-'a']++;
        strNew+=str[i];
    }
    return strNew;
}

#include<unordered_map>
#include<cstring>
char* uniqueChar(char *str){
    // Write your code here
    int len = strlen(str);
	char * ans = new char[len + 1];
    int top = 0;
    unordered_map<char, bool> um;
    
    for(int i = 0; str[i] != '\0'; i++){
        if(um.count(str[i]) > 0)
            continue;
        um[str[i]] = true;
        ans[top++] = str[i];
    }
    ans[top] = '\0';
    return ans;
}
//OR
#include<unordered_map>
#include<cstring>
char* uniqueChar(char *str){
    // Write your code here

	int length = strlen(str);
	char * ans = new char[length + 1];
	int top=0;
	unordered_map<char,bool> um;
	for(int i=0;str[i]!='\0';i++){
		if(um.count(str[i]) == 0){
			um[str[i]] = true;
			ans[top]=str[i];
			top++;
		}
	}
	ans[top] = '\0';
	
	return ans; 
}	

//aproach not wrong
#include<unordered_map>
char* uniqueChar(char *str){
    // Write your code here
    unordered_map<char, bool> um;
	string ans;
    for(int i = 0; str[i] != '\0'; i++){
        if(um.count(str[i]) > 0)
            continue;
        um[str[i]] = true;
        ans += str[i];
    }
    return ans.c_str();//wrong since, return type reqd. is char* and this returns const char*
}
