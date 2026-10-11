// Methods as per java.util.Queue
// ------------------------------
// add(T obj)       -> boolean
// remove()         -> T obj    (throws NoSuchElementException if empty)
// peek()           -> T obj    (returns null if empty)
// isEmpty()        -> boolean
// size()           -> int
// clear()          -> void
// contains(T obj)  -> boolean

// PTR: functions like getFirst, getLast exist in LinkedList but not in Queue (interface)

// Other functions from Queue
// --------------------------
// offer(T obj)     -> boolean
// poll()           -> T obj    (returns null if empty)
// element()        -> T obj    (throws NoSuchElementException if empty)

import java.util.NoSuchElementException;

class MyQueue<T> extends MyArrayList<T> {
    public boolean add(T obj) { // redundant defintion
        return super.add(obj);
    }

    public T remove() throws NoSuchElementException {
        if (isEmpty())
            throw new NoSuchElementException();
        T fifoPoppedElement = removeFirst();
        return fifoPoppedElement;
    }

    public T peek() { // use element for throwing exception when queue is empty
        if (isEmpty())
            return null;
        return getFirst();
    }
    // isEmpty, size, clear, contains are already there in MyArrayList

    public boolean offer(T obj) {
        return add(obj);
    }

    public T poll() { // use remove for throwing exception when queue is empty
        if (isEmpty())
            return null;
        T fifoPoppedElement = removeFirst();
        return fifoPoppedElement;
    }

    public T element() throws NoSuchElementException {
        if (isEmpty())
            throw new NoSuchElementException();
        return getFirst();
    }

}

public class _03_QueueImpl {
    public static void main(String[] args) {
        System.out.println("=== Test 1: Basic add/offer operations ===");
        MyQueue<Integer> queue = new MyQueue<>();
        queue.add(10);
        queue.add(20);
        queue.offer(30);
        System.out.println("Size: " + queue.size() + ", isEmpty: " + queue.isEmpty()); // 3, false
        System.out.println();

        System.out.println("=== Test 2: peek vs element (non-destructive) ===");
        System.out.println("peek: " + queue.peek() + ", element: " + queue.element()); // 10, 10
        System.out.println("Size unchanged: " + queue.size()); // 3
        System.out.println();

        System.out.println("=== Test 3: poll vs remove (destructive) ===");
        System.out.println("poll: " + queue.poll() + ", remove: " + queue.remove()); // 10, 20
        System.out.println("Size: " + queue.size() + ", front: " + queue.peek()); // 1, 30
        System.out.println();

        System.out.println("=== Test 4: FIFO verification ===");
        queue.clear();
        for (int i = 1; i <= 5; i++) queue.add(i * 100);
        System.out.print("Poll order: ");
        while (!queue.isEmpty()) {
            System.out.print(queue.poll());
            if (!queue.isEmpty()) System.out.print(",");
        }
        System.out.println(); // 100,200,300,400,500
        System.out.println();

        System.out.println("=== Test 5: Contains ===");
        queue.offer(50);
        queue.offer(60);
        queue.offer(70);
        System.out.println("Contains 60: " + queue.contains(60) + ", contains 999: " + queue.contains(999)); // true, false
        System.out.println();

        System.out.println("=== Test 6: Return values ===");
        System.out.println("add: " + queue.add(80) + ", offer: " + queue.offer(90)); // true, true
        System.out.println("Size: " + queue.size()); // 5
        System.out.println();

        System.out.println("=== Test 7: Safe methods on empty queue (return null) ===");
        queue.clear();
        System.out.println("peek: " + queue.peek() + ", poll: " + queue.poll()); // null, null
        System.out.println();

        System.out.println("=== Test 8: Unsafe methods on empty queue (throw exception) ===");
        try {
            queue.element();
        } catch (NoSuchElementException e) {
            System.out.println("✓ element() threw NoSuchElementException");
        }
        try {
            queue.remove();
        } catch (NoSuchElementException e) {
            System.out.println("✓ remove() threw NoSuchElementException");
        }
        System.out.println();

        System.out.println("=== Test 9: Mixed operations ===");
        queue.add(1);
        queue.add(2);
        System.out.println("Front: " + queue.peek()); // 1
        queue.add(3);
        System.out.println("poll: " + queue.poll() + ", front now: " + queue.peek()); // 1, 2
        queue.add(4);
        System.out.println("poll: " + queue.poll() + ", poll: " + queue.poll()); // 2, 3
        System.out.println("Front: " + queue.peek()); // 4
        System.out.println();

        System.out.println("=== Test 10: Queue growth (15 elements) ===");
        queue.clear();
        for (int i = 1; i <= 15; i++) queue.offer(i * 10);
        System.out.println("Size: " + queue.size()); // 15
        System.out.println("Front: " + queue.peek() + ", back: " + queue.get(queue.size() - 1)); // 10, 150
        System.out.println();

        System.out.println("=== Test 11: Process all elements ===");
        queue.clear();
        queue.add(5);
        queue.add(15);
        queue.add(25);
        queue.add(35);
        System.out.print("Order: ");
        int size = queue.size();
        for (int i = 0; i < size; i++) {
            System.out.print(queue.poll());
            if (i < size - 1) System.out.print(" -> ");
        }
        System.out.println();
        System.out.println("Empty after processing: " + queue.isEmpty()); // true
        System.out.println();

        System.out.println("=== Test 12: Null handling ===");
        MyQueue<String> strQueue = new MyQueue<>();
        strQueue.add("apple");
        strQueue.add(null);
        strQueue.add("banana");
        System.out.println("Size: " + strQueue.size()); // 3
        System.out.println("Contains null: " + strQueue.contains(null)); // true
        System.out.println("poll: " + strQueue.poll()); // apple
        System.out.println("poll: " + strQueue.poll()); // null
        System.out.println("poll: " + strQueue.poll()); // banana
        System.out.println();

        System.out.println("=== All Tests Completed Successfully! ===");
    }
}
