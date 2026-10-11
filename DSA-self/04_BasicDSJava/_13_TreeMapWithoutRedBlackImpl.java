// ============================================================
// SortedMap — An interface in Java
// ============================================================
// Keys are always sorted (natural order or custom Comparator).
// Use when you need a sorted map with range queries — not just O(1) lookup.
// Prefer HashMap for pure O(1) lookup; use TreeMap when ORDER matters.
// FYI, TreeMap is actually a Red-Black BST. All operations O(log n).

// O(log n) Core operations  ★ most important for CP
// ---------------------------------------------------
// put(K key, V val)        -> V          insert or update; returns old value (null if new)
// putIfAbsent(K key, V val)-> V          only insert if key absent; returns existing value (null if absent); returns current value (even null) if key exists
// get(K key)               -> V          returns null if key absent
// getOrDefault(K key, V d) -> V          returns d if key absent OR if key's value is null (⚠ same as HashMap, not truly key-aware)
// remove(K key)            -> V          returns removed value, null if absent
// remove(K key, V val)     -> boolean    only remove if key exists AND value matches; returns true if removed
// containsKey(K key)       -> boolean
// containsValue(V val)     -> boolean    O(n) — linear scan (no index on values)
// size()                   -> int
// isEmpty()                -> boolean
// clear()                  -> void
// replace(K key, V val)          -> V       only update if key exists; returns old value (null if absent)
// replace(K key, V old, V newV)  -> boolean only update if key exists AND old value matches; returns true if updated
// merge(K key, V val, BiFunction<? super V, ? super V, ? extends V> fn)
//                          -> V          if key absent (or value null), set to val; else apply fn(existing, val); returns new value

// O(1) Utility
// -------------
// comparator()             -> Comparator<? super K>   returns the comparator used to order keys, or null if natural ordering

// O(log n) Sorted-order navigation  ★★ killer feature vs HashMap
// ---------------------------------------------------------------
// firstKey()               -> K          smallest key; throws NoSuchElementException if empty
// lastKey()                -> K          largest key;  throws NoSuchElementException if empty
// floorKey(K key)          -> K          largest key <= given; null if none
// ceilingKey(K key)        -> K          smallest key >= given; null if none
// lowerKey(K key)          -> K          largest key <  given (strictly); null if none
// higherKey(K key)         -> K          smallest key >  given (strictly); null if none

// getEntry(K key)          -> Map.Entry  internal helper to find node by key; returns null if not found
// firstEntry()             -> Map.Entry  smallest key-value pair; throws NoSuchElementException if empty
// lastEntry()              -> Map.Entry  largest key-value pair;  throws NoSuchElementException if empty
// pollFirstEntry()         -> Map.Entry  remove & return smallest; null if empty
// pollLastEntry()          -> Map.Entry  remove & return largest;  null if empty
// floorEntry(K key)        -> Map.Entry  entry with largest key <= given; null if none
// ceilingEntry(K key)      -> Map.Entry  entry with smallest key >= given; null if none
// lowerEntry(K key)        -> Map.Entry  entry with largest key <  given (strictly); null if none
// higherEntry(K key)       -> Map.Entry  entry with smallest key >  given (strictly); null if none

// O(log n + result) Range views (live, backed by original map) : NOT IMPLEMENTED HERE
// -------------------------------------------------------------
// headMap(K toKey)                         -> SortedMap    keys strictly < toKey
// headMap(K toKey, boolean inclusive)      -> NavigableMap keys < toKey (or <= if inclusive)
// tailMap(K fromKey)                       -> SortedMap    keys >= fromKey
// tailMap(K fromKey, boolean inclusive)    -> NavigableMap keys > fromKey (or >= if inclusive)
// subMap(K from, K to)                     -> SortedMap    keys in [from, to)
// subMap(K from, boolean, K to, boolean)   -> NavigableMap full inclusive/exclusive control

// O(n) Iteration
// ---------------
// keySet()                 -> Set<K>            ascending order
// values()                 -> Collection<V>     insertion order within each key level (use entrySet for sorted values)
// entrySet()               -> Set<Entry<K,V>>   unordered set; iterate keySet() for sorted order
// descendingKeySet()       -> NavigableSet<K>   descending order
// descendingMap()          -> NavigableMap<K,V> full map view in reverse key order
// forEach(BiConsumer fn)   -> void              ascending comparator order; iterative in-order BST traversal; O(n), no intermediate collection

// Common CP Patterns
// ------------------
// Frequency Map (sorted)   — put(x, getOrDefault(x,0)+1); iterate keySet() in order
// Predecessor / Successor  — lowerKey / higherKey  (BST predecessor/successor)
// Range Count              — subMap(lo, true, hi, true).size()
// K-th Smallest Key        — not O(log n) in TreeMap; use Order-Statistics Tree or sorted list
// Sliding Window Min/Max   — TreeMap<val, freq>; firstKey()/lastKey(); remove key when freq hits 0
// Coordinate Compression   — put compressed index; floor/ceiling for range queries
// Meeting Rooms / Intervals— ceilingKey to find next non-overlapping interval
// Count of smaller numbers — track sorted insertions; use headMap(x).size() for count < x

