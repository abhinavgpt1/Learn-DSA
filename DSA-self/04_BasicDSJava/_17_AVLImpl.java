// ref: 
// - https://www.geeksforgeeks.org/dsa/introduction-to-avl-tree/
// - https://www.geeksforgeeks.org/dsa/insertion-in-an-avl-tree/
// - https://www.geeksforgeeks.org/dsa/deletion-in-an-avl-tree/
//
// Comparison with Red Black Tree:
// The AVL tree and other self-balancing search trees like Red Black are useful to get all basic operations done in O(logn) time.
// The AVL trees are more balanced compared to Red-Black Trees, but they may cause more rotations during insertion and deletion.
// So if your application involves many frequent insertions and deletions, then Red Black trees should be preferred.
// And if the insertions and deletions are less frequent and search is the more frequent operation, then the AVL tree should be preferred over Red Black Tree.
// 
// Rule of thumb:
//   Reads dominate?  → AVL          (shorter tree = fewer comparisons per lookup)
//   Writes dominate? → Red-Black    (bounded rotations per mutation)
//   Not sure?        → Red-Black    (what most standard libraries default to)
//
// ============================================================

class MyAVLTreeNode<T> extends MyBinarySearchTreeNode<T> {
    int height;

    public MyAVLTreeNode(T key) {
        super(key);
        height = 1;
    }
}

class MyAVLTree<T extends Comparable<? super T>> extends MyBinarySearchTree<T> {

    // Accepts MyBinarySearchTreeNode<T> so children (node.left/node.right) pass without casts.
    // Reads the O(1) stored height field; cast is safe since all nodes are MyAVLTreeNode at runtime.
    private int height(MyBinarySearchTreeNode<T> node) {
        return node == null ? 0 : ((MyAVLTreeNode<T>) node).height;
    }

    /**
     * Diagram for right rotation - O(1) time complexity
     *
     *      y                               x
     *     / \     Right Rotation          / \
     *    x   T3   - - - - - - - >       T1   y
     *   / \                                 / \
     *  T1  T2                             T2  T3
     */
    private MyAVLTreeNode<T> rightRotate(MyAVLTreeNode<T> y) {
        MyAVLTreeNode<T> x = (MyAVLTreeNode<T>) y.left;
        MyAVLTreeNode<T> T2 = (MyAVLTreeNode<T>) x.right;

        // Perform rotation
        x.right = y;
        y.left = T2;

        // Update heights - O(1) time complexity
        // height() accepts MyBinarySearchTreeNode<T>, so children pass without casts.
        y.height = 1 + Math.max(height(y.left), height(y.right));
        x.height = 1 + Math.max(height(x.left), height(x.right));
        return x;
    }

    /**
     * Diagram for left rotation - O(1) time complexity
     *
     *      x                              y
     *     / \     Left Rotation          / \
     *    T1  y   - - - - - - - >       x  T3
     *       / \                       / \
     *      T2 T3                     T1 T2
     */
    private MyAVLTreeNode<T> leftRotate(MyAVLTreeNode<T> x) {
        MyAVLTreeNode<T> y = (MyAVLTreeNode<T>) x.right;
        MyAVLTreeNode<T> T2 = (MyAVLTreeNode<T>) y.left;

        // Perform rotation
        y.left = x;
        x.right = T2;

        // Update heights - O(1) time complexity
        x.height = 1 + Math.max(height(x.left), height(x.right));
        y.height = 1 + Math.max(height(y.left), height(y.right));
        return y;
    }

