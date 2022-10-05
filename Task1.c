#include <stdio.h>
float f(float x)
{
    float xSquared = x * x;
    return (xSquared + 1) * (xSquared + x) + 1;
}
int main()
{
    printf("Enter x to calculate value of x^4 + x^3 + x^2 + x + 1: ");
    float x = 0;
    int scanned = scanf("%f", &x);
    while (scanned == 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a number, try again: ");
        scanned = scanf("%f", &x);
    }
    printf("x^4 + x^3 + x^2 + x + 1 = %g", f(x));
    return 0;
}
