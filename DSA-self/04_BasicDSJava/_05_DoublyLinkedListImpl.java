// ============================================================
// DoublyLinkedList — CP-focused method reference
// ============================================================

// Core operations
// ---------------
// add(index, T obj)    -> void      add at index
// addFirst(T obj)      -> void      add at head
// addLast(T obj)       -> void      add at tail
// remove(index)        -> T         remove at index
// removeFirst()        -> T         throws NoSuchElementException if empty
// removeLast()         -> T         throws NoSuchElementException if empty
// pollFirst()          -> T         returns null if empty  (safe removeFirst)
// pollLast()           -> T         returns null if empty  (safe removeLast)
// get(index)           -> T         get at index
// getFirst()           -> T         throws NoSuchElementException if empty
// getLast()            -> T         throws NoSuchElementException if empty
// peekFirst()          -> T         returns null if empty
// peekLast()           -> T         returns null if empty
// isEmpty()            -> boolean
// set(index, T obj)    -> T         set at index, return old value
// size()               -> int

// Stack aliases  (DLL used as stack)
// ------------------------------------
// push(T obj)          -> void      addFirst
// pop()                -> T         removeFirst — throws if empty
// peek()               -> T         peekFirst

// Queue aliases  (DLL used as queue)
// ------------------------------------
// offer(T obj)         -> boolean   addLast
// poll()               -> T         pollFirst — returns null if empty

// O(n) operations  (useful for specific problems)
// -------------------------------------------------
// contains(T obj)      -> boolean
// remove(T obj)        -> boolean   unlink first occurrence — key for LRU Cache
// indexOf(T obj)       -> int       -1 if not found
// lastIndexOf(T obj)   -> int       -1 if not found
// clear()              -> void
// reversed()           -> MyDoublyLinkedList<T>  returns a new list with reversed order

// Common CP Patterns
// ------------------
// LRU Cache            — HashMap + DLL  →  O(1) get/put
// Monotonic Deque      — Sliding Window Max/Min  (pollLast while condition)
// Browser History      — addFirst / removeFirst / removeLast for back/forward
// Palindrome Check     — peekFirst + pollLast comparison loop
// Flatten DLL          — merge child lists in-place

// ============================================================

import java.util.NoSuchElementException;

class MyDoublyLinkedList<T> {
    class Node<K> {
        K data;
        Node<K> prev;
        Node<K> next;
    
        Node(K data) {
            this.prev = this.next = null;
            this.data = data;
        }
    }
    private Node<T> head;
    private Node<T> tail;
    private int size;

    MyDoublyLinkedList() {
        head = tail = null;
        size = 0;
    }

    // ── Core operations ────────────────────────────────────────────

    public void add(int index, T obj) {
        if (index < 0 || index > size) throw new IndexOutOfBoundsException();
        if (index == 0) {
            addFirst(obj);
        } else if (index == size) {
            addLast(obj);
        } else {
            Node<T> node = new Node<>(obj);
            Node<T> cur = head;
            for (int i = 0; i < index; i++) cur = cur.next;
            Node<T> prev = cur.prev;
            node.prev = prev;
            node.next = cur;

            prev.next = node;
            cur.prev = node;
            size++;
        }
    }

    public void addFirst(T obj) {
        Node<T> node = new Node<>(obj);
        if (head == null) {
            head = tail = node;
        } else {
            node.next = head;
            head.prev = node;
            head = node;
        }
        size++;
    }

    public void addLast(T obj) {
        Node<T> node = new Node<>(obj);
        if (tail == null) {
            head = tail = node;
        } else {
            node.prev = tail;
            tail.next = node;
            tail = node;
        }
        size++;
    }

    public T remove(int index) {
        if (index < 0 || index >= size) throw new IndexOutOfBoundsException();
        if (index == 0) return removeFirst();
        if (index == size - 1) return removeLast();

        Node<T> cur = head;
        for (int i = 0; i < index; i++) cur = cur.next;

        T data = cur.data;
        
        Node<T> prev = cur.prev, next = cur.next;
        prev.next = next;
        next.prev = prev;
        cur.prev = cur.next = null; // clear dangling refs
        size--;
        return data;
    }

