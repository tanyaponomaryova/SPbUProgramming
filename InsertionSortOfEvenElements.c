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

void insertionSortOfEvenElements(int array[], int length)
{
    for (int i = 1; i < length; i++)
    {
        if (array[i] % 2 == 0)
        {
            int temp = array[i];
            int index = i;
            for (int j = i - 1; j >= 0 && (temp < array[j] || array[j] % 2 != 0); j--)
            {
                if (array[j] % 2 == 0)
                {
                    array[index] = array[j];
                    index = j;
                }
            }
            array[index] = temp;
        }
    }
}

int main()
{
    printf("Enter size of array (natural number) to sort even elements: ");
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
    insertionSortOfEvenElements(array, length);
    printArray(array, length);
}