/*
13. Roman to Integer
Easy

Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000

For example, 2 is written as II in Roman numeral, just two one's added together. 12 is written as XII, which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

    I can be placed before V (5) and X (10) to make 4 and 9. 
    X can be placed before L (50) and C (100) to make 40 and 90. 
    C can be placed before D (500) and M (1000) to make 400 and 900.

Given a roman numeral, convert it to an integer.

 

Example 1:

Input: s = "III"
Output: 3
Explanation: III = 3.

Example 2:

Input: s = "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.

Example 3:

Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

 

Constraints:

    1 <= s.length <= 15
    s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
    It is guaranteed that s is a valid roman numeral in the range [1, 3999].


*/
//100%
class Solution
{
private:

int fun(const char a)
{
    if(a == 'I') return 1;
    if(a == 'V') return 5;
    if(a == 'X') return 10;
    if(a == 'L') return 50;
    if(a == 'C') return 100;
    if(a == 'D') return 500;
    if(a == 'M') return 1000;
    
    return 0;
}

public:

int romanToInt(std::string s) 
{
    int res = 0;
    int dim = s.size();
    
    for(int i = 0; i < dim; i++)
    {
        if(i < (dim - 1) && 
           fun(s[i]) < fun(s[i+1]))
        {
            res -= fun(s[i]);
        }
        else
        {
            res += fun(s[i]);
        }
    }
    
    return res;
}

};
//my
class Solution {
public:
    int getNum(char ch){
       switch(ch){
           case 'I':
               return 1;
            case 'V':
               return 5;
               case 'X':
               return 10;
               case 'L':
               return 50;
               case 'C':
               return 100;
               case 'D':
               return 500;
               case 'M':
               return 1000;
       } 
        return 0;
    }
    int romanToInt(string s) {
        stack<char> stk;
        int ans = 0;
        for(int i=0; i<s.length(); i++){
            if(stk.empty())
                stk.push(s[i]);
            else{
                int numPrev = getNum(stk.top());
                int num = getNum(s[i]);
                if(numPrev >= num)
                {
                    stk.pop();
                    stk.push(s[i]);
                    ans += numPrev;
                }
                else{
                    stk.pop();
                    ans += -numPrev + num;
                }
            }             
        }
        while(!stk.empty()){
            ans += getNum(stk.top());
            stk.pop();
        }
        return ans;
    }
};
/*
int ans = 0;
        int local = getNum(s[0]);
        for(int i=1; i<s.length(); i++){
            int num = getNum(s[i]);
            if(getNum(s[i]) > getNum(s[i-1]))
            {
                ans = -local + num;
                local = 0;
            }
            else{
                local += num;
            }                
            
        }
        if(local != 0)
            ans += local;
        return ans;
*/