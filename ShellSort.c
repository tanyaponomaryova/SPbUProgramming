#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray (int array[], int length) //length
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void shellSort(int array[], int length) 
{
    int step = length / 2;
    while (step > 0)
    {
        for (int i = 0; i < length; i++)
        {
            int temp = array[i];
            int index = i;
            while ((index >= step) && ( array[index - step] > temp))
            {
                array[index] = array[index - step];
                index = index - step;
            }
            array[index] = temp;
        }
        step = step / 2;
    }
}
int main()
{
    printf("Enter size of array (natural number) to sort it by shell sort: ");
    int length = 0;
    int scanned = scanf("%d", &length);
    while (scanned == 0 || length <= 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a natural number, try again: ");
        scanned = scanf("%d", &length);
    }
    int* array = calloc(length, sizeof(int));
    if (NULL == array)
    {
        printf("Error allocating memory for array");
        return -1;
    }
    printf("Enter numbers to array: ");
    for (int i = 0; i < length; i++)
    {
        scanned = scanf("%d", &array[i]);
        while (scanned == 0)
        {
            scanf("%*[^\n]");
            printf("You didn't enter a natural number, try again: ");
            scanned = scanf("%d", &array[i]);
        }
    }
    printf("Entered array: ");
    printArray(array, length);
    printf("Sorted array: ");
    shellSort(array, length);
    printArray(array, length);
}