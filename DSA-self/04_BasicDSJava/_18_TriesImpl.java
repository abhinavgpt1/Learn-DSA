// Trie (Prefix Tree)
// ==================
// Def: Tree-like data structure for storing strings, where each node represents a character and paths represent words/prefixes.
// Use cases: autocomplete, prefix search, lexicographic queries, word break, distinct substring counting, XOR problems (Binary Trie).
//
// Structure: each node stores children[26] (lowercase a-z) + isTerminal flag
// Time:  insert / search / delete / startsWith → O(L)  where L = word length
// Space: O(ALPHABET_SIZE * L * N)                      where N = number of words
//
// When to use a Trie over a HashMap<String, ...>:
//   - Need prefix queries (startsWith, autocomplete, LCP)
//   - Need lexicographic ordering without sorting
//   - Need XOR-max/min on integers (Binary Trie)
//   - Need to count distinct substrings / prefixes
//
// Variants:
//   - Standard Trie   — lowercase alphabet, 26-way branching
//   - Binary Trie     — bits 0/1, used for XOR problems (competitive programming)
//   - Compressed Trie — Patricia / Radix tree, merges single-child chains
//   - Suffix Trie     — all suffixes of a string (use Suffix Array for O(n log n) build)
//
// Common operations & algorithms:
//   longestCommonPrefix()    O(L)      — walk root while exactly 1 child & not terminal; append char
//   lexicographicallySmallest() O(L)  — greedily pick smallest non-null child (0→25) until terminal
//   lexicographicallyLargest()  O(L)  — greedily pick largest non-null child (25→0) until terminal
//   kthSmallest(k)           O(L×26)  — DFS (0→25); count subtree words to skip k-1, then descend
//
// Binary Trie (XOR problems) — bits 0/1, 32-way depth (one level per bit, MSB→LSB):
//   Structure: int[][] children (array-backed, pre-allocated); children[node][0/1] = child index
//   Visual (inserting 5=101, 3=011, 6=110, only showing bits 2→0 for brevity):
//              root
//           0/       \1
//          [0]        [1]
//         1/ \0     1/ \0
//        [01] [00] [11] [10]
//       1/              \0
//      [011]            [110]   ← 3(011), 6(110); 5(101) would be root→1→0→1
//   children[0][bit] = opposite-bit branch for maxXor; same-bit branch for minXor
//   maxXor(num)           O(BITS) — greedily go to opposite bit each level; accumulate result
//   minXor(num)           O(BITS) — greedily go to same bit each level; accumulate result
//   countXorLessThan(k)   O(BITS) — at each bit: if k-bit=1 → count same-bit subtree + go opposite
//
// Common CP problems:
//   LC 421  — Max XOR of two numbers in array           → Binary Trie, insert all, query maxXor each
//   LC 1707 — Max XOR with element from array (queries) → offline sort + Binary Trie
//   LC 212  — Word Search II (board + word list)        → Standard Trie + DFS with pruning
//   LC 336  — Palindrome Pairs                          → insert reversed words; 3-case check per word
//   LC 648  — Replace Words                             → insert roots; replace each word with shortest prefix
//   —       — Max XOR subarray                          → prefix XOR array; for each prefXor[i] query maxXor
//   —       — Count pairs with XOR in [lo, hi]          → countXorLessThan(hi+1) − countXorLessThan(lo)
//   —       — Word suggestion / autocomplete            → Trie + DFS + priority queue for top-K completions
//   —       — Spell checker / edit distance             → DFS on trie; prune branches exceeding edit budget
//   —       — IP routing (longest prefix match)         → Binary Trie on 32-bit IP; query longest match
//   —       — Count distinct substrings                 → insert all suffixes; answer = nodes − root
//             (for large strings: Suffix Array + LCP array, O(N log N))
//   —       — Minimum Word Break                        → DP (like wordBreak) but track min-cuts; dp[i] = min(dp[j]+1) for all j where s[j..i] in trie
//   —       — Unique rows in binary matrix              → insert each row as a binary string into Trie; skip if already present (search before insert)
//   —       — Word Boggle (board + dictionary)          → build Trie from dictionary; DFS on board with trie node pointer; prune on trie miss
//   —       — Sort array of strings                     → insert all into Trie; in-order DFS (children 0→25) to collect words in lexicographic order
//   —       — Display / print all Trie words            → DFS/BFS from root; accumulate path; print at each isTerminal node
//   —       — Pattern search using Suffix Trie          → insert all suffixes of text; search(pattern) → O(|pattern|) lookup; all occurrences = leaves under match node
//
// ref:
// - https://www.geeksforgeeks.org/dsa/trie-insert-and-search/
// - https://www.geeksforgeeks.org/dsa/trie-delete/
// - https://www.geeksforgeeks.org/dsa/introduction-to-trie-data-structure-and-algorithm-tutorials/
// ============================================================