// ============================================================

import java.util.ArrayDeque;
import java.util.Collection;
import java.util.Comparator;
import java.util.Deque;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Objects;
import java.util.Queue;
import java.util.Set;
import java.util.TreeSet;
import java.util.function.BiConsumer;
import java.util.function.BiFunction;

class MySortedMap<K, V> {
    class MySortedMapNode<X, Y> {
        X key;
        Y value;
        MySortedMapNode<X, Y> left;
        MySortedMapNode<X, Y> right;

        MySortedMapNode(X key, Y value) {
            this.key = key;
            this.value = value;
            this.left = this.right = null;
        }

        void clearNode() {
            this.key = null;
            this.value = null;
            this.left = null;
            this.right = null;
        }
    }

    MySortedMapNode<K, V> root;
    Comparator<? super K> cmp;
    private int size;

    MySortedMap() {
        this.root = null;
        this.cmp = null;
        this.size = 0;
    }

    MySortedMap(Comparator<? super K> comparator) {
        this.root = null;
        this.cmp = comparator;
        this.size = 0;
    }

    @SuppressWarnings("unchecked")
    private int compare(K key1, K key2) {
        if (cmp != null) {
            return cmp.compare(key1, key2);
        } else {
            return ((Comparable<K>) key1).compareTo(key2);
        }
    }

    // ── Core operations ────────────────────────
    V put(K key, V val) {
        if (isEmpty()) {
            root = new MySortedMapNode<>(key, val);
            size++;
            return null;
        }
        MySortedMapNode<K, V> parent = null;
        MySortedMapNode<K, V> itr = root;
        while (itr != null) {
            parent = itr;

            if (compare(key, itr.key) == 0) {
                V oldData = itr.value;
                itr.value = val;
                return oldData;
            } else if (compare(key, itr.key) <= 0) {
                itr = itr.left;
            } else {
                itr = itr.right;
            }
        }
        MySortedMapNode<K, V> node = new MySortedMapNode<>(key, val);
        if (compare(key, parent.key) <= 0)
            parent.left = node;
        else
            parent.right = node;
        size++;
        return null;
    }

    V putIfAbsent(K key, V val) {
        if (isEmpty()) {
            root = new MySortedMapNode<>(key, val);
            size++;
            return null;
        }
        MySortedMapNode<K, V> parent = null;
        MySortedMapNode<K, V> itr = root;
        while (itr != null) {
            parent = itr;

            if (compare(key, itr.key) == 0) {
                // TreeMap replaces value if key is found and value is null.
                V oldData = itr.value;
                if (itr.value == null)
                    itr.value = val;
                return oldData;
            } else if (compare(key, itr.key) <= 0) {
                itr = itr.left;
            } else {
                itr = itr.right;
            }
        }
        MySortedMapNode<K, V> node = new MySortedMapNode<>(key, val);
        if (compare(key, parent.key) <= 0)
            parent.left = node;
        else
            parent.right = node;
        size++;
        return null;
    }

    V get(K key) {
        MySortedMapNode<K, V> itr = root;
        while (itr != null) {
            if (compare(key, itr.key) == 0) {
                return itr.value;
            } else if (compare(key, itr.key) <= 0) {
                itr = itr.left;
            } else {
                itr = itr.right;
            }
        }
        return null;
    }

    V getOrDefault(K key, V defaultVal) {
        // TreeMap returns defaultVal even if key is found and corresponding value is
        // null
        V returnValue = get(key);
        return returnValue == null ? defaultVal : returnValue;
    }

    MySortedMapNode<K, V> remove(K key, MySortedMapNode<K, V> node) {
        if (node == null)
            return null;

        if (compare(key, node.key) == 0) {
            if (node.left == null) {
                MySortedMapNode<K, V> right = node.right; // save before clearNode nulls it
                node.clearNode(); // good practice to cleanup ref for GC
                size--;
                return right;
            } else if (node.right == null) {
                MySortedMapNode<K, V> left = node.left; // save before clearNode nulls it
                node.clearNode();
                size--;
                return left;
            } else {
                // find in-order predecessor: rightmost node of left subtree
                MySortedMapNode<K, V> itr = node.left;
                while (itr.right != null) {
                    itr = itr.right;
                }
                node.key = itr.key;
                node.value = itr.value;
                node.left = remove(itr.key, node.left);
                return node;
            }
        } else if (compare(key, node.key) <= 0) {
            node.left = remove(key, node.left);
            return node;
        } else {
            node.right = remove(key, node.right);
            return node;
        }
    }

