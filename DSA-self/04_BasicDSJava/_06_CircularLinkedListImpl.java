import java.util.NoSuchElementException;

// ============================================================
// Circular Linked List — CP-focused method reference
// ============================================================
// A singly linked CLL where tail.next = head (no null terminator).
// Key insight: maintain only a `tail` pointer — head is just tail.next.
// This gives O(1) addFirst AND addLast without a dummy node.

// O(1) Core operations  ★ most important for CP
// -----------------------------------------------
// addFirst(T obj)      -> void      add at head  (tail.next = newNode)
// addLast(T obj)       -> void      add at tail  (tail = newNode)
// removeFirst()        -> T         throws NoSuchElementException if empty
// peekFirst()          -> T         returns null if empty   (head = tail.next)
// peekLast()           -> T         returns null if empty
// isEmpty()            -> boolean
// size()               -> int

// O(n) operations
// ----------------
// removeLast()         -> T         O(n) — must walk to node before tail
// remove(T obj)        -> boolean   unlink first occurrence
// contains(T obj)      -> boolean
// indexOf(T obj)       -> int       -1 if not found
// clear()              -> void

// Common CP Patterns
// ------------------
// Josephus Problem     — rotate k steps then removeFirst; repeat N times
// Round-Robin          — rotate() advances tail by 1 (O(1)), no array shifting
// Circular Buffer      — fixed-size CLL, overwrite head when full
// Token Ring / Turn    — each node is a player; advance tail each round

// ============================================================

class Node<T> {
    T data;
    Node<T> next;

    Node(T data) {
        this.data = data;
        this.next = null;
    }
}

class MyCircularLinkedList<T> {

    private Node<T> head; // not needed since tail.next is head
    private Node<T> tail;
    private int size;

    MyCircularLinkedList() { 
        head = tail = null; size = 0; 
    }

    // ── O(1) Core ────────────────────────────────────────────

    public void addFirst(T obj) {
        Node<T> node = new Node<>(obj);
        if(isEmpty()) {
            head = tail = node;
            node.next = head;
        }
        else {
            tail.next = node;
            node.next = head;
            head = node;
        }
        size++;
    }

    public void addLast(T obj) {
        Node<T> node = new Node<>(obj);
        if(isEmpty()) {
            head = tail = node;
            node.next = head;
        }
        else {
            tail.next = node;
            node.next = head;
            tail = node;
        }
        size++;
    }

    public T removeFirst() {
        if (isEmpty()) throw new NoSuchElementException();
        T data = head.data;
        if (head == tail) {
            head = tail = null;
            // fyi, below else code works, but cleanup of node won't happen since tail still points to the node.
        } else {
            tail.next = head.next;
            head.next = null;
            head = tail.next;
        }
        size--;
        return data;
    }

    /** O(n) — must walk to the node before tail. */
    public T removeLast() {
        if (isEmpty()) throw new NoSuchElementException();
        T data = tail.data;
        if (head == tail) {
            head = tail = null;
        } else {
            Node<T> cur = head;
            while (cur.next != tail) cur = cur.next; // walk to node before tail
            cur.next = head;
            tail.next = null;
            tail = cur;
            // Approach 2: Iterate while curr != tail, and maintain prev.
        }
        size--;
        return data;
    }

    /** O(1) — advance tail by one node. Key for Josephus / Round-Robin. */
    public void rotate() {
        if (!isEmpty()) {
            tail = head;
            head = head.next;
        }
    }

    public T peekFirst() { return head == null ? null : head.data; }
    public T peekLast()  { return tail == null ? null : tail.data; }

    public boolean isEmpty() { return size == 0; }
    public int size()        { return size; }

    // ── O(n) helpers ─────────────────────────────────────────

    public boolean contains(T obj) {
        if (isEmpty()) return false;
        Node<T> cur = head;
        for (int i = 0; i < size; i++, cur = cur.next)
            if (eq(cur.data, obj)) return true;
        return false;
        // Approach 2: if no size tracking, use do-while(curr != head)
        // Approach 3: Iterate while curr != tail, and check tail separately.
    }

