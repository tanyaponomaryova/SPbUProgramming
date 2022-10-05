#include <stdio.h>

int main()
{   
    printf("This program counts number of zero elements in array. \n");
    int numberOfElements = 0;
    int counterOfZeros = 0;
    printf("How many elements will you enter into array? ");
    int scanned = scanf("%d", &numberOfElements);
    while (scanned == 0 || numberOfElements <= 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a correct number, try again: ");
        scanned = scanf("%d", &numberOfElements);
    }
    printf("Enter array: ");
    for (int i = 0; i < numberOfElements; i++)
    {
        int element = 1;
        scanf("%d", &element);
        if (element == 0)
        {
            counterOfZeros++;
        }
    }
    printf("Number of zero elements: %d", counterOfZeros);
}