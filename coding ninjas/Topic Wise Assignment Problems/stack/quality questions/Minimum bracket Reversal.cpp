/*
Minimum bracket Reversal
Send Feedback
Given a string expression which consists only ‘}’ and ‘{‘. The expression may not be balanced. You need to find the minimum number of bracket reversals which are required to make the expression balanced.
Return -1 if the given expression can't be balanced.
Input Format :
String S
Output Format :
Required count
Sample Input 1 :
{{{
Sample Output 1 :
-1
Sample Input 2 :
{{{{}}
Sample Output 2 :
1
*/

/*
WRONG SOLUTION
int countBracketReversals(char input[]){
    // Write your code here
    if(input==NULL)
        return -1;
    int i=0,in=0,out=0;
    while(input[i]!='\0'){
        if(input[i]=='{')
            in++;
        else
            out++;
        i++;
    }
    if((in+out)%2==0){
        return abs(in-out)/2;
    }
    return -1;
}

*/
//using string
#include<stack>
int countBracketReversals(string input) {
    // Write your code here
    if(input.size() % 2 == 1)
        return -1;
    stack<char> stk;
    for(int i = 0; i < input.length(); i++){
        if(input[i] == '{')
            stk.push(input[i]);
        else{
            if(stk.empty() || stk.top() == '}')
                stk.push(input[i]);
            else
                stk.pop();
        }
    }
    int count = 0;
    while(!stk.empty()){
        char ch1 = stk.top();stk.pop();
        char ch2 = stk.top();stk.pop();
        if(ch1 == ch2)
            count++;
        else
            count+=2;
    }
    return count;
}




//using char array
#include<stack>
int countBracketReversals(char input[]){
    // Write your code here
    if(input==NULL)
        return -1;
    stack<char> s;
    int i=0;
    //we push whenever we detect their is imbalance
    while(input[i]!='\0'){
        if(input[i]=='{')
            s.push('{');
        else{
             if(s.size()==0){
                    s.push('}');
                }
            else{
            
                char topch=s.top();
                if(topch=='{')
                    s.pop();
                else
                    s.push('}');    
            }
        }
        i++;
    }
    if(s.size()==0){//balanced
        return 0;
    }
    if(i % 2==1)//size of string is odd, i here is length
        return -1;
    
    int count_changes=0;
    while(!s.empty()){
        
        char ch1=s.top();s.pop();
        char ch2=s.top();s.pop();
        if(ch1==ch2)//  {,{ or },}
            count_changes++;
        else// only when sequence was }{ i.e. ch1={ , ch2=}
            count_changes+=2;
    }
    
    return count_changes;
   
    
}
