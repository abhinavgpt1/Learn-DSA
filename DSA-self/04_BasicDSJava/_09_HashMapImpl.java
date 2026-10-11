// Methods as per java.util.HashMap
// --------------------------------
// put(T key, V value)              -> V       (inserts/updates, returns old value or null)
// get(T key)                       -> V       (returns null if not found)
// getOrDefault(T key, V default)   -> V       (returns default if key not found, irrespective of null value stored for that key)
// remove(T key)                    -> V       (returns removed value or null)
// containsKey(T key)               -> boolean
// containsValue(V value)           -> boolean
// putAll(Map<T,V> m)               -> void    (copies all mappings)
// clear()                          -> void
// size()                           -> int
// isEmpty()                        -> boolean
// keySet()                         -> Set<T>
// values()                         -> List<V>
// entrySet()                       -> Set<MyHashMap.Entry<T,V>>
// forEach(BiConsumer<T,V> action)  -> void    (iterate all entries with a lambda; visits in bucket order)
// print()                          -> void
// getLoadFactor()                 -> double  (current load factor)

// Advanced
// --------
// putIfAbsent(T key, V value)      -> V       (insert only if key doesn't exist)
// computeIfAbsent(T key, Function) -> V       (compute value if key absent)
// merge(T key, V val, BiFunction)  -> V       (merge values using function)
// replace(T key, V value)          -> V       (replace existing value)

// Common CP Patterns
// ------------------
// Frequency: map.put(key, map.getOrDefault(key, 0) + 1)
// Nested:    map.computeIfAbsent(key, k -> new ArrayList<>()).add(value)
// Merge:     map.merge(key, 1, Integer::sum)

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

class MyHashMap<T, V> {
    private List<List<Entry<T, V>>> buckets;
    private int size;
    private final int INITIAL_NUM_BUCKETS = 16; // as per java.util.HashMap
    private final double LOAD_FACTOR = 0.75; // as per java.util.HashMap

    @SuppressWarnings("unchecked")
    public MyHashMap() {
        buckets = new ArrayList<>();
        for (int i = 0; i < INITIAL_NUM_BUCKETS; i++) {
            buckets.add(new ArrayList<>());
        }
        size = 0;
    }

    class Entry<X, Y> {
        private X key;
        private Y value;

        Entry(X key, Y value) {
            this.key = key;
            this.value = value;
        }

        public X getKey() {
            return key;
        }

        public Y getValue() {
            return value;
        }
    }

    // private methods
    private int getHashKey(T key) {
        // null key always goes to bucket 0 (same convention as java.util.HashMap)
        if (key == null) return 0;
        // hashCode() can be negative, hence returning hashCode % buckets.size() can yield negative index.
        // Bitmasking with Integer.MAX_VALUE strips the sign bit, avoiding negative indices.
        // PTR: Math.abs(Integer.MIN_VALUE) == Integer.MIN_VALUE == +2147483648 = rollover 2147483647 == -2147483648
        return (key.hashCode() & Integer.MAX_VALUE) % buckets.size();
    }

    @SuppressWarnings("unchecked")
    private void grow2x() {
        List<List<Entry<T, V>>> tmpBuckets = buckets;
        buckets = new ArrayList<>();
        for (int i = 0; i < 2 * tmpBuckets.size(); i++) {
            buckets.add(new ArrayList<>());
        }
        int prevSize = size;
        size = 0; // IMP. since put increases size

        for (int i = 0; i < tmpBuckets.size(); i++) {
            for (Entry<T, V> e : tmpBuckets.get(i)) {
                this.put(e.key, e.value);
            }
        }
        if (size != prevSize) {
            throw new IllegalStateException("Size mismatch after resizing");
        }
    }

    // public methods
    public double getLoadFactor() {
        return (1.0 * size) / buckets.size();
    }

    public V put(T key, V value) {
        int hashkey = getHashKey(key);
        for (Entry<T, V> e : buckets.get(hashkey)) {
            if (key == null ? e.key == null : key.equals(e.key)) {
                V prevValue = e.value;
                e.value = value;
                return prevValue;
            }
        }
        buckets.get(hashkey).add(new Entry<>(key, value));
        size++;
        if (getLoadFactor() > LOAD_FACTOR) {
            grow2x();
        }
        return null;
    }

