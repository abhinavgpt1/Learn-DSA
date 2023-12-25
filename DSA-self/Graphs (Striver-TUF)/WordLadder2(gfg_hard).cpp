/*
 * Word Ladder 2:
 * ----------------
 * Given two distinct words startWord and targetWord, and a list denoting wordList of unique words of equal lengths. Find all shortest transformation sequence(s) from startWord to targetWord. You can return them in any order possible.
 * Keep the following conditions in mind:
 *
 * A word can only consist of lowercase characters.
 * Only one letter can be changed in each transformation.
 * Each transformed word must exist in the wordList including the targetWord.
 * startWord may or may not be part of the wordList.
 * Return an empty list if there is no such transformation sequence.
 */

// All solutions are exponential in nature. The pruning is what differentiates
// None works in Leetcode - https://leetcode.com/problems/word-ladder-ii/

// Solution 1: BFS with queue containing sequences
class Solution {
    // Soln. 2 took no benefit of level-wise execution
    // Benefit (S(n)+O(n)): erasing last words should happen at the end of the level execution
public:
    vector<vector<string>> findSequences(string beginWord, string endWord, vector<string>& wordList) {
        queue<vector<string>> pending;
        set<string> wordSet(wordList.begin(), wordList.end());
        vector<vector<string>> ans;
        bool isEndWordReached = false;
        
        // Logic
        pending.push({beginWord}); //new way here
        wordSet.erase(beginWord); // erasing so that it can't be appended again

        while (!pending.empty() && !isEndWordReached) {
            
            // level-wise execution
            int levelSize = pending.size();
            set<string> visited;
            for (int z = 1; z <= levelSize; z++) {
                vector<string> sequence = pending.front();
                pending.pop();
                string lastWord = sequence.back(); //new way here
                // erasing lastWord here may populate upcoming lastWords in sequences here which is redundant (as the length will exceed minimum sequence length)

                if (lastWord == endWord) {
                    ans.push_back(sequence);
                    isEndWordReached = true; // will ensure that the first level where endWord occurs is the last level of execution
                    continue;
                }

                for (int i = 0; i < lastWord.length(); i++) {
                    string word = lastWord;
                    for (char ch = 'a'; ch <= 'z'; ch++) {
                        word[i] = ch;
                        if (wordSet.count(word)) {
                            vector<string> seqExtended = sequence;
                            seqExtended.push_back(word);
                            
                            pending.push(seqExtended);
                            // not deleting this word as it can be consumed in other sequences of the queue
                            
                            visited.insert(word);// pushing in visited to remove it after level-wise execution completes
                        }
                    }
                }
            }
            // Now that new words are consumed (w.r.t. lastWord of all queued sequences of a level),
            // these should not be consumed again otherwise minimum length count of sequence will exceed
            // Deleting words in visited
            for(string word: visited){
                wordSet.erase(word);
            }
        }
        return ans;
    }
};

// Solution 2: Less efficient than above
class Solution
{
public:
    vector<vector<string>> findSequences(string beginWord, string endWord, vector<string> &wordList)
    {
        queue<vector<string>> pending;
        set<string> wordSet(wordList.begin(), wordList.end());
        pending.push(vector<string>(1, beginWord));

        vector<vector<string>> ans;
        bool isEndWordReached = false;
        while (!pending.empty() && !isEndWordReached)
        {

            // level-wise execution
            int levelSize = pending.size();
            for (int z = 1; z <= levelSize; z++)
            {
                vector<string> sequence = pending.front();
                pending.pop();
                string lastWord = sequence[sequence.size() - 1];
                wordSet.erase(lastWord); // erasing so that it doesn't get appended again - to maintain shortest seq

                if (lastWord == endWord)
                {
                    ans.push_back(sequence);
                    isEndWordReached = true; // will ensure that the first level where endWord occurs is the last level of execution
                    continue;
                }

                for (int i = 0; i < lastWord.length(); i++)
                {
                    string word = lastWord;
                    for (char ch = 'a'; ch <= 'z'; ch++)
                    {
                        word[i] = ch;
                        if (wordSet.find(word) != wordSet.end())
                        {
                            vector<string> seq2 = sequence;
                            seq2.push_back(word);
                            pending.push(seq2);
                            // not deleting this word as it can be consumed in other sequences of the queue
                        }
                    }
                }
            }
        }
        return ans;
    }
};

// Solution 3: DFS depth till min sequence length - just like generating subsets problem (exponential soln.)
class Solution
{
    vector<vector<string>> findSeq(string beginWord, string endWord, set<string> &wordSet, int remSeqCount)
    {
        if (remSeqCount == 0)
        {
            vector<vector<string>> seqList;
            if (beginWord == endWord)
                seqList.push_back(vector<string>(1, endWord));
            return seqList;
        }
        vector<vector<string>> ans;
        for (int i = 0; i < beginWord.length(); i++)
        {
            string word = beginWord;
            for (char ch = 'a'; ch <= 'z'; ch++)
            {
                word[i] = ch;
                if (wordSet.count(word))
                {
                    wordSet.erase(word);
                    vector<vector<string>> seqList = findSeq(word, endWord, wordSet, remSeqCount - 1);
                    for (auto &seq : seqList)
                    {
                        seq.insert(seq.begin(), beginWord);
                        ans.push_back(seq);
                    }
                    wordSet.insert(word);
                }
            }
        }
        return ans;
    }
    // wordSet is local variable
    int findMinimumTransformationSeqCount(string beginWord, string endWord, set<string> wordSet)
    {
        queue<pair<string, int>> pending;
        pending.push({beginWord, 1});
        wordSet.erase(beginWord);

        while (!pending.empty())
        {
            string front = pending.front().first;
            int seqCount = pending.front().second;
            pending.pop();

            if (front == endWord)
                return seqCount;

            for (int i = 0; i < front.length(); i++)
            {
                string word = front;
                for (char ch = 'a'; ch <= 'z'; ch++)
                {
                    word[i] = ch;
                    if (wordSet.count(word))
                    {
                        wordSet.erase(word);
                        pending.push({word, seqCount + 1});
                    }
                }
            }
        }
        return 0;
    }

public:
    vector<vector<string>> findSequences(string beginWord, string endWord, vector<string> &wordList)
    {
        set<string> wordSet;
        for (string word : wordList)
            wordSet.insert(word);
        if (!wordSet.count(endWord))
            return vector<vector<string>>();

        int shortestTransformationSeqCount = findMinimumTransformationSeqCount(beginWord, endWord, wordSet);
        if (shortestTransformationSeqCount == 0)
            return vector<vector<string>>();

        return findSeq(beginWord, endWord, wordSet, shortestTransformationSeqCount - 1); // beginWord is already in sequence
    }
};