    private MyAVLTreeNode<T> insert(MyAVLTreeNode<T> node, T key) {
        // insert like normal BST
        if (node == null) {
            size++;
            return new MyAVLTreeNode<>(key);
        } else if (key.compareTo(node.data) <= 0) {
            node.left = insert((MyAVLTreeNode<T>) node.left, key);
        } else {
            node.right = insert((MyAVLTreeNode<T>) node.right, key);
        }

        // update height
        node.height = 1 + Math.max(height(node.left), height(node.right));

        // balancing
        int balance = height(node.left) - height(node.right);
        if (balance > 1) {
            // Left heavy subtree
            if (key.compareTo(node.left.data) <= 0) {
                // left left case - new key is inserted in left subtree of left child of node
                node = rightRotate(node);
            } else {
                // left right case
                node.left = leftRotate((MyAVLTreeNode<T>) node.left);
                node = rightRotate(node);
            }
        } else if (balance < -1) {
            // Right heavy subtree
            if (key.compareTo(node.right.data) > 0) {
                // right right case - new key is inserted in right subtree of right child of node
                node = leftRotate(node);
            } else {
                // right left case
                node.right = rightRotate((MyAVLTreeNode<T>) node.right);
                node = leftRotate(node);
            }
        }
        return node;
    }

    private MyAVLTreeNode<T> delete(MyAVLTreeNode<T> node, T key) {
        // delete like normal BST
        if (node == null) {
            return node;
        }

        if (key.compareTo(node.data) < 0) {
            node.left = delete((MyAVLTreeNode<T>) node.left, key);
        } else if (key.compareTo(node.data) > 0) {
            node.right = delete((MyAVLTreeNode<T>) node.right, key);
        } else {
            if (node.left == null) {
                node = (MyAVLTreeNode<T>) node.right;
                size--;
            } else if (node.right == null) {
                node = (MyAVLTreeNode<T>) node.left;
                size--;
            } else {
                // findMax() returns T (the value), not a node
                T temp = findMax(node.left);
                node.data = temp;
                node.left = delete((MyAVLTreeNode<T>) node.left, temp);
                // PTR: no size-- as it is done in the recursive delete call above
            }
        }
        if (node == null) {
            return node;
        }

        // update height
        node.height = 1 + Math.max(height(node.left), height(node.right));

        // balancing
        int balance = height(node.left) - height(node.right);
        if (balance > 1) {
            // Left heavy subtree
            if (height(node.left.left) >= height(node.left.right)) {
                // left left case = left sub-subtree is taller than right sub-subtree
                node = rightRotate(node);
            } else {
                // left right case
                node.left = leftRotate((MyAVLTreeNode<T>) node.left);
                node = rightRotate(node);
            }
        } else if (balance < -1) {
            // Right heavy subtree
            if (height(node.right.right) >= height(node.right.left)) {
                // right right case = right sub-subtree is taller than left sub-subtree
                node = leftRotate(node);
            } else {
                // right left case
                node.right = rightRotate((MyAVLTreeNode<T>) node.right);
                node = leftRotate(node);
            }
        }

        // Note: leftRotate() and rightRotate() are same for insertion and deletion,
        // only difference is in the technique to find out LL, LR, RR, RL and LR cases.
        //
        // In insertion, we can find out the case by comparing the key with the left and right child of node.
        //
        // But in deletion, we cannot find out the case by comparing the key with the
        // left and right child of node as the key is already deleted, so we need to
        // find out the case by comparing the height of left and right sub-subtrees of node.
        return node;
    }

    // -----------------Public methods-----------------

    // PTR: must override the no-arg height() from MyBinarySearchTree.
    // The parent's public height() calls its own PRIVATE height(node) — private methods
    // are not polymorphic, so without this override t.height() would bypass the O(1)
    // stored field above and fall back to O(n) recursion in the parent.
    @Override
    public int height() {
        return height(root);
    }

    @Override
    public void insert(T key) {
        root = insert((MyAVLTreeNode<T>) root, key);
    }

    @Override
    public void delete(T obj) {
        root = delete((MyAVLTreeNode<T>) root, obj);
    }
}

public class _17_AVLImpl {

    static int failures = 0;

    static void check(boolean condition, String msg) {
        if (condition) {
            System.out.println("  PASS — " + msg);
        } else {
            System.out.println("  FAIL — " + msg);
            failures++;
        }
    }

    // AVL height must satisfy h <= 1.44 * log2(n + 2)
    static boolean withinAVLHeightBound(int height, int n) {
        return height <= Math.ceil(1.44 * (Math.log(n + 2) / Math.log(2)));
    }