    public T removeFirst() {
        if (head == null) throw new NoSuchElementException();
        T data = head.data;
        if (head == tail) {
            head = tail = null;
        } else {
            Node<T> temp = head;
            head = head.next;
            head.prev = null;
            temp.next = null; // remove dangling reference
        }
        size--;
        return data;
    }

    public T removeLast() {
        if (tail == null) throw new NoSuchElementException();
        T data = tail.data;
        if (head == tail) {
            head = tail = null;
        } else {
            Node<T> temp = tail;
            tail = tail.prev;
            tail.next = null;
            temp.prev = null; // remove dangling reference
        }
        size--;
        return data;
    }

    public T pollFirst() { return head == null ? null : removeFirst(); }
    public T pollLast()  { return tail == null ? null : removeLast();  }

    public T get(int index) {
        if (index < 0 || index >= size) throw new IndexOutOfBoundsException();
        Node<T> cur = head;
        for (int i = 0; i < index; i++) cur = cur.next;
        return cur.data;
    }

    public T getFirst() {
        if (head == null) throw new NoSuchElementException();
        return head.data;
    }

    public T getLast() {
        if (tail == null) throw new NoSuchElementException();
        return tail.data;
    }

    public T peekFirst() { return head == null ? null : head.data; }
    public T peekLast()  { return tail == null ? null : tail.data; }

    public boolean isEmpty() { return size == 0; }

    public T set(int index, T obj) {
        if (index < 0 || index >= size) throw new IndexOutOfBoundsException();
        Node<T> cur = head;
        for (int i = 0; i < index; i++) cur = cur.next;
        T oldData = cur.data;
        cur.data = obj;
        return oldData;
    }

    public int size()        { return size; }

    // ── Stack / Queue aliases ────────────────────────────────

    public void push(T obj)        { addFirst(obj); }
    public T    pop()              { return removeFirst(); }   // throws if empty
    public T    peek()             { return peekFirst(); }

    public boolean offer(T obj)    { addLast(obj); return true; }
    public T       poll()          { return pollFirst(); }

    // ── O(n) helpers ─────────────────────────────────────────

    public boolean contains(T obj) {
        for (Node<T> cur = head; cur != null; cur = cur.next)
            if (eq(cur.data, obj)) return true;
        return false;
    }

    /** Unlinks the first occurrence of obj — critical for LRU Cache. */
    public boolean remove(T obj) {
        for (Node<T> cur = head; cur != null; cur = cur.next) {
            if (eq(cur.data, obj)) {
                unlink(cur);
                return true;
            }
        }
        return false;
    }

    public int indexOf(T obj) {
        int idx = 0;
        for (Node<T> cur = head; cur != null; cur = cur.next, idx++)
            if (eq(cur.data, obj)) return idx;
        return -1;
    }

    public int lastIndexOf(T obj) {
        int idx = size - 1;
        for (Node<T> cur = tail; cur != null; cur = cur.prev, idx--)
            if (eq(cur.data, obj)) return idx;
        return -1;
    }

    private boolean eq(T a, T b) {
        return a == null ? b == null : a.equals(b);
    }

    public void clear() {
        Node<T> cur = head;
        while (cur != null) {
            Node<T> next = cur.next;
            cur.prev = cur.next = null; // break links for GC
            cur = next;
        }
        // below code is enough to delete the entire linked list, 
        // but a good practice is to break links between nodes.
        head = tail = null;
        size = 0;
    }

    public MyDoublyLinkedList<T> reversed() {
        MyDoublyLinkedList<T> rev = new MyDoublyLinkedList<>();
        for (Node<T> cur = head; cur != null; cur = cur.next)
            rev.addFirst(cur.data);
        return rev;
    }

    // ── Internal helpers ─────────────────────────────────────

