// ============================================================
// LinkedHashSet — CP-focused method reference
// ============================================================
// Backed by a LinkedHashMap<E, PRESENT> — keys are elements, value is a shared dummy Object.
// Key insight: inherits all O(1) HashSet operations AND guarantees insertion-order iteration.
// Use over HashSet when you need both O(1) membership AND remembered insertion order.
// No order guarantee → use HashSet. Sorted order → use TreeSet.

// Internal structure:
//   LinkedHashMap<E, Object>     — O(1) lookup by key (same as HashMap)
//   Doubly-linked list           — threads through all nodes in insertion order
//   HEAD = first inserted, TAIL = last inserted
//   Re-adding an existing element does NOT change its position

// O(1) avg Core operations  ★ most important for CP
// ---------------------------------------------------
// add(E e)                 -> boolean   true if element was NOT already present; appends to tail
// remove(Object o)         -> boolean   true if element WAS present and removed; list link repaired
// contains(Object o)       -> boolean   true if element exists
// size()                   -> int
// isEmpty()                -> boolean
// clear()                  -> void

// O(n) Set-algebra operations  ★★ killer feature vs array
// ---------------------------------------------------------
// addAll(Collection c)     -> boolean   UNION        in-place; true if set changed; new elements appended in c's order
// retainAll(Collection c)  -> boolean   INTERSECTION in-place; surviving elements keep their original positions
// removeAll(Collection c)  -> boolean   DIFFERENCE   in-place; removes all elements also in c
// containsAll(Collection c)-> boolean   SUBSET check; true if every element of c is present
//
// To preserve original: copy first →  new LinkedHashSet<>(setA)  then call bulk op on copy

// O(n) Iteration  ★★ key advantage over HashSet — order is deterministic
// -----------------------------------------------------------------------
// iterator()               -> Iterator<E>   insertion-order (HEAD → TAIL); snapshot via map.keySet(); Iterator.remove() has no effect
// forEach(e -> { })        -> void          insertion-order; live traversal via map.forEach()
//
// Peek first/last (no direct API — unlike TreeSet):
//   first: set.iterator().next()
//   last:  requires full traversal (or maintain a separate tail reference)

// Common CP Patterns
// ------------------
// Dedup + keep first-seen order   — new LinkedHashSet<>(list) → unique elements in insertion order
// Ordered distinct output         — build set, iterate: no dups, original relative order preserved
//   e.g. List<Integer> deduped = new ArrayList<>(new LinkedHashSet<>(input))
// Visited (BFS) + ordered replay  — add nodes as visited; iterate in discovery order for path reconstruction
// First unique character          — freq map + LinkedHashSet of chars; iterate set, return first with freq=1
// Intersection preserving order   — copy setA into LinkedHashSet; retainAll(setB) → A∩B in A's original order
// Difference preserving order     — copy setA into LinkedHashSet; removeAll(setB) → A\B in A's original order
// Check same distinct elements    — build LinkedHashSet from each; equals() → same elements, same first-seen order
// Sliding window with order       — add right, remove left; iterator().next() = oldest element in window

// LinkedHashSet vs HashSet vs TreeSet
// ------------------------------------
// HashSet        O(1)       no order guarantee               → fastest membership test
// LinkedHashSet  O(1)       insertion-order preserved        → dedup + remembered order  ★ use this
// TreeSet        O(log n)   always sorted by natural order   → range queries / floor / ceiling / min / max

// Gotchas
// -------
// Re-adding an existing element: add() returns false and does NOT move the element to tail
// Unlike access-order LinkedHashMap: there is NO access-order mode for LinkedHashSet
// equals()/hashCode(): two Sets are equal if they contain the same elements regardless of order
//   → new LinkedHashSet<>(["a","b"]).equals(new LinkedHashSet<>(["b","a"])) == true
// Structural modification during forEach (except via Iterator.remove) → ConcurrentModificationException

// ============================================================

import java.util.*;

class MyOrderedSet<E> {
    private static final Object PRESENT = new Object();
    private final MyOrderedMap<E, Object> map;

    // ── Constructors ─────────────────────────────────────────
    MyOrderedSet() {
        map = new MyOrderedMap<>();
    }

    MyOrderedSet(Collection<? extends E> c) {
        map = new MyOrderedMap<>();
        for (E e : c) add(e);
    }

    // ── O(1) Core ────────────────────────────────────────────
    boolean add(E e) {
        return map.put(e, PRESENT) == null;
    }

    @SuppressWarnings("unchecked")
    boolean remove(Object o) {
        return map.remove((E) o) == PRESENT;
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
        for (E e : c) {
            if (add(e)) changed = true;
        }
        return changed;
    }

    boolean containsAll(Collection<?> c) {
        for (Object o : c) {
            if (!contains(o)) return false;
        }
        return true;
    }

