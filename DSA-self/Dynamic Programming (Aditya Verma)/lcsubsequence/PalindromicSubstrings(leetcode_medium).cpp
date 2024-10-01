/**
 * 647. Palindromic Substrings
 * ---------------------------
 * Given a string s, return the number of palindromic substrings in it.
 * A string is a palindrome when it reads the same backward as forward.
 * A substring is a contiguous sequence of characters within the string.
 *
 * Constraints:
 * 1 <= s.length <= 1000
 * s consists of lowercase English letters.
 *
 */

// link: https://leetcode.com/problems/palindromic-substrings/description/
// link: https://www.geeksforgeeks.org/problems/count-palindrome-sub-strings-of-a-string0652/1
// article: https://www.geeksforgeeks.org/count-palindrome-sub-strings-string-set-2/
// article: https://www.geeksforgeeks.org/count-palindrome-sub-strings-string/

// Best soln. - O(n), O(1): using Manacher's algo - https://cp-algorithms.com/string/manacher.html

// Solution 1: Iterative: Using Center Expansion -> O(n*n), O(1)
class Solution {
public:
    int countSubstrings(string s) {
        int n=s.length(), cnt=0;
        // center at s[i]
        for(int i=0; i<n; i++){
            int left = i, right = i;
            while(left>=0 && right<n){
                if(s[left] != s[right])
                    break;
                left--; right++; cnt++;
            }
        }
        // center at s[i], s[i+1]
        for(int i=0; i<n; i++){
            int left = i, right = i+1;
            while(left>=0 && right<n){
                if(s[left] != s[right])
                    break;
                left--; right++; cnt++;
            }
        }
        return cnt;
    }

    // old code less clean
    int countSubstrings(string s)
    {
        int n = s.length();
        int cnt = 0;
        string ans = "";
        for (int i = 0; i < s.length(); i++)
        {
            int left = i, right = i;

            while (left >= 0 && right < n && s[left] == s[right]) // assuming s[i] as the palindrome center when len=odd
            {
                left--;
                right++;
                cnt++;
            }

            if (i < n && s[i] == s[i + 1])
            { // assuming s[i], s[i+1] as the palindrome center when len=even
                left = i;
                right = i + 1;
                while (left >= 0 && right < n && s[left] == s[right])
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

// Solution 2: Bottom-up: Intuitive: O(n*n), O(n*n)
class Solution
{
    void evalpal(string s, vector<vector<int>> &ispal, int n)
    {
        for (int i = 0; i < n; i++)
            ispal[i][i] = 1;
        for (int i = 1; i < n; i++)
        {
            if (s[i - 1] == s[i])
                ispal[i - 1][i] = 1;
            else
                ispal[i - 1][i] = 0;
        }
        for (int len = 3; len <= n; len++)
        {
            for (int i = 0; i <= n - len; i++)
            {
                int j = i + len - 1;
                if (s[i] == s[j])
                    ispal[i][j] = ispal[i + 1][j - 1];
                else
                    ispal[i][j] = 0;
            }
        }
    }

public:
    int countSubstrings(string s)
    {
        int n = s.length();
        vector<vector<int>> ispal(n, vector<int>(n, -1));
        evalpal(s, ispal, n);
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                if (ispal[i][j] == 1)
                    ans++;
            }
        }
        return ans;
    }
};