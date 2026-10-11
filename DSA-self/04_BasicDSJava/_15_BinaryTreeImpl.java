// Methods
// -------
// clear()                      -> void
// contains(T data)             -> boolean
// createTree(T[] arr)          -> void     (build tree from array)
// delete(T data)               -> void
// getSize()                    -> int
// height()                     -> int
// insert(T data)               -> void
// inOrder()                    -> void
// isBST()                      -> boolean
// isEmpty()                    -> boolean
// levelOrder()                 -> void
// preOrder()                   -> void
// printTree(TraversalStrategy) -> void
// postOrder()                  -> void
// update(T obj, T replacement) -> boolean

import java.util.LinkedList;
import java.util.Queue;

interface TraversalStrategy {
    void traverse();
}

class MyBinaryTreeNode<T> {
    // not making them private and creating {get, set}
    MyBinaryTreeNode<T> left;
    MyBinaryTreeNode<T> right;
    T data;

    MyBinaryTreeNode(T data) {
        this.left = null;
        this.right = null;
        this.data = data;
    }

    public void delete() {
        left = null;
        right = null;
        data = null;
    }
}

class MyBinaryTree<T extends Comparable<T>> {
    private MyBinaryTreeNode<T> root;
    private int size;

    class PreOrderTraversal implements TraversalStrategy {
        MyBinaryTreeNode<T> node;

        PreOrderTraversal() {
            this.node = root;
        }

        private void traverse(MyBinaryTreeNode<T> node) {
            if (node == null)
                return;
            System.out.print(node.data + " ");
            traverse(node.left);
            traverse(node.right);
        }

        @Override
        public void traverse() {
            traverse(this.node);
            System.out.println();
        }
    }

    class InOrderTraversal implements TraversalStrategy {
        MyBinaryTreeNode<T> node;

        InOrderTraversal() {
            this.node = root;
        }

        private void traverse(MyBinaryTreeNode<T> node) {
            if (node == null)
                return;
            traverse(node.left);
            System.out.print(node.data + " ");
            traverse(node.right);
        }

        @Override
        public void traverse() {
            traverse(this.node);
            System.out.println();
        }
    }

    class PostOrderTraversal implements TraversalStrategy {
        MyBinaryTreeNode<T> node;

        PostOrderTraversal() {
            this.node = root;
        }

        private void traverse(MyBinaryTreeNode<T> node) {
            if (node == null)
                return;
            traverse(node.left);
            traverse(node.right);
            System.out.print(node.data + " ");
        }

        @Override
        public void traverse() {
            traverse(this.node);
            System.out.println();
        }
    }

    class LevelOrderTraversal implements TraversalStrategy {
        MyBinaryTreeNode<T> node;

        LevelOrderTraversal() {
            this.node = root;
        }

        @Override
        public void traverse() {
            if (node == null) {
                System.out.println("Tree is empty.");
                return;
            }
            Queue<MyBinaryTreeNode<T>> pending = new LinkedList<>();
            pending.add(node);
            pending.add(null);
            while (!pending.isEmpty()) {
                MyBinaryTreeNode<T> first = pending.remove();
                if (first == null) {
                    System.out.println();

                    // to segragate nodes at a level
                    if (!pending.isEmpty())
                        pending.add(null);
                    continue;
                }
                System.out.print(first.data + " ");
                if (first.left != null)
                    pending.add(first.left);
                if (first.right != null)
                    pending.add(first.right);
            }
        }

    }

    // private methods
    private MyBinaryTreeNode<T> createTree(T[] valList, int index) {
        if (index >= valList.length || valList[index] == null) // instead of null it is -1 for integer BT generally
            return null;
        MyBinaryTreeNode<T> tmpRoot = new MyBinaryTreeNode<T>(valList[index]);
        tmpRoot.left = createTree(valList, 2 * index + 1);
        tmpRoot.right = createTree(valList, 2 * index + 2);
        size++;
        return tmpRoot;
    }

    private int height(MyBinaryTreeNode<T> node) {
        if (node == null)
            return 0;
        return 1 + Integer.max(height(node.left), height(node.right));
    }

    private void clear(MyBinaryTreeNode<T> node) {
        if (node == null)
            return;
        clear(node.left);
        clear(node.right);
        node.delete();
    }

