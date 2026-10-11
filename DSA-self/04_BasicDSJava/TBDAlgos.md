# Algos
Check algos in https://github.com/abhinavgpt1/Learn-DSA

> **Note:** Not all algorithms will be implemented here. The purpose of this BasicDS learning is to implement data structures from scratch and get hands-on experience with Java.

## SinglyLinkedListImpl: Algos
| Method                | Return Type   | Description                               | Time Complexity                                   |
|-----------------------|---------------|-------------------------------------------|---------------------------------------------------|
| `reverse()`           | `void`        | Reverse the linked list                   | O(n)                                              |
| `reverseRecursive()`  | `void`        | Recursive reversal                        | O(n)                                              |
| `hasCycle()`          | `boolean`     | Detect cycle using Floyd's algorithm      | O(n)                                              |
| `findMiddle()`        | `T`           | Find middle node using slow/fast pointers | O(n)                                              |
| `findNthFromEnd(n)`   | `T`           | Find nth node from end                    | O(n)                                              |
| `removeDuplicates()`  | `void`        | Remove duplicate values                   | O(n) - sorted, O(n²) or O(n) with set - unsorted  |
| `merge()`             | `void`        | Merge two sorted lists                    | O(n+m)                                            |
| `deleteNode()`        | `void`        | Delete node without head reference        | O(1)                                              |
| `isPalindrome()`      | `boolean`     | Check if list is palindrome               | O(n)                                              |

