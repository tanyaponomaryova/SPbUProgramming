#include <stdio.h>
float exponentiationInLinearTime(float number, int power)
{
    float answer = 1;
    for (int i = 0; i < power; i++)
    {
        answer = answer * number;
    }
    return answer;
}
float exponentiationInLogN(float number, int power)
{
    if (power == 0)
        return 1;
    float halfPower = exponentiationInLogN(number, power / 2);
    if (power % 2 == 0)
        return halfPower * halfPower;
    return halfPower * halfPower * number;
}
int main()
{
    printf("Enter base number: ");
    float enteredNumber = 0;
    int scanned = scanf("%f", &enteredNumber);
    while (scanned == 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a number, try again: ");
        scanned = scanf("%f", &enteredNumber);
    }

    printf("Enter exponent (natural number or 0): ");
    int powerOfNumber = 0;
    scanned = scanf("%d", &powerOfNumber);
    while (scanned == 0 || powerOfNumber < 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a natural number, try again: ");
        scanned = scanf("%d", &powerOfNumber);
    }
    printf("%g to the power of %d (in linear time): %g\n", enteredNumber, powerOfNumber, exponentiationInLinearTime(enteredNumber, powerOfNumber));
    printf("%g to the power of %d (in log n): %g\n", enteredNumber, powerOfNumber, exponentiationInLogN(enteredNumber, powerOfNumber));
    return 0;
}