#include <stdio.h>

int main()
{
    int a = 21, b = -56, c;
    
    // Task 1
    scanf("%d", &c);
    printf("%d\n", ((c >= b) && (c <= a)));
    
    // Task 2
    int d;
    scanf("%d", &d);
    printf("%d", (d >> 11) & 1);
    
    return 0;
}