// ── TrieNode ──────────────────────────────────────────────────────────────────

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

class TrieNode {
    TrieNode[] children;
    boolean isTerminal;
    char ch; // optional

    TrieNode() {
        children = new TrieNode[26];
        isTerminal = false;
        this.ch = '\0';
    }

    TrieNode(char ch) {
        children = new TrieNode[26];
        isTerminal = false;
        this.ch = ch;
    }
}

// ── Standard Trie
// ─────────────────────────────────────────────────────────────
class MyTrie {
    private TrieNode root;

    MyTrie() {
        root = new TrieNode();
    }

    private void insert(TrieNode node, String word, int index) {
        if (node == null)
            return; // defensive, should not happen in normal insert flow

        if (index == word.length()) {
            node.isTerminal = true;
            return;
        }
        char ch = word.charAt(index);
        int childIdx = ch - 'a';
        if (node.children[childIdx] == null) {
            node.children[childIdx] = new TrieNode(ch);
        }
        insert(node.children[childIdx], word, index + 1);
    }

    private boolean isEmpty(TrieNode node) {
        for (TrieNode child : node.children) {
            if (child != null)
                return false;
        }
        return true;
    }

    private TrieNode delete(TrieNode node, String word, int index) {
        if (node == null)
            return null; // word not found

        if (index == word.length()) {
            if (!node.isTerminal)
                return node; // word not found

            node.isTerminal = false; // This is all you need to do to "delete" the word logically. 
            // [IMP for Algos] Rest everything is just cleanup of nodes that are no longer needed

            if (isEmpty(node))
                return null;
            return node;
        }
        char ch = word.charAt(index);
        int childIdx = ch - 'a';
        node.children[childIdx] = delete(node.children[childIdx], word, index + 1);

        // PTR: if TrieNode had a count field, then a little rewiring would be needed here to decrement counts on the way back up, and only delete if child actually got removed (null) and not just logically unmarked as terminal. This is a common source of bugs in count-maintaining Trie delete implementations.

        // After deleting child, check if current node can also be deleted.
        if (!node.isTerminal && isEmpty(node)) {
            return null;
        }
        return node;
    }

    // ── Core Operations ───────────────────────────────────────────────────────

    // Insert a word. O(L)
    public void insert(String word) {
        insert(root, word, 0);
    }

    // Returns true if word exists exactly. O(L)
    public boolean search(String word) {
        TrieNode node = root;
        for (int i = 0; i < word.length(); i++) {
            char ch = word.charAt(i);
            int childIdx = ch - 'a';
            if (node.children[childIdx] == null) {
                return false;
            }
            node = node.children[childIdx];
        }
        return node.isTerminal;
    }

    // Returns true if any inserted word starts with prefix. O(L)
    public boolean startsWith(String prefix) {
        TrieNode node = root;
        for (int i = 0; i < prefix.length(); i++) {
            char ch = prefix.charAt(i);
            int childIdx = ch - 'a';
            if (node.children[childIdx] == null) {
                return false;
            }
            node = node.children[childIdx];
        }
        return true; // reached end of prefix successfully, no need to check isTerminal
    }

