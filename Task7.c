#include <stdio.h>
int isPrimeNumber(int x)
{
    for (int i = 2; i*i <= x; i++)
    {
        if (x % i == 0)
            return 0;
    }
    return 1;
}
int main()
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    if (n > 1)
    {
        for (int i = 2; i <= n; i++)
        {
            if (isPrimeNumber(i))
                printf("%d ", i);
        }
    }
    else
        printf("n must be > 1.");
}