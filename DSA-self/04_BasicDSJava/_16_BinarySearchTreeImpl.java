// Methods
// -------
// clear()                -> void
// contains(T data)       -> boolean
// createTree(T[] arr)    -> void (build tree from array)
// delete(T data)         -> void
// getSize()              -> int
// height()               -> int
// inOrder()              -> void
// insert(T data)         -> void
// isBalanced()           -> boolean (BST specific)
// isEmpty()              -> boolean
// levelOrder()           -> void
// postOrder()            -> void
// preOrder()             -> void
// printTree()            -> void
// update(T old, T new)   -> boolean (BST specific)

// Tip: Clean code can be written following SOLID if TreeNode and BinaryTree interfaces/abstract classes are created.

import java.util.LinkedList;
import java.util.Queue;

// Strategy pattern for different traversal algorithms
interface TraversalStrategy {
    void traverse();
}

class MyBinarySearchTreeNode<T> {
    MyBinarySearchTreeNode<T> left;
    MyBinarySearchTreeNode<T> right;
    T data;

    MyBinarySearchTreeNode(T data) {
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

// PTR: not allowing null storage in this impl, check TreeMap for that.
class MyBinarySearchTree<T extends Comparable<? super T>> {
    protected MyBinarySearchTreeNode<T> root;
    protected int size;

    // private methods
    private MyBinarySearchTreeNode<T> insert(T obj, MyBinarySearchTreeNode<T> node) {
        if (node == null) {
            size++;
            return new MyBinarySearchTreeNode<>(obj);
        } else if (obj.compareTo(node.data) <= 0) {
            node.left = insert(obj, node.left);
        } else {
            node.right = insert(obj, node.right);
        }
        return node;
    }

    private int height(MyBinarySearchTreeNode<T> node) {
        if (node == null)
            return 0;
        return 1 + Integer.max(height(node.left), height(node.right));
    }

    private boolean contains(T obj, MyBinarySearchTreeNode<T> node) {
        if (node == null || obj == null)
            return false;
        else if (node.data.compareTo(obj) == 0)
            return true;
        else if (obj.compareTo(node.data) <= 0)
            return contains(obj, node.left);
        else
            return contains(obj, node.right);
    }

    // can be optimised from T(n) = O(n) + 2*T(n/2) to O(n) using Pair containing
    // height(int), isBST(boolean) for subtree.
    private boolean isBalanced(MyBinarySearchTreeNode<T> node) {
        if (node == null)
            return true;
        return Math.abs(height(node.left) - height(node.right)) <= 1 && isBalanced(node.left) && isBalanced(node.right);
    }

    private void clear(MyBinarySearchTreeNode<T> node) {
        if (node == null)
            return;
        clear(node.left);
        clear(node.right);
        node.delete();
    }

    private MyBinarySearchTreeNode<T> delete(T obj, MyBinarySearchTreeNode<T> node) {
        if (node == null)
            return node;

        if (node.data.compareTo(obj) == 0) {
            if (node.left == null) {
                MyBinarySearchTreeNode<T> ans = node.right;
                node.delete(); // it's a good practice, but not mandatory here as it'll be garbage collected
                               // once control goes to parent method in stack.
                size--;
                return ans;
            } else if (node.right == null) {
                MyBinarySearchTreeNode<T> ans = node.left;
                node.delete();
                size--;
                return ans;
            } else {
                // find replacement
                T tmpValue = findMax(node.left);
                node.data = tmpValue;
                node.left = delete(tmpValue, node.left);

                // PTR: no size-- as it is done in the recursive delete call above
                return node;
            }
        } else if (obj.compareTo(node.data) <= 0) {
            node.left = delete(obj, node.left);
        } else {
            node.right = delete(obj, node.right);
        }
        return node;
    }

    class PreOrderTraversal implements TraversalStrategy {

        MyBinarySearchTreeNode<T> node;

        PreOrderTraversal() {
            this.node = root;
        }

        private void traverse(MyBinarySearchTreeNode<T> node) {
            if (node == null)
                return;
            System.out.print(node.data + " ");
            traverse(node.left);
            traverse(node.right);
        }

        @Override
        public void traverse() {
            traverse(node);
            System.out.println();
        }

    }

    class InOrderTraversal implements TraversalStrategy {

        MyBinarySearchTreeNode<T> node;

        InOrderTraversal() {
            this.node = root;
        }

        private void traverse(MyBinarySearchTreeNode<T> node) {
            if (node == null)
                return;
            traverse(node.left);
            System.out.print(node.data + " ");
            traverse(node.right);
        }

        @Override
        public void traverse() {
            traverse(node);
            System.out.println();
        }

    }

    class PostOrderTraversal implements TraversalStrategy {

        MyBinarySearchTreeNode<T> node;

        PostOrderTraversal() {
            this.node = root;
        }

        private void traverse(MyBinarySearchTreeNode<T> node) {
            if (node == null)
                return;
            traverse(node.left);
            traverse(node.right);
            System.out.print(node.data + " ");
        }

        @Override
        public void traverse() {
            traverse(node);
            System.out.println();
        }

    }

    class LevelOrderTraversal implements TraversalStrategy {

        MyBinarySearchTreeNode<T> node;

        LevelOrderTraversal() {
            this.node = root;
        }

        @Override
        public void traverse() {
            if (node == null) {
                System.out.println("Tree is empty.");
                return;
            }
            Queue<MyBinarySearchTreeNode<T>> pending = new LinkedList<>();
            pending.add(node);
            pending.add(null);
            while (!pending.isEmpty()) {
                MyBinarySearchTreeNode<T> first = pending.remove();
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

    // public methods
    public MyBinarySearchTree() {
        root = null;
        size = 0;
    }

    public void createTree(T[] valList) {
        for (T obj : valList) {
            if (obj == null)
                continue;
            insert(obj);
        }
    }

    public void insert(T obj) {
        root = insert(obj, root);
    }

    public void delete(T obj) {
        root = delete(obj, root);
    }

    public boolean update(T obj, T replacement) {
        // Update by deleting old value and inserting new value to maintain BST property
        if (!contains(obj, root))
            return false;

        // PTR: use public methods to maintain size correctly
        delete(obj);
        insert(replacement);
        return true;
    }

    public T findMax(MyBinarySearchTreeNode<T> node) {
        if (node == null)
            return null;
        if (node.right != null)
            return findMax(node.right);
        return node.data;
    }

    public int height() {
        return height(root);
    }

    public boolean contains(T obj) {
        return contains(obj, root);
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

    public int getSize() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public boolean isBalanced() {
        return isBalanced(root);
    }
}

public class _16_BinarySearchTreeImpl {

    static void check(boolean condition, String msg) {
        System.out.println("  " + (condition ? "PASS" : "FAIL") + " — " + msg);
    }

    public static void main(String[] args) {
        System.out.println("========== BST Test Suite ==========\n");

        // Test 1: Basic creation and insertion
        System.out.println("[Test 1] Create tree from array");
        MyBinarySearchTree<Integer> tree = new MyBinarySearchTree<>();
        Integer[] valList = { 5, 3, 1, 4, 7, 6, 8 };
        tree.createTree(valList);
        check(tree.getSize() == 7, "Size is 7");
        check(tree.height() == 3, "Height is 3");
        check(tree.isBalanced(), "Is balanced");
        System.out.print("  Level Order: ");
        tree.levelOrder();

        // Test 2: All traversal methods
        System.out.println("\n[Test 2] All Traversals");
        System.out.print("  PreOrder  (Expected: 5 3 1 4 7 6 8): ");
        tree.preOrder();
        System.out.print("  InOrder   (Expected: 1 3 4 5 6 7 8): ");
        tree.inOrder();
        System.out.print("  PostOrder (Expected: 1 4 3 6 8 7 5): ");
        tree.postOrder();

        // Test 3: Contains method
        System.out.println("\n[Test 3] Contains method");
        check(tree.contains(4), "Contains 4");
        check(!tree.contains(10), "Does not contain 10");
        check(!tree.contains(null), "Contains null → false");

        // Test 4: Update method
        System.out.println("\n[Test 4] Update method");
        check(tree.update(4, 9), "Update 4→9 returns true");
        System.out.print("  InOrder after update (Expected: 1 3 5 6 7 8 9): ");
        tree.inOrder();
        check(tree.getSize() == 7, "Size unchanged after update");
        check(!tree.update(100, 200), "Update non-existent 100→200 returns false");

        // Test 5: Delete operations
        System.out.println("\n[Test 5] Delete operations");
        tree.delete(9);  // leaf
        check(tree.getSize() == 6, "Size after deleting leaf (9) = 6");
        tree.delete(7);  // node with two children
        check(tree.getSize() == 5, "Size after deleting node with two children (7) = 5");
        tree.delete(5);  // root
        check(tree.getSize() == 4, "Size after deleting root (5) = 4");
        System.out.print("  Level Order after 3 deletes: ");
        tree.levelOrder();

        // Test 6: Insert after deletions
        System.out.println("\n[Test 6] Insert after deletions");
        tree.insert(10);
        tree.insert(2);
        check(tree.getSize() == 6, "Size after 2 inserts = 6");
        System.out.print("  Level Order: ");
        tree.levelOrder();

        // Test 7: Empty tree operations
        System.out.println("\n[Test 7] Empty tree operations");
        MyBinarySearchTree<Integer> emptyTree = new MyBinarySearchTree<>();
        check(emptyTree.isEmpty(), "isEmpty() = true");
        check(emptyTree.height() == 0, "Height = 0");
        check(!emptyTree.contains(5), "Contains 5 → false");
        System.out.print("  Level Order: ");
        emptyTree.levelOrder();

        // Test 8: Single element tree
        System.out.println("\n[Test 8] Single element tree");
        MyBinarySearchTree<Integer> singleTree = new MyBinarySearchTree<>();
        singleTree.insert(42);
        check(singleTree.getSize() == 1, "Size = 1");
        check(singleTree.height() == 1, "Height = 1");
        check(singleTree.isBalanced(), "Is balanced");
        check(!singleTree.isEmpty(), "isEmpty() = false");

        // Test 9: Unbalanced tree (ascending insertion → right-skewed)
        System.out.println("\n[Test 9] Unbalanced tree (linear)");
        MyBinarySearchTree<Integer> unbalancedTree = new MyBinarySearchTree<>();
        unbalancedTree.createTree(new Integer[] { 1, 2, 3, 4, 5, 6, 7 });
        check(unbalancedTree.height() == 7, "Height = 7");
        check(!unbalancedTree.isBalanced(), "Is NOT balanced");
        System.out.print("  InOrder (Expected: 1 2 3 4 5 6 7): ");
        unbalancedTree.inOrder();

        // Test 10: Clear operation
        System.out.println("\n[Test 10] Clear operation");
        tree.clear();
        check(tree.getSize() == 0, "Size after clear = 0");
        check(tree.isEmpty(), "isEmpty() = true after clear");
        check(!tree.contains(3), "Contains 3 → false after clear");

        // Test 11: Strategy pattern with printTree
        System.out.println("\n[Test 11] Strategy pattern usage");
        MyBinarySearchTree<Integer> strategyTree = new MyBinarySearchTree<>();
        strategyTree.createTree(new Integer[] { 4, 2, 6, 1, 3, 5, 7 });
        System.out.print("  PreOrder Strategy  (Expected: 4 2 1 3 6 5 7): ");
        strategyTree.printTree(strategyTree.new PreOrderTraversal());
        System.out.print("  InOrder Strategy   (Expected: 1 2 3 4 5 6 7): ");
        strategyTree.printTree(strategyTree.new InOrderTraversal());
        System.out.print("  PostOrder Strategy (Expected: 1 3 2 5 7 6 4): ");
        strategyTree.printTree(strategyTree.new PostOrderTraversal());

        // Test 12: String BST
        System.out.println("\n[Test 12] BST with Strings");
        MyBinarySearchTree<String> stringTree = new MyBinarySearchTree<>();
        stringTree.createTree(new String[] { "dog", "cat", "elephant", "ant", "bear", "fox" });
        check(stringTree.getSize() == 6, "Size = 6");
        check(stringTree.contains("cat"), "Contains 'cat'");
        check(!stringTree.contains("zebra"), "Does not contain 'zebra'");
        System.out.print("  InOrder (Expected: ant bear cat dog elephant fox): ");
        stringTree.inOrder();

        // Test 13: Duplicate handling (duplicates go left, so all 3 are stored)
        System.out.println("\n[Test 13] Duplicate handling");
        MyBinarySearchTree<Integer> dupTree = new MyBinarySearchTree<>();
        dupTree.insert(5);
        dupTree.insert(5);
        dupTree.insert(5);
        check(dupTree.getSize() == 3, "Size after inserting 5 three times = 3");
        System.out.print("  InOrder (Expected: 5 5 5): ");
        dupTree.inOrder();

        // Test 14: Delete non-existent element
        System.out.println("\n[Test 14] Delete non-existent element");
        MyBinarySearchTree<Integer> testTree = new MyBinarySearchTree<>();
        testTree.createTree(new Integer[] { 5, 3, 7 });
        int sizeBefore = testTree.getSize();
        testTree.delete(99);
        check(testTree.getSize() == sizeBefore, "Size unchanged after deleting non-existent 99");

        // Test 15: Subtype with inherited Comparable
        // Dog does NOT implement Comparable<Dog>; it inherits Comparable<Animal>.
        // This test ONLY compiles/runs with <T extends Comparable<? super T>>.
        System.out.println("\n[Test 15] Subtype with inherited Comparable<Animal> — Dog extends Animal");
        {
            class Animal implements Comparable<Animal> {
                String name;
                Animal(String name) { this.name = name; }

                @Override
                public int compareTo(Animal o) { return this.name.compareTo(o.name); }

                @Override
                public String toString() { return name; }
            }
            class Dog extends Animal {
                Dog(String name) { super(name); }
            }
            MyBinarySearchTree<Dog> dogTree = new MyBinarySearchTree<>();
            dogTree.insert(new Dog("Rex"));
            dogTree.insert(new Dog("Buddy"));
            dogTree.insert(new Dog("Max"));
            check(dogTree.getSize() == 3, "Size = 3");
            check(dogTree.contains(new Dog("Rex")), "Contains Rex");
            check(!dogTree.contains(new Dog("Fido")), "Does not contain Fido");
            System.out.print("  InOrder (Expected: Buddy Max Rex): ");
            dogTree.inOrder();
        }

        System.out.println("\n========== All Tests Complete ==========");
    }
}

/**
 * Output:
 * -------
 * ========== BST Test Suite ==========
 * 
 * [Test 1] Create tree from array
 *   PASS — Size is 7
 *   PASS — Height is 3
 *   PASS — Is balanced
 *   Level Order: 5 
 * 3 7 
 * 1 4 6 8 
 * 
 * [Test 2] All Traversals
 *   PreOrder  (Expected: 5 3 1 4 7 6 8): 5 3 1 4 7 6 8 
 *   InOrder   (Expected: 1 3 4 5 6 7 8): 1 3 4 5 6 7 8 
 *   PostOrder (Expected: 1 4 3 6 8 7 5): 1 4 3 6 8 7 5 
 * 
 * [Test 3] Contains method
 *   PASS — Contains 4
 *   PASS — Does not contain 10
 *   PASS — Contains null → false
 * 
 * [Test 4] Update method
 *   PASS — Update 4→9 returns true
 *   InOrder after update (Expected: 1 3 5 6 7 8 9): 1 3 5 6 7 8 9 
 *   PASS — Size unchanged after update
 *   PASS — Update non-existent 100→200 returns false
 * 
 * [Test 5] Delete operations
 *   PASS — Size after deleting leaf (9) = 6
 *   PASS — Size after deleting node with two children (7) = 5
 *   PASS — Size after deleting root (5) = 4
 *   Level Order after 3 deletes: 3 
 * 1 6 
 * 8 
 * 
 * [Test 6] Insert after deletions
 *   PASS — Size after 2 inserts = 6
 *   Level Order: 3 
 * 1 6 
 * 2 8 
 * 10 
 * 
 * [Test 7] Empty tree operations
 *   PASS — isEmpty() = true
 *   PASS — Height = 0
 *   PASS — Contains 5 → false
 *   Level Order: Tree is empty.
 * 
 * [Test 8] Single element tree
 *   PASS — Size = 1
 *   PASS — Height = 1
 *   PASS — Is balanced
 *   PASS — isEmpty() = false
 * 
 * [Test 9] Unbalanced tree (linear)
 *   PASS — Height = 7
 *   PASS — Is NOT balanced
 *   InOrder (Expected: 1 2 3 4 5 6 7): 1 2 3 4 5 6 7 
 * 
 * [Test 10] Clear operation
 *   PASS — Size after clear = 0
 *   PASS — isEmpty() = true after clear
 *   PASS — Contains 3 → false after clear
 * 
 * [Test 11] Strategy pattern usage
 *   PreOrder Strategy  (Expected: 4 2 1 3 6 5 7): 4 2 1 3 6 5 7 
 *   InOrder Strategy   (Expected: 1 2 3 4 5 6 7): 1 2 3 4 5 6 7 
 *   PostOrder Strategy (Expected: 1 3 2 5 7 6 4): 1 3 2 5 7 6 4 
 * 
 * [Test 12] BST with Strings
 *   PASS — Size = 6
 *   PASS — Contains 'cat'
 *   PASS — Does not contain 'zebra'
 *   InOrder (Expected: ant bear cat dog elephant fox): ant bear cat dog elephant fox 
 * 
 * [Test 13] Duplicate handling
 *   PASS — Size after inserting 5 three times = 3
 *   InOrder (Expected: 5 5 5): 5 5 5 
 * 
 * [Test 14] Delete non-existent element
 *   PASS — Size unchanged after deleting non-existent 99
 * 
 * [Test 15] Subtype with inherited Comparable<Animal> — Dog extends Animal
 *   PASS — Size = 3
 *   PASS — Contains Rex
 *   PASS — Does not contain Fido
 *   InOrder (Expected: Buddy Max Rex): Buddy Max Rex 
 * 
 * ========== All Tests Complete ==========
 */