    public static void main(String[] args) {

        // ── 1. Single element ─────────────────────────────────────────────────
        System.out.println("1. Single element");
        {
            MyAVLTree<Integer> t = new MyAVLTree<>();
            t.insert(10);
            check(t.getSize() == 1, "size = 1");
            check(t.height() == 1, "height = 1");
            check(!t.isEmpty(), "not empty");
            check(t.contains(10), "contains 10");
            check(!t.contains(null), "contains null → false");
            check(t.isBalanced(), "balanced");
        }

        // ── 2. Ascending insert — triggers RR (left) rotations ───────────────
        System.out.println("\n2. Ascending insert 1-7 (RR rotations)");
        {
            MyAVLTree<Integer> t = new MyAVLTree<>();
            for (int i = 1; i <= 7; i++) t.insert(i);
            check(t.getSize() == 7, "size = 7");
            check(t.isBalanced(), "balanced after ascending insert");
            check(withinAVLHeightBound(t.height(), 7), "height within AVL bound");
            for (int i = 1; i <= 7; i++) check(t.contains(i), "contains " + i);
            System.out.print("  InOrder (Expected: 1 2 3 4 5 6 7): ");
            t.inOrder();
        }

        // ── 3. Descending insert — triggers LL (right) rotations ─────────────
        System.out.println("\n3. Descending insert 7-1 (LL rotations)");
        {
            MyAVLTree<Integer> t = new MyAVLTree<>();
            for (int i = 7; i >= 1; i--) t.insert(i);
            check(t.getSize() == 7, "size = 7");
            check(t.isBalanced(), "balanced after descending insert");
            check(withinAVLHeightBound(t.height(), 7), "height within AVL bound");
            System.out.print("  InOrder (Expected: 1 2 3 4 5 6 7): ");
            t.inOrder();
        }

        // ── 4. LR rotation: insert 3, 1, 2 ───────────────────────────────────
        System.out.println("\n4. LR rotation (3, 1, 2)");
        {
            MyAVLTree<Integer> t = new MyAVLTree<>();
            t.insert(3); t.insert(1); t.insert(2);
            check(t.isBalanced(), "balanced after LR case");
            check(t.height() == 2, "height = 2 after LR rotation");
            check(t.getSize() == 3, "size = 3");
        }

        // ── 5. RL rotation: insert 1, 3, 2 ───────────────────────────────────
        System.out.println("\n5. RL rotation (1, 3, 2)");
        {
            MyAVLTree<Integer> t = new MyAVLTree<>();
            t.insert(1); t.insert(3); t.insert(2);
            check(t.isBalanced(), "balanced after RL case");
            check(t.height() == 2, "height = 2 after RL rotation");
            check(t.getSize() == 3, "size = 3");
        }

        // ── 6. Delete leaf ────────────────────────────────────────────────────
        System.out.println("\n6. Delete leaf");
        {
            MyAVLTree<Integer> t = new MyAVLTree<>();
            for (int v : new int[]{4, 2, 6, 1, 3, 5, 7}) t.insert(v);
            t.delete(1);  // leaf
            check(!t.contains(1), "1 removed");
            check(t.getSize() == 6, "size = 6");
            check(t.isBalanced(), "balanced after leaf delete");
        }

        // ── 7. Delete node with one child ─────────────────────────────────────
        System.out.println("\n7. Delete node with one child");
        {
            MyAVLTree<Integer> t = new MyAVLTree<>();
            // After inserting 4,2,6,1 — node 2 has only left child 1
            for (int v : new int[]{4, 2, 6, 1}) t.insert(v);
            t.delete(2);
            check(!t.contains(2), "2 removed");
            check(t.contains(1), "1 still present");
            check(t.getSize() == 3, "size = 3");
            check(t.isBalanced(), "balanced after one-child delete");
        }

        // ── 8. Delete node with two children ──────────────────────────────────
        System.out.println("\n8. Delete node with two children");
        {
            MyAVLTree<Integer> t = new MyAVLTree<>();
            for (int v : new int[]{4, 2, 6, 1, 3, 5, 7}) t.insert(v);
            t.delete(4);  // root, has two children
            check(!t.contains(4), "4 removed");
            check(t.getSize() == 6, "size = 6");
            check(t.isBalanced(), "balanced after two-child delete");
            for (int v : new int[]{1, 2, 3, 5, 6, 7}) check(t.contains(v), "contains " + v);
        }

        // ── 9. Delete causing rebalance ───────────────────────────────────────
        System.out.println("\n9. Delete causing rebalance");
        {
            MyAVLTree<Integer> t = new MyAVLTree<>();
            // Insert ascending 1-7, delete left subtree elements to force rebalance
            for (int i = 1; i <= 7; i++) t.insert(i);
            t.delete(1); t.delete(2); t.delete(3);
            check(t.isBalanced(), "balanced after cascading deletes");
            check(t.getSize() == 4, "size = 4");
            check(withinAVLHeightBound(t.height(), 4), "height within AVL bound");
        }

        // ── 10. Delete non-existent key ───────────────────────────────────────
        System.out.println("\n10. Delete non-existent key");
        {
            MyAVLTree<Integer> t = new MyAVLTree<>();
            t.insert(5); t.insert(3); t.insert(7);
            t.delete(99);  // not in tree
            check(t.getSize() == 3, "size unchanged");
            check(t.isBalanced(), "still balanced");
            check(t.contains(5) && t.contains(3) && t.contains(7), "original elements intact");
        }

        // ── 11. Delete all elements ───────────────────────────────────────────
        System.out.println("\n11. Delete all elements");
        {
            MyAVLTree<Integer> t = new MyAVLTree<>();
            int[] vals = {4, 2, 6, 1, 3, 5, 7};
            for (int v : vals) t.insert(v);
            for (int v : vals) t.delete(v);
            check(t.isEmpty(), "tree is empty");
            check(t.getSize() == 0, "size = 0");
            check(t.height() == 0, "height = 0");
        }

        // ── 12. Clear ─────────────────────────────────────────────────────────
        System.out.println("\n12. Clear");
        {
            MyAVLTree<Integer> t = new MyAVLTree<>();
            for (int i = 1; i <= 5; i++) t.insert(i);
            t.clear();
            check(t.isEmpty(), "empty after clear");
            check(t.getSize() == 0, "size = 0");
            check(t.height() == 0, "height = 0 after clear");
            t.insert(10);  // still usable after clear
            check(t.getSize() == 1, "can insert after clear");
        }

        // ── 13. Duplicate insert ──────────────────────────────────────────────
        System.out.println("\n13. Duplicate insert (goes to left subtree, size grows)");
        {
            MyAVLTree<Integer> t = new MyAVLTree<>();
            t.insert(5); t.insert(5); t.insert(5);
            check(t.getSize() == 3, "size = 3 (duplicates stored)");
            check(t.isBalanced(), "balanced");
            System.out.print("  InOrder (Expected: 5 5 5): ");
            t.inOrder();
        }

        // ── 14. Large ascending insert — stress AVL height bound ──────────────
        System.out.println("\n14. Large ascending insert (n=20) — height bound");
        {
            MyAVLTree<Integer> t = new MyAVLTree<>();
            for (int i = 1; i <= 20; i++) t.insert(i);
            check(t.getSize() == 20, "size = 20");
            check(t.isBalanced(), "balanced");
            check(withinAVLHeightBound(t.height(), 20), "height within AVL bound for n=20");
        }

        // ── 15. String type ───────────────────────────────────────────────────
        System.out.println("\n15. String element type");
        {
            MyAVLTree<String> t = new MyAVLTree<>();
            t.insert("banana"); t.insert("apple"); t.insert("cherry");
            t.insert("date"); t.insert("elderberry");
            check(t.isBalanced(), "balanced string tree");
            check(t.contains("apple"), "contains apple");
            check(!t.contains("fig"), "not contains fig");
            System.out.print("  InOrder (Expected: apple banana cherry date elderberry): ");
            t.inOrder();
            t.delete("banana");
            check(!t.contains("banana"), "banana removed");
            check(t.getSize() == 4, "size = 4 after delete");
            check(t.isBalanced(), "balanced after delete");
        }

        // ── 16. Subtype — Dog inherits Comparable<Animal>, not Comparable<Dog> ──
        System.out.println("\n16. Subtype test — Dog extends Animal implements Comparable<Animal>");
        {
            // Animal implements Comparable<Animal>; Dog only inherits that — it does NOT
            // implement Comparable<Dog>. The <? super T> bound lets MyBinarySearchTree<Dog>
            // and MyAVLTree<Dog> compile and work correctly.
            class Animal implements Comparable<Animal> {
                String name;

                Animal(String name) {
                    this.name = name;
                }

                @Override
                public int compareTo(Animal o) {
                    return this.name.compareTo(o.name);
                }

                @Override
                public String toString() {
                    return name;
                }
            }

            class Dog extends Animal {
                Dog(String name) {
                    super(name);
                }
            }
            MyAVLTree<Dog> t = new MyAVLTree<>();
            t.insert(new Dog("Rex"));
            t.insert(new Dog("Buddy"));
            t.insert(new Dog("Max"));
            t.insert(new Dog("Ace"));
            check(t.getSize() == 4, "size = 4");
            check(t.isBalanced(), "balanced dog tree");
            check(t.contains(new Dog("Rex")), "contains Rex");
            check(!t.contains(new Dog("Fido")), "not contains Fido");
            System.out.print("  InOrder (Expected: Ace Buddy Max Rex): ");
            t.inOrder();
            t.delete(new Dog("Buddy"));
            check(!t.contains(new Dog("Buddy")), "Buddy removed");
            check(t.getSize() == 3, "size = 3 after delete");
            check(t.isBalanced(), "still balanced after delete");
        }

        // ── 17. height() on empty tree ─────────────────────────────────────
        System.out.println("\n17. height() on empty tree");
        {
            MyAVLTree<Integer> t = new MyAVLTree<>();
            check(t.height() == 0, "height = 0 on empty tree");
            check(t.isEmpty(), "isEmpty");
            t.insert(1);
            check(t.height() == 1, "height = 1 after first insert");
        }

        // ── 18. createTree() bulk insert ──────────────────────────────────────
        System.out.println("\n18. createTree() bulk insert");
        {
            MyAVLTree<Integer> t = new MyAVLTree<>();
            t.createTree(new Integer[]{5, 3, 7, 1, 4, 6, 8});
            check(t.getSize() == 7, "size = 7");
            check(t.isBalanced(), "balanced after createTree");
            check(withinAVLHeightBound(t.height(), 7), "height within AVL bound");
            for (int v : new int[]{1, 3, 4, 5, 6, 7, 8}) check(t.contains(v), "contains " + v);
            System.out.print("  InOrder (Expected: 1 3 4 5 6 7 8): ");
            t.inOrder();
        }

        // ── 19. update() — inherited from MyBinarySearchTree ─────────────────
        System.out.println("\n19. update() inherited from BST");
        {
            MyAVLTree<Integer> t = new MyAVLTree<>();
            for (int v : new int[]{4, 2, 6, 1, 3, 5, 7}) t.insert(v);
            check(t.update(3, 9), "update returned true");
            check(!t.contains(3), "old value 3 gone");
            check(t.contains(9), "new value 9 present");
            check(t.getSize() == 7, "size unchanged");
            check(t.isBalanced(), "balanced after update");
            check(!t.update(99, 100), "update of non-existent returns false");
            check(t.getSize() == 7, "size unchanged after failed update");
        }

        System.out.println(failures == 0 ? "\nAll tests PASSED" : "\n" + failures + " test(s) FAILED");
    }
}