    V remove(K key) {
        Entry<K, V> p = getEntry(key);
        if (p == null)
            return null;
        V oldData = p.getValue();
        root = remove(key, root);
        return oldData;
    }

    boolean remove(K key, V val) {
        Entry<K, V> p = getEntry(key);
        if (p == null)
            return false;

        V oldData = p.getValue();
        if (Objects.equals(oldData, val)) {
            root = remove(key, root);
            return true;
        }
        return false;
    }

    boolean containsKey(K key) {
        MySortedMapNode<K, V> itr = root;
        while (itr != null) {
            if (compare(key, itr.key) == 0) {
                return true;
            } else if (compare(key, itr.key) <= 0) {
                itr = itr.left;
            } else {
                itr = itr.right;
            }
        }
        return false;
    }

    boolean containsValue(V val) {
        if (isEmpty())
            return false;
        Queue<MySortedMapNode<K, V>> pending = new LinkedList<>();
        pending.add(root);
        while (!pending.isEmpty()) {
            MySortedMapNode<K, V> front = pending.remove();
            if (Objects.equals(front.value, val))
                return true;

            if (front.left != null)
                pending.add(front.left);
            if (front.right != null)
                pending.add(front.right);
        }
        return false;
    }

    int size() {
        return size;
    }

    boolean isEmpty() {
        return size == 0;
    }

    void clear() {
        if (isEmpty())
            return;
        // root = null; size = 0; doing this should be enough, but we should cleanup all
        // ref
        Queue<MySortedMapNode<K, V>> pending = new LinkedList<>();
        pending.add(root);
        while (!pending.isEmpty()) {
            MySortedMapNode<K, V> front = pending.remove();

            if (front.left != null)
                pending.add(front.left);
            if (front.right != null)
                pending.add(front.right);
            front.clearNode();
        }
        root = null;
        size = 0;
    }

    V merge(K key, V val, BiFunction<? super V, ? super V, ? extends V> fn) {
        V oldVal = get(key);
        if (oldVal == null) {
            put(key, val);
            return val;
        } else {
            V newVal = fn.apply(oldVal, val);
            put(key, newVal);
            return newVal;
        }
    }

    // ── Sorted Navigation ────────────────────────────────────────────────────
    Entry<K, V> getEntry(K key) {
        MySortedMapNode<K, V> itr = root;
        while (itr != null) {
            if (compare(key, itr.key) == 0) {
                return Map.entry(itr.key, itr.value);
            } else if (compare(key, itr.key) <= 0) {
                itr = itr.left;
            } else {
                itr = itr.right;
            }
        }
        return null;
    }

    K firstKey() {
        if (isEmpty())
            throw new java.util.NoSuchElementException();
        MySortedMapNode<K, V> itr = root;
        while (itr.left != null) {
            itr = itr.left;
        }
        return itr.key;
    }

    K lastKey() {
        if (isEmpty())
            throw new java.util.NoSuchElementException();
        MySortedMapNode<K, V> itr = root;
        while (itr.right != null) {
            itr = itr.right;
        }
        return itr.key;
    }

    K floorKey(K key) {
        K floor = null;
        MySortedMapNode<K, V> itr = root;
        while (itr != null) {
            if (compare(key, itr.key) == 0) {
                return itr.key;
            } else if (compare(key, itr.key) < 0) {
                itr = itr.left;
            } else {
                floor = itr.key;
                itr = itr.right;
            }
        }
        return floor;
    }

    // lowerKey ~= floorKey but strictly less than given key
    K lowerKey(K key) {
        K lower = null;
        MySortedMapNode<K, V> itr = root;
        while (itr != null) {
            if (compare(key, itr.key) <= 0) {
                itr = itr.left;
            } else {
                lower = itr.key;
                itr = itr.right;
            }
        }
        return lower;
    }

    K ceilingKey(K key) {
        K ceiling = null;
        MySortedMapNode<K, V> itr = root;
        while (itr != null) {
            if (compare(key, itr.key) == 0) {
                return itr.key;
            } else if (compare(key, itr.key) > 0) {
                itr = itr.right;
            } else {
                ceiling = itr.key;
                itr = itr.left;
            }
        }
        return ceiling;
    }

    // higherKey ~= ceilingKey but strictly greater than given key
    K higherKey(K key) {
        K higher = null;
        MySortedMapNode<K, V> itr = root;
        while (itr != null) {
            if (compare(key, itr.key) >= 0) {
                itr = itr.right;
            } else {
                higher = itr.key;
                itr = itr.left;
            }
        }
        return higher;
    }

    Map.Entry<K, V> firstEntry() {
        if (isEmpty())
            throw new java.util.NoSuchElementException();
        MySortedMapNode<K, V> itr = root;
        while (itr.left != null) {
            itr = itr.left;
        }
        return Map.entry(itr.key, itr.value);
    }

