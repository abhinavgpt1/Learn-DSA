// ============================================================
// TreeSet — CP-focused method reference
// ============================================================
// Backed by a TreeMap<E, PRESENT> — keys are elements, value is a shared dummy Object.
// Key insight: a Red-Black BST under the hood — every operation is O(log n).
// Use over HashSet/LinkedHashSet when you need SORTED order, range queries,
// or navigation (floor/ceiling/predecessor/successor).
// O(1) membership → HashSet. Insertion-order → LinkedHashSet. Sorted → TreeSet ★

// Internal structure:
//   TreeMap<E, Object>     — Red-Black BST, sorted by natural order or Comparator
//   No hash table, no linked list — pure BST navigation
//   null elements NOT allowed (unless Comparator handles null explicitly)

// O(log n) Core operations  ★ most important for CP
// ---------------------------------------------------
// add(E e)                 -> boolean   true if element was NOT already present
// remove(Object o)         -> boolean   true if element WAS present and removed
// contains(Object o)       -> boolean   true if element exists
// size()                   -> int
// isEmpty()                -> boolean
// clear()                  -> void

// O(log n) Sorted-order navigation  ★★ killer feature vs HashSet/LinkedHashSet
// ------------------------------------------------------------------------------
// first()                  -> E         smallest element; throws NoSuchElementException if empty
// last()                   -> E         largest element;  throws NoSuchElementException if empty
// floor(E e)               -> E         largest element <= e; null if none       (≤ query)
// ceiling(E e)             -> E         smallest element >= e; null if none      (≥ query)
// lower(E e)               -> E         largest element strictly < e; null if none  (< query)
// higher(E e)              -> E         smallest element strictly > e; null if none (> query)
// pollFirst()              -> E         remove & return smallest; null if empty
// pollLast()               -> E         remove & return largest;  null if empty

// O(log n + result) Range views (live, backed by original set)  ★★ range CP patterns (not implemented here)
// ---------------------------------------------------------------------------------------------------------
// headSet(E toE)                        -> SortedSet     elements strictly < toE
// headSet(E toE, boolean inclusive)     -> NavigableSet  elements < toE (or <= if inclusive)
// tailSet(E fromE)                      -> SortedSet     elements >= fromE
// tailSet(E fromE, boolean inclusive)   -> NavigableSet  elements > fromE (or >= if inclusive)
// subSet(E from, E to)                  -> SortedSet     elements in [from, to)
// subSet(E from, boolean, E to, boolean)-> NavigableSet  full inclusive/exclusive control
//
// Range views are LIVE — modifications to the view reflect in the original set and vice versa.
// Range count: headSet(x).size() → count of elements < x  (O(n) traversal, but simple)

// O(n) Iteration
// ---------------
// iterator()               -> Iterator<E>          ascending order (smallest → largest)
// descendingIterator()     -> Iterator<E>          descending order (largest → smallest)
// descendingSet()          -> NavigableSet<E>      full set view in reverse sorted order
// forEach(e -> { })        -> void                 ascending order

// O(n) Set-algebra operations  ★ works on any Collection
// --------------------------------------------------------
// addAll(Collection c)     -> boolean   UNION        in-place; true if set changed
// retainAll(Collection c)  -> boolean   INTERSECTION in-place; surviving elements remain sorted
// removeAll(Collection c)  -> boolean   DIFFERENCE   in-place; removes all elements also in c
// containsAll(Collection c)-> boolean   SUBSET check; true if every element of c is present
//
// To preserve original: copy first → new TreeSet<>(setA)  then call bulk op on copy

// Common CP Patterns  ★★★
// ------------------------
// Predecessor / Successor      — lower(x) / higher(x)  → BST predecessor/successor in O(log n)
// Floor / Ceiling queries      — floor(x) / ceiling(x) → nearest ≤ or ≥ in O(log n)
// Sliding window min/max       — pollFirst()/pollLast() to pop extremes; O(log n) per step
// Sorted dedup                 — new TreeSet<>(list) → unique elements in sorted order
// Count elements < x           — headSet(x).size() → useful for inversion count-style problems
// Count elements in [lo, hi]   — subSet(lo, true, hi, true).size()
// K-th smallest element        — iterate or use headSet(x).size() + binary search on the set
// Binary search on sorted set  — ceiling(mid)/floor(mid) replaces manual binary search arrays
// Meeting rooms / intervals    — ceiling(start) to find next non-overlapping interval start
// Coordinate compression       — add all coords; use floor/ceiling for range mapping
// Merge intervals              — pollFirst() repeatedly; merge overlapping intervals greedily
// Ordered distinct output      — TreeSet guarantees sorted unique output without Arrays.sort()
// Two-pointer on sorted unique — convert list to TreeSet; use iterator for ascending sweep

