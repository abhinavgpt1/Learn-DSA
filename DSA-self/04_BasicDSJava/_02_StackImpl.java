// Methods as per java.util.Stack
// ------------------------------
// push(T obj)      -> T obj 
// pop()            -> T obj  
// peek()           -> T obj
// isEmpty()        -> boolean
// size()           -> int
// clear()          -> void    

// Other functions from its Parent class (Vector)
// ----------------------------------------------
// search(T obj)    -> int (1-based position from top, -1 if not found)
// contains(T obj)  -> boolean
// get(index)       -> T obj

import java.util.EmptyStackException;

class MyStack<T> extends MyArrayList<T> {
    public T push(T obj) {
        add(obj);
        return obj;
    }

    public T pop() throws EmptyStackException {
        if (isEmpty())
            throw new EmptyStackException();
        T lastPushedElementPopped = removeLast();
        return lastPushedElementPopped;
    }

    public T peek() throws EmptyStackException {
        if (isEmpty())
            throw new EmptyStackException();
        return getLast();
    }
    // isEmpty, size, clear, get, contains are already there in MyArrayList

    // Returns 1-based position from top of stack, -1 if not found
    // Top element is at position 1, second from top is at position 2, etc.
    public int search(T obj) {
        int index = lastIndexOf(obj); // find from top
        if (index == -1)
            return -1;
        return size() - index; // convert to 1-based position from top
    }
}

public class _02_StackImpl {
    public static void main(String[] args) {
        System.out.println("=== Test 1: Basic push operations ===");
        MyStack<Integer> stack = new MyStack<>();
        stack.push(10);
        stack.push(20);
        stack.push(30);
        System.out.println("Size: " + stack.size() + ", isEmpty: " + stack.isEmpty()); // 3, false
        System.out.println();

        System.out.println("=== Test 2: peek (non-destructive) ===");
        System.out.println("Top: " + stack.peek() + ", size unchanged: " + stack.size()); // 30, 3
        System.out.println();

        System.out.println("=== Test 3: pop (destructive) ===");
        System.out.println("pop: " + stack.pop() + ", pop: " + stack.pop()); // 30, 20
        System.out.println("Size: " + stack.size() + ", top: " + stack.peek()); // 1, 10
        System.out.println();

        System.out.println("=== Test 4: search (1-based from top) ===");
        stack.push(40);
        stack.push(50);
        stack.push(60);
        // Stack: [10, 40, 50, 60] top=60
        System.out.println("search(60): " + stack.search(60)); // 1 (top)
        System.out.println("search(50): " + stack.search(50)); // 2
        System.out.println("search(40): " + stack.search(40)); // 3
        System.out.println("search(10): " + stack.search(10)); // 4 (bottom)
        System.out.println("search(999): " + stack.search(999)); // -1
        System.out.println();

        System.out.println("=== Test 5: Contains ===");
        System.out.println("contains(50): " + stack.contains(50) + ", contains(100): " + stack.contains(100)); // true, false
        System.out.println();

        System.out.println("=== Test 6: push return value ===");
        Integer pushed = stack.push(70);
        System.out.println("push(70) returned: " + pushed + ", top: " + stack.peek()); // 70, 70
        System.out.println();

        System.out.println("=== Test 7: Clear ===");
        stack.clear();
        System.out.println("isEmpty: " + stack.isEmpty() + ", size: " + stack.size()); // true, 0
        System.out.println();

        System.out.println("=== Test 8: Exception on empty stack ===");
        try {
            stack.pop();
        } catch (EmptyStackException e) {
            System.out.println("✓ pop() threw EmptyStackException");
        }
        try {
            stack.peek();
        } catch (EmptyStackException e) {
            System.out.println("✓ peek() threw EmptyStackException");
        }
        System.out.println();

        System.out.println("=== Test 9: Duplicates and search ===");
        stack.push(100);
        stack.push(200);
        stack.push(100);
        stack.push(300);
        stack.push(100);
        // Stack: [100, 200, 100, 300, 100] top=100
        System.out.println("search(100): " + stack.search(100)); // 1 (finds topmost)
        System.out.println("search(300): " + stack.search(300)); // 2
        System.out.println("search(200): " + stack.search(200)); // 4
        System.out.println();

        System.out.println("=== Test 10: LIFO verification ===");
        stack.clear();
        for (int i = 1; i <= 5; i++) stack.push(i);
        System.out.print("Pop order: ");
        while (!stack.isEmpty()) {
            System.out.print(stack.pop());
            if (!stack.isEmpty()) System.out.print(",");
        }
        System.out.println(); // 5,4,3,2,1
        System.out.println();

        System.out.println("=== Test 11: Stack growth (15 elements) ===");
        for (int i = 1; i <= 15; i++) stack.push(i * 10);
        System.out.println("Size: " + stack.size()); // 15
        System.out.println("Top: " + stack.peek() + ", bottom: " + stack.get(0)); // 150, 10
        System.out.println();

        System.out.println("=== Test 12: Null handling ===");
        MyStack<String> strStack = new MyStack<>();
        strStack.push("first");
        strStack.push(null);
        strStack.push("third");
        System.out.println("Size: " + strStack.size()); // 3
        System.out.println("Contains null: " + strStack.contains(null)); // true
        System.out.println("search(null): " + strStack.search(null)); // 2
        System.out.println("pop: " + strStack.pop()); // third
        System.out.println("pop: " + strStack.pop()); // null
        System.out.println("pop: " + strStack.pop()); // first
        System.out.println();

        System.out.println("=== Test 13: Mixed push/pop operations ===");
        MyStack<Integer> calcStack = new MyStack<>();
        calcStack.push(5);
        calcStack.push(10);
        System.out.println("Top: " + calcStack.peek()); // 10
        calcStack.pop();
        calcStack.push(15);
        calcStack.push(20);
        System.out.println("Top: " + calcStack.peek()); // 20
        calcStack.pop();
        calcStack.pop();
        System.out.println("Top: " + calcStack.peek()); // 5
        System.out.println("Size: " + calcStack.size()); // 1
        System.out.println();

        System.out.println("=== All Tests Completed Successfully! ===");
    }
}