    public boolean remove(T obj) {
        if (isEmpty()) return false;
        Node<T> prev = tail;
        Node<T> cur  = head;
        for (int i = 0; i < size; i++) {
            if (eq(cur.data, obj)) {
                if (cur == head) {
                    removeFirst();
                } else if (cur == tail) {
                    removeLast(); // O(n) again. To avoid it write the whole logic again. Single element still needs to be handled here as special case.
                } else {
                    prev.next = cur.next;
                    cur.next = null;
                    size--;
                }
                return true;
            }
            prev = cur;
            cur = cur.next;
        }
        return false;
    }

    public int indexOf(T obj) {
        if (isEmpty()) return -1;
        Node<T> cur = head;
        for (int i = 0; i < size; i++, cur = cur.next)
            if (eq(cur.data, obj)) return i;
        return -1;
    }

    public void clear() {
        if (isEmpty()) return;
        Node<T> cur = head;
        tail.next = null; // break circular reference to help GC
        while (cur != null) {
            Node<T> next = cur.next;
            cur.next = null;
            cur = next;
        }
        head = tail = null;
        size = 0;
    }

    // ── Internal helpers ─────────────────────────────────────

    private boolean eq(T a, T b) {
        return a == null ? b == null : a.equals(b);
    }

    /** Prints all elements starting from head. */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append('[');
        Node<T> cur = head;
        for (int i = 0; i < size; i++) {
            sb.append(cur.data);
            if (i < size - 1)
                sb.append(", ");

            cur = cur.next;
        }
        sb.append(']');
        return sb.toString();
    }
}

public class _06_CircularLinkedListImpl {

    // ── tiny assertion helper ─────────────────────────────────
    static int passed = 0, failed = 0;

    static void check(String name, boolean condition) {
        if (condition) { System.out.println("  PASS  " + name); passed++; }
        else           { System.out.println("  FAIL  " + name); failed++; }
    }

    static void section(String title) {
        System.out.println("\n── " + title + " ──");
    }

