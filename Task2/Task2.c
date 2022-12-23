#include <stdio.h>
#include "circularList.h"

int lastWarrior(int numberOfWarriors, int periodicity)
{
    List *listPtr = NULL;
    createList(&listPtr);
    if (listPtr == NULL)
    {
        return -2;
    }
    int errorCode = 0;
    for (int i = 1; i <= numberOfWarriors; i++)
    {
        errorCode = addToList(listPtr, i);
        if (errorCode != 0)
        {
            freeList(listPtr);
            return errorCode;
        }
    }
    while (!isSingleNodeInList(listPtr))
    {
        deleteValueFromList(listPtr, periodicity);
    }
    int positionOfLastWarrior = 0;
    headOfList(listPtr, &positionOfLastWarrior);
    freeList(listPtr);
    return positionOfLastWarrior;
}

bool test()
{
    return lastWarrior(10, 3) == 4 &&
           lastWarrior(5, 1) == 5 &&
           lastWarrior(500, 100) == 480;
}

int main()
{
    if (!test())
    {
        printf("Test failed.");
        return -1;
    }
    printf("N warriors stand in a circle, each m-th is killed, \n");
    printf("this program determines number of initial position \nof warrior who will remain the last.\n");
    printf("(Numbering of warriors starts from 1) \n");
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
    int positionOfLastWarrior = lastWarrior(numberOfWarriors, periodicity);
    if (positionOfLastWarrior > 0)
    {
        printf("Position of last warrior in initial circle is %d.", positionOfLastWarrior);
    } else
    {
        printf("Memory allocation error.");
    }
    return 0;
}