    private boolean update(T obj, T replacement, MyBinaryTreeNode<T> node) {
        // Better solution: use findNode() and perform replacement.
        if (node == null)
            return false;
        
        if (node.data.compareTo(obj) == 0) {
            node.data = replacement;
            return true;
        } 
        boolean isUpdated = update(obj, replacement, node.left);
        if (isUpdated)
            return true;
        else
            return update(obj, replacement, node.right);
    }

    private boolean contains(MyBinaryTreeNode<T> node, T data) {
        if (node == null)
            return false;
        if (node.data.compareTo(data) == 0)
            return true;
        
        // Search both subtrees since this is not a BST
        return contains(node.left, data) || contains(node.right, data);
    }

    private boolean isBST(MyBinaryTreeNode<T> node, T minData, T maxData) {
        if(node == null)
            return true;

        return node.data.compareTo(minData) >= 0 && node.data.compareTo(maxData) < 0
            && isBST(node.left, minData, node.data)
            && isBST(node.right, node.data, maxData);
    }

    // public methods
    public MyBinaryTree() {
        root = null;
        size = 0;
    }

    public void createTree(T[] valList) {
        root = createTree(valList, 0);
    }

    public int height() {
        return height(root);
    }

    public int getSize() {
        return size;
    }

    public void preOrder() {
        new PreOrderTraversal().traverse();
    }

    public void inOrder() {
        new InOrderTraversal().traverse();
    }

    public void postOrder() {
        new PostOrderTraversal().traverse();
    }

    public void levelOrder() {
        new LevelOrderTraversal().traverse();
    }

    public void printTree(TraversalStrategy strategy) {
        strategy.traverse();
    }

    public void clear() {
        clear(root);
        size = 0;
        root = null; // IMP.
    }

    public void insert(T data) {
        // level order insert - creates a full tree if used n times
        MyBinaryTreeNode<T> newNode = new MyBinaryTreeNode<>(data);
        if (root == null) {
            root = newNode;
        } else {
            Queue<MyBinaryTreeNode<T>> pending = new LinkedList<>();
            pending.add(root);
            while (!pending.isEmpty()) {
                MyBinaryTreeNode<T> front = pending.remove();
                if (front.left == null) {
                    front.left = newNode;
                    break;
                } else {
                    pending.add(front.left);
                }
                
                if (front.right == null) {
                    front.right = newNode;
                    break;
                } else {
                    pending.add(front.right);
                }
            }
        }
        size++; // IMP.
    }

    public void delete(T data) {
        // Task: delete and replace with deepest rightmost node
        // check gfg problem: https://www.geeksforgeeks.org/problems/deletion-in-a-binary-tree/1

        // A BST like recursive deletion can also be done but multiple occurences will be deleted and it's tricky.
        if(root == null)
            return;
        if (root.left == null && root.right == null) {
            if (root.data.compareTo(data) == 0) {
                root = null;
                size--;
            }
            return;
        }
        
        class Pair {
            MyBinaryTreeNode<T> node;
            MyBinaryTreeNode<T> parent;
            
            Pair(MyBinaryTreeNode<T> node, MyBinaryTreeNode<T> parent) {
                this.node = node;
                this.parent = parent;
            }
        }

        Queue<Pair> pending = new LinkedList<>();
        pending.add(new Pair(root, null));

        MyBinaryTreeNode<T> nodeToDelete = null;
        MyBinaryTreeNode<T> lastNode = null;
        MyBinaryTreeNode<T> parentOfLastNode = null;
        while (!pending.isEmpty()) {
            Pair current = pending.remove();
            lastNode = current.node;
            parentOfLastNode = current.parent;

            if (lastNode.data.compareTo(data) == 0) {
                nodeToDelete = lastNode;
            }
            if (lastNode.left != null)
                pending.add(new Pair(lastNode.left, lastNode));
            if (lastNode.right != null)
                pending.add(new Pair(lastNode.right, lastNode));
        }

        if (nodeToDelete != null) {
            nodeToDelete.data = lastNode.data;
            
            // delete deepest rightmost node
            if (parentOfLastNode.right == lastNode) {
                parentOfLastNode.right = null;
            } else {
                parentOfLastNode.left = null;
            }
            size--;
        }
    }

    public boolean update(T obj, T replacement) {
        return update(obj, replacement, root);
    }

