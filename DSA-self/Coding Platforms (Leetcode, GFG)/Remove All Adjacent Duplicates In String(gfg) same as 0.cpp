/*
1047. Remove All Adjacent Duplicates In String
Easy

826

63

Add to List

Share
Given a string S of lowercase letters, a duplicate removal consists of choosing two adjacent and equal letters, and removing them.

We repeatedly make duplicate removals on S until we no longer can.

Return the final string after all such duplicate removals have been made.  It is guaranteed the answer is unique.

 

Example 1:

Input: "abbaca"
Output: "ca"
Explanation: 
For example, in "abbaca" we could remove "bb" since the letters are adjacent and equal, and this is the only possible move.  The result of this move is that the string is "aaca", of which only "aa" is possible, so the final string is "ca".
 

Note:

1 <= S.length <= 20000
S consists only of English lowercase letters.
*/
class Solution {
public:
    string removeDuplicates(string s) {
     
        string ans="";
        ans+=s[0];
        int top=0;
        for(int i=1;i<s.length();i++){
            
            if(top!=-1 && s[i]==ans[top]){
                ans=ans.substr(0,top);
                top--;
            }
            
            else{
                ans+=s[i];
                top++;
            }
            
        }
        
        return ans;
        
    }
};