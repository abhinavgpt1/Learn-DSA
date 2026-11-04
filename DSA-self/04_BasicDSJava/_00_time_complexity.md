Definition: Algorithm: An algorithm is a finite sequence of steps or instructions used to solve a particular problem.
- A problem can have multiple algorithms (solutions).
- The goal is to choose the most efficient algorithm.
- An algorithm can be optimized in two ways:
  - Time Complexity: How efficiently it uses time.
  - Space Complexity: How efficiently it uses memory.
Definition: Algorithm Analysis: the process of evaluating an algorithm's efficiency, usually in terms of the time and space it requires as the input size increases.

Important: First make sure the application works correctly. Optimization comes after that.

Definition: Time complexity: The time taken by an algorithm/program to run as a function of the length of the input. Usually expressed as Big O notation.
Definition: Space complexity: The amount of memory used by an algorithm/program as a function of the length of the input.
Definition: Big O notation: It's a mathematical way to describe the growth rate of an algorithm's time or space as the input size n increases.

The important thing is not the actual number of seconds an algorithm takes. It is how the number of operations grows as the input size increases.

Q1: Why not measure time in seconds?
Ans: The same algorithm can take different amounts of time on different machines because of differences in hardware, processors, memory, and other factors.

Instead, we analyze the number of operations relative to the input size.

Q2: Why is time complexity so important?
Ans:
- It can clearly distinguish between two different algorithms based on their efficiency.
- It's independent of the machine on which the algorithm is run.
- We can get a direct correlation with the length of the input.

Asymptotically means when the input size becomes very large. For example,
Suppose two algorithms take:
- Algorithm A: (3n + 10) operations
- Algorithm B: (n^2 + 2n) operations
For small inputs, the difference might not be significant. But as (n) grows very large:
- A grows linearly: (O(n)).
- B grows quadratically: (O(n^2)).
So, asymptotically, Algorithm A scales better than Algorithm B.

Core Asymptotic Bounds
• Big-O (O): Upper Bound
	• Represents the maximum or worst-case growth rate (f(n) ≤ c ⋅ g(n) for n ≥ n₀).
	• Tells you an algorithm will never take longer than this rate.
• Big-Omega (Ω): Lower Bound
	• Represents the minimum or best-case growth rate (f(n) ≥ c ⋅ g(n) for n ≥ n₀).
	• Tells you an algorithm will take at least this much time.
• Big-Theta (Θ): Tight Bound
	• Represents an exact match where the function is bounded both above and below by the same rate (c₁ ⋅ g(n) ≤ f(n) ≤ c₂ ⋅ g(n)).
	• Tells you the asymptotic behavior is locked tightly to that curve.

Notable problems:
- https://www.interviewbit.com/problems/amortized1/
- https://www.interviewbit.com/problems/choose3/
- https://www.interviewbit.com/problems/nestedcmpl2/
- https://www.interviewbit.com/problems/nestedcmpl3/
- https://www.interviewbit.com/problems/choose2/
- https://www.interviewbit.com/problems/reccmpl1/
- https://www.interviewbit.com/problems/reccmpl2/
- https://www.interviewbit.com/problems/reccmpl3/

ref: https://www.interviewbit.com/courses/programming/time-complexity/

Notable algorithms:
- GCD:
    - Brute force	O(min(a,b))	O(1)
    - Euclidean algo, iterative	O(log(min(a,b)))	O(1)
    - Euclidean algo, recursive	O(log(min(a,b)))	O(1)

Algorithm	    Best Time	Avg Time	Worst Time	Space Complexity	Key Idea
Linear Search	O(1)	    O(n)	    O(n)	    O(1)	            Check elements one by one; works on unsorted data
Binary Search	O(1)	    O(log n)	O(log n)	O(1) iterative	    Halve the search range; requires sorted data
Bubble Sort	    O(n)*	    O(n^2)	    O(n^2)	    O(1)	            Repeatedly swap adjacent out-of-order elements
Selection Sort	O(n^2)	    O(n^2)	    O(n^2)	    O(1)	            Find the minimum and place it at the beginning of the unsorted portion
Insertion Sort	O(n)	    O(n^2)	    O(n^2)	    O(1)	            Insert each element into its correct position in the sorted portion
Merge Sort	    O(nlog n)	O(nlog n)	O(nlog n)	O(n)	            Divide the array, sort each half, and merge
Quick Sort	    O(nlog n)	O(nlog n)	O(n^2)	    O(log n)**	        Choose a pivot, partition the array, and sort each partition

* Bubble Sort achieves O(n) best-case time when implemented with an early-exit check. 
**Quick Sort's space complexity is typically O(log n) on average, but can reach O(n) in the worst case due to recursion.
Binary Search uses O(log n) stack space in a recursive implementation.