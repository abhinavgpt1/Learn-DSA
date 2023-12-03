/*
Check redundant brackets
Send Feedback
Given a string mathematical expression, return true if redundant brackets are present in the expression. Brackets are redundant if there is nothing inside the bracket or more than one pair of brackets are present.
Assume the given string expression is balanced and contains only one type of bracket i.e. ().
Note: You will not get partial score for this problem. You will get marks only if all test cases are passed.
Input Format :
String s (Expression)
Output Format :
true or false
Sample Input 1:
((a + b)) 
Sample Output 1:
true
Sample Input 2:
(a+b) 
Sample Output 2:
false
*/
/*

//general Solution: checks balancing of strings as well
possible strings:

a+b -> false
(a+b) -> false
((a+b)) -> true
((a+b)*(e/f)) -> false
(a) -> false

For Such cases, we need opertor string
(a) vs (*)==((a+b)*(e/f))
 |      |
false   true
*/
#include<stack>
bool checkRedundantBrackets(string input) {
    // Write your code here
    stack<int> stk;
    string operators = "+-*/^%";
    for(int i = 0; i < input.length(); i++){
        
        if(input[i] != ')')
            stk.push(input[i]);
        
        else{
            
            //to check balanced expr.
            if(stk.empty())
            return true;
        
            int count = 0;
            bool hasOperator = false;
            while(stk.top() != '('){
                
                //to check balanced expr.
                if(stk.empty())
                   return true;
                
                if(operators.find(stk.top()) != string::npos )
                    hasOperator = true;
                
                stk.pop();
                count++;
            }
            stk.pop();
            
            if(count < 3 && hasOperator == false)
                return true;
            
        }
    }
    while(!stk.empty()){
        if(stk.top() == '(' || stk.top() == ')')
            return true;
        stk.pop();
    }
    return false;
}

//method 2: assuming expr. is balanced
#include<stack>
bool checkRedundantBrackets(string input) {
    // Write your code here
    stack<int> stk;
    string operators = "+-*/^%";
    for(int i = 0; i < input.length(); i++){
        
        if(input[i] != ')')
            stk.push(input[i]);
        
        else{
            int count = 0;
            bool hasOperator = false;
            while(stk.top() != '('){
                if(operators.find(stk.top()) != string::npos )
                    hasOperator = true;
                stk.pop();
                count++;
            }
            stk.pop();
            
            if(count < 3 && hasOperator == false)
                return true;
            
        }
    }
    return false;
}

//simpler, but gives false for case: (c)
bool checkRedundantBrackets(char *input) {
    // Write your code here
    if(input[0]=='\0')
        return true;
    
    bool characterDetected=false;
    for(int i=0;input[i]!='\0';i++){
        if(input[i]=='(')
            characterDetected=false;
        else if(input[i]==')'){
            if(characterDetected==false)
                return true;
        }
        else{
            characterDetected=true;
        }
    }
    return false;
}