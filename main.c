#include <stdbool.h>
#include <stdio.h>
#include "avlTree.h"

void printCommands()
{
    printf("Enter: \n0 - to exit, \n");
    printf("1 - to add key and string, \n");
    printf("2 - to get string by key, \n");
    printf("3 - to check for presence of a given key, \n");
    printf("4 - to remove given key with string, \n");
    printf("5 - to print tree in pre-order. \n");
}

int main()
{
    printf("Welcome to interactive AVL-tree! \n");
    Tree* treePtr = NULL;
    int errorCode = createTree(&treePtr);
    if (errorCode == -1)
    {
        printf("Memory allocation error while creating a tree. :(");
        return -1;
    }
    bool shouldGoOut = false;
    while (!shouldGoOut)
    {
        printCommands();
        int input = 0;
        bool isScanned = scanf("%d", &input);
        while (isScanned == false || input < 0 || input > 5)
        {
            scanf("%*[^\n]");
            printf("Incorrect input, try again: ");
            isScanned = scanf("%d", &input);
        }
        switch(input)
        {
            case 0:
            {
                shouldGoOut = true;
                break;
            }
            case 1:
            {
                printf("Enter key: ");
                int key = 0;
                isScanned = scanf("%d", &key);
                while (isScanned == false)
                {
                    scanf("%*[^\n]");
                    printf("Incorrect input, try again: ");
                    isScanned = scanf("%d", &key);
                }
                printf("Enter string: ");
                char string[1000] = {0};
                scanf("%s", string);
                errorCode = addKeyAndString(treePtr, key, string);
                if (errorCode == 0)
                {
                    printf("Key and string are successfully added to tree! \n");
                }
                else
                {
                    printf("Memory allocation error while adding key and string. \n");
                    freeTree(treePtr);
                    return -1;
                }
                break;
            }
            case 2:
            {
                printf("Enter key: ");
                int key = 0;
                isScanned = scanf("%d", &key);
                while (isScanned == false)
                {
                    scanf("%*[^\n]");
                    printf("Incorrect input, try again: ");
                    isScanned = scanf("%d", &key);
                }
                char* destinationString = NULL;
                errorCode = getStringFromTree(treePtr, key, &destinationString);
                if (destinationString == NULL)
                {
                    if (errorCode == 0)
                    {
                        printf("Entered key is not found :( \n");
                    }
                    else
                    {
                        printf("Memory allocation error while getting string from tree. \n");
                        freeTree(treePtr);
                        return -1;
                    }
                }
                else
                {
                    printf("Found string: %s \n", destinationString);
                }
                free(destinationString); // в функции getStringFromTree() каллоком выделяется память под строку
                break;
            }
            case 3:
            {
                printf("Enter key: ");
                int key = 0;
                isScanned = scanf("%d", &key);
                while (isScanned == false)
                {
                    scanf("%*[^\n]");
                    printf("Incorrect input, try again: ");
                    isScanned = scanf("%d", &key);
                }
                bool isFound = false;
                isFoundInTree(treePtr, key, &isFound);
                if (isFound)
                {
                    printf("Entered key exists. \n");
                }
                else
                {
                    printf("Entered key doesn't exist. \n");
                }
                break;
            }
            case 4:
            {
                printf("Enter key: ");
                int key = 0;
                isScanned = scanf("%d", &key);
                while (isScanned == false)
                {
                    scanf("%*[^\n]");
                    printf("Incorrect input, try again: ");
                    isScanned = scanf("%d", &key);
                }
                bool isDeleted = false;
                errorCode = deleteNodeFromTree(treePtr, key, &isDeleted);
                if (errorCode == 0) // нет ошибок
                {
                    if (isDeleted)
                    {
                        printf("Key and string are successfully deleted! \n");
                    }
                    else
                    {
                        printf("Key and string are not found. \n");
                    }
                }
                else if (errorCode == -1)
                {
                    printf("Memory allocation error while deleting key and string. :( \n");
                    freeTree(treePtr);
                    return -1;
                }
                break;
            }
            case 5:
            {
                printTreeInPreOrder(treePtr);
                break;
            }
        }
    }
    freeTree(treePtr);
    return 0;
}