    // Delete a word (only if it was inserted). Time: O(L), Space: O(L) call stack.
    // PTR: only remove nodes that are not shared by other words.
    // BUG FIX: do NOT assign root = delete(...); if the trie becomes empty the recursion
    //          returns null, setting root=null → NPE on any subsequent call.
    //          root is a permanent sentinel. Children cleanup still happens via
    //          in-place node.children[idx]=null assignments inside the recursion.
    public void delete(String word) {
        delete(root, word, 0);
    }

    // ── Prefix / Count Queries ────────────────────────────────────────────────

    // Count words that start with prefix. O(subtree_size) — BFS over all nodes under prefix endpoint.
    // PTR: Maintain a count field in TrieNode (increment on insert, decrement on delete)
    //      to reduce this to O(L) — navigate to prefix endpoint, return node.count.
    public int countWordsWithPrefix(String prefix) {
        // find the node till prefix
        TrieNode node = root;
        for(int i=0; i<prefix.length(); i++) {
            char ch = prefix.charAt(i);
            int charIdx = ch - 'a';
            if (node.children[charIdx] == null)
                return 0;
            node = node.children[charIdx];
        }
        int count = 0;
        Queue<TrieNode> pending = new LinkedList<>();
        pending.add(node);
        while(!pending.isEmpty()) {
            TrieNode front = pending.remove();
            if(front.isTerminal)
                count++;

            for(TrieNode child: front.children) {
                if (child != null) {
                    pending.add(child);
                }
            }
        }
        return count;
    }

    // Count total distinct words in the trie.
    // O(N*L) BFS, or O(1) if maintained separately.
    // PTR: HashSet<String> is unnecessary — each BFS path in a trie is unique by construction.
    public int countWords() {
        int count = 0;
        Queue<TrieNode> pending = new LinkedList<>();
        pending.add(root);
        while (!pending.isEmpty()) {
            TrieNode front = pending.remove();
            if (front.isTerminal)
                count++;
            for (TrieNode child : front.children) {
                if (child != null)
                    pending.add(child);
            }
        }
        return count;
    }

    // ── Autocomplete / Suggestions ────────────────────────────────────────────

    // Return all words in trie that start with prefix. O(RESULT_SIZE * L)
    // Approach: navigate to prefix endpoint, then BFS to collect all words.
    public List<String> autocomplete(String prefix) {
        List<String> results = new ArrayList<>();
        TrieNode node = root;
        for(int i=0; i<prefix.length(); i++) {
            char ch = prefix.charAt(i);
            int charIdx = ch - 'a';
            if (node.children[charIdx] == null)
                return results; // empty list, no words with this prefix
            node = node.children[charIdx];
        }
        // node is now at end of prefix, BFS to find all words under this node
        class Pair {
            TrieNode node;
            String word;
            Pair(TrieNode node, String word) {
                this.node = node;
                this.word = word;
            }
        }
        Queue<Pair> pending = new LinkedList<>();
        pending.add(new Pair(node, prefix));
        while(!pending.isEmpty()) {
            Pair front = pending.remove();
            if(front.node.isTerminal)
                results.add(front.word);

            for(TrieNode child: front.node.children) {
                if (child != null) {
                    pending.add(new Pair(child, front.word + child.ch));
                }
            }
        }
        return results;
    }

    // ── Competitive Programming Patterns ──────────────────────────────────────

