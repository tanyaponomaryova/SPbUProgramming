#include <stdio.h>
#include <stdbool.h>
#include "sortedList.h"

void showHelpMessage()
{
    printf("Enter: \n0 - to exit \n");
    printf("1 - to add value to sorted list \n");
    printf("2 - to delete value from list \n");
    printf("3 - to print list \n");
    printf("4 - to print help message \n");
}

int main()
{
    printf("Welcome to sorted list!");
    List* listPtr = NULL;
    createList(&listPtr);
    if (listPtr == NULL)
    {
        printf("Error allocating memory for list :(");
        return -1;
    }
    bool shouldGoOut = false;
    int errorCode = 0;
    showHelpMessage();
    while (!shouldGoOut)
    {
        int input = 0;
        int isScanned = scanf("%d", &input); // если введено не число, то IsScanned будет равно 0
        while (isScanned == 0 || input < 0 || input > 4)
        {
            scanf("%*[^\n]");
            printf("Incorrect input, try again: ");
            isScanned = scanf("%d", &input);
        }
        switch (input)
        {
            case 0:
                shouldGoOut = true;
                break;
            case 1:
                printf("Enter value to add to list: ");
                int valueToAdd = 0;
                isScanned = scanf("%d", &valueToAdd);
                while (isScanned == 0) // пока введено не число
                {
                    scanf("%*[^\n]");
                    printf("Incorrect input, try again: ");
                    isScanned = scanf("%d", &valueToAdd);
                }
                errorCode = addToList(listPtr, valueToAdd);
                if (errorCode == -2)
                {
                    printf("Error allocating memory for new element in list :(");
                    freeList(listPtr);
                    return -1;
                }
                else // errorCode == 0 (не может равняться -1, так как проверка на null была ранее)
                {
                    printf("Value %d successfully added!", valueToAdd);
                }
                break;
            case 2:
                printf("Enter value to delete from list: ");
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
                break;
            case 3:
                printList(listPtr);
                break;
            case 4:
                showHelpMessage();
        }
    }
    freeList(listPtr);
    return 0;
}