    public static void main(String[] args) {

        // ── 1. addFirst / addLast / size / isEmpty ────────────
        section("addFirst / addLast / size / isEmpty");
        MyCircularLinkedList<Integer> l = new MyCircularLinkedList<>();
        check("isEmpty on new list",    l.isEmpty());
        check("size == 0 on new list",  l.size() == 0);

        l.addLast(2);
        l.addFirst(1);
        l.addLast(3);
        check("toString [1, 2, 3]",  l.toString().equals("[1, 2, 3]"));
        check("size == 3",           l.size() == 3);
        check("!isEmpty",           !l.isEmpty());

        // ── 2. peekFirst / peekLast ───────────────────────────
        section("peekFirst / peekLast");
        check("peekFirst == 1",  l.peekFirst() == 1);
        check("peekLast  == 3",  l.peekLast()  == 3);
        check("size unchanged",  l.size() == 3);

        // ── 3. removeFirst ────────────────────────────────────
        section("removeFirst");
        check("removeFirst == 1",              l.removeFirst() == 1);
        check("peekFirst == 2 after remove",   l.peekFirst()   == 2);
        check("list is [2, 3]",                l.toString().equals("[2, 3]"));
        check("removeFirst == 2",              l.removeFirst() == 2);
        check("removeFirst last element == 3", l.removeFirst() == 3);
        check("isEmpty after removing all",    l.isEmpty());

        // ── 4. removeLast ─────────────────────────────────────
        section("removeLast");
        l.addLast(1); l.addLast(2); l.addLast(3);
        check("removeLast == 3",              l.removeLast() == 3);
        check("peekLast == 2 after remove",   l.peekLast()   == 2);
        check("list is [1, 2]",               l.toString().equals("[1, 2]"));
        check("removeLast == 2",              l.removeLast() == 2);
        check("removeLast last element == 1", l.removeLast() == 1);
        check("isEmpty after removeLast all", l.isEmpty());

        // ── 5. Exceptions on empty ────────────────────────────
        section("Exceptions on empty list");
        try { l.removeFirst(); check("removeFirst throws on empty", false); }
        catch (NoSuchElementException e) { check("removeFirst throws on empty", true); }

        try { l.removeLast(); check("removeLast throws on empty", false); }
        catch (NoSuchElementException e) { check("removeLast throws on empty", true); }

        check("peekFirst on empty == null", l.peekFirst() == null);
        check("peekLast  on empty == null", l.peekLast()  == null);

        // ── 6. contains / indexOf ────────────────────────────
        section("contains / indexOf");
        l.addLast(1); l.addLast(2); l.addLast(3); l.addLast(2);
        check("contains 2",        l.contains(2));
        check("!contains 99",     !l.contains(99));
        check("indexOf 1 == 0",    l.indexOf(1) == 0);
        check("indexOf 2 == 1",    l.indexOf(2) == 1);   // first occurrence
        check("indexOf 99 == -1",  l.indexOf(99) == -1);

        // ── 7. remove(obj) ────────────────────────────────────
        section("remove(obj)");
        check("remove(2) == true",        l.remove(2));          // middle element
        check("list is [1, 3, 2]",        l.toString().equals("[1, 3, 2]"));
        check("remove(1) head",           l.remove(1));
        check("list is [3, 2]",           l.toString().equals("[3, 2]"));
        check("remove(2) tail",           l.remove(2));
        check("list is [3]",              l.toString().equals("[3]"));
        check("remove only element",      l.remove(3));
        check("isEmpty after remove",     l.isEmpty());
        check("remove on empty == false", !l.remove(99));

        // ── 8. Null-safe operations ───────────────────────────
        section("Null-safe operations");
        MyCircularLinkedList<String> ns = new MyCircularLinkedList<>();
        ns.addLast(null); ns.addLast("a"); ns.addLast(null);
        check("contains null",         ns.contains(null));
        check("indexOf null == 0",      ns.indexOf(null) == 0);
        check("remove null == true",    ns.remove((String) null));  // must not use != null check
        check("list is [a, null]",      ns.toString().equals("[a, null]"));

        // ── 9. clear ─────────────────────────────────────────
        section("clear");
        l.addLast(1); l.addLast(2); l.addLast(3);
        l.clear();
        check("isEmpty after clear",    l.isEmpty());
        check("size == 0 after clear",  l.size() == 0);
        check("toString after clear",   l.toString().equals("[]"));

        // ── 10. rotate() ──────────────────────────────────────
        // rotate() advances tail by 1: old head becomes new tail.
        // PTR: head field must be updated to tail.next after rotation.
        section("rotate()");
        l.addLast(1); l.addLast(2); l.addLast(3);   // [1, 2, 3], head=1, tail=3
        l.rotate();                                  // [2, 3, 1], head=2, tail=1
        check("peekFirst after 1 rotate == 2", l.peekFirst() == 2);
        check("peekLast  after 1 rotate == 1", l.peekLast()  == 1);
        check("toString after 1 rotate",       l.toString().equals("[2, 3, 1]"));
        l.rotate();                                  // [3, 1, 2]
        check("peekFirst after 2 rotates == 3", l.peekFirst() == 3);
        check("toString after 2 rotates",       l.toString().equals("[3, 1, 2]"));
        l.rotate();                                  // [1, 2, 3] — full cycle
        check("full cycle restore",             l.toString().equals("[1, 2, 3]"));
        l.clear();

        // ── 11. CP Pattern — Josephus Problem ────────────────
        // N=5 people (1..5), eliminate every k=2nd person.
        // Expected elimination order: 2, 4, 1, 5 → survivor: 3
        section("CP Pattern: Josephus (N=5, k=2)");
        MyCircularLinkedList<Integer> circle = new MyCircularLinkedList<>();
        for (int i = 1; i <= 5; i++) circle.addLast(i);
        int k = 2;
        int[] expectedOrder = {2, 4, 1, 5};
        int[] eliminated = new int[4];
        int ei = 0;
        while (circle.size() > 1) {
            for (int i = 0; i < k - 1; i++) circle.rotate();  // advance k-1 steps
            eliminated[ei++] = circle.removeFirst();           // remove the k-th person
        }
        check("Josephus elimination order correct", java.util.Arrays.equals(eliminated, expectedOrder));
        check("Josephus survivor == 3", circle.peekFirst() == 3);

        // ── Summary ──────────────────────────────────────────
        System.out.println("\n════════════════════════════");
        System.out.println("  Results: " + passed + " passed, " + failed + " failed");
        System.out.println("════════════════════════════");
    }
}