    // Longest word in trie that is a prefix of a given string. O(L)
    // e.g. Trie has {"ap","app","apple"}; query "applesauce" → "apple"
    // Approach: walk trie following characters of query; track last isTerminal
    // position.
    public String longestWordPrefixOf(String query) {
        TrieNode node = root;
        String wordPrefix = "";
        StringBuilder curr = new StringBuilder();
        for (int i = 0; i < query.length(); i++) {
            char ch = query.charAt(i);
            int charIdx = ch - 'a';
            if (node.children[charIdx] == null) {
                break;
            }
            node = node.children[charIdx];
            curr.append(ch);

            if (node.isTerminal) {
                wordPrefix = curr.toString();
            }
        }
        return wordPrefix;
    }

    // Word Break: can `s` be segmented into trie words? O(L^2) DP + O(L) trie lookup.
    // PTR: dp[i] = true if s[0..i-1] can be segmented.
    // For each i, check all j < i: dp[j] && search(s.substring(j, i)).
    public boolean wordBreak(String s) {
        int[] dp = new int[s.length() + 1]; // 0 = false, 1 = true, -1 = unvisited
        Arrays.fill(dp, -1);

        dp[0] = 1; // empty string can be segmented

        // This can be done recursively as well where you call isWordBreak(s, 0, s.length() - 1)
        // which checks for dp[i] && isWordBreak(s, i, end). PTR: set dp[1] before calling recursion. 
        for (int i = 1; i <= s.length(); i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] == 1 && search(s.substring(j, i))) {
                    dp[i] = 1;
                    break;
                }
            }
        }
        return dp[s.length()] == 1;
    }

    // Count distinct substrings of a string. O(N^2) build, O(1) query.
    // Approach: insert every suffix of the string; answer = total nodes created
    // (excluding root).
    // PTR: Use Suffix Array + LCP array for O(N log N) if string is large.
    // BUG FIX: use a local root — inserting into this.root would pollute the trie
    //          and give wrong counts if any nodes already exist from prior inserts.
    public int countDistinctSubstrings(String s) {
        TrieNode localRoot = new TrieNode();
        int count = 0;
        for (int i = 0; i < s.length(); i++) {
            TrieNode node = localRoot;
            for (int j = i; j < s.length(); j++) {
                char ch = s.charAt(j);
                int charIdx = ch - 'a';
                if (node.children[charIdx] == null) {
                    node.children[charIdx] = new TrieNode(ch);
                    count++; // new substring found
                }
                node = node.children[charIdx];
            }
        }
        return count;
    }
}

public class _18_TriesImpl {
    static int failures = 0;

    static void check(boolean condition, String msg) {
        if (condition) System.out.println("PASS — " + msg);
        else { System.out.println("FAIL — " + msg); failures++; }
    }

