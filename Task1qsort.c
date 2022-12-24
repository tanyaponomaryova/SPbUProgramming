#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int isArraySorted(int array[], int length)
{
    for (int i = 1; i < length; i++)
    {
        if (array[i - 1] > array[i])
        {
            return 0;
        }
    }
    return 1;
}

void swap(int *firstElement, int *secondElement)
{
    int temp = *firstElement;
    *firstElement = *secondElement;
    *secondElement = temp;
}

void printArray(int array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void insertionSort(int array[], int start, int end)
{
    for (int i = start + 1; i <= end; i++)
    {
        int currentIndex = i;
        while (currentIndex > start && array[currentIndex] < array[currentIndex - 1])
        {
            swap(&array[currentIndex], &array[currentIndex - 1]);
            currentIndex--;
        }
    }
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
    if (end - start + 1 < 10)
    {
        insertionSort(array, start, end);
        return;
    }
    int partitionIndex = partition(array, start, end);
    quickSort(array, start, partitionIndex - 1);
    quickSort(array, partitionIndex + 1, end);
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
    int *array = calloc(length, sizeof(int));
    if (NULL == array)
    {
        printf("Error allocating memory for array");
        return -1;
    }
    srand(time(NULL));
    for (int i = 0; i < length; i++)
    {
        array[i] = rand() % 100;
    }
    printf("Randomly generated array: ");
    printArray(array, length);
    quickSort(array, 0, length - 1);
    if (isArraySorted(array, length))
    {
        printf("Sorted array: ");
        printArray(array, length);
    } else
    {
        printf("Sorting error somewhere :0");
    }
    free(array);
    return 0;
}