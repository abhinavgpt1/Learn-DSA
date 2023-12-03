/*
647. Palindromic Substrings
Medium
Given a string s, return the number of palindromic substrings in it.

A string is a palindrome when it reads the same backward as forward.

A substring is a contiguous sequence of characters within the string.

 

Example 1:

Input: s = "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".
Example 2:

Input: s = "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
 

Constraints:

1 <= s.length <= 1000
s consists of lowercase English letters.
*/

// SAME AS LONGEST PALINDROMIC SUBSTRING
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.length();
        int cnt = 0;
        string ans = "";
        for(int i=0; i<s.length(); i++){
            int left = i, right = i;
            
            while(left >= 0 && right <n && s[left] == s[right])
            {
                left--;
                right++;
                cnt++;
            }
            
            
            if(i<n && s[i] == s[i+1]){
                left = i;
                right = i+1;
                while(left >= 0 && right < n && s[left] == s[right])
                {
                    left--;
                    right++;
                    cnt++;
                }
            }
            
        }
        return cnt;
    }
};