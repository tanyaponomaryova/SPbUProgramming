#include <stdio.h>
#include <stdlib.h>
int main()
{   
    printf("This program finds partial quotient of the input numbers.\n");
    int divident = 0;
    int divisor = 0;
    int answer = 0;
    printf("Enter divident (integer): ");
    int scanned = scanf("%d", &divident);
    while (scanned == 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a number, try again: ");
        scanned = scanf("%d", &divident);
    }
    printf("Enter divisor (integer): ");
    scanned = scanf("%d", &divisor);
    while (scanned == 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a number, try again: ");
        scanned = scanf("%d", &divisor);
    }
    int moduleOfDivident = abs(divident);
    int moduleOfDivisor = abs(divisor);
    if (divisor == 0)
        printf("Result of division by zero is undefined.");
    else 
    {
        while ((moduleOfDivident - answer * moduleOfDivisor >= moduleOfDivisor) || (divident < 0 && moduleOfDivident > answer * moduleOfDivisor))
        {
            answer++;
        }
        if ((divident < 0) ^ (divisor < 0))
        {
            answer = -answer;
        }
        printf("Result of finding partial quotient of division: %d", answer);
    }
    return 0;
}
