#include <stdio.h>
#include <mm_malloc.h>

int main()
{
    // Task 1
    // create array in stack
    // initialize by []
    // print referring by pointers
    printf("Task 1:\n");
    int n = 4;
    double* arr1 = alloca(n * sizeof(double));
    double* pointer = arr1;
    arr1[0] = 56.4;
    arr1[1] = 36.5;
    arr1[2] = 7.7;
    arr1[3] = 44.3;
    
    for (int i = 0; i < n; i++) {
        printf("%.1f ", *(pointer + i));
    }
    
    // Task 2
    // Create array in heap
    printf("\n\nTask 2:\n");
    double* arr2 = malloc(n * sizeof(double));
    arr2[0] = 56.4;
    arr2[1] = 36.5;
    arr2[2] = 7.7;
    arr2[3] = 44.3;
    for (int i = 0; i < n; i++) {
        printf("%.1f ", arr2[i]);
    }
    free(arr2);
    
    return 0;
}
