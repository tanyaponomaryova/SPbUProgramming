#include <stdio.h>

int main()
{   
    int counterOfElements = 0;
    int array[1000] = {0};
    int counterOfZeros = 0;
    printf("How many numbers will you enter? ");
    scanf("%d", &counterOfElements);
    printf("Enter numbers into array: ");
    for (int i = 0; i < 1000; i++)
        array[i] = 1;
    for (int i = 0; i < counterOfElements; i++)
        scanf("%d", &array[i]);
    for (int i = 0; i < counterOfElements; i++)
    {
        if (array[i] == 0)
            counterOfZeros++;
    }
    printf("Number of zero elements: %d", counterOfZeros);
}