#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void swap(int *firstElement, int *secondElement)
{
    int temp = *firstElement;
    *firstElement = *secondElement;
    *secondElement = temp;
}

int partition(int array[], int start, int end)
{
    int pivot = array[start];
    int partitionIndex = end;
    for (int i = end; i > start; i--)
    {
        if (array[i] >= pivot)
        {
            swap(&array[i], &array[partitionIndex]);
            partitionIndex--;
        }
    }
    swap(&array[start], &array[partitionIndex]);
    return partitionIndex;
}

void quickSort(int array[], int start, int end)
{
    if (end <= start)
    {
        return;
    }
    int partitionIndex = partition(array, start, end);
    quickSort(array, start, partitionIndex - 1);
    quickSort(array, partitionIndex + 1, end);
}

int searchMostFrequentElement(int array[], int length)
{
    quickSort(array, 0, length - 1);
    int mostFrequentElement = array[0];
    int maxCounter = 1;
    int counter = 1;
    for (int i = 1; i < length; i++)
    {
        if (array[i] == array[i - 1])
        {
            counter++;
        } else
        {
            if (counter > maxCounter)
            {
                mostFrequentElement = array[i - 1];
                maxCounter = counter;
            }
            counter = 1;
        }
    }
    if (counter > maxCounter)
    {
        mostFrequentElement = array[length - 2];
    }
    return mostFrequentElement;
}

int main()
{
    printf("Enter size of array to be randomly generated (natural number): ");
    int length = 0;
    int scanned = scanf("%d", &length);
    while (scanned == 0 || length <= 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a natural number, try again: ");
        scanned = scanf("%d", &length);
    }

    int *array = calloc(length, sizeof(int));
    if (NULL == array)
    {
        printf("Error allocating memory for array");
        return -1;
    }
    srand(time(NULL));
    for (int i = 0; i < length; i++)
    {
        array[i] = rand() % 10;
    }

    printf("Generated array: ");
    printArray(array, length);
    printf("Most frequently occurring element in array: ");
    printf("%d\n", searchMostFrequentElement(array, length));

    free(array);
    return 0;
}