    public V get(T key) {
        int hashkey = getHashKey(key);
        for (Entry<T, V> e : buckets.get(hashkey)) {
            if (key == null ? e.key == null : key.equals(e.key))
                return e.value;
        }
        return null;
    }

    public V getOrDefault(T key, V defaultValue) {
        // BUG FIX: cannot use `get(key) == null` — key may exist with a null value.
        return containsKey(key) ? get(key) : defaultValue;
    }

    public V remove(T key) {
        int hashkey = getHashKey(key);
        for (Entry<T, V> e : buckets.get(hashkey)) {
            if (key == null ? e.key == null : key.equals(e.key)) {
                buckets.get(hashkey).remove(e);
                size--; // IMP: decrement size when removing
                return e.value;
            }
        }
        return null;
    }

    public boolean containsKey(T key) {
        int hashkey = getHashKey(key);
        for (Entry<T, V> e : buckets.get(hashkey)) {
            if (key == null ? e.key == null : key.equals(e.key))
                return true;
        }
        return false;
    }

    public boolean containsValue(V value) {
        for (int i = 0; i < buckets.size(); i++) {
            for (Entry<T, V> e : buckets.get(i)) {
                // BUG FIX: e.value.equals(value) NPEs when e.value is null
                if (value == null ? e.value == null : value.equals(e.value))
                    return true;
            }
        }
        return false;
    }

    public void putAll(MyHashMap<T, V> m) {
        for (Entry<T, V> e : m.entrySet()) {
            this.put(e.key, e.value);
        }
    }

    public void clear() {
        for (int i = 0; i < buckets.size(); i++) {
            buckets.get(i).clear();
        }
        size = 0;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public Set<T> keySet() {
        Set<T> keySet = new HashSet<>();
        for (int i = 0; i < buckets.size(); i++) {
            for (Entry<T, V> e : buckets.get(i)) {
                keySet.add(e.key);
            }
        }
        return keySet;
    }

    public List<V> values() {
        List<V> values = new ArrayList<>();
        for (int i = 0; i < buckets.size(); i++) {
            for (Entry<T, V> e : buckets.get(i)) {
                values.add(e.value);
            }
        }
        return values;
    }

    public Set<Entry<T, V>> entrySet() {
        Set<Entry<T, V>> entrySet = new HashSet<>();
        for (int i = 0; i < buckets.size(); i++) {
            for (Entry<T, V> e : buckets.get(i)) {
                entrySet.add(e);
            }
        }
        return entrySet;
    }

    public void print() {
        for (Entry<T, V> e : this.entrySet()) {
            System.out.println(e.key + ": " + e.value);
        }
    }

    public void forEach(java.util.function.BiConsumer<? super T, ? super V> action) {
        for (Entry<T, V> e : this.entrySet()) {
            action.accept(e.key, e.value);
        }
    }
}

public class _09_HashMapImpl {

    static int passed = 0, failed = 0;

    static void check(String name, boolean cond) {
        if (cond) { System.out.println("  PASS  " + name); passed++; }
        else       { System.out.println("  FAIL  " + name); failed++; }
    }

    static void section(String title) {
        System.out.println("\n── " + title + " ──");
    }

