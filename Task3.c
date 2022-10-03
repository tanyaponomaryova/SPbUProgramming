#include <stdio.h>
#include <limits.h>
#include <stdlib.h>


void bubbleSort (int array[], int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - i - 1; j++)
        {
            if (array[j] > array[j+1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void printArray (int array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int searchMaxInArray (int array[], int length)
{
    int maximum = INT_MIN;
    for (int i = 0; i < length; i++)
    {
        if (array[i] > maximum)
        {
            maximum = array[i]; 
        }    
    }
    return maximum;
}

int searchMinInArray (int array[], int length)
{
    int minimum = INT_MAX;
    for (int i = 0; i < length; i++)
    {
        if (array[i] < minimum)
            minimum = array[i]; 
    }
    return minimum;
}

int countingSort (int array[], int length)
{
    int maximumElement = searchMaxInArray(array, length);
    int minimumElement = searchMinInArray(array, length);
    int numberOfCounters = maximumElement - minimumElement + 1;
    int* arrayOfCounters = calloc(numberOfCounters, sizeof(int));
    if (NULL == arrayOfCounters)
    {
        return 0;
    }
    for (int i = 0; i < length; i++)
    {
        arrayOfCounters[ array[i] - minimumElement ]++;
    }
    int index = 0;
    for (int i = 0; i < numberOfCounters; i++)
    {
        for (int j = 0; j < arrayOfCounters[i]; j++)
        {
            array[index] = i + minimumElement;
            index++;
        }
    }
    free(arrayOfCounters);
    return 1;
}

int main()
{
    printf("Enter array size (natural number): ");
    int arraySize = 0;
    int scanned = scanf("%d", &arraySize);
    while (scanned == 0 || arraySize <= 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a natural number, try again: ");
        scanned = scanf("%d", &arraySize);
    }
    int* array1 = calloc(arraySize, sizeof(int));
    int* array2 = calloc(arraySize, sizeof(int));
    if (array1 == NULL || array2 == NULL)
    {
        printf("Error allocating memory for array\n");
        return -1;
    }

    printf("Enter numbers to array: ");
    
    for (int i = 0; i < arraySize; i++)
    {
        int scanned = scanf("%d", &array1[i]);
        while (scanned == 0)
        {
            scanf("%*[^\n]");
            printf("You didn't enter a number, try again: ");
            scanned = scanf("%d", &array1[i]);
        }
        array2[i] = array1[i];
    }

    printf("Entered array: ");
    printArray(array1, arraySize);

    bubbleSort(array2, arraySize);
    printf("Array sorted by bubble sort: ");
    printArray(array2, arraySize);
    free(array2);
    array2 = NULL;

    if (countingSort(array1, arraySize))
    {
        printf("Array sorted by counting sort: ");
        printArray(array1, arraySize);
    }
    else
        printf("Error allocating memory for array of counters in counting sort");
    free(array1);
    array1 = NULL;   
    return 0;
}
