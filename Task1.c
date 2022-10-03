#include <stdio.h>
int recursiveFibonacci(int n)
{
    if (n <= 1)
        return n;
    return recursiveFibonacci(n-1) + recursiveFibonacci(n-2);
}

int iterativeFibonacci(int n)
{
    if (n <= 1)
        return n;
    int prevNumber = 1;
    int prevprevNumber = 0; 
    int currentNumber = 0;
    for (int i = 2; i <= n; i++)
    {
        currentNumber = prevNumber + prevprevNumber;
        prevprevNumber = prevNumber;
        prevNumber = currentNumber;
    }
    return currentNumber;
}

int main()
{
    
    while (1)
    {
        printf("Enter positive number n to get n-th Fibonacci number (enter 0 to exit): ");
        int n = 0;
        int scanned = scanf("%d", &n);
        while (scanned == 0 || n < 0)
        {
            scanf("%*[^\n]");
            printf("You didn't enter a positive number, try again (enter 0 to exit): ");
            scanned = scanf("%d", &n);
        }
        if (n == 0)
            break;
        printf("n Fibonacci number calculated recursively: %d\n", recursiveFibonacci(n));
        printf("n Fibonacci number calculated iteratively: %d\n", iterativeFibonacci(n));  
    }
    return 0;
}