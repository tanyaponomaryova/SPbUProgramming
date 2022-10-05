#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter n to get prime numbers <= n: ");
    int n = 0;
    int scanned = scanf("%d", &n);
    while (scanned == 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a number, try again: ");
        scanned = scanf("%d", &n);
    }
    if (n > 1)
    {
        int* sieve = calloc(n + 1, sizeof(int));
        if (sieve == NULL)
        {
            printf("Error allocating memory for sieve");
            return -1;
        }
        sieve[0] = 1;
        sieve[1] = 1;
        for (int i = 2; i * i <= n; i++)
        {
            if (sieve[i] == 0)
            {
                for (int j = i * i; j <= n; j += i)
                {
                    sieve[j] = 1;
                }
            }
        }
        printf("Prime numbers <= n: ");
        for (int k = 0; k <= n; k++)
        {
            if (sieve[k] == 0)
            {
                printf("%d ", k);
            }
        }
        free(sieve);
    }
    else
    {
        printf("There is no prime numbers <= %d.", n);
    }
    return 0;
}