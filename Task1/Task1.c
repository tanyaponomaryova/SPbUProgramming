#include <stdio.h>
#include <stdbool.h>
#include "sortedList.h"

void begin()
{
    printf("Enter: \n0 - to exit \n");
    printf("1 - to add value to sorted list \n");
    printf("2 - to delete value from list \n");
    printf("3 - to print list \n");
}

int main()
{
    List* listPtr = NULL;
    createList(&listPtr);
    bool shouldGoOut = false;
    while (!shouldGoOut)
    {
        begin();
        int input = 0;
        int isScanned = scanf("%d", &input); // если введено не число то IsScanned будет равно 0
        while (isScanned == 0 || input < 0 || input > 3)
        {
            scanf("%*[^\n]");
            printf("Incorrect input, try again: ");
            isScanned = scanf("%d", &input);
        }
        if (input == 0)
        {
            shouldGoOut = true;
        }
        if (input == 1)
        {
            printf("Enter value: ");
            int valueToAdd = 0;
            isScanned = scanf("%d", &valueToAdd);
            while (isScanned == 0) // пока введено не число
            {
                scanf("%*[^\n]");
                printf("Incorrect input, try again: ");
                isScanned = scanf("%d", &valueToAdd);
            }
            addToList(listPtr, valueToAdd);
        }
        if (input == 2)
        {
            printf("Enter value: ");
            int valueToDelete = 0;
            isScanned = scanf("%d", &valueToDelete);
            while (isScanned == 0) // пока введено не число
            {
                scanf("%*[^\n]");
                printf("Incorrect input, try again: ");
                isScanned = scanf("%d", &valueToDelete);
            }
            int isDeleted = deleteValue(listPtr, valueToDelete);
            if (isDeleted == 1)
            {
                printf("Entered value successfully deleted! \n");
            }
            else if (isDeleted == 0)
            {
                printf("Entered value is not found. \n");
            }
        }
        if (input == 3)
        {
            printf("The list: ");
            printList(listPtr);
        }
    }
    freeList(listPtr);
    return 0;
}