    Map.Entry<K, V> lastEntry() {
        if (isEmpty())
            throw new java.util.NoSuchElementException();
        MySortedMapNode<K, V> itr = root;
        while (itr.right != null) {
            itr = itr.right;
        }
        return Map.entry(itr.key, itr.value);
    }

    Map.Entry<K, V> pollFirstEntry() {
        if (isEmpty())
            return null;
        Map.Entry<K, V> first = firstEntry(); // we need to return it as well, hence not using remove(firstKey())
        remove(first.getKey());
        return first;
    }

    Map.Entry<K, V> pollLastEntry() {
        if (isEmpty())
            return null;
        Map.Entry<K, V> last = lastEntry(); // we need to return it as well, hence not using remove(lastKey())
        remove(last.getKey());
        return last;
    }

    // --------Following 4 methods are similar to their key counterparts but return
    // entry instead of key--------
    Map.Entry<K, V> floorEntry(K key) {
        Map.Entry<K, V> floor = null;
        MySortedMapNode<K, V> itr = root;
        while (itr != null) {
            if (compare(key, itr.key) == 0) {
                return Map.entry(itr.key, itr.value);
            } else if (compare(key, itr.key) < 0) {
                itr = itr.left;
            } else {
                floor = Map.entry(itr.key, itr.value);
                itr = itr.right;
            }
        }
        return floor;
    }

    Map.Entry<K, V> ceilingEntry(K key) {
        Map.Entry<K, V> ceiling = null;
        MySortedMapNode<K, V> itr = root;
        while (itr != null) {
            if (compare(key, itr.key) == 0) {
                return Map.entry(itr.key, itr.value);
            } else if (compare(key, itr.key) > 0) {
                itr = itr.right;
            } else {
                ceiling = Map.entry(itr.key, itr.value);
                itr = itr.left;
            }
        }
        return ceiling;
    }

    Map.Entry<K, V> lowerEntry(K key) {
        Map.Entry<K, V> lower = null;
        MySortedMapNode<K, V> itr = root;
        while (itr != null) {
            if (compare(key, itr.key) <= 0) {
                itr = itr.left;
            } else {
                lower = Map.entry(itr.key, itr.value);
                itr = itr.right;
            }
        }
        return lower;
    }

    Map.Entry<K, V> higherEntry(K key) {
        Map.Entry<K, V> higher = null;
        MySortedMapNode<K, V> itr = root;
        while (itr != null) {
            if (compare(key, itr.key) >= 0) {
                itr = itr.right;
            } else {
                higher = Map.entry(itr.key, itr.value);
                itr = itr.left;
            }
        }
        return higher;
    }

    // ── Iteration ────────────────────────────────────────────────────────────
    Set<K> keySet() {
        // 1. Use TreeSet to guarantee ascending sorted order (matches TreeMap.keySet()
        // contract)
        TreeSet<K> keys = cmp == null ? new TreeSet<>() : new TreeSet<>(cmp);
        // 2. Do a In-order traversal to a get list in sorted order if cmp is null. If
        // cmp is not null, we can do any traversal since TreeSet will sort it for us.

        if (isEmpty())
            return keys;

        Queue<MySortedMapNode<K, V>> pending = new LinkedList<>();
        pending.add(root);
        while (!pending.isEmpty()) {
            MySortedMapNode<K, V> front = pending.remove();
            keys.add(front.key);
            if (front.left != null)
                pending.add(front.left);
            if (front.right != null)
                pending.add(front.right);
        }
        return keys;
    }

    Collection<V> values() {
        if (isEmpty())
            return List.of();
        List<V> values = new LinkedList<>();
        Queue<MySortedMapNode<K, V>> pending = new LinkedList<>();
        pending.add(root);
        while (!pending.isEmpty()) {
            MySortedMapNode<K, V> front = pending.remove();
            values.add(front.value);
            if (front.left != null)
                pending.add(front.left);
            if (front.right != null)
                pending.add(front.right);
        }
        return values;
    }

    Set<Map.Entry<K, V>> entrySet() {
        if (isEmpty())
            return Set.of();
        Set<Map.Entry<K, V>> entries = new HashSet<>();
        Queue<MySortedMapNode<K, V>> pending = new LinkedList<>();
        pending.add(root);
        while (!pending.isEmpty()) {
            MySortedMapNode<K, V> front = pending.remove();
            entries.add(Map.entry(front.key, front.value));
            if (front.left != null)
                pending.add(front.left);
            if (front.right != null)
                pending.add(front.right);
        }
        return entries;
    }

    Set<K> descendingKeySet() {
        // TreeMap's descendingKeySet returns a NavigableSet view of the keys in reverse
        // order.
        // For simplicity, we can return a new TreeSet with reversed comparator, but
        // that would be O(n log n).
        MySortedMap<K, V> descMap = descendingMap();
        return descMap.keySet();
    }

