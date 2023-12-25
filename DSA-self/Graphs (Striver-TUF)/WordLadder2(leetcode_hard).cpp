/*
 * Word Ladder 2:
 * ----------------
 * A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
 * 
 * Every adjacent pair of words differs by a single letter.
 * Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
 * sk == endWord
 * Given two words, beginWord and endWord, and a dictionary wordList, return all the shortest transformation sequences from beginWord to endWord, or an empty list if no such sequence exists. Each sequence should be returned as a list of the words [beginWord, s1, s2, ..., sk].
 */

// ref - https://leetcode.com/problems/word-ladder-ii/
// This solution will be exponential in nature, but only traverses over the sequences which will be part of ans

class Solution {
    // O(N*M*logN)
    map<string, int> getSequenceCountMap(string beginWord, string endWord, set<string> wordSet) {
        // wordSet is a local variable
        queue<pair<string, int>> pending;
        map<string, int> seqCountMap; // keeps track of sequence count from startWord for every word in wordList (if reachable)
        pending.push({beginWord, 1});
        wordSet.erase(beginWord);

        while (!pending.empty()) { // O(N)
            string front = pending.front().first;
            int seqCount = pending.front().second;
            pending.pop();
            seqCountMap[front] = seqCount;

            for (int i = 0; i < front.length(); i++) { //O(M * 26 * logN)
                string word = front;
                for (char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch;
                    if (wordSet.count(word)) {
                        wordSet.erase(word);
                        pending.push({word, seqCount + 1});
                    }
                }
            }
        }
        return seqCountMap;
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        set<string> wordSet(wordList.begin(), wordList.end());
        if (!wordSet.count(endWord))
            return vector<vector<string>>();

        map<string, int> seqCountMap = getSequenceCountMap(beginWord, endWord, wordSet);

        if(!seqCountMap.count(endWord)) //endWord is unreachable
            return vector<vector<string>>();      
        
        vector<vector<string>> ans;
        // Below process can be done by DFS too
        // Making sequences from endWord i.e. backtracking
        // Checking 26M times over words where seqCountMap[word] = seqCount[front]-1
        queue<pair<string, vector<string>>> pending;
        pending.push({endWord, {endWord}});
        while(!pending.empty()){
            string front = pending.front().first;
            vector<string> seq = pending.front().second;
            pending.pop();
            int seqCountFront = seqCountMap[front];

            if(front == beginWord){
                reverse(seq.begin(), seq.end());
                ans.push_back(seq);
                continue;
            }

            for(int i=0; i<front.length(); i++){
                string word = front;
                for(char ch='a'; ch<='z'; ch++){
                    word[i] = ch;
                    if(seqCountMap.count(word) && seqCountMap[word] == seqCountFront - 1) {
                        seq.push_back(word);
                        pending.push({word, seq});
                        seq.pop_back();
                    }
                }
            }
        }
        return ans;
    }
};