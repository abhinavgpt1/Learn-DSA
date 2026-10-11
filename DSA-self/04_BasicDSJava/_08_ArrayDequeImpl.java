import java.util.NoSuchElementException;

// ============================================================
// ArrayDeque — CP-focused method reference
// ============================================================
// Backed by a circular resizable array.
// Faster than LinkedList for stack/queue because of cache locality.
// Prefer ArrayDeque over Stack (synchronized) and LinkedList (GC overhead).

// O(1) amortized — Core deque operations  ★ most important for CP
// -----------------------------------------------------------------
// addFirst(T obj)      -> void      add at front
// addLast(T obj)       -> void      add at rear
// removeFirst()        -> T         throws NoSuchElementException if empty
// removeLast()         -> T         throws NoSuchElementException if empty
// getFirst()           -> T         throws NoSuchElementException if empty
// getLast()            -> T         throws NoSuchElementException if empty
// offerFirst(T obj)    -> boolean   identical to addFirst, skip the alias
// offerLast(T obj)     -> boolean   identical to addLast, skip the alias
// pollFirst()          -> T         returns null if empty  (safe removeFirst)
// pollLast()           -> T         returns null if empty  (safe removeLast)
// peekFirst()          -> T         returns null if empty
// peekLast()           -> T         returns null if empty
// isEmpty()            -> boolean
// size()               -> int

// Stack aliases  (faster than java.util.Stack)
// ----------------------------------------------
// push(T obj)          -> void      addFirst
// pop()                -> T         removeFirst — throws if empty
// peek()               -> T         peekFirst   — returns null if empty

// Queue aliases  (faster than LinkedList as Queue)
// --------------------------------------------------
// offer(T obj)         -> boolean   addLast
// poll()               -> T         pollFirst — returns null if empty

// O(n) operations
// ----------------
// contains(T obj)      -> boolean
// remove(T obj)        -> boolean          removes first occurrence
// clear()              -> void
// toArray()            -> Object[]
// reversed()           -> ArrayDeque<T>    returns Deque ideally.

// Common CP Patterns
// ------------------
// Monotonic Deque      — Sliding Window Max/Min  →  pollLast while condition, then addLast
// BFS                  — offer(node) + poll()  (queue mode)
// DFS (iterative)      — push(node) + pop()    (stack mode)
// Undo/Redo            — two ArrayDeques for history
// Next Greater Element — addFirst / peekFirst as monotonic stack
// Sliding Window / Two-pointer   — offerLast(right), pollFirst() when invalid

// ============================================================

@SuppressWarnings("unchecked")
class MyArrayDeque<T> {

    private T[] arr;
    private int head;   // index of first element
    private int tail;   // index one past last element
    private int size;

    private static final int DEFAULT_CAPACITY = 16;

    MyArrayDeque() {
        // arr = new T[DEFAULT_CAPACITY]; // WRONG: cannot create generic array
        arr  = (T[]) new Object[DEFAULT_CAPACITY];
        head = tail = -1;
        size = 0;
    }

    // ── O(1) amortised Core ──────────────────────────────────

    public void addFirst(T obj) {
        if(isEmpty()) {
            head = tail = 0;
            arr[head] = obj;
            size = 1;
            return;
        }

        if(size == arr.length) resize();
        head = (head - 1 + arr.length) % arr.length;
        arr[head] = obj;
        size++;
    }

    public void addLast(T obj) {
        if(isEmpty()) {
            head = tail = 0;
            arr[tail] = obj;
            size = 1;
            return;
        }

        if (size == arr.length) resize();
        tail = (tail + 1) % arr.length;
        arr[tail] = obj;
        size++;
    }

    // PTR: remove functions can make tail < head when array is empty. Hence it's imp to track size, such that during addFirst/addLast, we can reset head and tail to 0.
    // _________h_____                  _________h_____                                              ___________h___
    // |_|_|_|_|5|_|_|  -removeLast()-> |_|_|_|_|_|_|_| -(if no size tracking, then on addFirst(7)-> |_|_|_|_|_|7|_| 
    // _________t_____                  _______t_______                                              _______t_______
    public T removeFirst() {
        if (isEmpty()) throw new NoSuchElementException();
        T data = arr[head];
        arr[head] = null;
        head = (head + 1) % arr.length;
        size--;
        return data;
    }

    public T removeLast() {
        if (isEmpty()) throw new NoSuchElementException();
        T data = arr[tail];
        arr[tail] = null;
        tail = (tail - 1 + arr.length) % arr.length;    // -1 % n = -1, hence we add arr.length to get positive remainder.
        size--;
        return data;
    }

    public T pollFirst()  { return isEmpty() ? null : removeFirst(); }
    public T pollLast()   { return isEmpty() ? null : removeLast();  }

    public T peekFirst()  { return isEmpty() ? null : arr[head]; }
    public T peekLast()   { return isEmpty() ? null : arr[tail]; }

