/*
520. Detect Capital
Easy

We define the usage of capitals in a word to be right when one of the following cases holds:

    All letters in this word are capitals, like "USA".
    All letters in this word are not capitals, like "leetcode".
    Only the first letter in this word is capital, like "Google".

Given a string word, return true if the usage of capitals in it is right.

 

Example 1:

Input: word = "USA"
Output: true

Example 2:

Input: word = "FlaG"
Output: false

 

Constraints:

    1 <= word.length <= 100
    word consists of lowercase and uppercase English letters.
*/
//100%
class Solution {
public:
    bool detectCapitalUse(string word) {
        int uppercase = 0;
        int lowercase = 0;
        int onlyFirst = 0;
        int size = word.size();
        for (int i = 0; i < size; i++)
        {
            int code = word[i];
            if (code >= 65 && code <= 90)
                uppercase++;
            if (code >= 97 && code <= 122)
                lowercase++;
            if (i == 0 && code >= 65 && code <= 90)
                onlyFirst++;
        }
        return uppercase == size || lowercase == size || (onlyFirst == 1 && lowercase == size - 1);
    }
};
//my soln.
class Solution {
public:
    bool detectCapitalUse(string word) {
        if(word.length() == 1)
            return true;
        bool mode = word[1] >= 97;
        if(mode){
        for(int i=1; i<word.length(); i++){
            
            if(word[i] < 97)
                return false;
            
        }        
            return true;
            }
        
            for(int i=1; i<word.length(); i++){
            
            if(word[i] > 90)
                return false;
            
            }  
            return (word[0] <= 90);
        
        
    }
};