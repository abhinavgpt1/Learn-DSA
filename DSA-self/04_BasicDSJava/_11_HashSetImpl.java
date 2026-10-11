import java.util.*;

// ============================================================
// HashSet — CP-focused method reference
// ============================================================
// Backed by a HashMap<E, PRESENT> — keys are elements, value is a shared dummy Object.
// Key insight: add/remove/contains all delegate to the underlying HashMap bucket array.
// No order guarantee. One null element allowed.

// O(1) avg Core operations  ★ most important for CP
// ---------------------------------------------------
// add(E e)                 -> boolean   true if element was NOT already present
// remove(Object o)         -> boolean   true if element WAS present and removed
// contains(Object o)       -> boolean   true if element exists
// size()                   -> int
// isEmpty()                -> boolean
// clear()                  -> void

// O(n) Set-algebra operations  ★★ killer feature vs array
// ---------------------------------------------------------
// addAll(Collection c)     -> boolean   UNION        in-place; true if set changed
// retainAll(Collection c)  -> boolean   INTERSECTION in-place; keeps only elements in c
// removeAll(Collection c)  -> boolean   DIFFERENCE   in-place; removes all in c
// containsAll(Collection c)-> boolean   SUBSET check; true if every element of c is present
//
// To preserve original: copy first →  new HashSet<>(setA)  then call bulk op on copy

// O(n) Iteration
// ---------------
// iterator()               -> Iterator<E>     no guaranteed order
// forEach(e -> { })        -> void            visits all elements; no order guarantee; no snapshot (live traversal via map.forEach)

// Common CP Patterns
// ------------------
// Deduplicate array        — new HashSet<>(Arrays.asList(arr)) → unique elements, O(n)
// Visited (BFS/DFS)        — visited.add(node); if (!visited.contains(next)) explore
// Two-sum / pair check     — load all into set; for each x check contains(target - x)
// Duplicate detection      — if (!set.add(x)) → x is a duplicate (first time seen = false)
// Intersection size        — new HashSet<>(a).retainAll(b) then size()
// Union size               — new HashSet<>(a).addAll(b) then size()
// Difference (A \ B)       — new HashSet<>(a).removeAll(b)
// Sliding window distinct  — add on right expand, remove on left shrink, track size()
// Count distinct           — set.size() after adding all elements
// Anagram check            — build char set from each word, check set equality

// HashSet vs LinkedHashSet vs TreeSet
// ------------------------------------
// HashSet        O(1)       no order                  → fastest membership test
// LinkedHashSet  O(1)       insertion-order preserved → dedup + keep order
// TreeSet        O(log n)   always sorted             → sorted set, range queries

// ============================================================

class MyHashSet<E> {
    private static final Object PRESENT = new Object();
    private final MyHashMap<E, Object> map;

    MyHashSet() {
        map = new MyHashMap<>();
    }

    MyHashSet(Collection<? extends E> c) {
        map = new MyHashMap<>();
        for (E e : c)
            add(e);
    }

    // ── O(1) Core ────────────────────────────────────────────
    boolean add(E e) {
        return map.put(e, PRESENT) == null;
    }

    @SuppressWarnings("unchecked")
    boolean remove(Object o) {
        return map.remove((E) o) != null;
    }

    @SuppressWarnings("unchecked")
    boolean contains(Object o) {
        return map.containsKey((E) o);
    }

    int size() {
        return map.size();
    }

    boolean isEmpty() {
        return map.isEmpty();
    }

    void clear() {
        map.clear();
    }

    // ── O(n) Set-algebra ─────────────────────────────────────
    boolean addAll(Collection<? extends E> c) {
        boolean changed = false;
        for (E e : c)
            if (add(e))
                changed = true;
        return changed;
    }

    boolean containsAll(Collection<?> c) {
        for (Object o : c)
            if (!contains(o))
                return false;
        return true;
    }

    boolean removeAll(Collection<?> c) {
        boolean changed = false;
        for (Object o : c)
            if (remove(o))
                changed = true;
        return changed;
    }

    boolean retainAll(Collection<?> c) {
        boolean changed = false;
        for (E e : map.keySet()) {
            if (!c.contains(e)) {
                remove(e);
                changed = true;
            }
        }
        return changed;
    }

