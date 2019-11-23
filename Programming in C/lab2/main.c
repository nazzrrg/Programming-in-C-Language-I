#include <stdio.h>
#include <math.h>

void z1(double a)
{
    if (floor(a) == 2 || a == 0 || a*a == 2.5) {
        printf("Error: unacceptable values for function z1\n");
    }
    else {
        double result = (5 - 2 * a * a) / ((1 + a + a * a) / (2 * a + a * a) - (1 - a + a * a) / (2 * a - a * a) + 2);
        
        printf("z1 = %lf\n", result);
    }
}

void z2(double a)
{
    double result = (4.00 - a * a) / 2;
    
    printf("z2 = %lf\n", result);
}

int main()
{
    double input;
    scanf("%lf", &input);
    
    z1(input);
    z2(input);
    
    return 0;
}
