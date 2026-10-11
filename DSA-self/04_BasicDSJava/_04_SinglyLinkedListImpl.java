// UML contains a LinkedList class and Node class.
// LinkedList has association with Node class.
// Node has self association with itself.

// SinglyLinkedList features (without using back pointer)
// ------------------------------------------------------
// addFirst(T obj)      -> boolean
// addLast(T obj)       -> boolean
// add(index, T obj)    -> boolean
// removeFirst()        -> T obj
// removeLast()         -> T obj
// remove(index)        -> T obj
// remove(T obj)        -> boolean
// getFirst()           -> T obj
// getLast()            -> T obj
// get(index)           -> T obj
// set(index, T obj)    -> T obj : returns old value
// size()               -> int
// isEmpty()            -> boolean
// contains(T obj)      -> boolean
// indexOf(T obj)       -> int
// clear()              -> void
// print()              -> void

// qq: will linkedList be deleted if head = null?
// ans: yes. Unlike c++ we don't need to free up every node. When head node becomes unreachable, all nodes become unreachable and GC will reclaim memory.
// PTR: if there is an external ref to middle node, nodes from middle onwards will not be deleted.

class Node<T> {
    private T data;
    private Node<T> next;

    Node(T data) {
        this.data = data;
        this.next = null;
    }

    public T getData() {
        return data;
    }

    public void setData(T data) {
        this.data = data;
    }

    public Node<T> getNext() {
        return next;
    }

    public void setNext(Node<T> next) {
        this.next = next;
    }

    public String toString() {
        return data.toString();
    }
}

class SinglyLinkedList<T> {
    private Node<T> head;
    private int size;

    public SinglyLinkedList() {
        this.head = null;
        this.size = 0;
    }

    // optional implementation
    class SLLIterator {
        private Node<T> itr;

        SLLIterator(Node<T> head) {
            itr = head;
        }

        boolean hasNext() {
            if (itr == null || itr.getNext() == null) // PTR: This will not iterate a LL with 1 element when used in a
                                                      // traditional way - while(hasNext()) { next(); }
                return false;
            return true;
        }

        Node<T> next() {
            if (itr != null)
                itr = itr.getNext();
            return itr;
        }
    }

    // private methods
    private void checkIndexWithinBounds(int index) throws IndexOutOfBoundsException {
        if (index < 0 || index >= size)
            throw new IndexOutOfBoundsException("Index is out of bound, index:" + index + ", sizeLL: " + size);
        // => ensures list is not empty
    }

    // public methods
    public SLLIterator getSLLIterator() {
        return new SLLIterator(head);
    }

    public boolean addFirst(T obj) {
        if (isLoop())
            return false;
        // covers head == null case as well
        Node<T> newNode = new Node<T>(obj);
        newNode.setNext(head);
        head = newNode;
        size++;
        return true;
    }

    // This entire code can be replaced by add(size, obj)
    public boolean addLast(T obj) {
        if (isLoop())
            return false;
        Node<T> newNode = new Node<T>(obj);
        if (head == null) {
            head = newNode;
        } else {
            // Traditional non-iterator dp way
            // Node<T> itr = head;
            // while (itr.getNext() != null) {
            // itr = itr.getNext();
            // }
            // itr.setNext(newNode);

            Node<T> currNode = head;
            SLLIterator iter = getSLLIterator();
            while (iter.hasNext()) {
                currNode = iter.next();
            }
            currNode.setNext(newNode);
        }
        size++;
        return true;
    }

    public boolean add(int index, T obj) {
        if (index < 0 || index > size)
            throw new IndexOutOfBoundsException("Index is out of bound, index:" + index + ", sizeLL: " + size);
        if (index == 0)
            return addFirst(obj);
        if (isLoop())
            return false;
        Node<T> newNode = new Node<T>(obj);

        // Traditional way without iterator pattern
        Node<T> prevNode = null;
        Node<T> currNode = head;
        int i = 0;
        while (i < index) {
            prevNode = currNode;
            currNode = currNode.getNext();
            i++;
        }
        prevNode.setNext(newNode);
        newNode.setNext(currNode);
        size++;
        return true;
    }

    public T removeFirst() {
        if (isLoop() || isEmpty())
            return null;
        T result = head.getData();
        head = head.getNext();
        size--;
        return result;
    }

    public T removeLast() {
        return remove(size - 1);
    }

    public T remove(int index) {
        if (isLoop())
            return null;
        checkIndexWithinBounds(index);
        if (index == 0)
            return removeFirst();

        Node<T> prevNode = null;
        Node<T> currNode = head;
        int i = 0;
        while (i < index) {
            prevNode = currNode;
            currNode = currNode.getNext();
            i++;
        }

        prevNode.setNext(currNode.getNext());
        // No, GC will NOT collect currNode at this moment because since currNode (local
        // variable) holds reference to it.
        // Only after this method returns and local variable goes out of scope, it
        // becomes eligible for GC (assuming no other refs)
        // if you want early release, then make currNode = null;
        currNode.setNext(null); // IMP. to avoid iteration
        size--;
        return currNode.getData();
    }

