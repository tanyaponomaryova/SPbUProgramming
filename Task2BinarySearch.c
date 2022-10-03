#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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

int binarySearch(int array[], int length, int number) //return 0 or 1
{
    int left = -1;
    int right = length;
    while (right - left > 1)
    {
        int mid = (right + left)/2;
        if (array[mid] > number)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    if (left > -1 && array[left] == number)
    {
        return 1;
    }
    return 0;
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

    printArray(array, length);
    quickSort(array, 0, length - 1);
    printArray(array, length);


    printf("Enter amount of numbers to be searched in array (natural number): ");
    int amountOfNumbers = 0;
    scanned = scanf("%d", &amountOfNumbers);
    while (scanned == 0 || amountOfNumbers <= 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a natural number, try again: ");
        scanned = scanf("%d", &amountOfNumbers);
    }

    for (int i = 0; i < amountOfNumbers; i++)
    {
        int randomNumber = rand()%15;
        if (binarySearch(array, length, randomNumber))
        {
            printf("%d is in the generated array \n", randomNumber);
        }
        else
        {
            printf("%d is not in the generated array \n", randomNumber);
        }
    }
}