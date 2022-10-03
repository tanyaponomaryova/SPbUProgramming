#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void printArray (int array[], int length) //length
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
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
    if (end - start + 1 <= 1)
    {
        return;
    }
    int pivotIndex = partition(array, start, end);
    quickSort(array, start, pivotIndex - 1);
    quickSort(array, pivotIndex + 1, end);
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
            if (counter > maxCounter)
            {
                maxCounter = counter;
                mostFrequentElement = array[i];
            }
        }
        else
        {
            counter = 1;
        } 
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
    int* array = calloc(length, sizeof(int));
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

    return 0;
}