#include "qsort.h"

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int array[], int start, int end)
{
    int pivot = array[start];
    int rightIndex = end;
    int leftIndex = start + 1;
    while (rightIndex > leftIndex)
    {
        while (array[leftIndex] <= pivot)
        {
            leftIndex++;
        }
        while (array[rightIndex] > pivot)
        {
            rightIndex--;
        }
        if (leftIndex < rightIndex)
        {
            swap(&array[leftIndex], &array[rightIndex]);
        }
    }
    swap(&array[start], &array[rightIndex]);

    return rightIndex;
}

void quickSort(int array[], int start, int end)
{
    if (end - start + 1 <= 1)
    {
        return;
    }
    int pivotIndex = partition(array, start, end);
    quickSort(array, start, pivotIndex - 1);
    quickSort(array, pivotIndex + 1, end);
}
