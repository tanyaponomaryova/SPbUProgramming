#include <stdio.h>
#include <stdlib.h>
void reverseArray(int array[], int firstIndex, int secondIndex)
{
    for (int i = firstIndex; i < (secondIndex + firstIndex + 1)/2; i++)
    {
        
        array[i] = array[i] + array[secondIndex + firstIndex - i];
        array[secondIndex + firstIndex - i] = array[i] - array[secondIndex + firstIndex - i];
        array[i] = array[i] - array[secondIndex + firstIndex - i];
    }
}
int main()
{  
    printf("Enter size of first segment of array: ");
    int firstSegmentSize = 0;
    int scanned = scanf("%d", &firstSegmentSize);
    while (scanned == 0 || firstSegmentSize < 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a correct number, try again: ");
        scanned = scanf("%d", &firstSegmentSize);
    }
    printf("Enter size of second segment of array: ");
    int secondSegmentSize = 0;
    scanned = scanf("%d", &secondSegmentSize);
    while (scanned == 0 || secondSegmentSize < 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a correct number, try again: ");
        scanned = scanf("%d", &secondSegmentSize);
    }
    int* array = calloc(firstSegmentSize + secondSegmentSize, sizeof(int));
    if (array == NULL)
    {
        printf("Error allocating memory for array");
        return -1;
    }

    printf("Enter numbers to array: ");

    for (int i = 0; i < firstSegmentSize + secondSegmentSize; i++)
    {
        scanned = scanf("%d", &array[i]);
        while (scanned == 0)
        {
            scanf("%*[^\n]");
            printf("You didn't enter an integer, try again: ");
            scanned = scanf("%d", &array[i]);
        }
    }
    reverseArray(array, 0, firstSegmentSize - 1); 
    reverseArray(array, firstSegmentSize, firstSegmentSize + secondSegmentSize - 1);
    reverseArray(array, 0, firstSegmentSize + secondSegmentSize - 1);
    printf("New array: ");
    for (int i = 0; i < firstSegmentSize + secondSegmentSize; i++)
        printf("%d ", array[i]);
    free(array);
    return 0;
}