    public boolean contains(T data) {
        return contains(root, data);
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public boolean isBST(T min, T max) {
        return isBST(root, min, max);
    }

    public boolean isBST() {
        if (root == null) {
            return true;
        }
        if (root.data instanceof Integer) {
            @SuppressWarnings("unchecked")
            T min = (T) Integer.valueOf(Integer.MIN_VALUE);
            @SuppressWarnings("unchecked")
            T max = (T) Integer.valueOf(Integer.MAX_VALUE);
            return isBST(root, min, max);
        } else if (root.data instanceof Double) {
            @SuppressWarnings("unchecked")
            T min = (T) Double.valueOf(Double.NEGATIVE_INFINITY);
            @SuppressWarnings("unchecked")
            T max = (T) Double.valueOf(Double.POSITIVE_INFINITY);
            return isBST(root, min, max);
        } else if (root.data instanceof Short) {
            @SuppressWarnings("unchecked")
            T min = (T) Short.valueOf(Short.MIN_VALUE);
            @SuppressWarnings("unchecked")
            T max = (T) Short.valueOf(Short.MAX_VALUE);
            return isBST(root, min, max);
        } else if (root.data instanceof Long) {
            @SuppressWarnings("unchecked")
            T min = (T) Long.valueOf(Long.MIN_VALUE);
            @SuppressWarnings("unchecked")
            T max = (T) Long.valueOf(Long.MAX_VALUE);
            return isBST(root, min, max);
        } else if (root.data instanceof Float) {
            @SuppressWarnings("unchecked")
            T min = (T) Float.valueOf(Float.NEGATIVE_INFINITY);
            @SuppressWarnings("unchecked")
            T max = (T) Float.valueOf(Float.POSITIVE_INFINITY);
            return isBST(root, min, max);
        }
        throw new UnsupportedOperationException("isBST() without parameters only supports Integer, Double, Short, Long, and Float types");
    }
}

public class _15_BinaryTreeImpl {
    public static void main(String[] args) {
        System.out.println("========== Binary Tree Test Suite ==========\n");
        
        MyBinaryTree<Integer> tree = new MyBinaryTree<>();
        
        // Test 1: Create tree from array
        System.out.println("[Test 1] Create tree from array");
        Integer[] valList = { 1, 2, 3, 4, 5, null, null, null, null, null, null };
        tree.createTree(valList);
        System.out.println("Size: " + tree.getSize() + " (Expected: 5)");
        System.out.println("Height: " + tree.height() + " (Expected: 3)");
        System.out.println("Is empty: " + tree.isEmpty() + " (Expected: false)");
        
        // Test 2: Traversals
        System.out.println("\n[Test 2] Tree traversals");
        System.out.print("PreOrder:  ");
        tree.preOrder();
        System.out.print("InOrder:   ");
        tree.inOrder();
        System.out.print("PostOrder: ");
        tree.postOrder();
        System.out.print("LevelOrder: ");
        tree.levelOrder();
        
        // Test 3: printTree with strategy pattern
        System.out.println("\n[Test 3] Strategy pattern usage");
        System.out.print("Using PreOrder Strategy: ");
        tree.printTree(tree.new PreOrderTraversal());
        System.out.print("Using InOrder Strategy: ");
        tree.printTree(tree.new InOrderTraversal());
        
        // Test 4: Contains
        System.out.println("\n[Test 4] Contains operation");
        System.out.println("Contains 3: " + tree.contains(3) + " (Expected: true)");
        System.out.println("Contains 4: " + tree.contains(4) + " (Expected: true)");
        System.out.println("Contains 10: " + tree.contains(10) + " (Expected: false)");
        
        // Test 5: Insert operation
        System.out.println("\n[Test 5] Insert operation");
        tree.insert(6);
        tree.insert(7);
        System.out.println("Size after 2 inserts: " + tree.getSize() + " (Expected: 7)");
        System.out.println("Contains 6: " + tree.contains(6) + " (Expected: true)");
        System.out.println("Contains 7: " + tree.contains(7) + " (Expected: true)");
        System.out.print("Level Order after insert: ");
        tree.levelOrder();
        
        // Test 6: Delete operation
        System.out.println("\n[Test 6] Delete operation");
        tree.delete(4);
        System.out.println("Size after delete: " + tree.getSize() + " (Expected: 6)");
        System.out.println("Contains 4: " + tree.contains(4) + " (Expected: false)");
        System.out.print("Level Order after delete: ");
        tree.levelOrder();
        
        // Test 7: Delete non-existent
        System.out.println("\n[Test 7] Delete non-existent element");
        int sizeBefore = tree.getSize();
        tree.delete(100);
        System.out.println("Size unchanged: " + (sizeBefore == tree.getSize()) + " (Expected: true)");
        
        // Test 8: Clear operation
        System.out.println("\n[Test 8] Clear operation");
        tree.clear();
        System.out.println("Size after clear: " + tree.getSize() + " (Expected: 0)");
        System.out.println("Height after clear: " + tree.height() + " (Expected: 0)");
        System.out.println("Is empty: " + tree.isEmpty() + " (Expected: true)");
        
        // Test 9: Build with multiple inserts
        System.out.println("\n[Test 9] Build tree with inserts");
        MyBinaryTree<Integer> tree2 = new MyBinaryTree<>();
        tree2.insert(10);
        tree2.insert(20);
        tree2.insert(30);
        tree2.insert(40);
        System.out.println("Size: " + tree2.getSize() + " (Expected: 4)");
        System.out.print("Level Order: ");
        tree2.levelOrder();
        
        // Test 10: Single node operations
        System.out.println("\n[Test 10] Single node tree");
        MyBinaryTree<Integer> tree3 = new MyBinaryTree<>();
        tree3.insert(42);
        System.out.println("Size: " + tree3.getSize() + " (Expected: 1)");
        System.out.println("Height: " + tree3.height() + " (Expected: 1)");
        System.out.println("Contains 42: " + tree3.contains(42) + " (Expected: true)");
        tree3.delete(42);
        System.out.println("Size after delete: " + tree3.getSize() + " (Expected: 0)");
        System.out.println("Is empty: " + tree3.isEmpty() + " (Expected: true)");
        
        // Test 11: Perfect binary tree
        System.out.println("\n[Test 11] Perfect binary tree");
        MyBinaryTree<Integer> tree4 = new MyBinaryTree<>();
        Integer[] perfectTree = {1, 2, 3, 4, 5, 6, 7};
        tree4.createTree(perfectTree);
        System.out.println("Size: " + tree4.getSize() + " (Expected: 7)");
        System.out.println("Height: " + tree4.height() + " (Expected: 3)");
        System.out.print("PreOrder: ");
        tree4.preOrder();
        
        // Test 12: BST validation with Integer
        System.out.println("\n[Test 12] BST validation (Integer)");
        System.out.println("Is tree4 a BST: " + tree4.isBST() + " (Expected: false)");
        
        // Create actual BST
        MyBinaryTree<Integer> bst = new MyBinaryTree<>();
        Integer[] bstArray = {4, 2, 6, 1, 3, 5, 7};
        bst.createTree(bstArray);
        System.out.println("Is bst a BST: " + bst.isBST() + " (Expected: true)");
        System.out.print("InOrder of BST (should be sorted): ");
        bst.inOrder();
        
        // Test 13: BST validation with Double
        System.out.println("\n[Test 13] BST validation (Double)");
        MyBinaryTree<Double> doubleBST = new MyBinaryTree<>();
        Double[] doubleBSTArray = {4.5, 2.3, 6.7, 1.1, 3.4, 5.5, 7.8};
        doubleBST.createTree(doubleBSTArray);
        System.out.println("Is doubleBST a BST: " + doubleBST.isBST() + " (Expected: true)");
        System.out.print("InOrder of Double BST (sorted): ");
        doubleBST.inOrder();
        
        // Non-BST with Double
        MyBinaryTree<Double> doubleTree = new MyBinaryTree<>();
        Double[] doubleArray = {1.0, 2.0, 3.0, 4.0, 5.0};
        doubleTree.createTree(doubleArray);
        System.out.println("Is doubleTree a BST: " + doubleTree.isBST() + " (Expected: false)");
        
        // Test 14: BST validation with Short
        System.out.println("\n[Test 14] BST validation (Short)");
        MyBinaryTree<Short> shortBST = new MyBinaryTree<>();
        Short[] shortBSTArray = {(short)40, (short)20, (short)60, (short)10, (short)30, (short)50, (short)70};
        shortBST.createTree(shortBSTArray);
        System.out.println("Is shortBST a BST: " + shortBST.isBST() + " (Expected: true)");
        System.out.print("InOrder of Short BST (sorted): ");
        shortBST.inOrder();
        
        // Non-BST with Short
        MyBinaryTree<Short> shortTree = new MyBinaryTree<>();
        Short[] shortArray = {(short)1, (short)2, (short)3, (short)4, (short)5};
        shortTree.createTree(shortArray);
        System.out.println("Is shortTree a BST: " + shortTree.isBST() + " (Expected: false)");
        
        // Test 15: Delete root node
        System.out.println("\n[Test 15] Delete root node");
        MyBinaryTree<Integer> tree5 = new MyBinaryTree<>();
        Integer[] arr5 = {10, 20, 30, 40, 50};
        tree5.createTree(arr5);
        System.out.print("Before delete root: ");
        tree5.levelOrder();
        tree5.delete(10);
        System.out.println("Size after delete root: " + tree5.getSize() + " (Expected: 4)");
        System.out.print("After delete root: ");
        tree5.levelOrder();
        
        // Test 16: Delete deepest node itself
        System.out.println("\n[Test 16] Delete deepest node");
        MyBinaryTree<Integer> tree6 = new MyBinaryTree<>();
        Integer[] arr6 = {1, 2, 3, 4, 5};
        tree6.createTree(arr6);
        System.out.print("Before delete deepest: ");
        tree6.levelOrder();
        tree6.delete(5);
        System.out.println("Size after delete: " + tree6.getSize() + " (Expected: 4)");
        System.out.println("Contains 5: " + tree6.contains(5) + " (Expected: false)");
        System.out.print("After delete deepest: ");
        tree6.levelOrder();
        
        // Test 17: Multiple consecutive deletes
        System.out.println("\n[Test 17] Multiple consecutive deletes");
        MyBinaryTree<Integer> tree7 = new MyBinaryTree<>();
        Integer[] arr7 = {1, 2, 3, 4, 5, 6, 7};
        tree7.createTree(arr7);
        System.out.println("Initial size: " + tree7.getSize() + " (Expected: 7)");
        System.out.print("Initial tree: ");
        tree7.levelOrder();
        
        tree7.delete(1);
        System.out.println("After delete 1, size: " + tree7.getSize() + " (Expected: 6)");
        System.out.print("After delete 1: ");
        tree7.levelOrder();
        
        tree7.delete(3);
        System.out.println("After delete 3, size: " + tree7.getSize() + " (Expected: 5)");
        System.out.print("After delete 3: ");
        tree7.levelOrder();
        
        tree7.delete(5);
        System.out.println("After delete 5, size: " + tree7.getSize() + " (Expected: 4)");
        System.out.print("After delete 5: ");
        tree7.levelOrder();
        
        // Test 18: Delete until empty
        System.out.println("\n[Test 18] Delete until empty");
        MyBinaryTree<Integer> tree8 = new MyBinaryTree<>();
        tree8.insert(1);
        tree8.insert(2);
        tree8.insert(3);
        System.out.println("Initial size: " + tree8.getSize() + " (Expected: 3)");
        tree8.delete(1);
        System.out.println("After delete 1: " + tree8.getSize() + " (Expected: 2)");
        tree8.delete(3);
        System.out.println("After delete 3: " + tree8.getSize() + " (Expected: 1)");
        tree8.delete(2);
        System.out.println("After delete 2: " + tree8.getSize() + " (Expected: 0)");
        System.out.println("Is empty: " + tree8.isEmpty() + " (Expected: true)");
        
        // Test 19: Delete from empty tree
        System.out.println("\n[Test 19] Delete from empty tree");
        MyBinaryTree<Integer> tree9 = new MyBinaryTree<>();
        tree9.delete(10);
        System.out.println("Size remains: " + tree9.getSize() + " (Expected: 0)");
        System.out.println("Is empty: " + tree9.isEmpty() + " (Expected: true)");
        
        // Test 20: Height validation after operations
        System.out.println("\n[Test 20] Height validation");
        MyBinaryTree<Integer> tree10 = new MyBinaryTree<>();
        System.out.println("Empty tree height: " + tree10.height() + " (Expected: 0)");
        tree10.insert(1);
        System.out.println("Single node height: " + tree10.height() + " (Expected: 1)");
        tree10.insert(2);
        tree10.insert(3);
        System.out.println("3-node tree height: " + tree10.height() + " (Expected: 2)");
        tree10.insert(4);
        tree10.insert(5);
        tree10.insert(6);
        tree10.insert(7);
        System.out.println("Perfect 7-node tree height: " + tree10.height() + " (Expected: 3)");
        
        System.out.println("\n========== All Tests Complete ==========");
    }
}