    // ── Iteration ────────────────────────────────────────────
    // iterator() — operates on a snapshot (map.keySet() returns a new copy each call).
    // Iterator.remove() has no effect on the underlying map.
    // To delete while iterating, collect elements first, then call this.remove(e).
    Iterator<E> iterator() {
        return map.keySet().iterator();
    }

    void forEach(java.util.function.Consumer<? super E> fn) {
        map.forEach((k, v) -> fn.accept(k));
    }
}

public class _11_HashSetImpl {

    static int passed = 0, failed = 0;

    static void check(String name, boolean cond) {
        if (cond) {
            System.out.println("  PASS  " + name);
            passed++;
        } else {
            System.out.println("  FAIL  " + name);
            failed++;
        }
    }

    static void section(String title) {
        System.out.println("\n── " + title + " ──");
    }

    public static void main(String[] args) {

        // ── 1. add / contains / size ──────────────────────────
        section("add / contains / size");
        MyHashSet<Integer> s = new MyHashSet<>();
        check("isEmpty on new set", s.isEmpty());
        check("add 1 → true (new)", s.add(1));
        check("add 2 → true (new)", s.add(2));
        check("add 3 → true (new)", s.add(3));
        check("add duplicate 2 → false", !s.add(2));
        check("size = 3", s.size() == 3);
        check("contains(1) = true", s.contains(1));
        check("contains(99) = false", !s.contains(99));
        check("not empty", !s.isEmpty());

        // ── 2. remove ────────────────────────────────────────
        section("remove");
        check("remove present → true", s.remove(2));
        check("remove absent → false", !s.remove(99));
        check("size after remove = 2", s.size() == 2);
        check("removed element gone", !s.contains(2));
        check("other elements intact", s.contains(1) && s.contains(3));

        // ── 3. clear / isEmpty ───────────────────────────────
        section("clear / isEmpty");
        s.clear();
        check("isEmpty after clear", s.isEmpty());
        check("size = 0 after clear", s.size() == 0);
        s.add(10);
        check("add after clear works", s.contains(10));
        check("size = 1 after add", s.size() == 1);
        s.clear();

        // ── 4. copy constructor / deduplication ──────────────
        section("copy constructor — deduplication");
        List<Integer> withDups = Arrays.asList(3, 1, 4, 1, 5, 9, 2, 6, 5, 3);
        MyHashSet<Integer> dedup = new MyHashSet<>(withDups);
        check("unique count = 7", dedup.size() == 7);
        check("contains 9", dedup.contains(9));
        check("add duplicate → false", !dedup.add(3));
        check("add new element → true", dedup.add(99));
        check("size = 8 after new add", dedup.size() == 8);

        // ── 5. addAll — UNION ────────────────────────────────
        section("addAll (union)");
        MyHashSet<Integer> a = new MyHashSet<>(Arrays.asList(1, 2, 3));
        MyHashSet<Integer> b = new MyHashSet<>(Arrays.asList(3, 4, 5));
        MyHashSet<Integer> union = new MyHashSet<>(Arrays.asList(1, 2, 3));
        boolean unionChanged = union.addAll(Arrays.asList(3, 4, 5));
        check("addAll returns true (changed)", unionChanged);
        check("union size = 5", union.size() == 5);
        check("union contains 1 and 5", union.contains(1) && union.contains(5));
        check("a unchanged (size=3)", a.size() == 3);
        check("b unchanged (size=3)", b.size() == 3);

        // ── 6. retainAll — INTERSECTION ──────────────────────
        section("retainAll (intersection)");
        MyHashSet<Integer> inter = new MyHashSet<>(Arrays.asList(1, 2, 3));
        boolean interChanged = inter.retainAll(Arrays.asList(3, 4, 5));
        check("retainAll returns true (changed)", interChanged);
        check("intersection = {3}", inter.size() == 1 && inter.contains(3));
        check("1 and 2 gone", !inter.contains(1) && !inter.contains(2));
        check("a unchanged (size=3)", a.size() == 3);
        check("b unchanged (size=3)", b.size() == 3);

        // ── 7. removeAll — DIFFERENCE ────────────────────────
        section("removeAll (difference A \\ B)");
        MyHashSet<Integer> diff = new MyHashSet<>(Arrays.asList(1, 2, 3));
        boolean diffChanged = diff.removeAll(Arrays.asList(3, 4, 5));
        check("removeAll returns true (changed)", diffChanged);
        check("diff = {1, 2}", diff.size() == 2);
        check("diff contains 1 and 2", diff.contains(1) && diff.contains(2));
        check("3 removed", !diff.contains(3));
        check("b unchanged (size=3)", b.size() == 3);

        // ── 8. containsAll — SUBSET CHECK ────────────────────
        section("containsAll (subset check)");
        MyHashSet<Integer> sup = new MyHashSet<>(Arrays.asList(1, 2, 3, 4, 5));
        MyHashSet<Integer> sub = new MyHashSet<>(Arrays.asList(2, 4));
        check("sub ⊆ sup", sup.containsAll(Arrays.asList(2, 4)));
        check("sup ⊄ sub", !sub.containsAll(Arrays.asList(1, 2, 3, 4, 5)));
        check("containsAll empty collection → true", sup.containsAll(new ArrayList<>()));
        check("empty set containsAll empty → true", new MyHashSet<Integer>().containsAll(new ArrayList<>()));

        // ── 9. retainAll — edge cases ─────────────────────────
        section("retainAll — edge cases");
        MyHashSet<Integer> r1 = new MyHashSet<>(Arrays.asList(1, 2, 3));
        check("retainAll identical elements → false", !r1.retainAll(Arrays.asList(1, 2, 3)));
        check("size unchanged after no-op retainAll", r1.size() == 3);
        MyHashSet<Integer> r2 = new MyHashSet<>(Arrays.asList(1, 2, 3));
        check("retainAll empty → true (all removed)", r2.retainAll(new ArrayList<>()));
        check("size = 0 after retainAll empty", r2.size() == 0);

        // ── 10. addAll / removeAll return values ──────────────
        section("addAll / removeAll return values");
        MyHashSet<Integer> rv = new MyHashSet<>(Arrays.asList(1, 2, 3));
        check("addAll all-duplicates → false", !rv.addAll(Arrays.asList(1, 2, 3)));
        check("addAll with one new → true", rv.addAll(Arrays.asList(3, 4)));
        check("removeAll no match → false", !rv.removeAll(Arrays.asList(99, 100)));
        check("removeAll with match → true", rv.removeAll(Arrays.asList(4, 99)));
        check("4 removed", !rv.contains(4));
        check("1,2,3 still present", rv.contains(1) && rv.contains(2) && rv.contains(3));

        // ── 11. iterator ─────────────────────────────────────
        section("iterator");
        MyHashSet<Integer> iterSet = new MyHashSet<>(Arrays.asList(10, 20, 30));
        Iterator<Integer> it = iterSet.iterator();
        List<Integer> itResult = new ArrayList<>();
        while (it.hasNext()) itResult.add(it.next());
        check("iterator yields 3 elements", itResult.size() == 3);
        check("iterator contains 10, 20, 30",
                itResult.contains(10) && itResult.contains(20) && itResult.contains(30));

        // ── 12. forEach ──────────────────────────────────────
        section("forEach");
        MyHashSet<Integer> feSet = new MyHashSet<>(Arrays.asList(10, 20, 30));
        List<Integer> collected = new ArrayList<>();
        feSet.forEach(collected::add);
        check("forEach visits all 3 elements", collected.size() == 3);
        check("forEach collected 10, 20, 30",
                collected.contains(10) && collected.contains(20) && collected.contains(30));
        // forEach on empty set — no iterations
        MyHashSet<Integer> feEmpty = new MyHashSet<>();
        int[] feCount = {0};
        feEmpty.forEach(e -> feCount[0]++);
        check("forEach on empty set: 0 visits", feCount[0] == 0);

        // ── 13. remove on empty set ───────────────────────────
        section("remove on empty set");
        MyHashSet<Integer> empty = new MyHashSet<>();
        check("remove from empty → false", !empty.remove(42));
        check("size still 0", empty.size() == 0);

        // ── 14. null element ──────────────────────────────────
        section("null element");
        MyHashSet<String> nullSet = new MyHashSet<>();
        check("add null → true", nullSet.add(null));
        check("add null duplicate → false", !nullSet.add(null));
        check("contains null = true", nullSet.contains(null));
        check("size = 1", nullSet.size() == 1);
        nullSet.add("hello");
        check("size = 2 after adding non-null", nullSet.size() == 2);
        check("remove null → true", nullSet.remove(null));
        check("null gone after remove", !nullSet.contains(null));
        check("'hello' still present", nullSet.contains("hello"));
        check("size = 1 after null remove", nullSet.size() == 1);

        // ── 15. String-type set ───────────────────────────────
        section("String-type set");
        MyHashSet<String> strSet = new MyHashSet<>(Arrays.asList("apple", "banana", "apple"));
        check("dedup: size = 2", strSet.size() == 2);
        check("contains 'banana'", strSet.contains("banana"));
        check("remove 'apple' → true", strSet.remove("apple"));
        check("remove absent → false", !strSet.remove("cherry"));
        check("size after remove = 1", strSet.size() == 1);

        // ── 16. CP — duplicate detection ─────────────────────
        section("CP — duplicate detection");
        int[] arr1 = {1, 2, 3, 4, 2};
        MyHashSet<Integer> seen1 = new MyHashSet<>();
        boolean hasDup = false;
        for (int x : arr1) if (!seen1.add(x)) { hasDup = true; break; }
        check("hasDuplicate = true", hasDup);

        int[] arr2 = {1, 2, 3, 4, 5};
        MyHashSet<Integer> seen2 = new MyHashSet<>();
        boolean hasDup2 = false;
        for (int x : arr2) if (!seen2.add(x)) { hasDup2 = true; break; }
        check("noDuplicate = false", !hasDup2);

        // ── 17. CP — two-sum ──────────────────────────────────
        section("CP — two-sum");
        int[] nums = {2, 7, 11, 15};
        int target = 9;
        MyHashSet<Integer> lookup = new MyHashSet<>();
        for (int n : nums) lookup.add(n);
        boolean found = false;
        for (int n : nums) {
            int need = target - n;
            if (need != n && lookup.contains(need)) { found = true; break; }
        }
        check("two-sum 9 found (2+7)", found);
        // target with no solution
        int target2 = 100;
        boolean found2 = false;
        for (int n : nums) {
            int need = target2 - n;
            if (need != n && lookup.contains(need)) { found2 = true; break; }
        }
        check("two-sum 100 not found", !found2);

        // ── 18. CP — anagram check ────────────────────────────
        // NOTE: containsAll() takes a Collection, so we convert each MyHashSet to a
        // List via ArrayList(iterator snapshot) before passing as the argument.
        // This exercises MyHashSet.containsAll(), not java.util.List.containsAll().
        section("CP — anagram check");
        MyHashSet<Character> ag1 = new MyHashSet<>();
        MyHashSet<Character> ag2 = new MyHashSet<>();
        for (char c : "listen".toCharArray()) ag1.add(c);
        for (char c : "silent".toCharArray()) ag2.add(c);
        List<Character> ag1List = new ArrayList<>(); ag1.forEach(ag1List::add);
        List<Character> ag2List = new ArrayList<>(); ag2.forEach(ag2List::add);
        check("anagram: same unique-char-set size", ag1.size() == ag2.size());
        check("anagram: ag1 ⊇ ag2 chars", ag1.containsAll(ag2List));
        check("anagram: ag2 ⊇ ag1 chars", ag2.containsAll(ag1List));

        MyHashSet<Character> ag3 = new MyHashSet<>();
        MyHashSet<Character> ag4 = new MyHashSet<>();
        for (char c : "hello".toCharArray()) ag3.add(c);
        for (char c : "world".toCharArray()) ag4.add(c);
        List<Character> ag3List = new ArrayList<>(); ag3.forEach(ag3List::add);
        List<Character> ag4List = new ArrayList<>(); ag4.forEach(ag4List::add);
        check("non-anagram: not mutual containsAll", !(ag3.containsAll(ag4List) && ag4.containsAll(ag3List)));

        // ── Summary ──────────────────────────────────────────
        System.out.println("\n════════════════════════════");
        System.out.println("  Results: " + passed + " passed, " + failed + " failed");
        System.out.println("════════════════════════════");
    }
}

