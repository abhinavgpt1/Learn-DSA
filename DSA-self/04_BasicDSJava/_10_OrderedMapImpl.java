import java.util.*;
import java.util.function.*;

// ============================================================
// LinkedHashMap — CP-focused cheat sheet
// HashMap + doubly-linked list | all ops O(1) avg | order preserved
// Use over HashMap when O(1) lookup AND iteration order both matter
// ============================================================

// ── Theory ──────────────────────────────────────────────────
// Internal structure:
//   HashMap<K, Node>     — O(1) lookup by key (same as HashMap)
//   Doubly-linked list   — threads through all nodes in insertion/access order
//
// Two ordering modes (chosen at construction):
//   Insertion-order (default) — iteration follows the order keys were FIRST put;
//                               re-putting an existing key does NOT change its position
//   Access-order              — new LinkedHashMap<>(cap, 0.75f, true)
//                               every get() or put() moves that entry to the TAIL (MRU end)
//                               HEAD = LRU (least recently used), TAIL = MRU (most recently used)
//
// Load factor & rehashing: same as HashMap (default capacity 16, load factor 0.75)
// Null keys/values: one null key allowed; multiple null values allowed

// ── Constructors ────────────────────────────────────────────
// new LinkedHashMap<>()                                        default cap 16, load 0.75, insertion-order
// new LinkedHashMap<>(int cap)
// new LinkedHashMap<>(int cap, float loadFactor)
// new LinkedHashMap<>(int cap, float load, boolean accessOrder)   true = access-order (LRU mode)
// new LinkedHashMap<>(Map<? extends K, ? extends V> m)            copy constructor; preserves m's order

// ── Core  O(1) avg ──────────────────────────────────────────
// put(key, val)                  -> V        insert/update; returns old val (null if new)
//                                            insertion-order: does NOT move existing key on re-put
//                                            access-order:    moves entry to TAIL on re-put
// putIfAbsent(key, val)          -> V        insert if absent; returns existing val (null if new)
//                                            does NOT trigger access-order move
// get(key)                       -> V        null if absent; moves to TAIL in access-order
// getOrDefault(key, def)         -> V        def if absent
// remove(key)                    -> V        removed val, null if absent
// remove(key, val)               -> boolean  remove only if key+val match
// containsKey(key)               -> boolean
// containsValue(val)             -> boolean  O(n) — walks linked list
// size() / isEmpty() / clear()
// replace(key, val)              -> V        update only if key exists; old val or null
// replace(key, oldVal, newVal)   -> boolean  update only if key+old match
// merge(key, val, fn)            -> V        absent/null → set val; else fn(existing, val); fn returning null removes key
// compute(key, fn)               -> V        fn(key, existing) → new val; null removes key; runs unconditionally
// computeIfAbsent(key, fn)       -> V        insert fn(key) only if key absent or null-mapped; fn returning null = no-op
// computeIfPresent(key, fn)      -> V        update fn(key, val) only if key present
// putAll(map)                    -> void     bulk-insert all entries from another map; preserves that map's iteration order
// replaceAll(fn)                 -> void     update every value in-place: val = fn(key, val); preserves key order

// ── Order-preserving  ★★ killer feature vs HashMap ──────────
// No firstKey/lastKey — use iterators or entrySet() to peek ends:
//   first (oldest/LRU):  map.entrySet().iterator().next()
//   last  (newest/MRU):  need to iterate to end (or maintain separate ref)
// Access-order: every get/put promotes entry to TAIL
// Use case: LRU eviction, recent-activity tracking, ordered dedup

// ── Iteration  O(n)  guaranteed in insertion/access order ───
// keySet()              Set<K>            oldest → newest
// values()              Collection<V>     oldest → newest
// entrySet()            Set<Entry<K,V>>   oldest → newest
// forEach((k, v) -> {})

