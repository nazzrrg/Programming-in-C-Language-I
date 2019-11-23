#include <stdio.h>

int main()
{
    
    // Task 1
    int a;
    scanf("%x", &a);
    
    // Task 2
    printf("Task 2: %o\n\n", a);
    
    // Task 3
    printf("Task 3: %x\n%x\n\n", a, a << 4);
    
    // Task 4
    printf("Task 4: %x\n%x\n\n", a, ~a);
    
    // Task 5
    int b;
    scanf("%x", b);
    printf("%x\n\n", a & b);
    
    return 0;
}