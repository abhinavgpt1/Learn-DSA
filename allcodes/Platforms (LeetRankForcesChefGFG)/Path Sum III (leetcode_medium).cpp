/*
437. Path Sum III
Medium

7036

355

Add to List

Share
Given the root of a binary tree and an integer targetSum, return the number of paths where the sum of the values along the path equals targetSum.

The path does not need to start or end at the root or a leaf, but it must go downwards (i.e., traveling only from parent nodes to child nodes).

 

Example 1:


Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
Output: 3
Explanation: The paths that sum to 8 are shown.
Example 2:

Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
Output: 3
 

Constraints:

The number of nodes in the tree is in the range [0, 1000].
-109 <= Node.val <= 109
-1000 <= targetSum <= 1000
*/

/* Ajna's article & approach 
----------------------------
This is a nice problem, as it is the composition of 2 classical ones: getting a series of values traversing a tree and verifying if any of those numbers have one or more subarrays summing up to a given targetSum.

The latter problem is here if you want a warm up and here I explained how it worked in more detail.

So my approach followed basically these 2 bits of logic, doing a composition of a DFS based tree traversal and at each iteration checking if the very last value mins the targetSum were already spotted; I used a vector initially, then moved up to an array to keep track of the already seen values with a huge performance boost.

In my approach I use 3 class variables:

my typical accumulator variable res initialised to 0 to count the number of matching occurrences;
sum that takes the values of targetSum and replaces it in all of my recursive calls (so that I do not have to pass it as a parameter)
seen, as mentioned to keep track of the values I spotted so far and created to hold 1001 values (an initial 0 at root level, plus other potential 1000 different ones, as specified in the specs).
Inside my main function I initialise the values and then, provided the tree is not empty (ie: !root), I call dfs.

This function receives 3 parameters:

a mandatory root, which is the node we are currently exploring;
an optional partialSum value, defaulted to 0 and keeping track of our current partial sum going down a specific branch;
an optional pos to tell us where to put out next value in seen and up to which point browse it (muuuch faster than expanding and reducing a vector, try the alternative code down below!)
We are looking for all the occurrences of values in seen which are partialSum - sum, because it means that said value n plus partialSum would equal sum, and for each such instance we increase res by one.

If we have a ->left branch we do the same with it, passing the update root, partialSum and pos (increased by 1) down as parameters; same thing with a ->right branch, if it exists.

When we are done, we just return res :)

The improved code (using an array for seen):
*/
//  approach 1
class Solution {
public:
    int res = 0, sum;
    int seen[1001];
    void dfs(TreeNode* root, int partialSum = 0, int pos = 1) {
        // updating partialSum with the current node
        partialSum += root->val;
        // checking if we already found an interval summing up to that
        for (int i = 0; i < pos; i++) if (seen[i] == partialSum - sum) res++;
        // updating seen
        seen[pos] = partialSum;
        // searching potential left and right branches
        if (root->left) dfs(root->left, partialSum, pos + 1);
        if (root->right) dfs(root->right, partialSum, pos + 1);
    }
    int pathSum(TreeNode* root, int targetSum) {
        sum = targetSum;
        // seen set with initial value 0 will help us match from the root
        seen[0] = 0;
        if (!root) return res;
        dfs(root);
        return res;
    }
};
//  approach 2 - Original approach, vector-based with some extra backtracking logic and going for about a meager ~60% Time, ~50% Space:

class Solution {
public:
    int res = 0, sum;
    // seen set with initial value 0 will help us match from the root
    vector<int> seen = {0};
    void dfs(TreeNode* root, int partialSum = 0) {
        // updating partialSum with the current node
        partialSum += root->val;
        // checking if we already found an interval summing up to that
        for (auto n: seen) if (n == partialSum - sum) res++;
        // updating seen
        seen.push_back(partialSum);
        // searching potential left and right branches
        if (root->left) dfs(root->left, partialSum);
        if (root->right) dfs(root->right, partialSum);
        // clearing seen one level, for backtracking purposes
        seen.pop_back();
    }
    int pathSum(TreeNode* root, int targetSum) {
        sum = targetSum;
        if (!root) return res;
        dfs(root);
        return res;
    }
};

// approach 3 - Alternative with unordered_map, almost as fast, but with space going down to 20% (I believe it used around 40-50% more space on average):

class Solution {
public:
    int res = 0, sum;
    unordered_map<int, int> seen;
    void dfs(TreeNode* root, int partialSum = 0) {
        // updating partialSum with the current node
        partialSum += root->val;
        // checking if we already found an interval summing up to that
        res += seen[partialSum - sum];
        // updating seen
        seen[partialSum]++;
        // searching potential left and right branches
        if (root->left) dfs(root->left, partialSum);
        if (root->right) dfs(root->right, partialSum);
        // clearing seen of the last value, for backtracking purposes
        seen[partialSum]--;
    }
    int pathSum(TreeNode* root, int targetSum) {
        sum = targetSum;
        // seen set with initial value 0 will help us match from the root
        seen[0] = 1;
        if (!root) return res;
        dfs(root);
        return res;
    }
};
//  approach 4 - my soln.