// ── LRU Cache pattern  ★★★ most common interview use ────────
// Use access-order + override removeEldestEntry for auto-eviction:
//
//   int MAX = 3;
//   LinkedHashMap<Integer,Integer> lru = new LinkedHashMap<>(MAX, 0.75f, true) {
//       protected boolean removeEldestEntry(Map.Entry<Integer,Integer> eldest) {
//           return size() > MAX;   // evict HEAD (LRU) after every put
//       }
//   };
//   lru.put(1, 1);  lru.put(2, 2);  lru.put(3, 3);  // {1,2,3}
//   lru.get(1);                                       // {2,3,1}  ← 1 promoted to tail
//   lru.put(4, 4);                                    // {3,1,4}  ← 2 evicted (was LRU)
//
// removeEldestEntry is called AFTER the new entry is inserted,
// so size() already includes the new entry when you check it.
//
// Manual eviction (no subclass needed):
//   map.remove(map.entrySet().iterator().next().getKey()); // remove LRU head

// ── CP Patterns ─────────────────────────────────────────────
// Freq map (ordered)        merge(x, 1, Integer::sum); iterate keySet() in insertion order
// Deduplicate + keep order  put each element as key; keySet() = unique elements in first-seen order
// LRU Cache (LC 146)        access-order + removeEldestEntry (see above)
// First inserted key        keySet().iterator().next()
// Last inserted key         iterate to end, or maintain a separate tail reference
// Sliding window distinct   map<val, lastSeenIndex>; remove stale entries when index < windowStart
// Bounded memo / cache      access-order LRU; evict when size exceeds bound
// Detect cycle (ordered)    put nodes in insertion order; check if new node already in map

// ── LinkedHashMap vs HashMap vs TreeMap ─────────────────────
// HashMap        O(1)       no order guarantee               → pure speed
// LinkedHashMap  O(1)       insertion-order or access-order  → speed + remembered order
// TreeMap        O(log n)   always sorted by key             → range queries / min / max

// ── Gotchas ─────────────────────────────────────────────────
// putIfAbsent does NOT move entry in access-order (unlike get / put)
// re-put (put on existing key) DOES move entry in access-order
// removeEldestEntry is called post-insertion; size() already reflects the new node
// Never wrap entrySet()/keySet() in a HashSet — you'll lose the ordering guarantee
// Structural modification during forEach/iterator (except Iterator.remove) → ConcurrentModificationException

// ============================================================

class MyOrderedMap<K, V> {
    class Node {
        K key;
        V value;
        Node prev, next;

        Node(K k, V v) {
            key = k;
            value = v;
        }

        void clearNode() {
            key = null; // help GC
            value = null;
            prev = null;
            next = null;
        }
    }

    private MyHashMap<K, Node> map;
    private Node head, tail;
    private int size;

    // ── Constructors ────────────────────────────────────────
    MyOrderedMap() {
        map = new MyHashMap<>();
        head = null;
        tail = null;
        size = 0;
    }

    // ── Core O(1) ───────────────────────────────────────────
    V put(K key, V val) {
        if(map.containsKey(key)) {
            Node node = map.get(key);
            V oldVal = node.value;
            node.value = val;
            return oldVal;
        } else {
            Node newNode = new Node(key, val);
            map.put(key, newNode);
            if (head == null) {
                head = tail = newNode;
            } else {
                tail.next = newNode;
                newNode.prev = tail;
                tail = newNode;
            }
            size++;
            return null;
        }
    }

    V putIfAbsent(K key, V val) {
        if (map.containsKey(key)) {
            return map.get(key).value;
        } else {
            put(key, val);
            return null;
        }
    }

    V get(K key) {
        if (map.containsKey(key)) {
            return map.get(key).value;
        } else {
            return null;
        }
    }

    V getOrDefault(K key, V def) {
        if (map.containsKey(key)) {
            return map.get(key).value;
        } else {
            return def;
        }
    }

    V remove(K key) {
        if (!map.containsKey(key))
            return null;
        Node node = map.get(key);
        V oldVal = node.value;
        
        // Remove from map first to avoid confusion with linked list removal
        map.remove(key);
        
        // Remove from linked list
        if (node == head) {
            head = head.next;
            if (head == null) { // List is now empty
                tail = null;
            } else {
                head.prev = null;
            }
        } else if (node == tail) {
            tail = tail.prev;
            tail.next = null;
            // No need to check for tail == null here since if node was tail, it can't be head (handled above)
        } else {
            node.prev.next = node.next;
            node.next.prev = node.prev;
        }
        node.clearNode();
        size--;
        return oldVal;
    }