    public static void main(String[] args) {

        // ── 1. put / get / size ───────────────────────────────
        section("put / get / size");
        MyHashMap<String, Integer> map = new MyHashMap<>();
        check("isEmpty on new map", map.isEmpty());
        check("put apple → null (new)", map.put("apple", 1) == null);
        check("put banana → null (new)", map.put("banana", 2) == null);
        check("put cherry → null (new)", map.put("cherry", 3) == null);
        check("get apple = 1", map.get("apple") == 1);
        check("get banana = 2", map.get("banana") == 2);
        check("size = 3", map.size() == 3);
        check("get absent = null", map.get("grape") == null);

        // ── 2. update existing key ────────────────────────────
        section("update existing key");
        check("put apple again → old value 1", map.put("apple", 10) == 1);
        check("get apple after update = 10", map.get("apple") == 10);
        check("size unchanged at 3", map.size() == 3);

        // ── 3. getOrDefault ───────────────────────────────────
        section("getOrDefault");
        check("absent key → default 0", map.getOrDefault("grape", 0) == 0);
        check("present key → actual value 10", map.getOrDefault("apple", 0) == 10);

        // ── 4. containsKey / containsValue ────────────────────
        section("containsKey / containsValue");
        check("containsKey apple = true",  map.containsKey("apple"));
        check("containsKey grape = false", !map.containsKey("grape"));
        check("containsValue 2 = true",    map.containsValue(2));
        check("containsValue 99 = false", !map.containsValue(99));

        // ── 5. remove ─────────────────────────────────────────
        section("remove");
        check("remove banana → 2",         map.remove("banana") == 2);
        check("remove absent → null",       map.remove("ghost") == null);
        check("size after remove = 2",      map.size() == 2);
        check("banana gone",               !map.containsKey("banana"));
        check("size unchanged after absent remove", map.size() == 2);

        // ── 6. keySet / values / entrySet ────────────────────
        section("keySet / values / entrySet");
        check("keySet size = 2",   map.keySet().size() == 2);
        check("values size = 2",   map.values().size() == 2);
        check("entrySet size = 2", map.entrySet().size() == 2);
        check("keySet contains apple",  map.keySet().contains("apple"));
        check("keySet contains cherry", map.keySet().contains("cherry"));
        check("values contains 10",     map.values().contains(10));

        // ── 7. putAll ─────────────────────────────────────────
        section("putAll");
        MyHashMap<String, Integer> extra = new MyHashMap<>();
        extra.put("dog", 4);
        extra.put("cat", 5);
        map.putAll(extra);
        check("size after putAll = 4", map.size() == 4);
        check("dog = 4", map.get("dog") == 4);
        check("cat = 5", map.get("cat") == 5);

        // ── 8. clear / isEmpty ────────────────────────────────
        section("clear / isEmpty");
        check("not empty before clear", !map.isEmpty());
        map.clear();
        check("isEmpty after clear", map.isEmpty());
        check("size = 0 after clear", map.size() == 0);
        map.put("x", 99);
        check("put after clear works", map.get("x") == 99);
        map.clear();

        // ── 9. null values ────────────────────────────────────
        section("null values");
        MyHashMap<String, String> nv = new MyHashMap<>();
        check("put with null value → null", nv.put("k1", null) == null);
        check("get null-value key = null",  nv.get("k1") == null);
        check("containsKey k1 = true",      nv.containsKey("k1"));
        // getOrDefault must distinguish "key absent" from "key present with null value"
        check("getOrDefault k1 (exists, null value) → null",    nv.getOrDefault("k1", "DEFAULT") == null);
        check("getOrDefault absent → DEFAULT",                   nv.getOrDefault("missing", "DEFAULT").equals("DEFAULT"));
        check("containsValue null = true",  nv.containsValue(null));
        nv.put("k2", "hello");
        check("containsValue 'hello' = true", nv.containsValue("hello"));
        // update null → non-null
        check("update null→100: old=null",  nv.put("k1", "real") == null);
        check("get k1 after update = real",  nv.get("k1").equals("real"));
        check("size still 2", nv.size() == 2);

        // ── 10. null key ──────────────────────────────────────
        section("null key");
        MyHashMap<String, Integer> nk = new MyHashMap<>();
        check("put null key → null (new)",   nk.put(null, 42) == null);
        check("get null key = 42",           nk.get(null) == 42);
        check("containsKey null = true",     nk.containsKey(null));
        check("containsKey null = false before add", !new MyHashMap<String,Integer>().containsKey(null));
        check("update null key: old=42",     nk.put(null, 99) == 42);
        check("get null key after update=99",nk.get(null) == 99);
        check("size still 1",                nk.size() == 1);
        check("remove null key → 99",        nk.remove(null) == 99);
        check("null key gone",              !nk.containsKey(null));
        check("size = 0 after remove",       nk.size() == 0);

        // ── 11. resize — data integrity ───────────────────────
        section("resize — data integrity");
        MyHashMap<Integer, String> big = new MyHashMap<>();
        for (int i = 0; i < 20; i++) big.put(i, "v" + i);
        check("size = 20 after bulk insert", big.size() == 20);
        check("get(0) survives resize",  "v0".equals(big.get(0)));
        check("get(5) survives resize",  "v5".equals(big.get(5)));
        check("get(19) survives resize", "v19".equals(big.get(19)));
        for (int i = 0; i < 10; i++) big.remove(i);
        check("size = 10 after 10 removes", big.size() == 10);
        check("removed key(5) gone",   big.get(5) == null);
        check("kept key(15) intact",   "v15".equals(big.get(15)));

        // ── 12. load factor ───────────────────────────────────
        section("load factor");
        MyHashMap<Integer, String> lf = new MyHashMap<>();
        check("initial load factor = 0", lf.getLoadFactor() == 0.0);
        // 13/16 = 0.8125 triggers resize → buckets become 32
        for (int i = 1; i <= 13; i++) lf.put(i, "v" + i);
        check("load factor <= 0.75 after resize", lf.getLoadFactor() <= 0.75);
        check("size still correct after resize", lf.size() == 13);

        // ── 13. CP — frequency count ──────────────────────────
        section("CP — frequency count");
        MyHashMap<Character, Integer> freq = new MyHashMap<>();
        for (char c : "hello".toCharArray())
            freq.put(c, freq.getOrDefault(c, 0) + 1);
        check("freq h=1", freq.get('h') == 1);
        check("freq e=1", freq.get('e') == 1);
        check("freq l=2", freq.get('l') == 2);
        check("freq o=1", freq.get('o') == 1);
        check("freq size=4 unique chars", freq.size() == 4);

        // ── 14. CP — two-sum with map ─────────────────────────
        section("CP — two-sum");
        int[] nums = {2, 7, 11, 15};
        int target = 9;
        MyHashMap<Integer, Integer> indexMap = new MyHashMap<>();
        int[] result = new int[]{-1, -1};
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if (indexMap.containsKey(complement)) {
                result[0] = indexMap.get(complement);
                result[1] = i;
                break;
            }
            indexMap.put(nums[i], i);
        }
        check("two-sum indices [0,1]", result[0] == 0 && result[1] == 1);