    /** Unlinks a node in O(1) — used by remove(obj) and LRU Cache. */
    void unlink(Node<T> node) {
        if (node.prev != null) node.prev.next = node.next; else head = node.next;
        if (node.next != null) node.next.prev = node.prev; else tail = node.prev;
        node.prev = node.next = null; // clear dangling refs
        size--;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("[");
        for (Node<T> cur = head; cur != null; cur = cur.next) {
            sb.append(cur.data);
            if (cur.next != null) sb.append(" <-> ");
        }
        return sb.append("]").toString();
    }

    public boolean isLoop() {
        // Brahma Algorithm / Floyd's Cycle-Finding Algorithm aka Tortoise and Hare Algo
        // IMP: PTR: Always initialise fast and slow to same place for Brahma's algo.
        // (NOT FOR FINDING LEFT MIDDLE ELEMENT OF LL)
        Node<T> slow = head, fast = head;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast)
                return true;
        }
        return false;
        // PTR: To get the starting node of loop, reset slow to head and traverse both
        // slow and fast one step at a time.
        // The node where they meet is the starting node of loop.
    }

    public Node<T> getMiddleNode() {
        if (head == null) return null;
        Node<T> slow = head, fast = head.next; // for left middle, start fast at head.next
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }
}
public class _05_DoublyLinkedListImpl {

    // ── tiny assertion helper ─────────────────────────────────
    static int passed = 0, failed = 0;

    static void check(String name, boolean condition) {
        if (condition) { System.out.println("  PASS  " + name); passed++; }
        else           { System.out.println("  FAIL  " + name); failed++; }
    }

    static void section(String title) {
        System.out.println("\n── " + title + " ──");
    }

