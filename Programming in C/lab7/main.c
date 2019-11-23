#include <stdio.h>
#include <math.h>

// Task 1
// create enum of months
enum months { JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER };

// Task 2
// Create struct for line
struct line {
    int x1, y1, x2, y2;
};

// Task 3
// Create bit field for ADSL modem in union with an int
union uni {
    struct {
        unsigned int DSL : 1;
        unsigned int PPP : 1;
        unsigned int Link : 1;
    } ADSL;
    unsigned short int state;
};
int main()
{
    
    // Task 1
    // Print enum value matching JULY
    printf("Task 1:\n%d\n\n", JULY);
    
    // Task 2
    // Initialize line and print length
    struct line l = { 0, 0, 3, 4 };
    float length = sqrt((l.x1 - l.x2) * (l.x1 - l.x2) + (l.y1 - l.y2) * (l.y1 - l.y2));
    printf("Task 2:\n%f\n\n", length);
    
    // Task 3
    // input hex and print ADSL states using unions to transfer bit values
    union uni a;
    scanf("%x", &a.state);
    printf("Task 3:\nDSL: %d\nPPP: %d\nLink: %d\n\n", a.ADSL.DSL, a.ADSL.PPP, a.ADSL.Link);
    
    return 0;
}