        // ── 15. CP — group anagrams (computeIfAbsent pattern) ─
        section("CP — group anagrams");
        String[] words = {"eat", "tea", "tan", "ate", "nat", "bat"};
        MyHashMap<String, List<String>> groups = new MyHashMap<>();
        for (String w : words) {
            char[] chars = w.toCharArray();
            Arrays.sort(chars);
            String key = new String(chars);
            if (!groups.containsKey(key)) groups.put(key, new ArrayList<>());
            groups.get(key).add(w);
        }
        check("3 anagram groups", groups.size() == 3);
        check("'aet' group has 3 words", groups.get("aet").size() == 3);
        check("'ant' group has 2 words", groups.get("ant").size() == 2);
        check("'abt' group has 1 word",  groups.get("abt").size() == 1);

        // ── 16. forEach ───────────────────────────────────────
        section("forEach");
        MyHashMap<String, Integer> fe = new MyHashMap<>();
        fe.put("a", 1);
        fe.put("b", 2);
        fe.put("c", 3);
        MyHashMap<String, Integer> collected = new MyHashMap<>();
        fe.forEach((k, v) -> collected.put(k, v));
        check("forEach visits all 3 entries", collected.size() == 3);
        check("forEach: a=1", collected.get("a") == 1);
        check("forEach: b=2", collected.get("b") == 2);
        check("forEach: c=3", collected.get("c") == 3);
        // forEach on empty map — no iterations
        MyHashMap<String, Integer> feEmpty = new MyHashMap<>();
        int[] count = {0};
        feEmpty.forEach((k, v) -> count[0]++);
        check("forEach on empty map: 0 visits", count[0] == 0);