// TreeSet vs HashSet vs LinkedHashSet
// ------------------------------------
// HashSet        O(1)        no order guarantee               → fastest membership test
// LinkedHashSet  O(1)        insertion-order preserved        → dedup + remembered order
// TreeSet        O(log n)    always sorted (natural/Comparator)→ range queries / navigation  ★ use this

// ============================================================

import java.util.*;

class MyTreeSet<E> {
    // Internal state — delegates to MyTreeMap (Red-Black BST)
    // TODO: replace MySortedMap with MyTreeMap once implemented
    private static final Object PRESENT = new Object();
    private final MySortedMap<E, Object> map;

    // ── Constructors ─────────────────────────────────────────
    MyTreeSet() {
        this.map = new MySortedMap<>();
    }

    MyTreeSet(Collection<? extends E> c) {
        this.map = new MySortedMap<>();
        addAll(c);
    }

    MyTreeSet(Comparator<? super E> comparator) {
        this.map = new MySortedMap<>(comparator);
    }

    // ── O(log n) Core ────────────────────────────────────────
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

    // ── O(log n) Navigation ★★ CP killer ───────────────────
    E first() {
        return map.firstKey();
    }

    E last() {
        return map.lastKey();
    }

    E floor(E e) {
        return map.floorKey(e);
    }

    E ceiling(E e) {
        return map.ceilingKey(e);
    }

    E lower(E e) {
        return map.lowerKey(e);
    }

    E higher(E e) {
        return map.higherKey(e);
    }

    E pollFirst() {
        Map.Entry<E, Object> e = map.pollFirstEntry();
        return e == null ? null : e.getKey();
    }

    E pollLast() {
        Map.Entry<E, Object> e = map.pollLastEntry();
        return e == null ? null : e.getKey();
    }

    // ── O(n) Iteration — sorted order ────────────────────────
    Iterator<E> iterator() {
        return map.keySet().iterator();
    }

    Iterator<E> descendingIterator() {
        return map.descendingKeySet().iterator();
    }

    // Safe: cmp==null only when caller used natural ordering, so E is Comparable at runtime.
    @SuppressWarnings("unchecked")
    MyTreeSet<E> descendingSet() {
        Comparator<? super E> cmp = map.comparator();
        Comparator<? super E> rev = cmp == null ? (Comparator<? super E>) Comparator.reverseOrder() : cmp.reversed();
        MyTreeSet<E> desc = new MyTreeSet<>(rev);
        for (E e : map.keySet()) {
            desc.add(e);
        }
        return desc;
    }

    void forEach(java.util.function.Consumer<? super E> fn) {
        map.forEach((k, v) -> fn.accept(k));
    }

    // ── O(n) Set-algebra ─────────────────────────────────────
    boolean addAll(Collection<? extends E> c) {
        boolean changed = false;
        for (E e : c) {
            if (add(e))
                changed = true;
        }
        return changed;
    }

    boolean containsAll(Collection<?> c) {
        for (Object o : c) {
            if (!contains(o))
                return false;
        }
        return true;
    }

