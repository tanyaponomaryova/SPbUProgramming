#include <stdio.h>
#include "search.h"

int main()
{
    FILE* file = fopen("Input.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file");
        return -1;
    }
    int array[1000] = {0};
    int length = 0;
    while (!feof(file))
    {
        fscanf(file, "%d", &array[length]);
        length++;
    }

    fclose(file);

    printf("Array from input file: ");
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    int mostFrequentElement = searchMostFrequentElement(array, length);
    printf("Most frequent element in array: %d", mostFrequentElement);

    return 0;
}
