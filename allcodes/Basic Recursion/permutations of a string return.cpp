#include <string>
using namespace std;

int returnPermutations(string input, int fixed, string output[]){
   	/* Don't write main() function.
	 * Don't read input, it is passed as function argument.
	 * Print output as specified in the question
	*/
    static int top;
	if(fixed==input.length())
    {
        output[top]=input;
            return top++;
    }
    for(int i=fixed;i<input.length();i++)
    {
        swap(input[fixed],input[i]);
        returnPermutations(input,fixed+1,output);
        swap(input[fixed],input[i]);
    }
    return top;
}
int returnPermutations(string input, string output[])
{
    return returnPermutations(input, 0, output);
}