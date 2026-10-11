// Methods as per java.util.PriorityQueue
// --------------------------------------
// add(T obj)   -> boolean
// remove()     -> T                        (throws Exception if empty)
// size()       -> int
// isEmpty()    -> boolean
// clear()      -> void
// peek()       -> T                        (returns null if empty)

// Additional Methods
// ------------------
// offer(T obj) -> boolean
// poll()       -> T                        (returns null if empty)
// element()    -> T                        (throws Exception if empty)
// contains(T obj) -> boolean
// remove(T obj) -> boolean               ⚠ O(n): linear scan using equals(), then O(log n) sift — O(n) total, NOT O(log n)
// toArray() -> T[]
// iterator() -> Iterator<T>
// comparator() -> Comparator<T>

import java.util.Arrays;
import java.util.Comparator;
import java.util.NoSuchElementException;

class MyPriorityQueue<T> {
    private T[] queue;
    private Comparator<T> comparator;
    private final int INITIAL_CAPACITY = 11; // same as in java.util.PriorityQueue
    private int size;

    // private methods
    private void swap(int i, int j) {
        T tmp = queue[i];
        queue[i] = queue[j];
        queue[j] = tmp;
    }

    private void heapifyUp() {
        // Get parent for i -> (i-1)/2
        int index = size - 1;
        while(index > 0) {
            int parent = (index - 1)/2;

            if(comparator.compare(queue[parent], queue[index]) > 0) { // think in terms of min-heap aka natural order
                swap(parent, index);
                index = parent;
            } else {
                break;
            }
        }
    }
    
    private void heapifyDown() {
        // Get child for i -> 2i + 1
        // Get child for i -> 2i + 2

        // PTR: replacing with smallest child is important for min-heap
        //      7
        //     / \
        //    3   5
        //  If we replace 7 with 5, then 3 will be left out of order (in context of min-heap)
        int index = 0;
        while(index < size) {
            int child1 = 2 * index + 1;
            int child2 = 2 * index + 2;
            int smallest = index;
            
            if(child1 < size && comparator.compare(queue[smallest], queue[child1]) > 0) { // think in terms of min-heap aka natural order
                smallest = child1;
            } 
            if(child2 < size && comparator.compare(queue[smallest], queue[child2]) > 0) {
                smallest = child2;
            }
            
            if(smallest == index) {
                break;
            }
            swap(index, smallest);
            index = smallest;
        }
    }

    @SuppressWarnings("unchecked")
    MyPriorityQueue(Comparator<T> comparator) {
        this.queue = (T[]) new Object[INITIAL_CAPACITY];
        this.size = 0;
        this.comparator = comparator;

        // PTR: T[] arr = new T[10]; isn't possible due to type erasure. 
        // Generics are compile-time only; arrays need runtime types. 
        // Java won't let you create new T[] because T doesn't exist at runtime—it becomes Object.
    }

    // public methods
    public boolean add(T obj){
        if(size == queue.length) {
            queue = Arrays.copyOf(queue, queue.length * 2);
            // internally this happens
            // int[] tmpArr = new int[2 * arr.length];
            // System.arraycopy(arr, 0, tmpArr, 0, arr.length);
            // arr = tmpArr;
        }
        queue[size++] = obj;
        heapifyUp();
        return true;
    }
    
    public T remove(){
        if(isEmpty()) 
            throw new NoSuchElementException("PriorityQueue is empty");
        T removed = queue[0];
        queue[0] = queue[size - 1];
        queue[size - 1] = null;
        size--;
        heapifyDown();
        return removed;
    }
    public int size(){
        return size;
    }
    public boolean isEmpty(){
        return size == 0;
    }
    public void clear(){
        // comparator and capacity doesn't change
        Arrays.fill(queue, null);
        size = 0;
    }

    public T peek(){
        if(isEmpty())
            return null;
        return queue[0];
    }
}