    public boolean remove(T obj) {
        if (isLoop() || isEmpty() || !contains(obj))
            return false;
        Node<T> prevNode = null;
        Node<T> currNode = head;

        while (currNode != null) {
            if (currNode.getData().equals(obj))
                break;

            prevNode = currNode;
            currNode = currNode.getNext();
        }
        if (prevNode == null) {
            removeFirst(); // size-- happens inside removeFirst()
        } else {
            prevNode.setNext(currNode.getNext());
            currNode.setNext(null);
            size--;
        }
        return true;
    }

    public T getFirst() {
        return get(0);
    }

    public T getLast() {
        return get(size - 1);
    }

    public T get(int index) {
        if (isLoop())
            return null;
        checkIndexWithinBounds(index); // ensures list is not empty
        Node<T> currNode = head;
        int i = 0;
        while (i < index) {
            currNode = currNode.getNext();
            i++;
        }
        return currNode.getData();
    }

    public T set(int index, T obj) {
        if (isLoop())
            return null;
        checkIndexWithinBounds(index); // ensures list is not empty
        Node<T> currNode = head;
        int i = 0;
        while (i < index) {
            currNode = currNode.getNext();
            i++;
        }
        T oldValue = currNode.getData();
        currNode.setData(obj);
        return oldValue;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public boolean contains(T obj) {
        if (isLoop())
            return false;

        Node<T> itr = head;
        while (itr != null) {
            if (itr.getData().equals(obj)) // assumming LL contains non-null elements only, otherwise need to handle
                                           // null case
                return true;
            itr = itr.getNext();
        }
        return false;
    }

    public int indexOf(T obj) {
        if (isLoop())
            return Integer.MAX_VALUE;

        Node<T> itr = head;
        int i = 0;
        while (itr != null) {
            if (itr.getData().equals(obj)) {
                return i;
            }
            itr = itr.getNext();
            i++;
        }
        return -1;
    }

    public void clear() {
        // works if there's a loop as well
        Node<T> itr = head;
        while (itr != null) {
            Node<T> nextNode = itr.getNext();
            itr.setNext(null); // break link to help GC
            itr.setData(null); // optional
            itr = nextNode;
        }

        // below code is enough to delete the entire linked list, but a good practice is
        // to break links between nodes as shown above.
        head = null; // GC will reclaim all nodes
        size = 0;
    }

    public void print() {
        if (isLoop()) {
            System.out.println("Cannot print as list contains loop");
            return;
        }
        Node<T> itr = head;
        while (itr != null) {
            System.out.println(itr.getData() + " ");
            itr = itr.getNext();
        }
    }

    public boolean isLoop() {
        // Brahma Algorithm / Floyd's Cycle-Finding Algorithm aka Tortoise and Hare Algo
        Node<T> slow = head;
        Node<T> fast = head;
        while (fast != null && fast.getNext() != null) {
            slow = slow.getNext();
            fast = fast.getNext().getNext();
            if (slow == fast)
                return true;
        }
        return false;
        // IMP: PTR: Always initialise fast and slow to same place for Brahma's algo.
        // (NOT FOR FINDING LEFT MIDDLE ELEMENT OF LL)
        // PTR: To get the starting node of loop, reset slow to head and traverse both
        // slow and fast one step at a time.
        // The node where they meet is the starting node of loop.
    }

    public T getMiddleData() {
        if (isLoop() || isEmpty())
            return null;
        Node<T> slow = head;
        Node<T> fast = head;
        while (fast != null && fast.getNext() != null) {
            slow = slow.getNext();
            fast = fast.getNext().getNext();
        }
        return slow.getData();

        // PTR: returns the right middle element in case of even number of nodes
        // To return left middle element, either
        // * initialize fast = head.getNext() at start
        // * modify the loop condition to while(fast.getNext() != null &&
        // fast.getNext().getNext() != null)
    }
}

public class _04_SinglyLinkedListImpl {
    public static void main(String[] args) {
        SinglyLinkedList<Integer> list = new SinglyLinkedList<>();

        // Test 1: Basic addFirst and addLast
        System.out.println("=== Test 1: Basic add operations ===");
        list.addFirst(10);
        list.addLast(20);
        list.addFirst(5);
        list.addLast(30);
        System.out.println("Size: " + list.size()); // Expected: 4
        System.out.println("First: " + list.getFirst()); // Expected: 5
        System.out.println("Last: " + list.getLast()); // Expected: 30

        // Test 2: add at specific index
        System.out.println("\n=== Test 2: add at index ===");
        list.add(2, 15); // List: [5, 10, 15, 20, 30]
        System.out.println("Size: " + list.size()); // Expected: 5
        System.out.println("Element at index 2: " + list.get(2)); // Expected: 15

        // Test 3: get operations
        System.out.println("\n=== Test 3: get operations ===");
        System.out.println("get(0): " + list.get(0)); // Expected: 5
        System.out.println("get(1): " + list.get(1)); // Expected: 10
        System.out.println("get(2): " + list.get(2)); // Expected: 15
        System.out.println("get(3): " + list.get(3)); // Expected: 20
        System.out.println("get(4): " + list.get(4)); // Expected: 30

        // Test 4: contains and indexOf
        System.out.println("\n=== Test 4: contains and indexOf ===");
        System.out.println("Contains 15: " + list.contains(15)); // Expected: true
        System.out.println("Contains 100: " + list.contains(100)); // Expected: false
        System.out.println("indexOf(15): " + list.indexOf(15)); // Expected: 2
        System.out.println("indexOf(100): " + list.indexOf(100)); // Expected: -1

        // Test 5: set operation
        System.out.println("\n=== Test 5: set operation ===");
        Integer oldValue = list.set(2, 25);
        System.out.println("Old value at index 2: " + oldValue); // Expected: 15
        System.out.println("New value at index 2: " + list.get(2)); // Expected: 25

        // Test 6: remove operations
        System.out.println("\n=== Test 6: remove by index ===");
        Integer removed = list.remove(2);
        System.out.println("Removed element: " + removed); // Expected: 25
        System.out.println("Size: " + list.size()); // Expected: 4

        // Test 7: remove by object
        System.out.println("\n=== Test 7: remove by object ===");
        boolean removeResult = list.remove(Integer.valueOf(20));
        System.out.println("Removed 20: " + removeResult); // Expected: true
        System.out.println("Size: " + list.size()); // Expected: 3
        System.out.println("Contains 20: " + list.contains(20)); // Expected: false

        // Test 8: removeFirst and removeLast
        System.out.println("\n=== Test 8: removeFirst and removeLast ===");
        Integer first = list.removeFirst();
        Integer last = list.removeLast();
        System.out.println("Removed first: " + first); // Expected: 5
        System.out.println("Removed last: " + last); // Expected: 30
        System.out.println("Size: " + list.size()); // Expected: 1
        System.out.println("Remaining element: " + list.getFirst()); // Expected: 10

        // Test 9: isEmpty
        System.out.println("\n=== Test 9: isEmpty ===");
        System.out.println("Is empty: " + list.isEmpty()); // Expected: false
        list.clear();
        System.out.println("Is empty after clear: " + list.isEmpty()); // Expected: true
        System.out.println("Size after clear: " + list.size()); // Expected: 0

        // Test 10: Build new list for middle element test
        System.out.println("\n=== Test 10: getMiddleData ===");
        list.addLast(1);
        list.addLast(2);
        list.addLast(3);
        list.addLast(4);
        list.addLast(5);
        System.out.println("Middle of [1,2,3,4,5]: " + list.getMiddleData()); // Expected: 3
        list.addLast(6);
        System.out.println("Middle of [1,2,3,4,5,6]: " + list.getMiddleData()); // Expected: 4 (right middle)

        // Test 11: Exception handling
        System.out.println("\n=== Test 11: Exception handling ===");
        list.clear();
        list.addLast(100);
        try {
            list.get(5);
            System.out.println("ERROR: Should have thrown exception");
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Correctly threw IndexOutOfBoundsException for get(5)");
        }

        try {
            list.add(10, 999);
            System.out.println("ERROR: Should have thrown exception");
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Correctly threw IndexOutOfBoundsException for add(10, 999)");
        }

        // Test 12: Remove from single element list
        System.out.println("\n=== Test 12: Single element operations ===");
        list.clear();
        list.addFirst(42);
        System.out.println("Size: " + list.size()); // Expected: 1
        System.out.println("First element: " + list.getFirst()); // Expected: 42
        boolean removed12 = list.remove(Integer.valueOf(42));
        System.out.println("Removed 42: " + removed12); // Expected: true
        System.out.println("Is empty: " + list.isEmpty()); // Expected: true

        // Test 13: Large list operations
        System.out.println("\n=== Test 13: Large list operations ===");
        list.clear();
        for (int i = 1; i <= 10; i++) {
            list.addLast(i * 10);
        }
        System.out.println("Size after adding 10 elements: " + list.size()); // Expected: 10
        System.out.println("First: " + list.getFirst()); // Expected: 10
        System.out.println("Last: " + list.getLast()); // Expected: 100
        System.out.println("Middle: " + list.getMiddleData()); // Expected: 60 (right middle)

        // Test 14: Remove non-existent element
        System.out.println("\n=== Test 14: Remove non-existent element ===");
        boolean removed14 = list.remove(Integer.valueOf(999));
        System.out.println("Remove 999 (not in list): " + removed14); // Expected: false

        // Test 15: Print list
        System.out.println("\n=== Test 15: Print list ===");
        list.clear();
        list.addLast(1);
        list.addLast(2);
        list.addLast(3);
        System.out.println("List elements:");
        list.print();

        System.out.println("\n=== All tests completed! ===");
    }
}