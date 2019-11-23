#include <stdio.h>
#include "square.h"

int main() {
    struct square s = newSquare();

    printf("perimeter: %d\n", squarePerimeter(s));

    printf("area: %d\n", squareArea(s));

    return 0;
}