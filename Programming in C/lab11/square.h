#ifndef LAB11_SQUARE_H
#define LAB11_SQUARE_H


struct square{
    int aX, aY, bX, bY;
};

struct square newSquare();

int squarePerimeter(const struct square s);

int squareArea(const struct square s);

#endif //LAB11_SQUARE_H