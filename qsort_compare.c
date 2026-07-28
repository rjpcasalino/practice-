#include <stdio.h>
#include <stdlib.h>

static inline void swap(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* 
 * Partition: places the pivot (last element) in its correct sorted position,
 * with smaller elements to the left and larger elements to the right.
 */
int partition(int arr[], int low, int high) 
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

/* ============================================================================
 * 1. Recursive Quicksort
 * Concise and natural because the compiler manages the call stack for us.
 * ============================================================================ */
void quicksort_recursive(int arr[], int low, int high) 
{
    if (low < high) {
        int p = partition(arr, low, high);
        quicksort_recursive(arr, low, p - 1);
        quicksort_recursive(arr, p + 1, high);
    }
}

/* ============================================================================
 * 2. Iterative Quicksort
 * Explicitly replaces function call recursion with an array-backed stack.
 * ============================================================================ */
void quicksort_iterative(int arr[], int n) 
{
    if (n <= 1) return;

    /* 
     * STACK SIZE OPTIMIZATION:
     * By always pushing the LARGER partition first and processing the smaller 
     * partition immediately, the maximum depth of this stack is strictly bounded 
     * to O(log2(N)).
     * 
     * Storing 128 integers (64 range pairs) is mathematically enough to sort 
     * up to 2^64 elements on the stack without allocating heap memory!
     */
    int stack[128];
    int top = -1;

    /* Push initial bounds [low, high] onto the stack */
    stack[++top] = 0;
    stack[++top] = n - 1;

    while (top >= 0) {
        /* Pop high and low indices */
        int high = stack[top--];
        int low  = stack[top--];

        if (low >= high) continue;

        int p = partition(arr, low, high);

        int left_low   = low;
        int left_high  = p - 1;
        int right_low  = p + 1;
        int right_high = high;

        int left_len  = (left_high >= left_low)  ? (left_high - left_low + 1) : 0;
        int right_len = (right_high >= right_low) ? (right_high - right_low + 1) : 0;

        /* Push larger sub-array first so the smaller one gets processed next */
        if (left_len > right_len) {
            if (left_len > 1) {
                stack[++top] = left_low;
                stack[++top] = left_high;
            }
            if (right_len > 1) {
                stack[++top] = right_low;
                stack[++top] = right_high;
            }
        } else {
            if (right_len > 1) {
                stack[++top] = right_low;
                stack[++top] = right_high;
            }
            if (left_len > 1) {
                stack[++top] = left_low;
                stack[++top] = left_high;
            }
        }
    }
}

/* Helper to print array contents */
void print_array(const char *label, int arr[], int n) 
{
    printf("%-20s: ", label);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) 
{
    int data1[] = { 42, 7, -5, 12, 1024, 0, 7, -99, 3 };
    int data2[] = { 42, 7, -5, 12, 1024, 0, 7, -99, 3 };
    int n = sizeof(data1) / sizeof(data1[0]);

    printf("==========================================\n");
    printf("     Recursive vs. Iterative Quicksort    \n");
    printf("==========================================\n\n");

    print_array("Original Array", data1, n);

    /* Test Recursive */
    quicksort_recursive(data1, 0, n - 1);
    print_array("Recursive Sort", data1, n);

    /* Test Iterative */
    quicksort_iterative(data2, n);
    print_array("Iterative Sort", data2, n);

    return 0;
}