    // ─────────────────────────────────────────────────────────
    public static void main(String[] args) {

        // ── 1. addFirst / addLast / size / isEmpty ────────────
        section("addFirst / addLast / size / isEmpty");
        MyDoublyLinkedList<Integer> l = new MyDoublyLinkedList<>();
        check("isEmpty on new list",    l.isEmpty());
        check("size == 0 on new list",  l.size() == 0);

        l.addLast(2);
        l.addFirst(1);
        l.addLast(3);
        check("toString after addFirst/addLast", l.toString().equals("[1 <-> 2 <-> 3]"));
        check("size == 3",  l.size() == 3);
        check("!isEmpty",  !l.isEmpty());

        // ── 2. add(index) ─────────────────────────────────────
        section("add(index)");
        l.add(1, 99);                                       // [1, 99, 2, 3]
        check("add(1,99) inserts at index 1",   l.toString().equals("[1 <-> 99 <-> 2 <-> 3]"));
        l.add(0, 0);                                        // [0, 1, 99, 2, 3]
        check("add(0,0) inserts at head",        l.toString().equals("[0 <-> 1 <-> 99 <-> 2 <-> 3]"));
        l.add(l.size(), 100);                               // append
        check("add(size,100) inserts at tail",   l.toString().equals("[0 <-> 1 <-> 99 <-> 2 <-> 3 <-> 100]"));
        try { l.add(-1, 5); check("add(-1) throws", false); }
        catch (IndexOutOfBoundsException e) { check("add(-1) throws", true); }
        try { l.add(l.size() + 1, 5); check("add(size+1) throws", false); }
        catch (IndexOutOfBoundsException e) { check("add(size+1) throws", true); }
        l.clear();

        // ── 3. get(index) / set(index) ────────────────────────
        section("get(index) / set(index)");
        l.addLast(10); l.addLast(20); l.addLast(30);
        check("get(0) == 10",   l.get(0) == 10);
        check("get(1) == 20",   l.get(1) == 20);
        check("get(2) == 30",   l.get(2) == 30);
        check("set(1,99) returns old value 20", l.set(1, 99) == 20);
        check("get(1) == 99 after set",          l.get(1) == 99);
        try { l.get(-1);      check("get(-1) throws", false); }
        catch (IndexOutOfBoundsException e) { check("get(-1) throws", true); }
        try { l.get(l.size()); check("get(size) throws", false); }
        catch (IndexOutOfBoundsException e) { check("get(size) throws", true); }
        l.clear();

        // ── 4. remove(index) ──────────────────────────────────
        section("remove(index)");
        l.addLast(1); l.addLast(2); l.addLast(3); l.addLast(4);
        check("remove(1) returns 2",         l.remove(1) == 2);
        check("list is [1 <-> 3 <-> 4]",     l.toString().equals("[1 <-> 3 <-> 4]"));
        check("remove(0) returns head 1",    l.remove(0) == 1);
        check("remove(size-1) returns tail", l.remove(l.size() - 1) == 4);
        check("list is [3]",                 l.toString().equals("[3]"));
        try { l.remove(-1);      check("remove(-1) throws", false); }
        catch (IndexOutOfBoundsException e) { check("remove(-1) throws", true); }
        try { l.remove(l.size()); check("remove(size) throws", false); }
        catch (IndexOutOfBoundsException e) { check("remove(size) throws", true); }
        l.clear();

        // ── 5. getFirst / getLast / peekFirst / peekLast ──────
        section("getFirst / getLast / peekFirst / peekLast");
        l.addLast(1); l.addLast(2); l.addLast(3);
        check("getFirst == 1",   l.getFirst() == 1);
        check("getLast  == 3",   l.getLast()  == 3);
        check("peekFirst == 1",  l.peekFirst() == 1);
        check("peekLast  == 3",  l.peekLast()  == 3);
        check("size unchanged after peeks", l.size() == 3);

        // ── 6. removeFirst / removeLast ───────────────────────
        section("removeFirst / removeLast");
        check("removeFirst == 1", l.removeFirst() == 1);
        check("removeLast  == 3", l.removeLast()  == 3);
        check("list is [2]",      l.toString().equals("[2]"));
        check("removeFirst last element == 2", l.removeFirst() == 2);
        check("isEmpty after removing all",    l.isEmpty());

        // ── 7. pollFirst / pollLast (null-safe) ───────────────
        section("pollFirst / pollLast on empty list");
        check("pollFirst on empty == null", l.pollFirst() == null);
        check("pollLast  on empty == null", l.pollLast()  == null);
        check("peekFirst on empty == null", l.peekFirst() == null);
        check("peekLast  on empty == null", l.peekLast()  == null);

        // ── 8. NoSuchElementException on empty ────────────────
        section("Exceptions on empty list");
        try { l.removeFirst(); check("removeFirst throws on empty", false); }
        catch (java.util.NoSuchElementException e) { check("removeFirst throws on empty", true); }

        try { l.removeLast(); check("removeLast throws on empty", false); }
        catch (java.util.NoSuchElementException e) { check("removeLast throws on empty", true); }

        try { l.getFirst(); check("getFirst throws on empty", false); }
        catch (java.util.NoSuchElementException e) { check("getFirst throws on empty", true); }

        try { l.getLast(); check("getLast throws on empty", false); }
        catch (java.util.NoSuchElementException e) { check("getLast throws on empty", true); }

        // ── 9. Stack: push / pop / peek ───────────────────────
        section("Stack: push / pop / peek");
        l.push(10); l.push(20); l.push(30);
        check("peek == 30 (top)",    l.peek() == 30);
        check("pop  == 30",          l.pop()  == 30);
        check("pop  == 20",          l.pop()  == 20);
        check("pop  == 10",          l.pop()  == 10);
        check("isEmpty after pops",  l.isEmpty());

        // ── 10. Queue: offer / poll ───────────────────────────
        section("Queue: offer / poll");
        l.offer(1); l.offer(2); l.offer(3);
        check("poll == 1 (FIFO)", l.poll() == 1);
        check("poll == 2",        l.poll() == 2);
        check("poll == 3",        l.poll() == 3);
        check("poll on empty == null", l.poll() == null);

        // ── 11. contains / indexOf / lastIndexOf ──────────────
        section("contains / indexOf / lastIndexOf");
        l.addLast(1); l.addLast(2); l.addLast(3); l.addLast(2);
        check("contains 2",              l.contains(2));
        check("!contains 99",           !l.contains(99));
        check("indexOf 1 == 0",          l.indexOf(1) == 0);
        check("indexOf 2 == 1",          l.indexOf(2) == 1);   // first occurrence
        check("indexOf 99 == -1",        l.indexOf(99) == -1);
        check("lastIndexOf 2 == 3",      l.lastIndexOf(2) == 3);
        check("lastIndexOf 1 == 0",      l.lastIndexOf(1) == 0);
        check("lastIndexOf 99 == -1",    l.lastIndexOf(99) == -1);

        // ── 12. remove(obj) ───────────────────────────────────
        section("remove(obj)");
        check("remove(2) == true",       l.remove(Integer.valueOf(2)));  // removes first 2
        check("list is [1 <-> 3 <-> 2]", l.toString().equals("[1 <-> 3 <-> 2]"));
        check("remove(1) (head)",        l.remove(Integer.valueOf(1)));
        check("remove(2) (tail)",        l.remove(Integer.valueOf(2)));
        check("list is [3]",             l.toString().equals("[3]"));
        check("remove(99) == false",    !l.remove(Integer.valueOf(99)));
        l.clear();

        // ── 13. reversed() ────────────────────────────────────
        section("reversed()");
        l.addLast(1); l.addLast(2); l.addLast(3);
        MyDoublyLinkedList<Integer> rev = l.reversed();
        check("reversed is [3 <-> 2 <-> 1]",   rev.toString().equals("[3 <-> 2 <-> 1]"));
        check("original unchanged [1 <-> 2 <-> 3]", l.toString().equals("[1 <-> 2 <-> 3]"));
        check("reversed size == 3",             rev.size() == 3);
        l.clear();

        // ── 14. Null-safe operations ──────────────────────────
        section("Null-safe operations");
        MyDoublyLinkedList<String> ns = new MyDoublyLinkedList<>();
        ns.addLast(null); ns.addLast("a"); ns.addLast(null);
        check("contains null",        ns.contains(null));
        check("indexOf null == 0",    ns.indexOf(null) == 0);
        check("lastIndexOf null == 2",ns.lastIndexOf(null) == 2);
        check("remove null",          ns.remove((String) null));   // removes first null
        check("list is [a <-> null]", ns.toString().equals("[a <-> null]"));

        // ── 15. clear ─────────────────────────────────────────
        section("clear");
        l.addLast(1); l.addLast(2); l.addLast(3);
        l.clear();
        check("isEmpty after clear",    l.isEmpty());
        check("size == 0 after clear",  l.size() == 0);
        check("toString after clear",   l.toString().equals("[]"));

        // ── 16. getMiddleNode ─────────────────────────────────
        section("getMiddleNode");
        MyDoublyLinkedList<Integer> m = new MyDoublyLinkedList<>();
        check("getMiddleNode on empty == null", m.getMiddleNode() == null);
        m.addLast(1);
        check("middle of [1] == 1",              m.getMiddleNode().data == 1);
        m.addLast(2); m.addLast(3);
        check("middle of [1,2,3] == 2 (left)",   m.getMiddleNode().data == 2);
        m.addLast(4);
        check("middle of [1,2,3,4] == 2 (left)", m.getMiddleNode().data == 2);
        m.addLast(5);
        check("middle of [1,2,3,4,5] == 3",      m.getMiddleNode().data == 3);

        // ── 17. isLoop ────────────────────────────────────────
        section("isLoop");
        MyDoublyLinkedList<Integer> cyc = new MyDoublyLinkedList<>();
        cyc.addLast(1); cyc.addLast(2); cyc.addLast(3);
        check("isLoop == false (no cycle)", !cyc.isLoop());
        check("still no loop after reads",  !cyc.isLoop());

        // ── Summary ───────────────────────────────────────────
        System.out.println("\n════════════════════════════");
        System.out.println("  Results: " + passed + " passed, " + failed + " failed");
        System.out.println("════════════════════════════");
    }
}

