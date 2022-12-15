#include "qsort.h"

void swap(int* firstElement, int* secondElement)
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