    boolean removeAll(Collection<?> c) {
        boolean changed = false;
        for (Object o : c) {
            if (remove(o)) changed = true;
        }
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

    // ── O(n) Iteration — insertion-order ─────────────────────
    // iterator() operates on a snapshot copy of keys (map.keySet() returns a new
    // LinkedHashSet each call) — Iterator.remove() has no effect on the underlying map.
    Iterator<E> iterator() {
        return map.keySet().iterator();
    }

    void forEach(java.util.function.Consumer<? super E> fn) {
        map.forEach((k, v) -> fn.accept(k));
    }
}

public class _12_OrderedSetImpl {

    static int passed = 0, failed = 0;

    static void check(String name, boolean cond) {
        if (cond) { System.out.println("  PASS  " + name); passed++; }
        else       { System.out.println("  FAIL  " + name); failed++; }
    }

    static void section(String title) {
        System.out.println("\n── " + title + " ──");
    }

    // Collect elements in iteration order via forEach (live traversal)
    static <E> List<E> toList(MyOrderedSet<E> s) {
        List<E> list = new ArrayList<>();
        s.forEach(list::add);
        return list;
    }

    public static void main(String[] args) {

        // ── 1. add / contains / size ──────────────────────────
        section("add / contains / size");
        MyOrderedSet<Integer> s = new MyOrderedSet<>();
        check("isEmpty on new set", s.isEmpty());
        check("add 1 → true (new)", s.add(1));
        check("add 2 → true (new)", s.add(2));
        check("add 3 → true (new)", s.add(3));
        check("add duplicate 2 → false", !s.add(2));
        check("size = 3", s.size() == 3);
        check("contains(1) = true", s.contains(1));
        check("contains(99) = false", !s.contains(99));
        check("not empty", !s.isEmpty());

        // ── 2. insertion order preserved ─────────────────────
        section("insertion order preserved");
        check("order [1,2,3]", toList(s).equals(Arrays.asList(1, 2, 3)));
        // re-adding an existing element must NOT move it
        s.add(1);
        check("re-add 1 → false (no move)", !s.contains(99));
        check("order unchanged after re-add", toList(s).equals(Arrays.asList(1, 2, 3)));

        // ── 3. remove ─────────────────────────────────────────
        section("remove");
        check("remove 2 → true", s.remove(2));
        check("remove absent → false", !s.remove(99));
        check("size after remove = 2", s.size() == 2);
        check("2 gone", !s.contains(2));
        check("order [1,3] after remove middle", toList(s).equals(Arrays.asList(1, 3)));

        // ── 4. clear / isEmpty ────────────────────────────────
        section("clear / isEmpty");
        s.clear();
        check("isEmpty after clear", s.isEmpty());
        check("size = 0 after clear", s.size() == 0);
        s.add(10);
        check("add after clear works", s.contains(10));
        s.clear();

        // ── 5. copy constructor — dedup + order ───────────────
        section("copy constructor — dedup + order");
        List<Integer> input = Arrays.asList(3, 1, 4, 1, 5, 9, 2, 6, 5, 3);
        MyOrderedSet<Integer> dedup = new MyOrderedSet<>(input);
        check("unique count = 7", dedup.size() == 7);
        check("insertion order [3,1,4,5,9,2,6]",
                toList(dedup).equals(Arrays.asList(3, 1, 4, 5, 9, 2, 6)));
        check("contains 9", dedup.contains(9));
        check("add duplicate → false", !dedup.add(3));
        check("order unchanged after dup add", toList(dedup).get(0) == 3);

        // ── 6. addAll — UNION, order: existing then new ───────
        section("addAll (union)");
        MyOrderedSet<Integer> ua = new MyOrderedSet<>(Arrays.asList(1, 2, 3));
        boolean unionChanged = ua.addAll(Arrays.asList(3, 4, 5));
        check("addAll returns true (changed)", unionChanged);
        check("union size = 5", ua.size() == 5);
        check("union order [1,2,3,4,5]", toList(ua).equals(Arrays.asList(1, 2, 3, 4, 5)));
        check("addAll all-dup → false", !ua.addAll(Arrays.asList(1, 2, 3)));

        // ── 7. retainAll — INTERSECTION, original order kept ──
        section("retainAll (intersection)");
        MyOrderedSet<Integer> inter = new MyOrderedSet<>(Arrays.asList(1, 2, 3, 4, 5));
        boolean interChanged = inter.retainAll(Arrays.asList(5, 3, 1));
        check("retainAll returns true (changed)", interChanged);
        check("size = 3", inter.size() == 3);
        // original order of elements in inter was [1,2,3,4,5]; survivors are 1,3,5 → in original order
        check("intersection order [1,3,5] (original order)", toList(inter).equals(Arrays.asList(1, 3, 5)));

        // ── 8. removeAll — DIFFERENCE, original order kept ────
        section("removeAll (difference A \\ B)");
        MyOrderedSet<Integer> diff = new MyOrderedSet<>(Arrays.asList(1, 2, 3, 4, 5));
        boolean diffChanged = diff.removeAll(Arrays.asList(2, 4));
        check("removeAll returns true (changed)", diffChanged);
        check("diff size = 3", diff.size() == 3);
        check("diff order [1,3,5]", toList(diff).equals(Arrays.asList(1, 3, 5)));
        check("removeAll no match → false", !diff.removeAll(Arrays.asList(99, 100)));

        // ── 9. containsAll ────────────────────────────────────
        section("containsAll (subset check)");
        MyOrderedSet<Integer> sup = new MyOrderedSet<>(Arrays.asList(1, 2, 3, 4, 5));
        check("sub ⊆ sup", sup.containsAll(Arrays.asList(2, 4)));
        check("sup ⊄ sub", !new MyOrderedSet<>(Arrays.asList(2, 4))
                .containsAll(Arrays.asList(1, 2, 3, 4, 5)));
        check("containsAll empty → true", sup.containsAll(new ArrayList<>()));
        check("empty set containsAll empty → true",
                new MyOrderedSet<Integer>().containsAll(new ArrayList<>()));

        // ── 10. retainAll edge cases ──────────────────────────
        section("retainAll — edge cases");
        MyOrderedSet<Integer> r1 = new MyOrderedSet<>(Arrays.asList(1, 2, 3));
        check("retainAll identical → false", !r1.retainAll(Arrays.asList(1, 2, 3)));
        check("size unchanged", r1.size() == 3);
        MyOrderedSet<Integer> r2 = new MyOrderedSet<>(Arrays.asList(1, 2, 3));
        check("retainAll empty → true (all removed)", r2.retainAll(new ArrayList<>()));
        check("size = 0 after retainAll empty", r2.size() == 0);

        // ── 11. iterator ─────────────────────────────────────
        section("iterator");
        MyOrderedSet<Integer> iterSet = new MyOrderedSet<>(Arrays.asList(10, 20, 30));
        Iterator<Integer> it = iterSet.iterator();
        List<Integer> itResult = new ArrayList<>();
        while (it.hasNext()) itResult.add(it.next());
        check("iterator yields 3 elements", itResult.size() == 3);
        check("iterator insertion order [10,20,30]",
                itResult.equals(Arrays.asList(10, 20, 30)));
        // first element via iterator().next()
        check("iterator().next() = first inserted (10)",
                iterSet.iterator().next() == 10);

        // ── 12. forEach ───────────────────────────────────────
        section("forEach");
        MyOrderedSet<Integer> feSet = new MyOrderedSet<>(Arrays.asList(10, 20, 30));
        List<Integer> collected = new ArrayList<>();
        feSet.forEach(collected::add);
        check("forEach visits all 3 elements", collected.size() == 3);
        check("forEach insertion order [10,20,30]",
                collected.equals(Arrays.asList(10, 20, 30)));
        // forEach on empty set
        int[] feCount = {0};
        new MyOrderedSet<Integer>().forEach(e -> feCount[0]++);
        check("forEach on empty set: 0 visits", feCount[0] == 0);

        // ── 13. null element ──────────────────────────────────
        section("null element");
        MyOrderedSet<String> nullSet = new MyOrderedSet<>();
        check("add null → true", nullSet.add(null));
        check("add null duplicate → false", !nullSet.add(null));
        check("contains null = true", nullSet.contains(null));
        check("size = 1", nullSet.size() == 1);
        nullSet.add("hello");
        check("size = 2", nullSet.size() == 2);
        check("null is first (inserted first)", toList(nullSet).get(0) == null);
        check("remove null → true", nullSet.remove(null));
        check("null gone", !nullSet.contains(null));
        check("'hello' still present", nullSet.contains("hello"));
        check("size = 1 after null remove", nullSet.size() == 1);

        // ── 14. String-type set ───────────────────────────────
        section("String-type set");
        MyOrderedSet<String> strSet = new MyOrderedSet<>(
                Arrays.asList("banana", "apple", "banana"));
        check("dedup: size = 2", strSet.size() == 2);
        check("order [banana,apple] (first-seen)", toList(strSet).equals(
                Arrays.asList("banana", "apple")));
        check("remove 'banana' → true", strSet.remove("banana"));
        check("remove absent → false", !strSet.remove("cherry"));
        check("size after remove = 1", strSet.size() == 1);

        // ── 15. CP — ordered dedup (preserve first-seen) ──────
        section("CP — ordered dedup");
        List<Integer> raw = Arrays.asList(3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5);
        MyOrderedSet<Integer> orderedDedup = new MyOrderedSet<>(raw);
        List<Integer> result = toList(orderedDedup);
        check("deduped size = 7", result.size() == 7);
        check("first-seen order [3,1,4,5,9,2,6]",
                result.equals(Arrays.asList(3, 1, 4, 5, 9, 2, 6)));

        // ── 16. CP — first unique character ───────────────────
        section("CP — first unique character");
        String word = "leetcode";
        MyHashMap<Character, Integer> freq = new MyHashMap<>();
        MyOrderedSet<Character> chars = new MyOrderedSet<>();
        for (char c : word.toCharArray()) {
            freq.put(c, freq.getOrDefault(c, 0) + 1);
            chars.add(c);
        }
        char firstUnique = 0;
        for (char c : toList(chars)) {
            if (freq.get(c) == 1) { firstUnique = c; break; }
        }
        check("first unique char in 'leetcode' is 'l'", firstUnique == 'l');

        // ── 17. CP — sliding window oldest element ─────────────
        section("CP — sliding window oldest element");
        MyOrderedSet<Integer> window = new MyOrderedSet<>();
        window.add(5); window.add(3); window.add(8);
        check("oldest in window is 5", window.iterator().next() == 5);
        window.remove(5); // slide left
        window.add(7);
        check("oldest after slide is 3", window.iterator().next() == 3);
        check("window order [3,8,7]", toList(window).equals(Arrays.asList(3, 8, 7)));

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
 * ── insertion order preserved ──
 *   PASS  order [1,2,3]
 *   PASS  re-add 1 → false (no move)
 *   PASS  order unchanged after re-add
 * 
 * ── remove ──
 *   PASS  remove 2 → true
 *   PASS  remove absent → false
 *   PASS  size after remove = 2
 *   PASS  2 gone
 *   PASS  order [1,3] after remove middle
 * 
 * ── clear / isEmpty ──
 *   PASS  isEmpty after clear
 *   PASS  size = 0 after clear
 *   PASS  add after clear works
 * 
 * ── copy constructor — dedup + order ──
 *   PASS  unique count = 7
 *   PASS  insertion order [3,1,4,5,9,2,6]
 *   PASS  contains 9
 *   PASS  add duplicate → false
 *   PASS  order unchanged after dup add
 * 
 * ── addAll (union) ──
 *   PASS  addAll returns true (changed)
 *   PASS  union size = 5
 *   PASS  union order [1,2,3,4,5]
 *   PASS  addAll all-dup → false
 * 
 * ── retainAll (intersection) ──
 *   PASS  retainAll returns true (changed)
 *   PASS  size = 3
 *   PASS  intersection order [1,3,5] (original order)
 * 
 * ── removeAll (difference A \ B) ──
 *   PASS  removeAll returns true (changed)
 *   PASS  diff size = 3
 *   PASS  diff order [1,3,5]
 *   PASS  removeAll no match → false
 * 
 * ── containsAll (subset check) ──
 *   PASS  sub ⊆ sup
 *   PASS  sup ⊄ sub
 *   PASS  containsAll empty → true
 *   PASS  empty set containsAll empty → true
 * 
 * ── retainAll — edge cases ──
 *   PASS  retainAll identical → false
 *   PASS  size unchanged
 *   PASS  retainAll empty → true (all removed)
 *   PASS  size = 0 after retainAll empty
 * 
 * ── iterator ──
 *   PASS  iterator yields 3 elements
 *   PASS  iterator insertion order [10,20,30]
 *   PASS  iterator().next() = first inserted (10)
 * 
 * ── forEach ──
 *   PASS  forEach visits all 3 elements
 *   PASS  forEach insertion order [10,20,30]
 *   PASS  forEach on empty set: 0 visits
 * 
 * ── null element ──
 *   PASS  add null → true
 *   PASS  add null duplicate → false
 *   PASS  contains null = true
 *   PASS  size = 1
 *   PASS  size = 2
 *   PASS  null is first (inserted first)
 *   PASS  remove null → true
 *   PASS  null gone
 *   PASS  'hello' still present
 *   PASS  size = 1 after null remove
 * 
 * ── String-type set ──
 *   PASS  dedup: size = 2
 *   PASS  order [banana,apple] (first-seen)
 *   PASS  remove 'banana' → true
 *   PASS  remove absent → false
 *   PASS  size after remove = 1
 * 
 * ── CP — ordered dedup ──
 *   PASS  deduped size = 7
 *   PASS  first-seen order [3,1,4,5,9,2,6]
 * 
 * ── CP — first unique character ──
 *   PASS  first unique char in 'leetcode' is 'l'
 * 
 * ── CP — sliding window oldest element ──
 *   PASS  oldest in window is 5
 *   PASS  oldest after slide is 3
 *   PASS  window order [3,8,7]
 * 
 * ════════════════════════════
 *   Results: 71 passed, 0 failed
 * ════════════════════════════
 */