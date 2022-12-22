#include <stdio.h>
#include "circularList.h"

int main()
{
    printf("N warriors stand in a circle, each m-th is killed, \n");
    printf("this program determines number of initial position \nof warrior who will remain the last.\n");
    printf("Enter n (natural number): ");
    int numberOfWarriors = 0;
    int isScanned = scanf("%d", &numberOfWarriors);
    while (isScanned == 0 || numberOfWarriors <= 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a natural number, try again: ");
        isScanned = scanf("%d", &numberOfWarriors);
    }
    printf("Enter m (natural number): ");
    int periodicity = 0;
    isScanned = scanf("%d", &periodicity);
    while (isScanned == 0 || periodicity <= 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a natural number, try again: ");
        isScanned = scanf("%d", &periodicity);
    }
    List* listPtr = NULL;
    createList(&listPtr);
    for (int i = 1; i <= numberOfWarriors; i++)
    {
        addToList(listPtr, i);
    }
    while (!isSingleNodeInList(listPtr))
    {
        deleteValueInList(listPtr, periodicity);
    }
    int lastWarrior = 0;
    headOfList(listPtr, &lastWarrior);
    printf("Position of last warrior in initial circle is %d.", lastWarrior);
    freeList(listPtr);
    return 0;
}