    boolean removeAll(Collection<?> c) {
        boolean changed = false;
        for (Object o : c) {
            if (remove(o))
                changed = true;
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
}

public class _14_TreeSetImpl {

    static void check(boolean condition, String msg) {
        if (!condition)
            throw new AssertionError("FAIL: " + msg);
    }

    public static void main(String[] args) {

        // ── 1. add / contains / size / isEmpty ───────────────────────────────
        System.out.println("1. add / contains / size / isEmpty");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            check(s.isEmpty(), "new set is empty");
            check(s.size() == 0, "size is 0");
            check(s.add(5), "add new element returns true");
            check(s.add(3), "add new element returns true");
            check(s.add(7), "add new element returns true");
            check(!s.add(5), "add duplicate returns false");
            check(s.size() == 3, "size after 3 unique adds");
            check(!s.isEmpty(), "not empty");
            check(s.contains(3), "contains existing");
            check(!s.contains(99), "contains missing returns false");
        }
        System.out.println("   PASS");

        // ── 2. remove / contains after remove ────────────────────────────────
        System.out.println("2. remove");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            s.add(1); s.add(2); s.add(3);
            check(s.remove(2), "remove existing returns true");
            check(!s.contains(2), "removed element not found");
            check(s.size() == 2, "size decremented");
            check(!s.remove(99), "remove missing returns false");
            check(s.size() == 2, "size unchanged after failed remove");
        }
        System.out.println("   PASS");

        // ── 3. first / last ───────────────────────────────────────────────────
        System.out.println("3. first / last");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            s.add(10); s.add(4); s.add(7); s.add(1); s.add(15);
            check(s.first() == 1, "first is min");
            check(s.last() == 15, "last is max");
            // single element
            MyTreeSet<Integer> single = new MyTreeSet<>();
            single.add(42);
            check(single.first() == 42, "first of single");
            check(single.last() == 42, "last of single");
            // empty → NoSuchElementException
            MyTreeSet<Integer> empty = new MyTreeSet<>();
            try { empty.first(); check(false, "first() on empty should throw"); }
            catch (java.util.NoSuchElementException ignored) {}
            try { empty.last(); check(false, "last() on empty should throw"); }
            catch (java.util.NoSuchElementException ignored) {}
        }
        System.out.println("   PASS");

        // ── 4. floor / ceiling / lower / higher ──────────────────────────────
        System.out.println("4. floor / ceiling / lower / higher");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            // set: {1, 3, 5, 7, 9}
            for (int v : new int[]{5, 3, 7, 1, 9}) s.add(v);

            check(s.floor(5) == 5, "floor of existing element");
            check(s.floor(4) == 3, "floor of gap");
            check(s.floor(0) == null, "floor below min is null");

            check(s.ceiling(5) == 5, "ceiling of existing element");
            check(s.ceiling(6) == 7, "ceiling of gap");
            check(s.ceiling(10) == null, "ceiling above max is null");

            check(s.lower(5) == 3, "lower strictly < 5");
            check(s.lower(1) == null, "lower of min is null");
            check(s.lower(6) == 5, "lower of gap");