    public T getFirst() {
        if (isEmpty()) throw new NoSuchElementException();
        return arr[head];
    }

    public T getLast() {
        if (isEmpty()) throw new NoSuchElementException();
        return arr[tail];
    }

    public boolean isEmpty() { return size == 0; }
    public int size()        { return size; }

    // ── Stack / Queue aliases ────────────────────────────────

    public void push(T obj)     { addFirst(obj); }
    public T    pop()           { return removeFirst(); }   // throws if empty
    public T    peek()          { return peekFirst(); }     // null if empty

    public boolean offer(T obj) { addLast(obj); return true; }
    public T       poll()       { return pollFirst(); }

    // ── O(n) helpers ─────────────────────────────────────────

    public boolean contains(T obj) {
        // Iterates head->tail and not 0->arr.length to avoid nulls in empty slots.
        for (int i = 0; i < size; i++) {
            int idx = (head + i) % arr.length;
            if (eq(arr[idx], obj))
                return true;
        }
        return false;
    }

    public boolean remove(T obj) {
        for (int i = 0; i < size; i++) {
            int idx = (head + i) % arr.length;
            if (eq(arr[idx], obj)) {
                // shift elements one step left
                for (int j = i; j < size - 1; j++) {
                    int cur  = (head + j) % arr.length;
                    int next = (head + j + 1) % arr.length;
                    arr[cur] = arr[next];
                }
                arr[tail] = null;
                tail = (tail - 1 + arr.length) % arr.length;
                size--;
                return true;
            }
        }
        return false;
    }

    public void clear() {
        for (int i = 0; i < size; i++)
            arr[(head + i) % arr.length] = null;
        head = tail = -1;
        size = 0;
    }

    public Object[] toArray() {
        Object[] out = new Object[size];
        for (int i = 0; i < size; i++)
            out[i] = arr[(head + i) % arr.length];
        return out;
    }

    // ── Internal helpers ─────────────────────────────────────

    private void resize() {
        T[] bigger = (T[]) new Object[arr.length * 2];
        for (int i = 0; i < size; i++)
            bigger[i] = arr[(head + i) % arr.length];
        arr  = bigger;
        head = 0;
        tail = size - 1;
    }

    private boolean eq(T a, T b) {
        return a == null ? b == null : a.equals(b);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("[");
        for (int i = 0; i < size; i++) {
            sb.append(arr[(head + i) % arr.length]);
            if (i < size - 1) sb.append(", ");
        }
        return sb.append("]").toString();
    }
}

public class _08_ArrayDequeImpl {

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

        // ── 1. addFirst / addLast / size / isEmpty ────────────────
        section("addFirst / addLast / size / isEmpty");
        MyArrayDeque<Integer> d = new MyArrayDeque<>();
        check("isEmpty on new deque",    d.isEmpty());
        check("size == 0 on new deque",  d.size() == 0);

        d.addLast(2);
        d.addFirst(1);
        d.addLast(3);
        check("toString after addFirst/addLast", d.toString().equals("[1, 2, 3]"));
        check("size == 3",   d.size() == 3);
        check("!isEmpty",   !d.isEmpty());

        // ── 2. getFirst / getLast / peekFirst / peekLast ──────────
        section("getFirst / getLast / peekFirst / peekLast");
        check("getFirst == 1",   d.getFirst() == 1);
        check("getLast  == 3",   d.getLast()  == 3);
        check("peekFirst == 1",  d.peekFirst() == 1);
        check("peekLast  == 3",  d.peekLast()  == 3);
        check("size unchanged after peeks", d.size() == 3);

        // ── 3. removeFirst / removeLast ───────────────────────────
        section("removeFirst / removeLast");
        check("removeFirst == 1",               d.removeFirst() == 1);
        check("removeLast  == 3",               d.removeLast()  == 3);
        check("peekLast after removeLast == 2",  d.peekLast()    == 2);  // verifies tail points to last element, not past it
        check("deque is [2]",                   d.toString().equals("[2]"));
        check("size == 1",                      d.size() == 1);
        check("removeFirst last element == 2",  d.removeFirst() == 2);
        check("isEmpty after removing all",     d.isEmpty());

        // ── 4. pollFirst / pollLast (null-safe) ───────────────────
        section("pollFirst / pollLast on empty deque");
        check("pollFirst on empty == null", d.pollFirst() == null);
        check("pollLast  on empty == null", d.pollLast()  == null);
        check("peekFirst on empty == null", d.peekFirst() == null);
        check("peekLast  on empty == null", d.peekLast()  == null);

        // ── 5. NoSuchElementException on empty ────────────────────
        section("Exceptions on empty deque");
        try { d.removeFirst(); check("removeFirst throws on empty", false); }
        catch (NoSuchElementException e) { check("removeFirst throws on empty", true); }

        try { d.removeLast(); check("removeLast throws on empty", false); }
        catch (NoSuchElementException e) { check("removeLast throws on empty", true); }