    @SuppressWarnings("unchecked")
    MySortedMap<K, V> descendingMap() {
        MySortedMap<K, V> descMap = new MySortedMap<>();
        descMap.cmp = cmp == null ? (Comparator<? super K>) Comparator.reverseOrder() : cmp.reversed();
        for (Map.Entry<K, V> entry : entrySet()) {
            descMap.put(entry.getKey(), entry.getValue());
        }
        return descMap;
    }

    // Iterative in-order traversal → visits entries in ascending comparator order,
    // O(n) time/space
    void forEach(BiConsumer<? super K, ? super V> action) {
        if (isEmpty())
            return;
        Deque<MySortedMapNode<K, V>> pending = new ArrayDeque<>();
        MySortedMapNode<K, V> curr = root;
        while (curr != null || !pending.isEmpty()) {
            while (curr != null) {
                pending.push(curr);
                curr = curr.left;
            }
            MySortedMapNode<K, V> front = pending.pop();
            action.accept(front.key, front.value);
            curr = front.right;
        }
    }

    // ── Extra ────────────────────────────────────────────────────────────────
    Comparator<? super K> comparator() {
        return cmp;
    }

    V replace(K key, V val) {
        if (containsKey(key)) {
            return put(key, val);
        }
        return null;
    }

    boolean replace(K key, V oldVal, V newVal) {
        Entry<K, V> p = getEntry(key);
        if (p == null)
            return false;

        V value = p.getValue();
        if (Objects.equals(value, oldVal)) {
            put(key, newVal);
            return true;
        }
        return false;
    }
}

public class _13_TreeMapWithoutRedBlackImpl {

    static void check(boolean condition, String msg) {
        if (!condition)
            throw new AssertionError("FAIL: " + msg);
    }