/**
 * Output:
 * -------
 * 1. Single element
 *   PASS — size = 1
 *   PASS — height = 1
 *   PASS — not empty
 *   PASS — contains 10
 *   PASS — contains null → false
 *   PASS — balanced
 * 
 * 2. Ascending insert 1-7 (RR rotations)
 *   PASS — size = 7
 *   PASS — balanced after ascending insert
 *   PASS — height within AVL bound
 *   PASS — contains 1
 *   PASS — contains 2
 *   PASS — contains 3
 *   PASS — contains 4
 *   PASS — contains 5
 *   PASS — contains 6
 *   PASS — contains 7
 *   InOrder (Expected: 1 2 3 4 5 6 7): 1 2 3 4 5 6 7 
 * 
 * 3. Descending insert 7-1 (LL rotations)
 *   PASS — size = 7
 *   PASS — balanced after descending insert
 *   PASS — height within AVL bound
 *   InOrder (Expected: 1 2 3 4 5 6 7): 1 2 3 4 5 6 7 
 * 
 * 4. LR rotation (3, 1, 2)
 *   PASS — balanced after LR case
 *   PASS — height = 2 after LR rotation
 *   PASS — size = 3
 * 
 * 5. RL rotation (1, 3, 2)
 *   PASS — balanced after RL case
 *   PASS — height = 2 after RL rotation
 *   PASS — size = 3
 * 
 * 6. Delete leaf
 *   PASS — 1 removed
 *   PASS — size = 6
 *   PASS — balanced after leaf delete
 * 
 * 7. Delete node with one child
 *   PASS — 2 removed
 *   PASS — 1 still present
 *   PASS — size = 3
 *   PASS — balanced after one-child delete
 * 
 * 8. Delete node with two children
 *   PASS — 4 removed
 *   PASS — size = 6
 *   PASS — balanced after two-child delete
 *   PASS — contains 1
 *   PASS — contains 2
 *   PASS — contains 3
 *   PASS — contains 5
 *   PASS — contains 6
 *   PASS — contains 7
 * 
 * 9. Delete causing rebalance
 *   PASS — balanced after cascading deletes
 *   PASS — size = 4
 *   PASS — height within AVL bound
 * 
 * 10. Delete non-existent key
 *   PASS — size unchanged
 *   PASS — still balanced
 *   PASS — original elements intact
 * 
 * 11. Delete all elements
 *   PASS — tree is empty
 *   PASS — size = 0
 *   PASS — height = 0
 * 
 * 12. Clear
 *   PASS — empty after clear
 *   PASS — size = 0
 *   PASS — height = 0 after clear
 *   PASS — can insert after clear
 * 
 * 13. Duplicate insert (goes to left subtree, size grows)
 *   PASS — size = 3 (duplicates stored)
 *   PASS — balanced
 *   InOrder (Expected: 5 5 5): 5 5 5 
 * 
 * 14. Large ascending insert (n=20) — height bound
 *   PASS — size = 20
 *   PASS — balanced
 *   PASS — height within AVL bound for n=20
 * 
 * 15. String element type
 *   PASS — balanced string tree
 *   PASS — contains apple
 *   PASS — not contains fig
 *   InOrder (Expected: apple banana cherry date elderberry): apple banana cherry date elderberry 
 *   PASS — banana removed
 *   PASS — size = 4 after delete
 *   PASS — balanced after delete
 * 
 * 16. Subtype test — Dog extends Animal implements Comparable<Animal>
 *   PASS — size = 4
 *   PASS — balanced dog tree
 *   PASS — contains Rex
 *   PASS — not contains Fido
 *   InOrder (Expected: Ace Buddy Max Rex): Ace Buddy Max Rex 
 *   PASS — Buddy removed
 *   PASS — size = 3 after delete
 *   PASS — still balanced after delete
 * 
 * 17. height() on empty tree
 *   PASS — height = 0 on empty tree
 *   PASS — isEmpty
 *   PASS — height = 1 after first insert
 * 
 * 18. createTree() bulk insert
 *   PASS — size = 7
 *   PASS — balanced after createTree
 *   PASS — height within AVL bound
 *   PASS — contains 1
 *   PASS — contains 3
 *   PASS — contains 4
 *   PASS — contains 5
 *   PASS — contains 6
 *   PASS — contains 7
 *   PASS — contains 8
 *   InOrder (Expected: 1 3 4 5 6 7 8): 1 3 4 5 6 7 8 
 * 
 * 19. update() inherited from BST
 *   PASS — update returned true
 *   PASS — old value 3 gone
 *   PASS — new value 9 present
 *   PASS — size unchanged
 *   PASS — balanced after update
 *   PASS — update of non-existent returns false
 *   PASS — size unchanged after failed update
 * 
 * All tests PASSED
 */