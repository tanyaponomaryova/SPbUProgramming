#include <stdio.h>
 int main()
 {
    int counterOfSums[28] = {0};
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
    for (int i = 0; i < 28; i++)
    {
        answer += counterOfSums[i] * counterOfSums[i];
    }
    printf("Amount of lucky tickets is %d.", answer);
 }