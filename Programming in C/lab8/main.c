#include <stdio.h>
#include <string.h>
#include <mm_malloc.h>

int main()
{
    unsigned int l1, l2;
    char *str1, *str2;

    scanf("%d", &l1);
    str1 = malloc(sizeof(char) * l1);
    scanf("%s", str1);

    scanf("%d", &l2);
    str2 = malloc(sizeof(char) * l2);
    scanf("%s", str2);

    // Task 1
    // Concat str1 and str2
    char* str3 = malloc(sizeof(char) * (l1 + l2));
    strcat(str3, str1);
    strcat(str3, str2);
    printf("Task 1:\n%s\n\n", str3);
    free(str3);

    // Task 3
    // Compare str1 to str2
    printf("Task 3:\n%d\n\n", strcmp(str1, str2));

    // Task 5
    // Copy str1 into str3
    str3 = malloc(sizeof(char) * l1);
    strcpy(str3, str1);
    printf("Task 5:\n%s\n\n", str3);
    free(str3);

    // Task 7
    // Print length of str1
    printf("Task 7:\n%d\n\n", strlen(str1));

    // Task 12
    // Print length of part of str1 which does not contain symbols from str2
    if (strpbrk(str1, str2) != NULL) {
        printf("Task 12:\n%d\n\n", strpbrk(str1, str2) - str1);
    } else {
        printf("Task 12:\n%d\n\n", strlen(str1));
    }

    free(str1);
    free(str2);
    return 0;
}