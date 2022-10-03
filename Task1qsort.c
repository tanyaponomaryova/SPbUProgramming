#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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

void insertionSort (int array[], int start, int finish) //indexes
{
    for (int i = start + 1; i <= finish; i++)
    {   
        int currentIndex = i;
        while (currentIndex > start && array[currentIndex] < array[currentIndex - 1])
        {
            swap(&array[currentIndex], &array[currentIndex - 1]);
            currentIndex -= 1;
        }
    }
}

int partition(int array[], int start, int end) //indexes
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
    if (end - start + 1 < 10)
    {
        insertionSort(array, start, end);
        return;
    }
    int pivotIndex = partition(array, start, end);
    quickSort(array, start, pivotIndex - 1);
    quickSort(array, pivotIndex + 1, end);
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
        array[i] = rand() % 100;
    }


    printf("Randomly generated array: ");
    printArray(array, length);
    quickSort(array, 0, length - 1);
    printf("Sorted array: ");
    printArray(array, length);

    free(array);
    array = NULL;
    return 0;
}