#include "search.h"
#include "qsort.h"

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