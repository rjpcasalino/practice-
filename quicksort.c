#include <stdlib.h> // Required for rand()
#include <stddef.h> // Required for size_t

/* 
 * swap: helper function to swap two elements in an array.
 * We make this `static inline` because it's tiny and called repeatedly inside a 
 * tight loop. This tells the compiler to just paste the code directly where it's 
 * used, saving us the overhead of an actual function call every time.
 */
static inline void swap(int v[], size_t i, size_t j) 
{
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
}

/* 
 * quicksort: sorts v[0]...v[n-1] into increasing order.
 * Modernization: Using `size_t` for the array size `n` instead of `int`. 
 * This is standard practice in modern C to prevent integer overflow on massive arrays.
 */
void quicksort(int v[], size_t n)
{
        /* 
         * Base case: an array of 0 or 1 elements is already sorted by definition. 
         * Nothing to do here, so bail out immediately.
         */
        if (n <= 1) 
                return;

        /* 
         * Pick a random pivot and move it out of the way to the start of the array (v[0]).
         * Why random? If we always picked the first or last element, already-sorted arrays 
         * would cause Quicksort to degrade to horrible O(n^2) performance. Randomizing 
         * protects us from that edge case.
         */
        swap(v, 0, rand() % n); 

        /* 
         * 'last' tracks the boundary index. Everything from index 1 up to 'last' 
         * will be strictly less than our pivot.
         */
        size_t last = 0;

        /* 
         * The Partitioning Loop:
         * We declare `i` right inside the loop (C99 style) instead of at the top of the function.
         * We start at 1 because v[0] is currently holding our pivot hostage.
         */
        for (size_t i = 1; i < n; i++) {
                /* 
                 * If we find an element smaller than our pivot (which is sitting at v[0]),
                 * we need to move it into our "smaller than" section. We expand that section 
                 * by pre-incrementing 'last' (++last) and swapping the element there.
                 */
                if (v[i] < v[0]) {
                        swap(v, ++last, i);
                }
        }

        /* 
         * Partitioning is done. All elements less than the pivot are grouped on the left.
         * Now we swap the pivot out of its temporary hiding spot at v[0] and put it 
         * into its rightful, final sorted position (v[last]).
         */
        swap(v, 0, last);

        /* 
         * Recursion time. We sort the two smaller sub-arrays we just created.
         * 
         * 1. Sort the left half: all elements strictly before our pivot.
         * The size of this half is exactly 'last'.
         */
        quicksort(v, last);

        /* 
         * 2. Sort the right half: all elements strictly after our pivot.
         * We use pointer arithmetic (v + last + 1) to pass a pointer to the start 
         * of the right sub-array. We adjust the size `n` by subtracting what we've 
         * already sorted (the left half and the pivot itself).
         * 
         * (Also, added the missing semicolon that was absent in the original code!)
         */
        quicksort(v + last + 1, n - last - 1); 
}