    public static void main(String[] args) {

        // ── Tests 1-8: insert / search / startsWith ──────────────────────────
        MyTrie t = new MyTrie();
        t.insert("apple"); t.insert("app"); t.insert("application"); t.insert("apt");
        t.insert("banana"); t.insert("band"); t.insert("bandana");

        check(t.search("apple"),         "1  search existing word");
        check(t.search("app"),           "2  search word that is prefix of another");
        check(!t.search("appl"),         "3  search partial word not inserted");
        check(!t.search(""),             "4  search empty string (not inserted)");
        check(t.startsWith("app"),       "5  startsWith common prefix");
        check(t.startsWith("ban"),       "6  startsWith prefix with multiple completions");
        check(!t.startsWith("xyz"),      "7  startsWith no match");
        check(t.startsWith("apple"),     "8  startsWith exact inserted word → true");

        // ── Tests 9-15: delete ───────────────────────────────────────────────
        t.delete("app");
        check(!t.search("app"),          "9  search deleted word → false");
        check(t.search("apple"),         "10 sibling word unaffected after deleting prefix-word");
        check(t.startsWith("app"),       "11 startsWith still works after deleting prefix-word");

        t.delete("bandana");
        check(!t.search("bandana"),      "12 search deleted leaf word → false");
        check(t.search("band"),          "13 prefix-word unaffected after deleting longer sibling");

        t.delete("xyz");                 // delete non-existent — must not throw or corrupt
        check(!t.search("xyz"),          "14 search after deleting non-existent word");
        check(t.search("band"),          "15 trie intact after deleting non-existent word");

        // ── Tests 16-20: countWordsWithPrefix ────────────────────────────────
        // Trie now has: apple, application, apt, banana, band  (5 words)
        check(t.countWordsWithPrefix("app") == 2,   "16 countWordsWithPrefix 'app' → 2");
        check(t.countWordsWithPrefix("ban") == 2,   "17 countWordsWithPrefix 'ban' → 2");
        check(t.countWordsWithPrefix("apple") == 1, "18 countWordsWithPrefix full word → 1");
        check(t.countWordsWithPrefix("xyz") == 0,   "19 countWordsWithPrefix no match → 0");
        check(t.countWordsWithPrefix("") == 5,       "20 countWordsWithPrefix empty prefix → all words");

        // ── Tests 21-22: countWords ──────────────────────────────────────────
        check(t.countWords() == 5,             "21 countWords → 5");
        check(new MyTrie().countWords() == 0,  "22 countWords empty trie → 0");

        // ── Tests 23-25: autocomplete ────────────────────────────────────────
        List<String> ac = t.autocomplete("app");
        check(ac.size() == 2 &&
              ac.containsAll(Arrays.asList("apple", "application")),
              "23 autocomplete 'app' → [apple, application]");

        List<String> acAll = t.autocomplete("");
        check(acAll.size() == 5,  "24 autocomplete empty prefix → all 5 words");

        List<String> acNone = t.autocomplete("xyz");
        check(acNone.isEmpty(),   "25 autocomplete no match → empty list");

        // ── Tests 26-29: longestWordPrefixOf ─────────────────────────────────
        MyTrie lp = new MyTrie();
        lp.insert("ap"); lp.insert("app"); lp.insert("apple");
        check(lp.longestWordPrefixOf("applesauce").equals("apple"), "26 longestWordPrefixOf → apple");
        check(lp.longestWordPrefixOf("ap").equals("ap"),            "27 longestWordPrefixOf exact match → ap");
        check(lp.longestWordPrefixOf("b").equals(""),               "28 longestWordPrefixOf no match → empty");
        check(lp.longestWordPrefixOf("a").equals(""),               "29 longestWordPrefixOf partial, no terminal → empty");

        // ── Tests 30-33: wordBreak ───────────────────────────────────────────
        MyTrie wb = new MyTrie();
        wb.insert("leet"); wb.insert("code"); wb.insert("apple"); wb.insert("pen");
        check(wb.wordBreak("leetcode"),   "30 wordBreak valid two-word segmentation");
        check(!wb.wordBreak("leetcodd"),  "31 wordBreak invalid (suffix not in trie)");
        check(wb.wordBreak("applepen"),   "32 wordBreak another two-word segmentation");
        check(!wb.wordBreak("applepe"),   "33 wordBreak partial last word not in trie");

        // ── Tests 34-36: countDistinctSubstrings ─────────────────────────────
        check(new MyTrie().countDistinctSubstrings("abab") == 7, "34 countDistinctSubstrings 'abab' → 7");
        check(new MyTrie().countDistinctSubstrings("abc") == 6,  "35 countDistinctSubstrings 'abc' → 6");
        // Bug regression: existing trie words must not affect the count
        MyTrie ds = new MyTrie();
        ds.insert("ab");  // adds nodes for 'a','b' to root — would corrupt count without local root
        check(ds.countDistinctSubstrings("abc") == 6, "36 countDistinctSubstrings unaffected by existing trie words");

        // ── Tests 37-39: delete root-null regression ──────────────────────────
        // BUG: root = delete(root, w, 0) sets root=null when trie empties → NPE.
        // FIX: root is a permanent sentinel; don't assign the return value.
        MyTrie solo = new MyTrie();
        solo.insert("solo");
        solo.delete("solo");
        check(!solo.search("solo"),  "37 delete only word → search false (no NPE)");
        check(!solo.startsWith("s"), "38 delete only word → startsWith false (no NPE)");
        solo.insert("new");
        check(solo.search("new"),    "39 insert into previously-emptied trie works");

        // ── Tests 40-43: BinaryTrie ───────────────────────────────────────────
        BinaryTrie bt = new BinaryTrie();
        for (int n : new int[]{3, 10, 5, 25, 2, 8}) bt.insert(n);
        check(bt.maxXor(5) == 28, "40 BinaryTrie maxXor(5) → 28  (5 XOR 25)");
        check(bt.minXor(5) == 0,  "41 BinaryTrie minXor(5) → 0   (5 XOR 5, self in trie)");
        check(bt.maxXor(2) == 27, "42 BinaryTrie maxXor(2) → 27  (2 XOR 25)");
        check(bt.minXor(7) == 2,  "43 BinaryTrie minXor(7) → 2   (7 XOR 5)");

        System.out.println();
        System.out.println(failures == 0 ? "All tests PASSED" : failures + " test(s) FAILED");
    }
}