/**
 * Output:
 * ── addFirst / addLast / size / isEmpty ──
 *   PASS  isEmpty on new list
 *   PASS  size == 0 on new list
 *   PASS  toString after addFirst/addLast
 *   PASS  size == 3
 *   PASS  !isEmpty
 * 
 * ── add(index) ──
 *   PASS  add(1,99) inserts at index 1
 *   PASS  add(0,0) inserts at head
 *   PASS  add(size,100) inserts at tail
 *   PASS  add(-1) throws
 *   PASS  add(size+1) throws
 * 
 * ── get(index) / set(index) ──
 *   PASS  get(0) == 10
 *   PASS  get(1) == 20
 *   PASS  get(2) == 30
 *   PASS  set(1,99) returns old value 20
 *   PASS  get(1) == 99 after set
 *   PASS  get(-1) throws
 *   PASS  get(size) throws
 * 
 * ── remove(index) ──
 *   PASS  remove(1) returns 2
 *   PASS  list is [1 <-> 3 <-> 4]
 *   PASS  remove(0) returns head 1
 *   PASS  remove(size-1) returns tail
 *   PASS  list is [3]
 *   PASS  remove(-1) throws
 *   PASS  remove(size) throws
 * 
 * ── getFirst / getLast / peekFirst / peekLast ──
 *   PASS  getFirst == 1
 *   PASS  getLast  == 3
 *   PASS  peekFirst == 1
 *   PASS  peekLast  == 3
 *   PASS  size unchanged after peeks
 * 
 * ── removeFirst / removeLast ──
 *   PASS  removeFirst == 1
 *   PASS  removeLast  == 3
 *   PASS  list is [2]
 *   PASS  removeFirst last element == 2
 *   PASS  isEmpty after removing all
 * 
 * ── pollFirst / pollLast on empty list ──
 *   PASS  pollFirst on empty == null
 *   PASS  pollLast  on empty == null
 *   PASS  peekFirst on empty == null
 *   PASS  peekLast  on empty == null
 * 
 * ── Exceptions on empty list ──
 *   PASS  removeFirst throws on empty
 *   PASS  removeLast throws on empty
 *   PASS  getFirst throws on empty
 *   PASS  getLast throws on empty
 * 
 * ── Stack: push / pop / peek ──
 *   PASS  peek == 30 (top)
 *   PASS  pop  == 30
 *   PASS  pop  == 20
 *   PASS  pop  == 10
 *   PASS  isEmpty after pops
 * 
 * ── Queue: offer / poll ──
 *   PASS  poll == 1 (FIFO)
 *   PASS  poll == 2
 *   PASS  poll == 3
 *   PASS  poll on empty == null
 * 
 * ── contains / indexOf / lastIndexOf ──
 *   PASS  contains 2
 *   PASS  !contains 99
 *   PASS  indexOf 1 == 0
 *   PASS  indexOf 2 == 1
 *   PASS  indexOf 99 == -1
 *   PASS  lastIndexOf 2 == 3
 *   PASS  lastIndexOf 1 == 0
 *   PASS  lastIndexOf 99 == -1
 * 
 * ── remove(obj) ──
 *   PASS  remove(2) == true
 *   PASS  list is [1 <-> 3 <-> 2]
 *   PASS  remove(1) (head)
 *   PASS  remove(2) (tail)
 *   PASS  list is [3]
 *   PASS  remove(99) == false
 * 
 * ── reversed() ──
 *   PASS  reversed is [3 <-> 2 <-> 1]
 *   PASS  original unchanged [1 <-> 2 <-> 3]
 *   PASS  reversed size == 3
 * 
 * ── Null-safe operations ──
 *   PASS  contains null
 *   PASS  indexOf null == 0
 *   PASS  lastIndexOf null == 2
 *   PASS  remove null
 *   PASS  list is [a <-> null]
 * 
 * ── clear ──
 *   PASS  isEmpty after clear
 *   PASS  size == 0 after clear
 *   PASS  toString after clear
 * 
 * ── getMiddleNode ──
 *   PASS  getMiddleNode on empty == null
 *   PASS  middle of [1] == 1
 *   PASS  middle of [1,2,3] == 2 (left)
 *   PASS  middle of [1,2,3,4] == 2 (left)
 *   PASS  middle of [1,2,3,4,5] == 3
 * 
 * ── isLoop ──
 *   PASS  isLoop == false (no cycle)
 *   PASS  still no loop after reads
 * 
 * ════════════════════════════
 *   Results: 83 passed, 0 failed
 * ════════════════════════════
 */