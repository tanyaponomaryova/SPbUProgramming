#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray (int array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void partition(int array[], int length)
{
    int left = 0;
    int right = length - 1;
    int pivot = array[0];
    while (left < right)
    {
        if (array[left] < pivot)
            left++;
        else if (array[right] >= pivot)
            right--;
        else
        {
            int temp = array[left];
            array[left] = array[right];
            array[right] = temp;
            left++;
            right--;
        }
    }
}

int main()
{
    printf("Enter size of array (natural number): ");
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

    srand(time(NULL));

    for (int i = 0; i < length; i++)
    {
        array[i] = rand() % 1000;
    }

    printf("Randomly generated array: ");
    printArray(array, length);
    partition(array, length);
    printf("Transformed array: ");
    printArray(array, length);

    free(array);
    array = NULL;

    return 0;
}