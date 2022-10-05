#include <stdio.h>
int module(int x)
{
    if (x >= 0)
        return x;
    return -x; 
}
int main()
{   
    int a;
    int b;
    int answer = 0;
    printf("Enter a: ");
    scanf("%d", &a);
    printf("Enter b: ");
    scanf("%d", &b);
    int moduleOfa = module(a);
    int moduleOfb = module(b);
    if (b == 0)
        printf("Result of division by zero is undefined.");
    else if (a >= 0)
    {
        while (a >= module(b))
        {
            a -= module(b);
            answer++;
        }
    }
    else 
    {
        while (moduleOfa > moduleOfb*answer)
            answer++;
    }
    if (a * b >= 0)
        printf("a / b = %d", answer);
    else
        printf("a / b = %d", -answer);
}
