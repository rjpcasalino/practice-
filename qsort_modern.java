import java.util.Comparator;
import java.util.concurrent.ThreadLocalRandom;

public class QuicksortModern {

    public static <T> void sort(T[] v, int left, int right, Comparator<T> cmp) {
        if (left >= right) return;

        // Pick random pivot securely
        int pivotIdx = ThreadLocalRandom.current().nextInt(left, right + 1);
        swap(v, left, pivotIdx);

        int last = left;
        for (int i = left + 1; i <= right; i++) {
            if (cmp.compare(v[i], v[left]) < 0) {
                swap(v, ++last, i);
            }
        }
        swap(v, left, last);

        sort(v, left, last - 1, cmp);
        sort(v, last + 1, right, cmp);
    }

    private static <T> void swap(T[] v, int i, int j) {
        T temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }

    public static void main(String[] args) {
        String[] sarr = {"zeta", "Acirc", "AElig", "Aacute"};

        // Use standard method reference String::compareTo instead of custom Scmp class
        QuicksortModern.sort(sarr, 0, sarr.length - 1, String::compareTo);

        for (String s : sarr) {
            System.out.println(s);
        }
    }
}
