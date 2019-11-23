#include <stdio.h>
#include <mm_malloc.h>
#include <math.h>

int* arrayInitialization(int filler, int* returnedLength) {
    *(returnedLength) = floor(log10(filler)) + 1;

    int* arr = (int*)malloc(sizeof(int) * *returnedLength);

    for (int i = *returnedLength - 1; i >= 0; i--)
    {
        arr[i] = filler % 10;
        filler /= 10;
    }

    return arr;
}

struct point {
    int x;
    int y;
};

double* pointArrayCreation(int n) {
    double *arr = (double *) malloc(sizeof(double) * n * (n - 1));
    return arr;
}

int main() {
    // Task 2
    printf("Task 2:\n");
    int n;
    scanf("%d", &n);

    struct point* pointArray = (struct point*)malloc(sizeof(struct point) * n);

    double* distanceArray = pointArrayCreation(n);

    free(distanceArray);
    free(pointArray);

    // Task 3
    printf("Task 3:\n");
    int input;
    scanf("%d", &input);

    int arrayLength;

    int* outputArray = arrayInitialization(input, &arrayLength);

    for (int i = 0; i < arrayLength; i++)
    {
        printf("%d ", outputArray[i]);
    }

    return 0;
}