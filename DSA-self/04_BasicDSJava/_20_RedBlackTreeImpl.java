// ============================================================
// TreeMap — supplementary notes (missing from TreeMapWithoutRedBlackImpl)
// See TreeMapWithoutRedBlackImpl.java for core methods, navigation, and CP patterns
// ============================================================

// ── Red-Black Tree — how Java's TreeMap actually works ───────
// A Red-Black tree is a self-balancing BST where every node is coloured RED or BLACK.
// It guarantees O(log n) for all operations by enforcing 5 invariants:
//
//   1. Every node is RED or BLACK.
//   2. The root is BLACK.
//   3. Every null leaf (NIL sentinel) is BLACK.
//   4. A RED node's children must both be BLACK (no two consecutive reds).
//   5. Every path from a node down to any NIL leaf passes through the SAME number
//      of BLACK nodes  →  called "black-height".
//
// Because of invariant 5, the longest possible path (alternating red-black) is at
// most TWICE the shortest (all black), keeping the tree height ≤ 2 log₂(n+1).
//
// Insertions / Deletions repair violations via two tools:
//   Recolouring  — flip colours of a node and its parent/uncle (O(1) per step)
//   Rotations    — local pointer restructuring that preserves BST order (O(1) each)
//
//   Left rotation on X:          Right rotation on Y:
//         X                              Y
//        / \           →               / \
//       α   Y                         X   γ
//          / \                       / \
//         β   γ                     α   β
//
// Insert fix-up: new node inserted RED.
//   Case 1 — uncle is RED   : recolour parent+uncle BLACK, grandparent RED; move up.
//   Case 2 — uncle is BLACK, "triangle" shape : rotate parent.
//   Case 3 — uncle is BLACK, "line" shape     : rotate grandparent, swap colours.
//
// Delete fix-up: more complex (handles "double-black" nodes via 4 cases of rotations
//   and recolouring). At most 3 rotations total per deletion.
//
// Net result: at most O(log n) recolourings + at most 2 rotations per insert,
//             at most 3 rotations per delete.  Height always ≤ 2 log₂(n+1).

// ── TreeMap vs HashMap vs LinkedHashMap ─────────────────────
// HashMap        O(1) avg        no order guarantee               → pure speed
// LinkedHashMap  O(1) avg        insertion-order or access-order  → speed + remembered order
// TreeMap        O(log n)        always sorted by key             → range queries / min / max
//
// Choose TreeMap when:
//   • You need keys in sorted order at all times
//   • You need floor/ceiling/range queries (subMap, headMap, tailMap)
//   • You need first/last/poll operations on a sorted set of entries
//
// Avoid TreeMap when:
//   • Pure lookup/insert speed matters (use HashMap instead)
//   • Key type doesn't implement Comparable and you have no Comparator
// ============================================================

import java.util.OrderedMap;
import java.util.LinkedList;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.Deque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;

public class TreeMapImpl {
    public static void main(String[] args) {
        TreeSet<Integer> treeSet = new TreeSet<>();
        treeSet.retainAll(java.util.Collections.singleton(5));
        TreeMap<Integer, String> treeMap = new TreeMap<>();
        treeMap.get(5);
        treeMap.comparator();
        HashSet<Integer> hashSet = new HashSet<>();
        hashSet.poll();
        Deque<Integer> deque = new LinkedList<>();
        deque.pop();
    }
}