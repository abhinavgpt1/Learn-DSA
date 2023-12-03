/*
Reverse Stack
Send Feedback
Reverse a given Stack with the help of another empty stack. Two stacks will be given. Out of which first contains some integers and second one is empty. You need to reverse the first one using second stack. Change in the given first stack itself.
Note : You don't need to print or return the stack, just reverse the given stack and it will be printed internally.
Input format :
Line 1 : Size of Stack
Line 2 : Stack elements (separated by space)
Sample Input 1 :
4 
1 2 3 4     (4 is at top)
Sample Output 1 :
1 2 3 4    (1 is at top)
*/
//method-recursion
#include <stack>

void reverseStack(stack<int> &input, stack<int> &extra) {
	// Write your code here
	if(input.size()==0)
        return;
    int recent=input.top();
    input.pop();
    reverseStack(input,extra);
    while(input.size()!=0){
        extra.push(input.top());
        input.pop();
    }
    input.push(recent);
    while(extra.size()!=0){
        input.push(extra.top());
        extra.pop();
    }
    
}