    public static void main(String[] args) {

        // ── 1. Basic put / get / containsKey / size ──────────────────────────
        System.out.println("1. Basic put / get / containsKey / size");
        {
            MySortedMap<Integer, String> map = new MySortedMap<>();
            check(map.put(5, "five") == null, "put new key returns null");
            check(map.put(3, "three") == null, "put new key returns null");
            check(map.put(7, "seven") == null, "put new key returns null");
            check(map.put(1, "one") == null, "put new key returns null");
            check(map.put(9, "nine") == null, "put new key returns null");
            check("five".equals(map.put(5, "FIVE")), "put existing returns old value");
            check("FIVE".equals(map.get(5)), "get returns updated value");
            check(map.get(99) == null, "get missing key returns null");
            check(map.containsKey(3), "containsKey existing");
            check(!map.containsKey(99), "containsKey missing");
            check(map.size() == 5, "size");
            check(!map.isEmpty(), "not empty");
        }
        System.out.println("   PASS");

        // ── 2. Remove: leaf, one-child, two-children ─────────────────────────
        System.out.println("2. Remove: leaf / one-child / two-children");
        {
            MySortedMap<Integer, String> map = new MySortedMap<>();
            // 5
            // / \
            // 3 7
            // / \ \
            // 1 4 9
            for (int k : new int[] { 5, 3, 7, 1, 4, 9 })
                map.put(k, "v" + k);

            // remove leaf (1)
            check("v1".equals(map.remove(1)), "remove leaf returns value");
            check(!map.containsKey(1) && map.size() == 5, "leaf removed");

            // remove node with one child (7 now has only right child 9)
            check("v7".equals(map.remove(7)), "remove one-child node returns value");
            check(!map.containsKey(7) && map.containsKey(9), "one-child remove correct");

            // remove root (5) which has two children
            check("v5".equals(map.remove(5)), "remove two-children root returns value");
            check(!map.containsKey(5), "two-children node removed");
            check(map.containsKey(3) && map.containsKey(4) && map.containsKey(9),
                    "children still present after two-children remove");
            check(map.size() == 3, "size after removes");

            // remove missing key
            check(map.remove(99) == null, "remove missing returns null");
        }
        System.out.println("   PASS");

        // ── 3. Two-children remove regression ────────────────────────────────
        // Bug: when left child has no right child, old code copied the node's
        // own key back (no-op) then deleted the WRONG node from the left subtree.
        System.out.println("3. Two-children remove regression (left child has no right child)");
        {
            MySortedMap<Integer, String> map = new MySortedMap<>();
            // 3
            // / \
            // 1 5
            map.put(3, "3");
            map.put(1, "1");
            map.put(5, "5");
            map.remove(3);
            check(!map.containsKey(3), "root removed");
            check(map.containsKey(1) && map.containsKey(5), "both children intact");
            check(map.size() == 2, "size correct");
            check(map.firstKey().equals(1) && map.lastKey().equals(5), "BST order preserved");
        }
        System.out.println("   PASS");

        // ── 4. Navigation: floor / ceiling / lower / higher ──────────────────
        System.out.println("4. Navigation: floor / ceiling / lower / higher");
        {
            MySortedMap<Integer, String> map = new MySortedMap<>();
            for (int k : new int[] { 10, 20, 30, 40, 50 })
                map.put(k, "v" + k);

            check(map.floorKey(25).equals(20), "floorKey between keys");
            check(map.floorKey(20).equals(20), "floorKey exact match");
            check(map.floorKey(5) == null, "floorKey below all keys → null");

            check(map.ceilingKey(25).equals(30), "ceilingKey between keys");
            check(map.ceilingKey(30).equals(30), "ceilingKey exact match");
            check(map.ceilingKey(60) == null, "ceilingKey above all keys → null");

            check(map.lowerKey(20).equals(10), "lowerKey strict");
            check(map.lowerKey(10) == null, "lowerKey below all → null");
            check(map.lowerKey(25).equals(20), "lowerKey between");

            check(map.higherKey(40).equals(50), "higherKey strict");
            check(map.higherKey(50) == null, "higherKey above all → null");
            check(map.higherKey(25).equals(30), "higherKey between");
        }
        System.out.println("   PASS");

        // ── 5. firstKey / lastKey / firstEntry / lastEntry ───────────────────
        System.out.println("5. firstKey / lastKey / firstEntry / lastEntry");
        {
            MySortedMap<Integer, String> map = new MySortedMap<>();
            for (int k : new int[] { 10, 20, 30 })
                map.put(k, "v" + k);
            check(map.firstKey().equals(10), "firstKey");
            check(map.lastKey().equals(30), "lastKey");
            check("v10".equals(map.firstEntry().getValue()), "firstEntry value");
            check("v30".equals(map.lastEntry().getValue()), "lastEntry value");
        }
        System.out.println("   PASS");

        // ── 6. pollFirstEntry / pollLastEntry ────────────────────────────────
        System.out.println("6. pollFirstEntry / pollLastEntry");
        {
            MySortedMap<Integer, String> map = new MySortedMap<>();
            for (int k : new int[] { 10, 20, 30, 40, 50 })
                map.put(k, "v" + k);

            check(map.pollFirstEntry().getKey().equals(10), "pollFirst removes smallest");
            check(map.firstKey().equals(20) && map.size() == 4, "map state after pollFirst");

            check(map.pollLastEntry().getKey().equals(50), "pollLast removes largest");
            check(map.lastKey().equals(40) && map.size() == 3, "map state after pollLast");

            // empty map — must return null, not throw NoSuchElementException
            MySortedMap<Integer, String> empty = new MySortedMap<>();
            check(empty.pollFirstEntry() == null, "pollFirst on empty → null");
            check(empty.pollLastEntry() == null, "pollLast on empty → null");
        }
        System.out.println("   PASS");

        // ── 7. clear() / containsValue() on empty map (NPE regression) ───────
        System.out.println("7. clear / containsValue on empty map");
        {
            MySortedMap<Integer, String> map = new MySortedMap<>();
            map.clear(); // must not throw NPE
            check(!map.containsValue("x"), "containsValue on empty map");

            map.put(1, "a");
            map.put(2, "b");
            check(map.containsValue("a"), "containsValue found");
            check(!map.containsValue("z"), "containsValue not found");

            map.clear();
            check(map.isEmpty() && map.size() == 0, "clear empties the map");
        }
        System.out.println("   PASS");

        // ── 8. keySet sorted order ────────────────────────────────────────────
        System.out.println("8. keySet sorted order");
        {
            MySortedMap<Integer, String> map = new MySortedMap<>();
            for (int k : new int[] { 5, 3, 7, 1, 4, 6, 9 })
                map.put(k, "v" + k);
            Integer prev = null;
            for (Integer k : map.keySet()) {
                if (prev != null)
                    check(k > prev, "keySet not in ascending order at " + k);
                prev = k;
            }
        }
        System.out.println("   PASS");

        // ── 9. Custom comparator (reverse order) ─────────────────────────────
        System.out.println("9. Custom comparator (reverse order)");
        {
            MySortedMap<Integer, String> map = new MySortedMap<>(); // MySortedMap<>(Comparator.reverseOrder()) doesn't
                                                                    // work since Comparator.reverseOrder() returns <T>
                                                                    // and not <? super T>
            map.cmp = Comparator.reverseOrder();
            map.put(5, "five");
            map.put(3, "three");
            map.put(7, "seven");
            // In reverse order the tree sorts: 7 < 5 < 3 (7 is "first")
            check(map.firstKey().equals(7), "firstKey with reverseOrder");
            check(map.lastKey().equals(3), "lastKey with reverseOrder");
            // floorKey(6): largest key ≤ 6 in comparator order → 7 (since 7 < 6 < 5 < 3 in
            // rev)
            check(map.floorKey(6).equals(7), "floorKey with reverseOrder");
            // ceilingKey(4): smallest key ≥ 4 in comparator order → 3 (since 3 > 4 in rev)
            check(map.ceilingKey(4).equals(3), "ceilingKey with reverseOrder");
        }
        System.out.println("   PASS");

        // ── 10. putIfAbsent / merge / replace ────────────────────────────────
        System.out.println("10. putIfAbsent / merge / replace / remove(key,val)");
        {
            MySortedMap<String, Integer> map = new MySortedMap<>();
            map.put("a", 1);
            check(map.putIfAbsent("a", 99).equals(1), "putIfAbsent existing → returns current value");
            check(map.get("a").equals(1), "putIfAbsent does not overwrite");
            check(map.putIfAbsent("b", 5) == null, "putIfAbsent new key → null");
            check(map.get("b").equals(5), "putIfAbsent new key stored");

            map.merge("a", 1, Integer::sum); // 1 + 1 = 2
            check(map.get("a").equals(2), "merge existing key");
            map.merge("c", 1, Integer::sum); // new key → 1
            check(map.get("c").equals(1), "merge new key");

            check(map.replace("a", 10).equals(2), "replace returns old value");
            check(map.get("a").equals(10), "replace updates value");
            check(map.replace("z", 5) == null, "replace missing key → null");
            check(map.replace("a", 10, 99), "replace(key,old,new) success");
            check(!map.replace("a", 10, 0), "replace(key,old,new) fail (old mismatch)");

            check(map.remove("a", 99), "remove(key,val) success");
            check(!map.containsKey("a"), "remove(key,val) actually removed");
            check(!map.remove("b", 999), "remove(key,val) fail (val mismatch)");
            check(map.containsKey("b"), "remove(key,val) did not remove on mismatch");
        }
        System.out.println("   PASS");

        // ── 11. getOrDefault ──────────────────────────────────────────────────
        System.out.println("11. getOrDefault");
        {
            MySortedMap<Integer, String> map = new MySortedMap<>();
            map.put(1, "one");
            check("one".equals(map.getOrDefault(1, "default")), "getOrDefault existing key");
            check("default".equals(map.getOrDefault(99, "default")), "getOrDefault missing key");
        }
        System.out.println("   PASS");

        // ── 12. Entry-based navigation ────────────────────────────────────────
        System.out.println("12. Entry-based navigation (floorEntry / ceilingEntry / lowerEntry / higherEntry)");
        {
            MySortedMap<Integer, String> map = new MySortedMap<>();
            for (int k : new int[] { 10, 20, 30, 40, 50 })
                map.put(k, "v" + k);

            check("v20".equals(map.floorEntry(25).getValue()), "floorEntry between keys");
            check("v30".equals(map.ceilingEntry(25).getValue()), "ceilingEntry between keys");
            check("v10".equals(map.lowerEntry(20).getValue()), "lowerEntry strict");
            check("v50".equals(map.higherEntry(40).getValue()), "higherEntry strict");
            check(map.lowerEntry(10) == null, "lowerEntry below all → null");
            check(map.higherEntry(50) == null, "higherEntry above all → null");
        }
        System.out.println("   PASS");

        // ── 13. getEntry ──────────────────────────────────────────────────────
        System.out.println("13. getEntry");
        {
            MySortedMap<Integer, String> map = new MySortedMap<>();
            map.put(10, "ten");
            map.put(20, "twenty");
            Map.Entry<Integer, String> e = map.getEntry(10);
            check(e != null && e.getKey().equals(10) && "ten".equals(e.getValue()), "getEntry existing key");
            check(map.getEntry(99) == null, "getEntry missing key → null");
        }
        System.out.println("   PASS");

        // ── 14. values / entrySet ─────────────────────────────────────────────
        System.out.println("14. values / entrySet");
        {
            MySortedMap<Integer, String> map = new MySortedMap<>();
            map.put(1, "a");
            map.put(2, "b");
            map.put(3, "c");

            java.util.Collection<String> vals = map.values();
            check(vals.size() == 3 && vals.contains("a") && vals.contains("b") && vals.contains("c"),
                    "values contains all entries");

            java.util.Set<Map.Entry<Integer, String>> entries = map.entrySet();
            check(entries.size() == 3, "entrySet size");
            boolean found = false;
            for (Map.Entry<Integer, String> en : entries)
                if (en.getKey().equals(2) && "b".equals(en.getValue())) {
                    found = true;
                    break;
                }
            check(found, "entrySet contains (2, b)");
        }
        System.out.println("   PASS");

        // ── 15. descendingKeySet / descendingMap ──────────────────────────────
        System.out.println("15. descendingKeySet / descendingMap");
        {
            MySortedMap<Integer, String> map = new MySortedMap<>();
            for (int k : new int[] { 10, 20, 30, 40 })
                map.put(k, "v" + k);

            // descendingKeySet: must be in descending order
            Integer prev = null;
            for (Integer k : map.descendingKeySet()) {
                if (prev != null)
                    check(k < prev, "descendingKeySet not in descending order at " + k);
                prev = k;
            }
            check(prev.equals(10), "descendingKeySet last element is smallest key");

            // descendingMap: firstKey should be the largest
            MySortedMap<Integer, String> desc = map.descendingMap();
            check(desc.firstKey().equals(40), "descendingMap firstKey is largest");
            check(desc.lastKey().equals(10), "descendingMap lastKey is smallest");
            check("v40".equals(desc.get(40)), "descendingMap get existing key");
        }
        System.out.println("   PASS");

        // ── 16. comparator() ──────────────────────────────────────────────────
        System.out.println("16. comparator()");
        {
            // natural ordering → comparator() must return null
            MySortedMap<Integer, String> natural = new MySortedMap<>();
            check(natural.comparator() == null, "natural order map: comparator() == null");

            // custom comparator → comparator() must return the same instance
            Comparator<Integer> rev = Comparator.reverseOrder();
            MySortedMap<Integer, String> custom = new MySortedMap<>(rev);
            check(custom.comparator() == rev, "custom comparator map: comparator() returns same instance");

            // verify the returned comparator actually governs order
            custom.put(1, "one");
            custom.put(2, "two");
            custom.put(3, "three");
            check(custom.firstKey().equals(3), "custom comparator: firstKey is largest (reverse order)");
            check(custom.comparator().compare(5, 3) < 0, "returned comparator: 5 < 3 in reverse order");
        }
        System.out.println("   PASS");

        // ── 17. forEach ───────────────────────────────────────────────────────
        System.out.println("17. forEach");
        {
            // ascending order with natural comparator
            MySortedMap<Integer, String> map = new MySortedMap<>();
            for (int k : new int[] { 30, 10, 50, 20, 40 })
                map.put(k, "v" + k);

            List<Integer> keys = new java.util.ArrayList<>();
            List<String> vals = new java.util.ArrayList<>();
            map.forEach((k, v) -> {
                keys.add(k);
                vals.add(v);
            });

            check(keys.equals(java.util.Arrays.asList(10, 20, 30, 40, 50)), "forEach ascending key order");
            check(vals.equals(java.util.Arrays.asList("v10", "v20", "v30", "v40", "v50")), "forEach values match keys");
            check(keys.size() == 5, "forEach visits all entries");

            // empty map — action must never be called
            int[] count = { 0 };
            new MySortedMap<Integer, String>().forEach((k, v) -> count[0]++);
            check(count[0] == 0, "forEach on empty map: 0 visits");

            // single-element map
            MySortedMap<Integer, String> single = new MySortedMap<>();
            single.put(42, "answer");
            List<Integer> singleKeys = new java.util.ArrayList<>();
            single.forEach((k, v) -> singleKeys.add(k));
            check(singleKeys.equals(java.util.Arrays.asList(42)), "forEach single-element map");

            // forEach respects custom comparator (reverse order → visits largest first)
            MySortedMap<Integer, String> rev = new MySortedMap<>();
            rev.cmp = Comparator.reverseOrder();
            rev.put(1, "a");
            rev.put(2, "b");
            rev.put(3, "c");
            List<Integer> revKeys = new java.util.ArrayList<>();
            rev.forEach((k, v) -> revKeys.add(k));
            check(revKeys.equals(java.util.Arrays.asList(3, 2, 1)), "forEach with reverseOrder comparator");
        }
        System.out.println("   PASS");

        System.out.println("\nAll tests passed!");
    }
}

/**
 * Output:
 * -------
 * 1. Basic put / get / containsKey / size
 *    PASS
 * 2. Remove: leaf / one-child / two-children
 *    PASS
 * 3. Two-children remove regression (left child has no right child)
 *    PASS
 * 4. Navigation: floor / ceiling / lower / higher
 *    PASS
 * 5. firstKey / lastKey / firstEntry / lastEntry
 *    PASS
 * 6. pollFirstEntry / pollLastEntry
 *    PASS
 * 7. clear / containsValue on empty map
 *    PASS
 * 8. keySet sorted order
 *    PASS
 * 9. Custom comparator (reverse order)
 *    PASS
 * 10. putIfAbsent / merge / replace / remove(key,val)
 *    PASS
 * 11. getOrDefault
 *    PASS
 * 12. Entry-based navigation (floorEntry / ceilingEntry / lowerEntry / higherEntry)
 *    PASS
 * 13. getEntry
 *    PASS
 * 14. values / entrySet
 *    PASS
 * 15. descendingKeySet / descendingMap
 *    PASS
 * 16. comparator()
 *    PASS
 * 17. forEach
 *    PASS
 * 
 * All tests passed!
 */