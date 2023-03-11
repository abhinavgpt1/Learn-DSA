/*
We define the following terms:

Lexicographical Order, also known as alphabetic or dictionary order, orders characters as follows:
For example, ball < cat, dog < dorm, Happy < happy, Zoo < ball.

A substring of a string is a contiguous block of characters in the string. For example, the substrings of abc are a, b, c, ab, bc, and abc.
Given a string, , and an integer, , complete the function so that it finds the lexicographically smallest and largest substrings of length .

Function Description

Complete the getSmallestAndLargest function in the editor below.

getSmallestAndLargest has the following parameters:

string s: a string
int k: the length of the substrings to find
Returns

string: the string ' + "\n" + ' where and are the two substrings
Input Format

The first line contains a string denoting .
The second line contains an integer denoting .

Constraints

 consists of English alphabetic letters only (i.e., [a-zA-Z]).
Sample Input 0

welcometojava
3
Sample Output 0

ava
wel
Explanation 0

String  has the following lexicographically-ordered substrings of length :

We then return the first (lexicographically smallest) substring and the last (lexicographically largest) substring as two newline-separated values (i.e., ava\nwel).

The stub code in the editor then prints ava as our first line of output and wel as our second line of output.
*/

import java.util.Scanner;

public class Solution {

    public static String getSmallestAndLargest(String s, int k) {
        String smallest = "";
        String largest = "";
        
        // Complete the function
        // 'smallest' must be the lexicographically smallest substring of length 'k'
        // 'largest' must be the lexicographically largest substring of length 'k'
        
        int smallestIndex = 0, largestIndex = 0;
        for(int i=1; i<=s.length() - k; i++){
            if(s.charAt(i) < s.charAt(smallestIndex))
                smallestIndex = i;
            else if(s.charAt(i) == s.charAt(smallestIndex)){
                if(s.substring(i, i+k).compareTo(s.substring(smallestIndex, smallestIndex + k)) < 0)
                smallestIndex = i;
            }
            if(s.charAt(i) > s.charAt(largestIndex))
                largestIndex = i;
            else if(s.charAt(i) == s.charAt(largestIndex)){
                if(s.substring(i, i+k).compareTo(s.substring(largestIndex, largestIndex + k)) > 0)
                largestIndex = i;
            }
        }
        smallest = s.substring(smallestIndex, smallestIndex + k);
        largest = s.substring(largestIndex, largestIndex + k);
        return smallest + "\n" + largest;
    }
}

// Editorial
import java.util.*;

public class Solution {
    
    public static String getSmallestAndLargestCompareTo(String s, int k) {
        String substring = s.substring(0, k);
        String smallest = substring;
        String largest = substring;
        
        for (int i = 1; i <= s.length() - k; i++) {
            // Create a substring of length 'k'
            substring = s.substring(i, i + k);
            	
            // If current substring is lexicographically smaller than 'smallest'
            if (substring.compareTo(smallest) < 0) {
                smallest = substring;
            }
            
            // If current substring is lexicographically larger than 'largest'
            if (substring.compareTo(largest) > 0) {
                largest = substring;
            }
        }
        
        return smallest + "\n" + largest;
    }
  
    public static String getSmallestAndLargestList(String s, int k) {
        Vector<String> substrings = new Vector<String>();
        
        for (int i = 0; i <= s.length() - k; i++) {
            // Add a substring of length 'k' to our list
            substrings.add( s.substring(i, i + k) );	
        }
        
        // Sort list
        Collections.sort(substrings);
        
        // Set first and last elements as smallest and largest
        String smallest = substrings.get(0);
        String largest = substrings.get(substrings.size() - 1);
        
        return smallest + "\n" + largest;
    }
    
    public static String getSmallestAndLargestArray(String s, int k) {
        // Because each substring has length 'k', we know the number of possible substrings
        String[] substrings = new String[s.length() - k + 1];
        
        for (int i = 0; i <= s.length() - k; i++) {
            // Add a substring of length 'k' to our array
            substrings[i] =  s.substring(i, i + k);	
        }
        
        // Sort array
        Arrays.sort(substrings);
        
        // Set first and last elements as smallest and largest
        String smallest = substrings[0];
        String largest = substrings[substrings.length - 1];
        
        return smallest + "\n" + largest;
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        String s = scan.next();
        int k = scan.nextInt();
        scan.close();
      
        System.out.println(getSmallestAndLargestCompareTo(s, k));
        System.out.println(getSmallestAndLargestList(s, k));
        System.out.println(getSmallestAndLargestArray(s, k));
    }
}