/**
 * Output:
 * -------
 * ── add / contains / size ──
 *   PASS  isEmpty on new set
 *   PASS  add 1 → true (new)
 *   PASS  add 2 → true (new)
 *   PASS  add 3 → true (new)
 *   PASS  add duplicate 2 → false
 *   PASS  size = 3
 *   PASS  contains(1) = true
 *   PASS  contains(99) = false
 *   PASS  not empty
 * 
 * ── remove ──
 *   PASS  remove present → true
 *   PASS  remove absent → false
 *   PASS  size after remove = 2
 *   PASS  removed element gone
 *   PASS  other elements intact
 * 
 * ── clear / isEmpty ──
 *   PASS  isEmpty after clear
 *   PASS  size = 0 after clear
 *   PASS  add after clear works
 *   PASS  size = 1 after add
 * 
 * ── copy constructor — deduplication ──
 *   PASS  unique count = 7
 *   PASS  contains 9
 *   PASS  add duplicate → false
 *   PASS  add new element → true
 *   PASS  size = 8 after new add
 * 
 * ── addAll (union) ──
 *   PASS  addAll returns true (changed)
 *   PASS  union size = 5
 *   PASS  union contains 1 and 5
 *   PASS  a unchanged (size=3)
 *   PASS  b unchanged (size=3)
 * 
 * ── retainAll (intersection) ──
 *   PASS  retainAll returns true (changed)
 *   PASS  intersection = {3}
 *   PASS  1 and 2 gone
 *   PASS  a unchanged (size=3)
 *   PASS  b unchanged (size=3)
 * 
 * ── removeAll (difference A \ B) ──
 *   PASS  removeAll returns true (changed)
 *   PASS  diff = {1, 2}
 *   PASS  diff contains 1 and 2
 *   PASS  3 removed
 *   PASS  b unchanged (size=3)
 * 
 * ── containsAll (subset check) ──
 *   PASS  sub ⊆ sup
 *   PASS  sup ⊄ sub
 *   PASS  containsAll empty collection → true
 *   PASS  empty set containsAll empty → true
 * 
 * ── retainAll — edge cases ──
 *   PASS  retainAll identical elements → false
 *   PASS  size unchanged after no-op retainAll
 *   PASS  retainAll empty → true (all removed)
 *   PASS  size = 0 after retainAll empty
 * 
 * ── addAll / removeAll return values ──
 *   PASS  addAll all-duplicates → false
 *   PASS  addAll with one new → true
 *   PASS  removeAll no match → false
 *   PASS  removeAll with match → true
 *   PASS  4 removed
 *   PASS  1,2,3 still present
 * 
 * ── iterator ──
 *   PASS  iterator yields 3 elements
 *   PASS  iterator contains 10, 20, 30
 * 
 * ── forEach ──
 *   PASS  forEach visits all 3 elements
 *   PASS  forEach collected 10, 20, 30
 *   PASS  forEach on empty set: 0 visits
 * 
 * ── remove on empty set ──
 *   PASS  remove from empty → false
 *   PASS  size still 0
 * 
 * ── null element ──
 *   PASS  add null → true
 *   PASS  add null duplicate → false
 *   PASS  contains null = true
 *   PASS  size = 1
 *   PASS  size = 2 after adding non-null
 *   PASS  remove null → true
 *   PASS  null gone after remove
 *   PASS  'hello' still present
 *   PASS  size = 1 after null remove
 * 
 * ── String-type set ──
 *   PASS  dedup: size = 2
 *   PASS  contains 'banana'
 *   PASS  remove 'apple' → true
 *   PASS  remove absent → false
 *   PASS  size after remove = 1
 * 
 * ── CP — duplicate detection ──
 *   PASS  hasDuplicate = true
 *   PASS  noDuplicate = false
 * 
 * ── CP — two-sum ──
 *   PASS  two-sum 9 found (2+7)
 *   PASS  two-sum 100 not found
 * 
 * ── CP — anagram check ──
 *   PASS  anagram: same unique-char-set size
 *   PASS  anagram: ag1 ⊇ ag2 chars
 *   PASS  anagram: ag2 ⊇ ag1 chars
 *   PASS  non-anagram: not mutual containsAll
 * 
 * ════════════════════════════
 *   Results: 81 passed, 0 failed
 * ════════════════════════════
 */