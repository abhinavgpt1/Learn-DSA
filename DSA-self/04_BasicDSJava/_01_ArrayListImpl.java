// Methods as per java.util.ArrayList
// ----------------------------------
// add(T obj)           -> boolean
// add(index, T obj)    -> void
// addFirst(T obj)      -> void
// addLast(T obj)       -> void
// remove(T obj)        -> boolean
// remove(index)        -> T obj
// removeFirst()        -> T obj
// removeLast()         -> T obj
// contains(T obj)      -> boolean
// get(index)           -> T obj
// getFirst()           -> T obj
// getLast()            -> T obj
// set(index, T obj)    -> T obj
// size()               -> int
// clear()              -> void
// isEmpty()            -> boolean
// indexOf(T obj)       -> int
// lastIndexOf(T obj)   -> int
// sort(Comparator c)   -> void

import java.util.Arrays;
import java.util.Comparator;

class MyArrayList<T> {
    private T[] arr;
    private int size;
    private final int DEFAULT_CAPACITY = 10; // same as java.util.ArrayList

    @SuppressWarnings("unchecked")
    MyArrayList() {
        arr = (T[]) new Object[DEFAULT_CAPACITY];
        size = 0;
        /**
         * QQ - Why unchecked exception can be thrown here?
         * Ans - The real problem is that later, if code treats this array as a
         * String[], Integer[], etc., a ClassCastException can occur. e.g.
         * MyArrayList<String> list = new MyArrayList<>();
         * String[] s = list.arr; → may throw ClassCastException
         */
    }

    // private methods
    private void checkIfAdditionPossibleElseGrow() {
        if (size == arr.length)
            grow2x();
    }

    @SuppressWarnings("unchecked")
    private void grow2x() {
        T[] tmpArr = (T[]) new Object[2 * arr.length];
        System.arraycopy(arr, 0, tmpArr, 0, arr.length);
        arr = tmpArr;
    }

    private void checkIndexWithinBounds(int index) throws IndexOutOfBoundsException {
        if (index < 0 || index >= size)
            throw new IndexOutOfBoundsException("Index is out of bound, index:" + index + ", sizeArr: " + size);
    }

    // public methods
    public boolean add(T n) {
        checkIfAdditionPossibleElseGrow();
        arr[size++] = n;
        return true; // marks success
    }

    public void add(int index, T n) {
        if (index < 0 || index > size)
            throw new IndexOutOfBoundsException("Index is out of bound, index:" + index + ", sizeArr: " + size);
        checkIfAdditionPossibleElseGrow();
        for (int i = size - 1; i >= index; i--) {
            arr[i + 1] = arr[i];
        }
        arr[index] = n;
        size++;
    }

    public void addFirst(T n) {
        add(0, n);
    }

    public void addLast(T n) {
        add(size, n);
    }

    // remove & return the Object.
    public T remove(int index) {
        // isEmpty() check becomes redundant since size = 0 and any index value will fail checkIndexWithinBounds
        checkIndexWithinBounds(index);
        T removedElement = arr[index];
        
        // a creative way to do this => System.arraycopy(arr, index + 1, arr, index, size - index - 1);
        for (int i = index; i <= size - 2; i++) {
            arr[i] = arr[i + 1];
        }

        // clear arr[size-1] and decrease size
        arr[--size] = null; // default value for int on heap memory
        return removedElement;
    }

    // remove by Object and not index.
    public boolean remove(T obj) {
        // null is a valid element in ArrayList, so search for it
        int index = indexOf(obj);
        if (index == -1)
            return false;
        remove(index);
        return true;
    }

    public int indexOf(T obj) {
        for (int i = 0; i < size; i++) {
            if ((obj == null && arr[i] == null) || (obj != null && obj.equals(arr[i])))
                return i;
        }
        return -1;
    }

    public T removeFirst() {
        return remove(0);
    }

    public T removeLast() {
        return remove(size - 1);
    }

    public boolean contains(T obj) {
        return indexOf(obj) >= 0; // !=-1 also works, but what if it changes in future let's say Integer.MIN_VALUE
    }

    public T get(int index) {
        checkIndexWithinBounds(index);
        return arr[index];
    }

    public T getFirst() {
        return get(0);
    }

    public T getLast() {
        return get(size - 1);
    }

    public T set(int index, T obj) {
        checkIndexWithinBounds(index);
        T prevValue = arr[index];
        arr[index] = obj;
        return prevValue;
    }

    public int size() {
        return size;
    }