/**
 * Output:
 * -------
 * PASS — 1  search existing word
 * PASS — 2  search word that is prefix of another
 * PASS — 3  search partial word not inserted
 * PASS — 4  search empty string (not inserted)
 * PASS — 5  startsWith common prefix
 * PASS — 6  startsWith prefix with multiple completions
 * PASS — 7  startsWith no match
 * PASS — 8  startsWith exact inserted word → true
 * PASS — 9  search deleted word → false
 * PASS — 10 sibling word unaffected after deleting prefix-word
 * PASS — 11 startsWith still works after deleting prefix-word
 * PASS — 12 search deleted leaf word → false
 * PASS — 13 prefix-word unaffected after deleting longer sibling
 * PASS — 14 search after deleting non-existent word
 * PASS — 15 trie intact after deleting non-existent word
 * PASS — 16 countWordsWithPrefix 'app' → 2
 * PASS — 17 countWordsWithPrefix 'ban' → 2
 * PASS — 18 countWordsWithPrefix full word → 1
 * PASS — 19 countWordsWithPrefix no match → 0
 * PASS — 20 countWordsWithPrefix empty prefix → all words
 * PASS — 21 countWords → 5
 * PASS — 22 countWords empty trie → 0
 * PASS — 23 autocomplete 'app' → [apple, application]
 * PASS — 24 autocomplete empty prefix → all 5 words
 * PASS — 25 autocomplete no match → empty list
 * PASS — 26 longestWordPrefixOf → apple
 * PASS — 27 longestWordPrefixOf exact match → ap
 * PASS — 28 longestWordPrefixOf no match → empty
 * PASS — 29 longestWordPrefixOf partial, no terminal → empty
 * PASS — 30 wordBreak valid two-word segmentation
 * PASS — 31 wordBreak invalid (suffix not in trie)
 * PASS — 32 wordBreak another two-word segmentation
 * PASS — 33 wordBreak partial last word not in trie
 * PASS — 34 countDistinctSubstrings 'abab' → 7
 * PASS — 35 countDistinctSubstrings 'abc' → 6
 * PASS — 36 countDistinctSubstrings unaffected by existing trie words
 * PASS — 37 delete only word → search false (no NPE)
 * PASS — 38 delete only word → startsWith false (no NPE)
 * PASS — 39 insert into previously-emptied trie works
 * PASS — 40 BinaryTrie maxXor(5) → 28  (5 XOR 25)
 * PASS — 41 BinaryTrie minXor(5) → 0   (5 XOR 5, self in trie)
 * PASS — 42 BinaryTrie maxXor(2) → 27  (2 XOR 25)
 * PASS — 43 BinaryTrie minXor(7) → 2   (7 XOR 5)
 * 
 * All tests PASSED
 */