#include <stdio.h>
#define arrayOfContersSize 28
int main()
{
    int counterOfSums[arrayOfContersSize] = {0};
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; k < 10; k++)
                {
                    counterOfSums[i + j + k]++;
                }
        }
    }
    int answer = 0;
    for (int i = 0; i < arrayOfContersSize; i++)
    {
        answer += counterOfSums[i] * counterOfSums[i];
    }
    printf("Amount of lucky tickets is %d.", answer);
    return 0;
}