    boolean remove(K key, V val) {
        if (!map.containsKey(key))
            return false;
        Node node = map.get(key);
        if (!Objects.equals(node.value, val))
            return false;
        remove(key);
        return true;
    }

    boolean containsKey(K key) {
        return map.containsKey(key);
    }

    boolean containsValue(V val) {
        Node current = head;
        while (current != null) {
            if (Objects.equals(current.value, val)) {
                return true;
            }
            current = current.next;
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
        // Clear linked list
        Node current = head;
        while (current != null) {
            Node next = current.next;
            current.clearNode();
            current = next;
        }
        head = tail = null;
        
        // Clear map
        map.clear();
        
        size = 0;
    }

    V replace(K key, V val) {
        if (!map.containsKey(key))
            return null;
        Node node = map.get(key);
        V oldVal = node.value;
        node.value = val;
        return oldVal;
    }

    boolean replace(K key, V oldVal, V newVal) {
        if (!map.containsKey(key))
            return false;
        Node node = map.get(key);
        if (!Objects.equals(node.value, oldVal))
            return false;
        node.value = newVal;
        return true;
    }

    V merge(K key, V val, BiFunction<? super V, ? super V, ? extends V> fn) {
        if (!map.containsKey(key)) {
            put(key, val);
            return val;
        } else {
            Node node = map.get(key);
            V newVal = fn.apply(node.value, val);
            if (newVal == null) remove(key); // fn returning null removes the key
            else node.value = newVal;
            return newVal;
        }
    }

    // runs unconditionally; fn(key, null) if absent; null result removes key
    V compute(K key, BiFunction<? super K, ? super V, ? extends V> fn) {
        V existing = map.containsKey(key) ? map.get(key).value : null;
        V newVal = fn.apply(key, existing);
        if (newVal == null) remove(key);
        else put(key, newVal);
        return newVal;
    }

    // only runs if key absent OR key mapped to null; fn returning null = no-op (no insert)
    V computeIfAbsent(K key, Function<? super K, ? extends V> fn) {
        if (map.containsKey(key)) {
            V existing = map.get(key).value;
            if (existing != null) return existing; // key present with real value → return as-is
        }
        V newVal = fn.apply(key);
        if (newVal != null) put(key, newVal); // only insert if fn returned non-null
        return newVal;
    }

    // only runs if key present; fn returning null removes the key
    V computeIfPresent(K key, BiFunction<? super K, ? super V, ? extends V> fn) {
        if (!map.containsKey(key)) return null;
        Node node = map.get(key);
        V newVal = fn.apply(key, node.value);
        if (newVal == null) remove(key); // fn returning null removes the key
        else node.value = newVal;
        return newVal;
    }

    void putAll(Map<? extends K, ? extends V> m) {
        for (Map.Entry<? extends K, ? extends V> e : m.entrySet()) {
            put(e.getKey(), e.getValue());
        }
    }

    void replaceAll(BiFunction<? super K, ? super V, ? extends V> fn) {
        Node current = head;
        while (current != null) {
            current.value = fn.apply(current.key, current.value);
            current = current.next;
        }
    }

    // ── Iteration O(n) ──────────────────────────────────────
    Set<K> keySet() {
        Set<K> keys = new LinkedHashSet<>();
        Node current = head;
        while (current != null) {
            keys.add(current.key);
            current = current.next;
        }
        return keys;
    }

    Collection<V> values() {
        List<V> values = new ArrayList<>();
        Node current = head;
        while (current != null) {
            values.add(current.value);
            current = current.next;
        }
        return values;
    }

    Set<Map.Entry<K, V>> entrySet() {
        Set<Map.Entry<K, V>> entries = new LinkedHashSet<>();
        Node current = head;
        while (current != null) {
            entries.add(Map.entry(current.key, current.value));
            current = current.next;
        }
        return entries;
    }

    void forEach(BiConsumer<? super K, ? super V> action) {
        Node current = head;
        while (current != null) {
            action.accept(current.key, current.value);
            current = current.next;
        }
    }
}

public class _10_OrderedMapImpl {
    static int pass = 0, fail = 0;

    static void check(String label, boolean cond) {
        if (cond) { System.out.println("  PASS: " + label); pass++; }
        else       { System.out.println("  FAIL: " + label); fail++; }
    }

