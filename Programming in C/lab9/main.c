#include <stdio.h>
#include <stdlib.h>

int main() {
    // Task 2
    // Calculate monthly pay
    int minutes, package, extra;
    scanf("%d%d%d", &minutes, &package, &extra);
    printf("Task 2:\n");
    if (minutes > 499){
        printf("%d\n\n", package + extra * (minutes - 499));
    } else
    {
        printf("%d\n\n", package);
    }

    // Task 3
    // Read digit print as char
    printf("Task 3:\n");
    int d;
    char* c = malloc(sizeof(char));
    scanf("%d", &d);
    sprintf(c, "%d", d);
    printf("%s\n\n", c);
    return 0;
}