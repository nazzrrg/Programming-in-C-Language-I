#include <stdio.h>

int main()
{
    // Task 1
    // initialize array in {} print it
    printf("Task 1:\n");
    int mass[7] = { 23, 5678, 2, 564, 365, 77, 443 };
    for (int i = 0; i < 7; i++) {
        printf("%d ", mass[i]);
    }
    printf("\n\nTask 2:\n");
    
    // Task 2
    // matrix multiplication
    int a[2][2] = { 1, 1, 1, 4 }, b[2][2] = { 1, 0, 0, 1 }, c[2][2] = { 0, 0, 0, 0 };
    
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                c[k][i] += a[k][j] * b[j][i];
            }
        }
    }
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