public class _07_PriorityQueueImpl {
    public static void main(String[] args) {
        System.out.println("=== Test 1: Min-Heap (Natural Order) ===");
        MyPriorityQueue<Integer> minHeap = new MyPriorityQueue<>(Integer::compareTo);
        minHeap.add(5);
        minHeap.add(3);
        minHeap.add(7);
        minHeap.add(1);
        minHeap.add(9);
        minHeap.add(2);
        minHeap.add(8);
        
        System.out.println("Size: " + minHeap.size()); // 7
        System.out.println("Peek (should be 1): " + minHeap.peek()); // 1
        
        System.out.println("Elements in ascending order:");
        while(!minHeap.isEmpty()) {
            System.out.print(minHeap.remove() + " ");
        }
        System.out.println("\n");
        
        System.out.println("=== Test 2: Max-Heap (Reverse Order) ===");
        MyPriorityQueue<Integer> maxHeap = new MyPriorityQueue<>((a, b) -> b.compareTo(a));
        maxHeap.add(5);
        maxHeap.add(3);
        maxHeap.add(7);
        maxHeap.add(1);
        maxHeap.add(9);
        maxHeap.add(2);
        
        System.out.println("Peek (should be 9): " + maxHeap.peek()); // 9
        
        System.out.println("Elements in descending order:");
        while(!maxHeap.isEmpty()) {
            System.out.print(maxHeap.remove() + " ");
        }
        System.out.println("\n");
        
        System.out.println("=== Test 3: Edge Cases ===");
        MyPriorityQueue<Integer> pq = new MyPriorityQueue<>(Integer::compareTo);
        
        // Test empty queue
        System.out.println("Is empty: " + pq.isEmpty()); // true
        System.out.println("Peek on empty: " + pq.peek()); // null
        
        // Test single element
        pq.add(42);
        System.out.println("Size after adding one: " + pq.size()); // 1
        System.out.println("Remove single element: " + pq.remove()); // 42
        System.out.println("Is empty after removal: " + pq.isEmpty()); // true
        
        // Test clear
        pq.add(1);
        pq.add(2);
        pq.add(3);
        System.out.println("Size before clear: " + pq.size()); // 3
        pq.clear();
        System.out.println("Size after clear: " + pq.size()); // 0
        System.out.println();
        
        System.out.println("=== Test 4: Capacity Expansion ===");
        MyPriorityQueue<Integer> bigHeap = new MyPriorityQueue<>(Integer::compareTo);
        System.out.println("Adding 20 elements (initial capacity is 11)...");
        for(int i = 20; i > 0; i--) {
            bigHeap.add(i);
        }
        System.out.println("Size: " + bigHeap.size()); // 20
        System.out.println("First 5 removed: ");
        for(int i = 0; i < 5; i++) {
            System.out.print(bigHeap.remove() + " ");
        }
        System.out.println("\n");
        
        System.out.println("=== Test 5: Exception Handling ===");
        MyPriorityQueue<Integer> emptyPq = new MyPriorityQueue<>(Integer::compareTo);
        try {
            emptyPq.remove();
            System.out.println("ERROR: Should have thrown exception!");
        } catch (NoSuchElementException e) {
            System.out.println("✓ Correctly threw NoSuchElementException");
        }
        System.out.println();
        
        System.out.println("=== Test 6: String Priority Queue ===");
        MyPriorityQueue<String> stringHeap = new MyPriorityQueue<>(String::compareTo);
        stringHeap.add("banana");
        stringHeap.add("apple");
        stringHeap.add("cherry");
        stringHeap.add("date");
        stringHeap.add("avocado");
        
        System.out.println("Strings in alphabetical order:");
        while(!stringHeap.isEmpty()) {
            System.out.print(stringHeap.remove() + " ");
        }
        System.out.println("\n");
        
        System.out.println("=== Test 7: Duplicate Elements ===");
        MyPriorityQueue<Integer> dupHeap = new MyPriorityQueue<>(Integer::compareTo);
        dupHeap.add(5);
        dupHeap.add(3);
        dupHeap.add(5);
        dupHeap.add(3);
        dupHeap.add(5);
        
        System.out.println("Removing duplicates:");
        while(!dupHeap.isEmpty()) {
            System.out.print(dupHeap.remove() + " ");
        }
        System.out.println("\n");
        
        System.out.println("=== All Tests Completed Successfully! ===");
    }
}