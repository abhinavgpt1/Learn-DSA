/*
 * Word Ladder 1:
 * ----------------
 * Given two distinct words startWord and targetWord, and a list denoting wordList of unique words of equal lengths. Find the length of the shortest transformation sequence from startWord to targetWord.
 * Keep the following conditions in mind:
 * 
 * A word can only consist of lowercase characters.
 * Only one letter can be changed in each transformation.
 * Each transformed word must exist in the wordList including the targetWord.
 * startWord may or may not be part of the wordList
 * The second part of this problem can be found here.
 * 
 * Note: If no possible way to transform sequence from startWord to targetWord return 0
 */

 // Solution 1: Starting from startWord towards targetWord: T(N) = O(N * M * logN)
class Solution {
public:
    int wordLadderLength(string startWord, string targetWord, vector<string>& wordList) {
        //optimised BFS approach
        set<string> visited(wordList.begin(), wordList.end()); //Great way to initialize
        if(visited.count(targetWord) == 0) //same length strings is given in question
            return 0;
        
        visited.erase(startWord);
            
        queue<pair<string, int>> pending;
        pending.push({startWord, 1});
        
        // T(N) = O(N * M * logN)
        //unordered_set will have O(1) complexity -> T(N) = O(N * M)

        while(!pending.empty()){
            string word = pending.front().first;
            int level = pending.front().second;
            pending.pop();
            
            if(word == targetWord) //cleaner to put this check here than in for loop, but there will exist unneccesary strings in queue
                return level; // put this check in below for loop and return level + 1 for slightly better efficiency
            
            //M*26*logN
            for(int i=0; i<word.length(); i++)
            {
                char orgChar = word[i];
                for(char ch = 'a'; ch <= 'z'; ch++){
                    word[i] = ch;
                    
                    if(visited.count(word)){
                        pending.push({word, level + 1});
                        visited.erase(word);
                    }
                }
                word[i] = orgChar;
            }
        }
        return 0;
    }
};

// Solution 2: Starting from targetWord towards startWord: T(N) = O(N * M * logN)
class Solution {
public:
    // DP is wrong as it doesn't consider the words consumed before
    // TLE can't be improved on the method involving traversing whole wordSet with words removal and insertion again and again
    int wordLadderLength(string startWord, string targetWord, vector<string>& wordList) {
        set<string> wordSet;
        for(string word: wordList)
            wordSet.insert(word);
        if(!wordSet.count(targetWord)) //target not in wordList
            return 0;
            
        queue<string> pending;
        map<string, int> seqCountToTarget;
        pending.push(targetWord);
        seqCountToTarget[targetWord] = 1;
        
        while(!pending.empty()){ // *(N) due to visited check by seqCountToTarget
            string front = pending.front(); pending.pop();
            int seqCountFront = seqCountToTarget[front];
            
            for(int i=0; i<front.length(); i++){ // *(M)
                char charAtI = front[i];
                for(char ch='a'; ch<='z'; ch++){ // *(26)
                    front[i] = ch;
                    if(!seqCountToTarget.count(front) && wordSet.count(front)){// *2*(logN)
                        seqCountToTarget[front] = seqCountFront + 1;
                        pending.push(front);
                    }
                }
                front[i] = charAtI;
            }
        }
        // When startWord is in wordList
        if(wordSet.count(startWord))
            return seqCountToTarget[startWord]; //default 0 i.e. startWord is unreachable to target

        // When startWord is not in wordList
        int ans = INT_MAX;
        for(int i=0; i<startWord.length(); i++){ // *(M)
            char charAtI = startWord[i];
            for(char ch='a'; ch<='z'; ch++){ // *(26)
                startWord[i] = ch;
                // checking for minimum non-zero sequence count to targetWord
                if(wordSet.count(startWord) && seqCountToTarget.count(startWord)){ //default 0 will disrupt ans
                    ans = min(ans, seqCountToTarget[startWord]);
                }
            }
            startWord[i] = charAtI;
        }
        if(ans == INT_MAX) //startWord wasn't in list and is unreachable to targetWord
            return 0;
        return ans + 1; //counting the startWord in sequence
    }
};

// Solution 3: Cannot be improved to resolved TLE as this is an exponential soln.
// Usage of DP will make it worse as words omitted from wordSet isn't accounted in dp of any transformed startWord
class Solution {
    public:
        int findTransformation(string startWord, string targetWord, set<string> &wordSet, int countSeq) {
            if(startWord == targetWord)
                return countSeq; // count of sequence needs to be returned
            if(wordSet.empty())
                return INT_MAX;
            int minTransformationCount = INT_MAX;
            for(int i=0; i<startWord.length(); i++){
                char charAtI = startWord[i];
                // cout<<startWord<<":start:"<<endl;
                for(char ch = 'a'; ch<='z'; ch++){
                    startWord[i] = ch;
                    if(wordSet.count(startWord)){
                        // cout<<startWord<<endl;
                        wordSet.erase(startWord);
                        minTransformationCount = min(
                            findTransformation(startWord, targetWord, wordSet, countSeq + 1), 
                            minTransformationCount);
                        wordSet.insert(startWord);
                    }
                }
                startWord[i] = charAtI;
                // cout<<startWord<<":end:"<<endl;
            }
            return minTransformationCount;
        }
        int wordLadderLength(string startWord, string targetWord, vector<string>& wordList) {
            set<string> wordSet;
            for(string word: wordList)
                wordSet.insert(word);
            if(wordSet.count(targetWord) == 0)
                return 0;
            // cout<<startWord<<" <><><> "<<targetWord<<endl;
            int minTransformationCount = findTransformation(startWord, targetWord, wordSet, 1);
            if(minTransformationCount == INT_MAX)
                return 0;
            return minTransformationCount;
        }
    };