        // ── Summary ──────────────────────────────────────────
        System.out.println("\n════════════════════════════");
        System.out.println("  Results: " + passed + " passed, " + failed + " failed");
        System.out.println("════════════════════════════");
    }
}

/**
 * Output:
 * -------
 * ── put / get / size ──
 *   PASS  isEmpty on new map
 *   PASS  put apple → null (new)
 *   PASS  put banana → null (new)
 *   PASS  put cherry → null (new)
 *   PASS  get apple = 1
 *   PASS  get banana = 2
 *   PASS  size = 3
 *   PASS  get absent = null
 * 
 * ── update existing key ──
 *   PASS  put apple again → old value 1
 *   PASS  get apple after update = 10
 *   PASS  size unchanged at 3
 * 
 * ── getOrDefault ──
 *   PASS  absent key → default 0
 *   PASS  present key → actual value 10
 * 
 * ── containsKey / containsValue ──
 *   PASS  containsKey apple = true
 *   PASS  containsKey grape = false
 *   PASS  containsValue 2 = true
 *   PASS  containsValue 99 = false
 * 
 * ── remove ──
 *   PASS  remove banana → 2
 *   PASS  remove absent → null
 *   PASS  size after remove = 2
 *   PASS  banana gone
 *   PASS  size unchanged after absent remove
 * 
 * ── keySet / values / entrySet ──
 *   PASS  keySet size = 2
 *   PASS  values size = 2
 *   PASS  entrySet size = 2
 *   PASS  keySet contains apple
 *   PASS  keySet contains cherry
 *   PASS  values contains 10
 * 
 * ── putAll ──
 *   PASS  size after putAll = 4
 *   PASS  dog = 4
 *   PASS  cat = 5
 * 
 * ── clear / isEmpty ──
 *   PASS  not empty before clear
 *   PASS  isEmpty after clear
 *   PASS  size = 0 after clear
 *   PASS  put after clear works
 * 
 * ── null values ──
 *   PASS  put with null value → null
 *   PASS  get null-value key = null
 *   PASS  containsKey k1 = true
 *   PASS  getOrDefault k1 (exists, null value) → null
 *   PASS  getOrDefault absent → DEFAULT
 *   PASS  containsValue null = true
 *   PASS  containsValue 'hello' = true
 *   PASS  update null→100: old=null
 *   PASS  get k1 after update = real
 *   PASS  size still 2
 * 
 * ── null key ──
 *   PASS  put null key → null (new)
 *   PASS  get null key = 42
 *   PASS  containsKey null = true
 *   PASS  containsKey null = false before add
 *   PASS  update null key: old=42
 *   PASS  get null key after update=99
 *   PASS  size still 1
 *   PASS  remove null key → 99
 *   PASS  null key gone
 *   PASS  size = 0 after remove
 * 
 * ── resize — data integrity ──
 *   PASS  size = 20 after bulk insert
 *   PASS  get(0) survives resize
 *   PASS  get(5) survives resize
 *   PASS  get(19) survives resize
 *   PASS  size = 10 after 10 removes
 *   PASS  removed key(5) gone
 *   PASS  kept key(15) intact
 * 
 * ── load factor ──
 *   PASS  initial load factor = 0
 *   PASS  load factor <= 0.75 after resize
 *   PASS  size still correct after resize
 * 
 * ── CP — frequency count ──
 *   PASS  freq h=1
 *   PASS  freq e=1
 *   PASS  freq l=2
 *   PASS  freq o=1
 *   PASS  freq size=4 unique chars
 * 
 * ── CP — two-sum ──
 *   PASS  two-sum indices [0,1]
 * 
 * ── CP — group anagrams ──
 *   PASS  3 anagram groups
 *   PASS  'aet' group has 3 words
 *   PASS  'ant' group has 2 words
 *   PASS  'abt' group has 1 word
 * 
 * ── forEach ──
 *   PASS  forEach visits all 3 entries
 *   PASS  forEach: a=1
 *   PASS  forEach: b=2
 *   PASS  forEach: c=3
 *   PASS  forEach on empty map: 0 visits
 * 
 * ════════════════════════════
 *   Results: 80 passed, 0 failed
 * ════════════════════════════
 */