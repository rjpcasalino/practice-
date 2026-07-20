#include <stdio.h>
#include <stdlib.h> /* Required for qsort() */
#include <stddef.h> /* Required for size_t */

/*
 * compare_ints: The comparator function for qsort.
 * 
 * qsort is generic, meaning it can sort an array of ANYTHING (ints, floats, 
 * massive custom structs). Because of this, it passes pointers as generic 
 * `const void *`. It is our job to cast them back to their actual type before 
 * comparing them.
 */
int compare_ints(const void *a, const void *b) 
{
        /* 
         * Step 1: Cast the generic void pointers back to integer pointers, 
         * then dereference them (the `*` at the front) to get the actual values.
         */
        int val_a = *(const int *)a;
        int val_b = *(const int *)b;

        /* 
         * Step 2: Return the result.
         * qsort expects:
         *  - A negative number if 'a' should go before 'b'
         *  - Zero if they are identical
         *  - A positive number if 'a' should go after 'b'
         * 
         * Pro-Tip: Older C tutorials often tell you to just `return val_a - val_b;`. 
         * DO NOT DO THIS. If val_a is a large positive number and val_b is a large 
         * negative number, subtracting them will cause an integer overflow, wrapping 
         * around to a negative number and completely breaking your sort. 
         * Using explicit `<` and `>` is the modern, safe way.
         */
        if (val_a < val_b) return -1;
        if (val_a > val_b) return 1;
        return 0;
}

/*
 * helper function just to print the array so we can see the results.
 */
void print_array(int arr[], size_t n) 
{
        for (size_t i = 0; i < n; i++) {
                printf("%d ", arr[i]);
        }
        printf("\n");
}

int main() 
{
        /* An intentionally messy, unsorted array with duplicates and negative numbers */
        int data[] = { 42, 7, -5, 12, 1024, 0, 7, -99, 3 };
        
        /* Modern way to calculate the number of elements in a statically declared array */
        size_t n = sizeof(data) / sizeof(data[0]);

        printf("Before sorting:\n");
        print_array(data, n);

        /* 
         * Call the standard library's qsort.
         * Arg 1: Pointer to the start of the array
         * Arg 2: Number of elements in the array
         * Arg 3: Size (in bytes) of a single element
         * Arg 4: Pointer to our custom comparator function
         */
        qsort(
            data, 
            n, 
            sizeof(int), 
            compare_ints
        );

        printf("\nAfter sorting:\n");
        print_array(data, n);

        return 0;
}
