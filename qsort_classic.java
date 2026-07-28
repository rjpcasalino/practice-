import java.util.Random;

public class Quicksort {
    private static final Random rgen = new Random();

    // Quicksort.rand: return random integer in range [left, right]
    static int rand(int left, int right) {
        return left + rgen.nextInt(right - left + 1); // FIXED: Safe range generation
    }

    // Quicksort.swap: swap v[i] and v[j]
    static void swap(Object[] v, int i, int j) {
        Object temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }

    // Quicksort.sort: quicksort v[left]..v[right]
    static void sort(Object[] v, int left, int right, Cmp cmp) {
        int i, last;

        if (left >= right) // FIXED: was 'left <= right'
            return;

        swap(v, left, rand(left, right)); // move pivot element
        last = left;
        for (i = left + 1; i <= right; i++) { // partition
            if (cmp.cmp(v[i], v[left]) < 0) {
                swap(v, ++last, i);
            }
        }
        swap(v, left, last);
        sort(v, left, last - 1, cmp);
        sort(v, last + 1, right, cmp);
    }

    public static void main(String[] args) {
        String[] sarr = {"zeta", "Acirc", "AElig", "Aacute"};

        System.out.print("Before: ");
        for (String s : sarr) System.out.print(s + " ");
        System.out.println();

        Quicksort.sort(sarr, 0, sarr.length - 1, new Scmp());

        System.out.print("After:  ");
        for (String s : sarr) System.out.print(s + " ");
        System.out.println();
    }
}

interface Cmp {
    int cmp(Object x, Object y);
}

// Icmp: Integer comparison
class Icmp implements Cmp {
    public int cmp(Object o1, Object o2) {
        int i1 = ((Integer) o1).intValue();
        int i2 = ((Integer) o2).intValue();
        if (i1 < i2)
            return -1;
        else if (i1 == i2)
            return 0;
        else
            return 1; // FIXED: was 'return i;'
    }
}

// Scmp: String comparison
class Scmp implements Cmp {
    public int cmp(Object o1, Object o2) {
        String s1 = (String) o1;
        String s2 = (String) o2;
        return s1.compareTo(s2);
    }
}
