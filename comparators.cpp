#include<bits/stdc++.h>
using namespace std;

//comparator class, inshort, Functor
class customComparatorClassGreat {
public:
    bool operator()(int a, int b){
        return a > b;
    }
};

class customComparatorClassLess {

public:
    bool operator()(int a, int b){
        return a < b;
    }
};

class customComparatorClassPair_LessSecond_GreatFirst_Value {
    
public:
    static string lesson;

    //if a's 2nd value < b's 2nd value - we don't to swap places - therefore return false here
    //return true to swap
    //in priority queue 'a' is element with level lower than 'b'
    //    x       -> level 0
    //  a   x     -> level 1
    // b x x x    -> level 2
    bool operator()(pair<int, int> a, pair<int, int> b){
        if(a.second != b.second)
            return a.second > b.second; // w.r.t. pQueue, we will swap as we want pair with lower 2nd value on top
        else
            return a.first < b.first; // w.r.t. pQueue, we will swap as we want pair with higher 1st value on top
    }
};
string customComparatorClassPair_LessSecond_GreatFirst_Value :: lesson = "greater<> in sort will sort in desc. and greater<> in priority queue will form min heap, so choose comparator decisions wisely";

//comparator functions
bool customComparatorFunctionLess(int a, int b) {
    return a < b;
}

bool customComparatorFunctionGreat(int a, int b) {
    return a > b;
}
int main(){
    cout<<"Min heap: ";
    priority_queue<int, vector<int>, customComparatorClassGreat> minheap;
    minheap.push(90);
    minheap.push(10);
    minheap.push(20);
    minheap.push(40);
    while(!minheap.empty()){
        cout<<minheap.top()<<" ";
        minheap.pop();
    }
    cout<<endl;
    
    cout<<"Max heap: ";
    priority_queue<int, vector<int>, customComparatorClassLess> maxheap; //maxHeap
    maxheap.push(90);
    maxheap.push(10);
    maxheap.push(20);
    maxheap.push(40);
    while(!maxheap.empty()){
        cout<<maxheap.top()<<" ";
        maxheap.pop();
    }
    cout<<endl;

    cout<<"Vector sort (Desc.): ";
    vector<int> vect;
    vect.push_back(10);
    vect.push_back(30);
    vect.push_back(40);
    vect.push_back(20);

    // sort(vect.begin(), vect.end(), customComparatorFunctionLess);//sort in ascending order
    // sort(vect.begin(), vect.end(), customComparatorFunctionGreat);//sort in descending order
    // sort(vect.begin(), vect.end(), customComparatorClassLess());//sort in ascending order
    sort(vect.begin(), vect.end(), customComparatorClassGreat());//sort in descending order
    
    for(int x: vect)
        cout<<x<<" ";
    cout<<endl<<endl;

    cout<<"************  Lesson: greater<int> is a functor (comparator class) and greater<int>() creates an instance of it - similar to comparator function  **********."<<endl<<endl;

    cout<<"Default bahavior of pair in priority queue: ";
    priority_queue<pair<int, int>> defmaxheappairs;
    defmaxheappairs.push({90, 3});
    defmaxheappairs.push({90, 4});
    defmaxheappairs.push({10, 5});
    defmaxheappairs.push({30, 5});
    defmaxheappairs.push({20, 1});
    defmaxheappairs.push({40, 8});

    //output: sorted by greatest of first and if equal then sorted by greatest of second value in pair
    while(!defmaxheappairs.empty()){
        cout<<"{"<<defmaxheappairs.top().first << ":"<<defmaxheappairs.top().second<<"}, ";
        defmaxheappairs.pop();
    }
    cout<<endl;

    cout<<"Default behavior of pair in priority queue with greater<int, int>: ";
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> defminheappairs;
    defminheappairs.push({90, 3});
    defminheappairs.push({90, 4});
    defminheappairs.push({10, 5});
    defminheappairs.push({10, 1});
    defminheappairs.push({30, 5});
    defminheappairs.push({20, 1});
    defminheappairs.push({40, 8});

    //output: sorted by least of first and if equal then sorted by least of second value in pair
    while(!defminheappairs.empty()){
        cout<<"{"<<defminheappairs.top().first << ":"<<defminheappairs.top().second<<"}, ";
        defminheappairs.pop();
    }
    
    cout<<endl<<endl;

    cout<<"Q- WAP to sort pair of values in ascending order of pair's second value. If they are same sort by Desc. value of first value in pair."<<endl;
    cout<<"Ans: Custom sort in prioity queue"<<": ";
    priority_queue<pair<int, int>, vector<pair<int, int>>, customComparatorClassPair_LessSecond_GreatFirst_Value> minheappairs;
    
    minheappairs.push({90, 3});
    minheappairs.push({90, 4});
    minheappairs.push({10, 5});
    minheappairs.push({60, 5});
    minheappairs.push({20, 1});
    minheappairs.push({40, 8});

    //output: 20:1, 90:3, 90: 4, 60:5, 10:5, 40:8
    while(!minheappairs.empty()){
        cout<<"{"<<minheappairs.top().first << ":"<<minheappairs.top().second<<"}, ";
        minheappairs.pop();
    }
    cout<<endl<<endl;

    cout<<"**********  Lesson: "<<customComparatorClassPair_LessSecond_GreatFirst_Value().lesson<<"  **********"<<endl<<endl;

    cout<<"Same Custom Comparator on sort: ";
    vector<pair<int, int>> vecPairs;
    vecPairs.push_back({90, 3});
    vecPairs.push_back({90, 4});
    vecPairs.push_back({10, 5});
    vecPairs.push_back({60, 5});
    vecPairs.push_back({20, 1});
    vecPairs.push_back({40, 8});

    sort(vecPairs.begin(), vecPairs.end(), customComparatorClassPair_LessSecond_GreatFirst_Value());

    //output: sorted by greatest of second value and least of first value - the opposite of what comparator states
    // {40:8}, {10:5}, {60:5}, {90:4}, {90:3}, {20:1}
    for(pair<int, int> x: vecPairs){
        cout<<"{"<<x.first << ":"<<x.second<<"}, ";
    }
    cout<<endl<<endl;
    cout<<"**********  Lesson: < and > in comparators work as asc. and desc. order for sort  **********"<<endl<<endl;
}