    public static void main(String[] args) {

        // ── 1. put / get / size / insertion order ────────────
        System.out.println("1. put / get / insertion order");
        MyOrderedMap<Integer, String> m = new MyOrderedMap<>();
        m.put(3, "three"); m.put(1, "one"); m.put(2, "two");
        check("get(3)=three",         "three".equals(m.get(3)));
        check("get(1)=one",           "one".equals(m.get(1)));
        check("size=3",               m.size() == 3);
        check("keySet order [3,1,2]", m.keySet().equals(new LinkedHashSet<>(Arrays.asList(3,1,2))));

        // ── 2. Re-put does NOT change order ──────────────────
        System.out.println("2. re-put keeps position");
        String oldVal = m.put(3, "THREE");
        check("returns old val 'three'",       "three".equals(oldVal));
        check("value updated to THREE",        "THREE".equals(m.get(3)));
        check("order still [3,1,2]",           m.keySet().equals(new LinkedHashSet<>(Arrays.asList(3,1,2))));
        check("size unchanged at 3",           m.size() == 3);

        // ── 3. getOrDefault ───────────────────────────────────
        System.out.println("3. getOrDefault");
        check("existing key returns val",      "one".equals(m.getOrDefault(1, "??")));
        check("missing key returns default",   "??".equals(m.getOrDefault(99, "??")));

        // ── 4. putIfAbsent ────────────────────────────────────
        System.out.println("4. putIfAbsent");
        String existing = m.putIfAbsent(1, "ONE");   // key exists
        m.putIfAbsent(4, "four");                     // new key
        check("returns existing val for present key",  "one".equals(existing));
        check("value not overwritten",                 "one".equals(m.get(1)));
        check("new key inserted",                      "four".equals(m.get(4)));
        check("size now 4",                            m.size() == 4);

        // ── 5. remove(key) and remove(key,val) ───────────────
        System.out.println("5. remove");
        m.remove(4);
        boolean r1 = m.remove(1, "wrong");   // mismatch → false
        boolean r2 = m.remove(1, "one");     // match → true
        check("remove(1,wrong)=false",  !r1);
        check("remove(1,one)=true",      r2);
        check("key 1 gone",             !m.containsKey(1));
        check("size now 2",              m.size() == 2);

        // ── 6. replace ────────────────────────────────────────
        System.out.println("6. replace");
        m.put(1, "one");
        String old = m.replace(1, "ONE");
        boolean swapped = m.replace(2, "two", "TWO");
        boolean noSwap  = m.replace(2, "two", "TWO2"); // wrong old val
        check("replace(1) returns 'one'",        "one".equals(old));
        check("replace(1) sets ONE",             "ONE".equals(m.get(1)));
        check("replace(2,two,TWO)=true",          swapped);
        check("replace(2,two,TWO2)=false",        !noSwap);
        check("replace missing key=null",         m.replace(99, "x") == null);

        // ── 7. containsKey / containsValue ───────────────────
        System.out.println("7. containsKey / containsValue");
        check("containsKey(1)=true",     m.containsKey(1));
        check("containsKey(99)=false",  !m.containsKey(99));
        check("containsValue(ONE)=true", m.containsValue("ONE"));
        check("containsValue(?)=false", !m.containsValue("nope"));

        // ── 8. merge ─────────────────────────────────────────
        System.out.println("8. merge");
        MyOrderedMap<String, Integer> freq = new MyOrderedMap<>();
        for (String w : new String[]{"a","b","a","c","b","a"})
            freq.merge(w, 1, Integer::sum);
        check("a=3", freq.get("a") == 3);
        check("b=2", freq.get("b") == 2);
        check("c=1", freq.get("c") == 1);
        check("order [a,b,c]", freq.keySet().equals(new LinkedHashSet<>(Arrays.asList("a","b","c"))));
        // merge with fn returning null → remove
        freq.merge("c", 1, (old2, v) -> null);
        check("merge fn=null removes key", !freq.containsKey("c"));

        // ── 9. compute ───────────────────────────────────────
        System.out.println("9. compute");
        MyOrderedMap<String, Integer> cm = new MyOrderedMap<>();
        cm.put("x", 10);
        cm.compute("x", (k, v) -> v + 5);                // update
        check("compute update 10+5=15",   cm.get("x") == 15);
        cm.compute("y", (k, v) -> v == null ? 1 : v + 1); // absent → insert
        check("compute absent inserts 1", cm.get("y") == 1);
        cm.compute("x", (k, v) -> null);                  // null → remove
        check("compute null removes key", !cm.containsKey("x"));

        // ── 10. computeIfAbsent ──────────────────────────────
        System.out.println("10. computeIfAbsent");
        MyOrderedMap<String, List<Integer>> grouped = new MyOrderedMap<>();
        grouped.computeIfAbsent("evens", k -> new ArrayList<>()).add(2);
        grouped.computeIfAbsent("evens", k -> new ArrayList<>()).add(4); // key present → no new list
        grouped.computeIfAbsent("odds",  k -> new ArrayList<>()).add(1);
        check("evens has [2,4]",   Arrays.asList(2,4).equals(grouped.get("evens")));
        check("odds has [1]",      Arrays.asList(1).equals(grouped.get("odds")));
        // fn returning null → no insert
        MyOrderedMap<String,String> ca = new MyOrderedMap<>();
        ca.computeIfAbsent("k", x -> null);
        check("computeIfAbsent fn=null does not insert", !ca.containsKey("k"));

        // ── 11. computeIfPresent ─────────────────────────────
        System.out.println("11. computeIfPresent");
        MyOrderedMap<String, Integer> cp = new MyOrderedMap<>();
        cp.put("a", 5);
        cp.computeIfPresent("a", (k, v) -> v * 2);
        check("computeIfPresent updates 5*2=10", cp.get("a") == 10);
        cp.computeIfPresent("missing", (k, v) -> 99); // absent → no-op
        check("computeIfPresent absent = no-op", !cp.containsKey("missing"));
        cp.computeIfPresent("a", (k, v) -> null);     // null → remove
        check("computeIfPresent fn=null removes key", !cp.containsKey("a"));

        // ── 12. replaceAll ────────────────────────────────────
        System.out.println("12. replaceAll");
        MyOrderedMap<String, Integer> ra = new MyOrderedMap<>();
        ra.put("a", 1); ra.put("b", 2); ra.put("c", 3);
        ra.replaceAll((k, v) -> v * 10);
        check("a=10", ra.get("a") == 10);
        check("b=20", ra.get("b") == 20);
        check("c=30", ra.get("c") == 30);
        check("order preserved", ra.keySet().equals(new LinkedHashSet<>(Arrays.asList("a","b","c"))));

        // ── 13. putAll ────────────────────────────────────────
        System.out.println("13. putAll");
        MyOrderedMap<Integer,String> dest = new MyOrderedMap<>();
        dest.put(1, "one");
        LinkedHashMap<Integer,String> src = new LinkedHashMap<>();
        src.put(2, "two"); src.put(3, "three");
        dest.putAll(src);
        check("size=3 after putAll",    dest.size() == 3);
        check("new key 2 present",      "two".equals(dest.get(2)));
        check("existing key 1 intact",  "one".equals(dest.get(1)));

        // ── 14. keySet / values / entrySet / forEach ─────────
        System.out.println("14. iteration");
        MyOrderedMap<Integer,Integer> iter = new MyOrderedMap<>();
        iter.put(10,100); iter.put(20,200); iter.put(30,300);
        check("keySet [10,20,30]",    iter.keySet().equals(new LinkedHashSet<>(Arrays.asList(10,20,30))));
        check("values [100,200,300]", iter.values().equals(Arrays.asList(100,200,300)));
        check("entrySet size=3",      iter.entrySet().size() == 3);
        List<Integer> fKeys = new ArrayList<>();
        iter.forEach((k, v) -> fKeys.add(k));
        check("forEach order [10,20,30]", fKeys.equals(Arrays.asList(10,20,30)));

        // ── 15. clear / isEmpty ───────────────────────────────
        System.out.println("15. clear / isEmpty");
        MyOrderedMap<String,String> cl = new MyOrderedMap<>();
        check("isEmpty on new map", cl.isEmpty());
        cl.put("x","1"); cl.put("y","2");
        check("not empty after puts", !cl.isEmpty());
        cl.clear();
        check("isEmpty after clear",  cl.isEmpty());
        check("size=0 after clear",   cl.size() == 0);
        check("key gone after clear", !cl.containsKey("x"));
        // reuse after clear
        cl.put("z", "3");
        check("put after clear works", "3".equals(cl.get("z")));

        // ── 16. remove head / tail / middle (linked-list edge cases) ──
        System.out.println("16. remove head/tail/middle");
        MyOrderedMap<Integer,String> rm = new MyOrderedMap<>();
        rm.put(1,"a"); rm.put(2,"b"); rm.put(3,"c"); rm.put(4,"d");
        rm.remove(1); // remove head
        check("remove head: key 1 gone",   !rm.containsKey(1));
        check("new head is 2",              rm.keySet().iterator().next() == 2);
        rm.remove(4); // remove tail
        check("remove tail: key 4 gone",   !rm.containsKey(4));
        rm.remove(3); // remove middle (now: 2,3 → remove 3, leaving 2)
        check("remove middle: key 3 gone", !rm.containsKey(3));
        check("only key 2 remains",         rm.size() == 1 && rm.containsKey(2));

        System.out.println("\n" + pass + " passed, " + fail + " failed.");
        if (fail == 0) System.out.println("All tests passed!");
    }
}

/**
 * Output:
 * 1. put / get / insertion order
 *   PASS: get(3)=three
 *   PASS: get(1)=one
 *   PASS: size=3
 *   PASS: keySet order [3,1,2]
 * 2. re-put keeps position
 *   PASS: returns old val 'three'
 *   PASS: value updated to THREE
 *   PASS: order still [3,1,2]
 *   PASS: size unchanged at 3
 * 3. getOrDefault
 *   PASS: existing key returns val
 *   PASS: missing key returns default
 * 4. putIfAbsent
 *   PASS: returns existing val for present key
 *   PASS: value not overwritten
 *   PASS: new key inserted
 *   PASS: size now 4
 * 5. remove
 *   PASS: remove(1,wrong)=false
 *   PASS: remove(1,one)=true
 *   PASS: key 1 gone
 *   PASS: size now 2
 * 6. replace
 *   PASS: replace(1) returns 'one'
 *   PASS: replace(1) sets ONE
 *   PASS: replace(2,two,TWO)=true
 *   PASS: replace(2,two,TWO2)=false
 *   PASS: replace missing key=null
 * 7. containsKey / containsValue
 *   PASS: containsKey(1)=true
 *   PASS: containsKey(99)=false
 *   PASS: containsValue(ONE)=true
 *   PASS: containsValue(?)=false
 * 8. merge
 *   PASS: a=3
 *   PASS: b=2
 *   PASS: c=1
 *   PASS: order [a,b,c]
 *   PASS: merge fn=null removes key
 * 9. compute
 *   PASS: compute update 10+5=15
 *   PASS: compute absent inserts 1
 *   PASS: compute null removes key
 * 10. computeIfAbsent
 *   PASS: evens has [2,4]
 *   PASS: odds has [1]
 *   PASS: computeIfAbsent fn=null does not insert
 * 11. computeIfPresent
 *   PASS: computeIfPresent updates 5*2=10
 *   PASS: computeIfPresent absent = no-op
 *   PASS: computeIfPresent fn=null removes key
 * 12. replaceAll
 *   PASS: a=10
 *   PASS: b=20
 *   PASS: c=30
 *   PASS: order preserved
 * 13. putAll
 *   PASS: size=3 after putAll
 *   PASS: new key 2 present
 *   PASS: existing key 1 intact
 * 14. iteration
 *   PASS: keySet [10,20,30]
 *   PASS: values [100,200,300]
 *   PASS: entrySet size=3
 *   PASS: forEach order [10,20,30]
 * 15. clear / isEmpty
 *   PASS: isEmpty on new map
 *   PASS: not empty after puts
 *   PASS: isEmpty after clear
 *   PASS: size=0 after clear
 *   PASS: key gone after clear
 *   PASS: put after clear works
 * 16. remove head/tail/middle
 *   PASS: remove head: key 1 gone
 *   PASS: new head is 2
 *   PASS: remove tail: key 4 gone
 *   PASS: remove middle: key 3 gone
 *   PASS: only key 2 remains
 * 
 * 63 passed, 0 failed.
 * All tests passed!
 */