## BinaryTreeImpl: Algos
| Method                              | Return Type        | Description                                      | Time Complexity |
|-------------------------------------|--------------------|--------------------------------------------------|-----------------|
| **Insertion & Serialization**       |                    |                                                  |                 |
| `serialize()`                       | `String`           | Convert tree to string representation            | O(n)            |
| `deserialize(String data)`          | `BinaryTreeNode`   | Reconstruct tree from string                     | O(n)            |
| **DFS Traversals (Iterative)**      |                    |                                                  |                 |
| `preorderIterative()`               | `List<T>`          | Preorder using stack                             | O(n)            |
| `inorderIterative()`                | `List<T>`          | Inorder using stack                              | O(n)            |
| `postorderIterative()`              | `List<T>`          | Postorder using stack                            | O(n)            |
| **BFS Traversals**                  |                    |                                                  |                 |
| `levelOrderSingleList()`            | `List<T>`          | All nodes in level order                         | O(n)            |
| `zigzagLevelOrder()`                | `List<List<T>>`    | Zigzag pattern traversal                         | O(n)            |
| `reverseLevelOrder()`               | `List<List<T>>`    | Bottom to top traversal                          | O(n)            |
| **Path & Sum Algorithms**           |                    |                                                  |                 |
| `hasPathSum(int sum)`               | `boolean`          | Check if root-to-leaf path sum exists            | O(n)            |
| `pathSum(int sum)`                  | `List<List<T>>`    | All paths with given sum                         | O(n)            |
| `printRootToLeafPaths()`            | `void`             | Print all root-to-leaf paths                     | O(n)            |
| `pathToNode(BinaryTreeNode node)`   | `List<T>`          | Path from root to given node                     | O(n)            |
| `maxPathSum()`                      | `int`              | Maximum path sum between any two nodes           | O(n)            |
| **Tree Property Checks**            |                    |                                                  |                 |
| `isBalanced()`                      | `boolean`          | Check if height-balanced                         | O(n)            |
| `isSymmetric()`                     | `boolean`          | Check if tree is mirror of itself                | O(n)            |
| `isSameTree(BinaryTreeNode other)`  | `boolean`          | Compare two trees                                | O(n)            |
| `isSubtree(BinaryTreeNode subRoot)` | `boolean`          | Check if subRoot is subtree                      | O(n×m)          |
| `isComplete()`                      | `boolean`          | Check if complete binary tree                    | O(n)            |
| `isFull()`                          | `boolean`          | Check if full (0 or 2 children)                  | O(n)            |
| `isPerfect()`                       | `boolean`          | Check if perfect binary tree                     | O(n)            |
| `isLeaf(BinaryTreeNode node)`       | `boolean`          | Check if node is leaf                            | O(1)            |
| **View Algorithms**                 |                    |                                                  |                 |
| `leftView()`                        | `List<T>`          | Leftmost nodes at each level                     | O(n)            |
| `rightView()`                       | `List<T>`          | Rightmost nodes at each level                    | O(n)            |
| `topView()`                         | `List<T>`          | Nodes visible from top                           | O(n log n)      |
| `bottomView()`                      | `List<T>`          | Nodes visible from bottom                        | O(n log n)      |
| `boundaryTraversal()`               | `List<T>`          | Left boundary + leaves + right boundary          | O(n)            |
| `verticalOrder()`                   | `List<List<T>>`    | Vertical order traversal                         | O(n log n)      |
| `diagonalTraversal()`               | `List<List<T>>`    | Diagonal traversal                               | O(n)            |
| **Tree Measurements**               |                    |                                                  |                 |
| `minDepth()`                        | `int`              | Shortest path to leaf                            | O(n)            |
| `maxDepth()`                        | `int`              | Maximum depth (same as height)                   | O(n)            |
| `diameter()`                        | `int`              | Longest path between any two nodes               | O(n)            |
| `maxWidth()`                        | `int`              | Maximum width at any level                       | O(n)            |
| `countLeaves()`                     | `int`              | Count leaf nodes                                 | O(n)            |
| `countInternalNodes()`              | `int`              | Count non-leaf nodes                             | O(n)            |
| `countFullNodes()`                  | `int`              | Count nodes with 2 children                      | O(n)            |
| `countHalfNodes()`                  | `int`              | Count nodes with 1 child                         | O(n)            |
| **Search & Query Algorithms**       |                    |                                                  |                 |
| `search(T data)`                    | `BinaryTreeNode`   | Find node with given data                        | O(n)            |
| `findMin()`                         | `T`                | Find minimum value in tree                       | O(n)            |
| `findMax()`                         | `T`                | Find maximum value in tree                       | O(n)            |
| `findLCA(BinaryTreeNode p, q)`      | `BinaryTreeNode`   | Find Lowest Common Ancestor                      | O(n)            |
| `kthSmallest(int k)`                | `T`                | Find kth smallest element                        | O(n)            |
| `kthLargest(int k)`                 | `T`                | Find kth largest element                         | O(n)            |
| `findDistance(BinaryTreeNode p, q)` | `int`              | Distance between two nodes                       | O(n)            |
| `nodesAtDistanceK(target, int k)`   | `List<T>`          | Nodes at distance k from target                  | O(n)            |
| **Sum & Aggregate Algorithms**      |                    |                                                  |                 |
| `sumOfNodes()`                      | `int`              | Sum of all node values                           | O(n)            |
| `sumOfLeafNodes()`                  | `int`              | Sum of leaf node values                          | O(n)            |
| `sumOfNonLeafNodes()`               | `int`              | Sum of internal node values                      | O(n)            |
| `sumAtLevel(int level)`             | `int`              | Sum of nodes at given level                      | O(n)            |
| **Utility Algorithms**              |                    |                                                  |                 |
| `mirror()`                          | `void`             | Invert/mirror the tree                           | O(n)            |
| `convertToMirror()`                 | `void`             | Convert tree to its mirror                       | O(n)            |
| `deleteDeepest(BinaryTreeNode node)`| `void`             | Delete deepest rightmost node                    | O(n)            |
| `getLevel(BinaryTreeNode node)`     | `int`              | Get level of given node                          | O(n)            |
| `areTreesIdentical(t1, t2)`         | `boolean`          | Check if two trees are identical                 | O(n)            |
| `allPathsSourceToTarget()`          | `List<List<T>>`    | All paths from root to leaves                    | O(n)            |

## BinarySearchTreeImpl: Algos

