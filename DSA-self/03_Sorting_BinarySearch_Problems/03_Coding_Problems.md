### Coding Problems

1. https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/
2. https://leetcode.com/problems/search-insert-position/description/
3. https://leetcode.com/problems/search-in-rotated-sorted-array-ii/description/
4. https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/description/
5. https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
    - Check your solution by saving ans and comparing mid with n-1 element - 100% runtime and 99% memory
    - Alternate way to Aditya Verma's approach. No need to check (arr[start] <= arr[end]) return start;
6. https://leetcode.com/problems/find-peak-element/description/
7. https://www.geeksforgeeks.org/problems/find-duplicates-in-an-array/1
    - Check editorial for index approach (Negative Marking approach: PTR: doesn't work for arr[i] <= 0. Better, make new array and mark that position true and add to array if you come on same arr[arr[i]])
8. https://leetcode.com/problems/single-element-in-a-sorted-array/description/
9. https://www.geeksforgeeks.org/kth-smallest-element-in-the-array-using-constant-space-when-array-cant-be-modified/
    - Read properly, it's a great.
10. https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/description/
    - Based on 9, 1. cnt in O(n^2) which yields cntLess and cntEqual. 2. cnt in O(n) which yields cntLessOrEqual: O(n log(max-min))
    - Can use the save ans approach by A.V.
11. https://www.geeksforgeeks.org/maximum-subarray-size-subarrays-size-sum-less-k/
12. https://www.geeksforgeeks.org/problems/aggressive-cows/0
    - Check editorial too
13. https://leetcode.com/problems/search-a-2d-matrix-ii/
14. https://leetcode.com/problems/ugly-number-iii/description/
15. https://leetcode.com/problems/find-k-th-smallest-pair-distance/
    - Check the sliding window approach
16. https://www.geeksforgeeks.org/sum-manhattan-distances-pairs-points/
17. https://practice.geeksforgeeks.org/problems/inversion-of-array/0
18. https://practice.geeksforgeeks.org/problems/segregate-even-and-odd-numbers/0
    - Segregation is fine using 2 pointer approach. But sorting both sets require sort() operation 2 times overall.
19. https://leetcode.com/problems/next-permutation/
20. https://practice.geeksforgeeks.org/problems/sorting-elements-of-an-array-by-frequency/0
21. https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/
    - Check best solution: count can be found in O(m)
22. https://practice.geeksforgeeks.org/problems/allocate-minimum-number-of-pages/0
23. https://leetcode.com/problems/nth-magical-number/
    - Same as ugly number iii problem. Do check editorial with ans saving technique
24. https://leetcode.com/problems/count-of-smaller-numbers-after-self/