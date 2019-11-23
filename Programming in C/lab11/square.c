#include "square.h"
#include <stdio.h>

struct square newSquare() {
    struct square s;

    printf("enter left lower point coordinates: \n");
    scanf("%d%d", &s.aX, &s.aY);

    printf("enter right upper point coordinates: \n");
    scanf("%d%d", &s.bX, &s.bY);

    return s;
}

int squarePerimeter(const struct square s) {
    return (s.bX - s.aX) * 2 + (s.bY - s.aY) * 2;
}

int squareArea(const struct square s) {
    return (s.bX - s.aX) * (s.bY - s.aY);
}