| Method                              | Return Type     | Description                                   | Time Complexity              |
|-------------------------------------|-----------------|-----------------------------------------------|------------------------------|
| **Min/Max Operations**              |                 |                                               |                              |
| `findMin()`                         | `T`             | Find minimum element (leftmost)               | O(log n) avg, O(n) worst     |
| `deleteMin()`                       | `void`          | Delete minimum element                        | O(log n) avg, O(n) worst     |
| `deleteMax()`                       | `void`          | Delete maximum element                        | O(log n) avg, O(n) worst     |
| **Successor/Predecessor**           |                 |                                               |                              |
| `inorderSuccessor(T data)`          | `T`             | Find next larger element                      | O(log n) avg, O(n) worst     |
| `inorderPredecessor(T data)`        | `T`             | Find next smaller element                     | O(log n) avg, O(n) worst     |
| **Range Queries**                   |                 |                                               |                              |
| `rangeSearch(T min, T max)`         | `List<T>`       | Find all elements in range [min, max]         | O(k + log n)                 |
| `countInRange(T min, T max)`        | `int`           | Count elements in range                       | O(k + log n)                 |
| `floor(T data)`                     | `T`             | Largest element ≤ data                        | O(log n) avg                 |
| `ceiling(T data)`                   | `T`             | Smallest element ≥ data                       | O(log n) avg                 |
| **Kth Element Operations**          |                 |                                               |                              |
| `kthSmallest(int k)`                | `T`             | Find kth smallest (use inorder)               | O(n) or O(log n)*            |
| `kthLargest(int k)`                 | `T`             | Find kth largest (use reverse inorder)        | O(n) or O(log n)*            |
| `rank(T data)`                      | `int`           | Number of elements < data                     | O(n) or O(log n)*            |
| **BST Validation**                  |                 |                                               |                              |
| `isBST()`                           | `boolean`       | Validate BST property                         | O(n)                         |
| `isBSTInOrder()`                    | `boolean`       | Validate using inorder traversal              | O(n)                         |
| `isBSTMinMax()`                     | `boolean`       | Validate using min-max approach               | O(n)                         |
| **Tree Conversion**                 |                 |                                               |                              |
| `sortedArrayToBST(T[] arr)`         | `BSTNode`       | Convert sorted array to balanced BST          | O(n)                         |
| `bstToSortedArray()`                | `List<T>`       | Convert BST to sorted array (inorder)         | O(n)                         |
| `bstToMinHeap()`                    | `void`          | Convert BST to min heap                       | O(n)                         |
| `bstToGreaterSumTree()`             | `void`          | Transform to greater sum tree                 | O(n)                         |
| `flattenToSortedList()`             | `Node`          | Convert BST to sorted linked list             | O(n)                         |
| **LCA & Path Operations**           |                 |                                               |                              |
| `lowestCommonAncestor(T p, T q)`    | `T`             | Find LCA in BST (optimized)                   | O(log n) avg, O(n) worst     |
| `distance(T p, T q)`                | `int`           | Distance between two nodes                    | O(log n) avg                 |
| `pathFromRoot(T data)`              | `List<T>`       | Get path from root to node                    | O(log n) avg                 |
| **Balancing & Restructuring**       |                 |                                               |                              |
| `balanceBST()`                      | `void`          | Balance unbalanced BST                        | O(n)                         |
| `mergeTwoBSTs(BST other)`           | `BST`           | Merge two BSTs into balanced BST              | O(m + n)                     |
| `trimBST(T low, T high)`            | `BSTNode`       | Remove nodes outside [low, high]              | O(n)                         |
| **Pair & Sum Operations**           |                 |                                               |                              |
| `findPair(int sum)`                 | `Pair<T, T>`    | Find pair with given sum                      | O(n)                         |
| `findPairInTwoBSTs(BST other, sum)` | `boolean`       | Find pair from two BSTs with sum              | O(n)                         |
| `correctSwappedNodes()`             | `void`          | Fix two swapped nodes in BST                  | O(n)                         |
| **Special BST Problems**            |                 |                                               |                              |
| `countNodesInRange(T low, T high)`  | `int`           | Count nodes in given range                    | O(k + log n)                 |
| `closestValue(T target)`            | `T`             | Find value closest to target                  | O(log n) avg                 |
| `closestKValues(T target, int k)`   | `List<T>`       | Find k closest values to target               | O(log n + k)                 |
| `verticalSum()`                     | `Map<Int, Int>` | Vertical sum in BST                           | O(n)                         |
| `printInRange(T min, T max)`        | `void`          | Print elements in sorted order [min, max]     | O(k + log n)                 |
| **Morris Traversal (Space O(1))**   |                 |                                               |                              |
| `morrisInorder()`                   | `List<T>`       | Inorder without recursion/stack               | O(n), Space O(1)             |
| `morrisPreorder()`                  | `List<T>`       | Preorder without recursion/stack              | O(n), Space O(1)             |
| **Additional Utilities**            |                 |                                               |                              |
| `sumOfLeftLeaves()`                 | `int`           | Sum of all left leaf nodes                    | O(n)                         |
| `sumOfRightLeaves()`                | `int`           | Sum of all right leaf nodes                   | O(n)                         |
| `maxDifference()`                   | `int`           | Max diff between node and ancestor            | O(n)                         |
| `printCommonNodes(BST other)`       | `void`          | Print nodes common to both BSTs               | O(m + n)                     |

**Note:**
- *O(log n) for kth element and rank operations require augmented BST with size at each node
- Average case assumes balanced BST; worst case occurs with skewed tree
- Most BST operations degrade to O(n) in worst case (unbalanced); use AVL/Red-Black for guaranteed O(log n)


