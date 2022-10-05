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
    printf("Enter n to get prime numbers : ");
    int lengths = 0;
    int scanned = scanf("%d", &lengths);
    while (scanned == 0 || lengths <= 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a correct number, try again: ");
        scanned = scanf("%d", &lengths);
    }


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