            check(s.higher(5) == 7, "higher strictly > 5");
            check(s.higher(9) == null, "higher of max is null");
            check(s.higher(4) == 5, "higher of gap");
        }
        System.out.println("   PASS");

        // ── 5. pollFirst / pollLast ───────────────────────────────────────────
        System.out.println("5. pollFirst / pollLast");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            s.add(3); s.add(1); s.add(5);
            check(s.pollFirst() == 1, "pollFirst returns min");
            check(s.size() == 2, "size decremented after pollFirst");
            check(s.pollLast() == 5, "pollLast returns max");
            check(s.size() == 1, "size decremented after pollLast");
            check(s.pollFirst() == 3, "pollFirst on last element");
            check(s.isEmpty(), "empty after all polls");
            // empty set → null (no NPE)
            check(s.pollFirst() == null, "pollFirst on empty returns null");
            check(s.pollLast() == null, "pollLast on empty returns null");
        }
        System.out.println("   PASS");

        // ── 6. clear ─────────────────────────────────────────────────────────
        System.out.println("6. clear");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            s.add(1); s.add(2); s.add(3);
            s.clear();
            check(s.isEmpty(), "empty after clear");
            check(s.size() == 0, "size 0 after clear");
            check(!s.contains(1), "no elements after clear");
            s.add(10); // can still use after clear
            check(s.size() == 1, "add after clear works");
        }
        System.out.println("   PASS");

        // ── 7. iterator (ascending) ───────────────────────────────────────────
        System.out.println("7. iterator ascending");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            s.add(5); s.add(2); s.add(8); s.add(1); s.add(4);
            java.util.Iterator<Integer> it = s.iterator();
            int[] expected = {1, 2, 4, 5, 8};
            for (int exp : expected) {
                check(it.hasNext(), "hasNext");
                check(it.next() == exp, "ascending order: expected " + exp);
            }
            check(!it.hasNext(), "iterator exhausted");
        }
        System.out.println("   PASS");

        // ── 8. descendingIterator ─────────────────────────────────────────────
        System.out.println("8. descendingIterator");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            s.add(5); s.add(2); s.add(8); s.add(1); s.add(4);
            java.util.Iterator<Integer> it = s.descendingIterator();
            int[] expected = {8, 5, 4, 2, 1};
            for (int exp : expected) {
                check(it.hasNext(), "hasNext");
                check(it.next() == exp, "descending order: expected " + exp);
            }
        }
        System.out.println("   PASS");

        // ── 9. descendingSet ──────────────────────────────────────────────────
        System.out.println("9. descendingSet");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            s.add(3); s.add(1); s.add(5);
            MyTreeSet<Integer> desc = s.descendingSet();
            check(desc.first() == 5, "descendingSet first is max");
            check(desc.last() == 1, "descendingSet last is min");
            check(desc.size() == 3, "descendingSet same size");
        }
        System.out.println("   PASS");

        // ── 10. addAll (union) ────────────────────────────────────────────────
        System.out.println("10. addAll (union)");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            s.add(1); s.add(3); s.add(5);
            check(s.addAll(java.util.Arrays.asList(3, 4, 5, 6)), "addAll returns true when changed");
            check(s.size() == 5, "union size"); // {1,3,4,5,6}
            check(s.contains(4) && s.contains(6), "new elements present");
            check(!s.addAll(java.util.Arrays.asList(1, 3)), "addAll returns false when no change");
        }
        System.out.println("   PASS");

        // ── 11. removeAll (difference) ────────────────────────────────────────
        System.out.println("11. removeAll (difference)");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            s.add(1); s.add(2); s.add(3); s.add(4);
            check(s.removeAll(java.util.Arrays.asList(2, 4, 99)), "removeAll returns true when changed");
            check(s.size() == 2, "size after removeAll"); // {1,3}
            check(s.contains(1) && s.contains(3), "remaining elements correct");
            check(!s.removeAll(java.util.Arrays.asList(99, 100)), "removeAll returns false when no match");
        }
        System.out.println("   PASS");

        // ── 12. retainAll (intersection) ──────────────────────────────────────
        System.out.println("12. retainAll (intersection)");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            s.add(1); s.add(2); s.add(3); s.add(4);
            check(s.retainAll(java.util.Arrays.asList(2, 4, 6)), "retainAll returns true when changed");
            check(s.size() == 2, "size after retainAll"); // {2,4}
            check(s.contains(2) && s.contains(4), "retained elements correct");
            check(!s.contains(1) && !s.contains(3), "non-retained elements gone");
            check(!s.retainAll(java.util.Arrays.asList(2, 4)), "retainAll false when nothing changes");
        }
        System.out.println("   PASS");

        // ── 13. containsAll (subset) ──────────────────────────────────────────
        System.out.println("13. containsAll (subset check)");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            s.add(1); s.add(2); s.add(3); s.add(4); s.add(5);
            check(s.containsAll(java.util.Arrays.asList(2, 4)), "subset present");
            check(s.containsAll(java.util.Arrays.asList(1, 2, 3, 4, 5)), "full set is subset of itself");
            check(!s.containsAll(java.util.Arrays.asList(2, 99)), "returns false if any missing");
        }
        System.out.println("   PASS");

        // ── 14. Collection constructor ────────────────────────────────────────
        System.out.println("14. Collection constructor (dedup + sorted)");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>(java.util.Arrays.asList(5, 3, 5, 1, 3, 9));
            check(s.size() == 4, "duplicates removed: {1,3,5,9}");
            check(s.first() == 1 && s.last() == 9, "sorted order preserved");
        }
        System.out.println("   PASS");

        // ── 15. Custom comparator (reverse order) ─────────────────────────────
        System.out.println("15. Custom comparator (reverse order)");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>(Comparator.reverseOrder());
            s.add(3); s.add(1); s.add(5); s.add(2);
            check(s.first() == 5, "first with reverse cmp is max");
            check(s.last() == 1, "last with reverse cmp is min");
            // floor/ceiling respect the custom comparator
            check(s.floor(4) == 5, "floor with reverse cmp: largest key <= 4 in reverse = 5");
        }
        System.out.println("   PASS");

        // ── 16. forEach ───────────────────────────────────────────────────────
        System.out.println("16. forEach (ascending)");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            s.add(4); s.add(1); s.add(7);
            java.util.List<Integer> out = new java.util.ArrayList<>();
            s.forEach(out::add);
            check(out.equals(java.util.Arrays.asList(1, 4, 7)), "forEach in ascending order");
        }
        System.out.println("   PASS");

        // ── 17. retainAll that empties the set ────────────────────────────────
        System.out.println("17. retainAll empties set");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            s.add(1); s.add(2); s.add(3);
            check(s.retainAll(java.util.Arrays.asList(99, 100)), "retainAll returns true");
            check(s.isEmpty(), "set is empty after retaining disjoint collection");
            check(s.size() == 0, "size is 0");
        }
        System.out.println("   PASS");

        // ── 18. removeAll that empties the set ───────────────────────────────
        System.out.println("18. removeAll empties set");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            s.add(1); s.add(2); s.add(3);
            check(s.removeAll(java.util.Arrays.asList(1, 2, 3, 4)), "removeAll returns true");
            check(s.isEmpty(), "set is empty after removing all elements");
        }
        System.out.println("   PASS");

        // ── 19. forEach on empty set ──────────────────────────────────────────
        System.out.println("19. forEach on empty set");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            int[] count = {0};
            s.forEach(e -> count[0]++);
            check(count[0] == 0, "forEach on empty set: action never called");
        }
        System.out.println("   PASS");

        // ── 20. descendingSet iterator order ─────────────────────────────────
        System.out.println("20. descendingSet iterator order");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            s.add(1); s.add(5); s.add(3); s.add(7); s.add(2);
            MyTreeSet<Integer> desc = s.descendingSet();
            java.util.Iterator<Integer> it = desc.iterator();
            int[] expected = {7, 5, 3, 2, 1};
            for (int exp : expected) {
                check(it.hasNext(), "hasNext");
                check(it.next() == exp, "descendingSet iterator: expected " + exp);
            }
            check(!it.hasNext(), "iterator exhausted");
        }
        System.out.println("   PASS");

        // ── 21. addAll from empty collection ─────────────────────────────────
        System.out.println("21. addAll from empty collection");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            s.add(1); s.add(2);
            check(!s.addAll(java.util.Collections.emptyList()), "addAll empty → false");
            check(s.size() == 2, "size unchanged");
        }
        System.out.println("   PASS");

        // ── 22. String element type ───────────────────────────────────────────
        System.out.println("22. String element type");
        {
            MyTreeSet<String> s = new MyTreeSet<>();
            s.add("banana"); s.add("apple"); s.add("cherry");
            check(s.first().equals("apple"), "first string");
            check(s.last().equals("cherry"), "last string");
            check(s.floor("blueberry").equals("banana"), "floor string");
            check(s.ceiling("blueberry").equals("cherry"), "ceiling string");
            check(s.contains("banana"), "contains string");
            check(!s.contains("grape"), "not contains string");
            s.remove("banana");
            check(!s.contains("banana"), "string removed");
            check(s.size() == 2, "size after string remove");
        }
        System.out.println("   PASS");

        // ── 23. pollFirst / pollLast alternating ─────────────────────────────
        System.out.println("23. pollFirst / pollLast alternating");
        {
            MyTreeSet<Integer> s = new MyTreeSet<>();
            for (int v : new int[]{1, 2, 3, 4, 5}) s.add(v);
            check(s.pollFirst() == 1, "pollFirst: 1");
            check(s.pollLast()  == 5, "pollLast: 5");
            check(s.pollFirst() == 2, "pollFirst: 2");
            check(s.pollLast()  == 4, "pollLast: 4");
            check(s.pollFirst() == 3, "pollFirst: 3 (last element)");
            check(s.isEmpty(), "empty after alternating polls");
        }
        System.out.println("   PASS");

        System.out.println("\nAll tests PASSED");
    }
}

/**
 * Output:
 * -------
 * 1. add / contains / size / isEmpty
 *    PASS
 * 2. remove
 *    PASS
 * 3. first / last
 *    PASS
 * 4. floor / ceiling / lower / higher
 *    PASS
 * 5. pollFirst / pollLast
 *    PASS
 * 6. clear
 *    PASS
 * 7. iterator ascending
 *    PASS
 * 8. descendingIterator
 *    PASS
 * 9. descendingSet
 *    PASS
 * 10. addAll (union)
 *    PASS
 * 11. removeAll (difference)
 *    PASS
 * 12. retainAll (intersection)
 *    PASS
 * 13. containsAll (subset check)
 *    PASS
 * 14. Collection constructor (dedup + sorted)
 *    PASS
 * 15. Custom comparator (reverse order)
 *    PASS
 * 16. forEach (ascending)
 *    PASS
 * 17. retainAll empties set
 *    PASS
 * 18. removeAll empties set
 *    PASS
 * 19. forEach on empty set
 *    PASS
 * 20. descendingSet iterator order
 *    PASS
 * 21. addAll from empty collection
 *    PASS
 * 22. String element type
 *    PASS
 * 23. pollFirst / pollLast alternating
 *    PASS
 *
 * All tests PASSED
 */