    public void clear() {
        size = 0;
        Arrays.fill(arr, null); // length remains same
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public int lastIndexOf(T obj) {
        for (int i = size - 1; i >= 0; i--) {
            if ((obj == null && arr[i] == null) || (obj != null && obj.equals(arr[i])))
                return i;
        }
        return -1;

        // Creative way to implement both indexOf and lastIndexOf in a single function
        // is to use Iterator and reverse iterator (doesn't exist by default in Java)
    }

    public void sort(Comparator<T> c) {
        // IMP: Only sort elements up to size, not the entire array
        Arrays.sort(arr, 0, size, c);
        
        // Solution for int[]
        // arr = Arrays.stream(arr).limit(size).sorted(c).mapToInt(Integer::intValue).toArray();
    }
}

public class _01_ArrayListImpl {
    public static void main(String[] args) {
        System.out.println("=== Test 1: Basic operations ===");
        MyArrayList<Integer> list = new MyArrayList<>();
        list.add(10);
        list.add(20);
        list.add(30);
        list.addFirst(5);
        list.addLast(40);
        System.out.println("Size: " + list.size()); // 5
        System.out.println("First: " + list.getFirst() + ", Last: " + list.getLast()); // 5, 40
        System.out.println("Element at index 2: " + list.get(2)); // 20
        System.out.println();
        
        System.out.println("=== Test 2: Add at index ===");
        list.add(2, 15);
        System.out.println("After add(2, 15): " + list.get(2)); // 15
        System.out.println("Size: " + list.size()); // 6
        System.out.println();
        
        System.out.println("=== Test 3: Contains and indexOf ===");
        System.out.println("Contains 20: " + list.contains(20)); // true
        System.out.println("Contains 100: " + list.contains(100)); // false
        System.out.println("Index of 20: " + list.indexOf(20)); // 3
        System.out.println();
        
        System.out.println("=== Test 4: Set and remove ===");
        Integer oldValue = list.set(1, 12);
        System.out.println("Old value: " + oldValue); // 10
        Integer removed = list.remove(2);
        System.out.println("Removed: " + removed); // 15
        System.out.println("Size: " + list.size()); // 5
        System.out.println();
        
        System.out.println("=== Test 5: Remove by object ===");
        boolean removed2 = list.remove(Integer.valueOf(20));
        System.out.println("Removed 20: " + removed2); // true
        System.out.println("Contains 20: " + list.contains(20)); // false
        System.out.println();
        
        System.out.println("=== Test 6: RemoveFirst and removeLast ===");
        Integer first = list.removeFirst();
        Integer last = list.removeLast();
        System.out.println("Removed first: " + first + ", last: " + last); // 5, 40
        System.out.println("Size: " + list.size()); // 2
        System.out.println();
        
        System.out.println("=== Test 7: lastIndexOf with duplicates ===");
        list.clear();
        list.add(10);
        list.add(20);
        list.add(10);
        list.add(30);
        System.out.println("First index of 10: " + list.indexOf(10)); // 0
        System.out.println("Last index of 10: " + list.lastIndexOf(10)); // 2
        System.out.println();
        
        System.out.println("=== Test 8: Sort ===");
        list.sort(Comparator.naturalOrder());
        System.out.print("Ascending: ");
        for (int i = 0; i < list.size(); i++) {
            System.out.print(list.get(i) + " ");
        }
        System.out.println(); // 10 10 20 30
        list.sort(Comparator.reverseOrder());
        System.out.print("Descending: ");
        for (int i = 0; i < list.size(); i++) {
            System.out.print(list.get(i) + " ");
        }
        System.out.println(); // 30 20 10 10
        System.out.println();
        
        System.out.println("=== Test 9: isEmpty and clear ===");
        System.out.println("Is empty: " + list.isEmpty()); // false
        list.clear();
        System.out.println("After clear - isEmpty: " + list.isEmpty() + ", size: " + list.size()); // true, 0
        System.out.println();
        
        System.out.println("=== Test 10: Array growth (15 elements) ===");
        for (int i = 1; i <= 15; i++) {
            list.add(i * 10);
        }
        System.out.println("Size: " + list.size()); // 15
        System.out.println("First: " + list.getFirst() + ", Last: " + list.getLast()); // 10, 150
        System.out.println();
        
        System.out.println("=== Test 11: Exception handling ===");
        try {
            list.get(100);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("✓ IndexOutOfBoundsException for get(100)");
        }
        try {
            list.add(100, 999);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("✓ IndexOutOfBoundsException for add(100, 999)");
        }
        System.out.println();
        
        System.out.println("=== Test 12: Null handling ===");
        MyArrayList<String> strList = new MyArrayList<>();
        strList.add("apple");
        strList.add(null);
        strList.add("banana");
        strList.add(null);
        System.out.println("Size: " + strList.size()); // 4
        System.out.println("Contains null: " + strList.contains(null)); // true
        System.out.println("First null at: " + strList.indexOf(null)); // 1
        System.out.println("Last null at: " + strList.lastIndexOf(null)); // 3
        strList.remove(null);
        System.out.println("After remove - first null at: " + strList.indexOf(null)); // 2
        System.out.println();
        
        System.out.println("=== Test 13: Edge cases ===");
        MyArrayList<Integer> emptyList = new MyArrayList<>();
        System.out.println("Empty list - contains 10: " + emptyList.contains(10)); // false
        System.out.println("Empty list - remove 10: " + emptyList.remove(Integer.valueOf(10))); // false
        try {
            emptyList.getFirst();
        } catch (IndexOutOfBoundsException e) {
            System.out.println("✓ IndexOutOfBoundsException for getFirst() on empty list");
        }
        System.out.println();
        
        System.out.println("=== All Tests Completed Successfully! ===");
    }
}