        try { d.getFirst(); check("getFirst throws on empty", false); }
        catch (NoSuchElementException e) { check("getFirst throws on empty", true); }

        try { d.getLast(); check("getLast throws on empty", false); }
        catch (NoSuchElementException e) { check("getLast throws on empty", true); }

        // ── 6. Stack: push / pop / peek ───────────────────────────
        section("Stack: push / pop / peek");
        d.push(10); d.push(20); d.push(30);
        check("peek == 30 (top)",   d.peek() == 30);
        check("pop  == 30",         d.pop()  == 30);
        check("pop  == 20",         d.pop()  == 20);
        check("pop  == 10",         d.pop()  == 10);
        check("isEmpty after pops", d.isEmpty());

        // ── 7. Queue: offer / poll ────────────────────────────────
        section("Queue: offer / poll (FIFO)");
        d.offer(1); d.offer(2); d.offer(3);
        check("poll == 1 (FIFO)", d.poll() == 1);
        check("poll == 2",        d.poll() == 2);
        check("poll == 3",        d.poll() == 3);
        check("poll on empty == null", d.poll() == null);

        // ── 8. contains / remove(obj) ─────────────────────────────
        section("contains / remove(obj)");
        d.addLast(1); d.addLast(2); d.addLast(3); d.addLast(2);
        check("contains 2",             d.contains(2));
        check("!contains 99",          !d.contains(99));
        check("remove(2) == true",      d.remove(2));          // removes first 2; verifies shift+null logic
        check("deque is [1, 3, 2]",     d.toString().equals("[1, 3, 2]"));
        check("peekLast after remove",  d.peekLast() == 2);    // old tail slot must be null, new tail must hold 2
        check("remove(1) (front)",      d.remove(1));
        check("remove(2) (back)",       d.remove(2));
        check("deque is [3]",           d.toString().equals("[3]"));
        check("remove only element",    d.remove(3));          // size drops to 0; tail wraps to arr.length-1
        check("isEmpty after remove",   d.isEmpty());
        // add after becoming empty via remove (not clear) — verifies isEmpty() reset of head/tail
        d.addFirst(99);
        check("addFirst after empty-via-remove",  d.peekFirst() == 99);
        check("peekLast  after empty-via-remove", d.peekLast()  == 99);
        check("size == 1 after re-add",           d.size() == 1);
        d.addLast(100);
        check("addLast after single re-add",      d.toString().equals("[99, 100]"));
        check("contains 99 after re-add",          d.contains(99));
        d.clear();

        // ── 9. Null-safe operations ───────────────────────────────
        section("Null-safe operations");
        MyArrayDeque<String> ns = new MyArrayDeque<>();
        ns.addLast(null); ns.addLast("a"); ns.addLast(null);
        check("contains null",         ns.contains(null));
        check("remove null == true",   ns.remove(null));    // removes first null
        check("deque is [a, null]",    ns.toString().equals("[a, null]"));
        check("peekFirst == a",        "a".equals(ns.peekFirst()));
        check("peekLast  == null",     ns.peekLast() == null);

        // ── 10. clear ────────────────────────────────────────────
        section("clear");
        d.addLast(1); d.addLast(2); d.addLast(3);
        d.clear();
        check("isEmpty after clear",   d.isEmpty());
        check("size == 0 after clear", d.size() == 0);
        check("toString after clear",  d.toString().equals("[]"));

        // ── 11. toArray ──────────────────────────────────────────
        section("toArray");
        d.addLast(10); d.addLast(20); d.addLast(30);
        Object[] arr = d.toArray();
        check("toArray length == 3",  arr.length == 3);
        check("toArray[0] == 10",     arr[0].equals(10));
        check("toArray[1] == 20",     arr[1].equals(20));
        check("toArray[2] == 30",     arr[2].equals(30));
        d.clear();

        // ── 12. Resize — fill beyond default capacity (16) ───────
        section("Resize (> 16 elements)");
        for (int i = 1; i <= 20; i++) d.addLast(i);
        check("size == 20 after resize",          d.size() == 20);
        check("peekFirst == 1 after resize",       d.peekFirst() == 1);
        check("peekLast  == 20 after resize",      d.peekLast()  == 20);
        for (int i = 1; i <= 20; i++)
            check("drain in order " + i,           d.pollFirst() == i);
        check("isEmpty after drain",               d.isEmpty());
        // add after becoming empty via drain (not clear) — verifies isEmpty() reset
        d.addLast(42);
        check("addLast after drain",               d.peekFirst() == 42 && d.peekLast() == 42);
        d.addFirst(41);
        check("addFirst after drain",              d.toString().equals("[41, 42]"));
        d.clear();

        // ── Summary ──────────────────────────────────────────────
        System.out.println("\n════════════════════════════");
        System.out.println("  Results: " + passed + " passed, " + failed + " failed");
        System.out.println("════════════════════════════");
    }
}
 