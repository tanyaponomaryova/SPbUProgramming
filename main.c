#include <stdbool.h>
#include <stdio.h>
#include "avlTree.h"

void printCommands()
{
    printf("Enter: \n0 - to exit, \n");
    printf("1 - to add string by key, \n");
    printf("2 - to get string by key, \n");
    printf("3 - to check for presence of a given key, \n");
    printf("4 - to remove given key with its string, \n");
    printf("5 - to print tree in pre-order. \n");
}

int main()
{
    printf("Welcome to interactive AVL-tree! \n");
    Tree* treePtr = NULL;
    createTree(&treePtr);
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
                addKeyAndString(treePtr, key, string);
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
                getStringFromTree(treePtr, key, &destinationString);
                if (destinationString == NULL)
                {
                    printf("Entered key is not found :( \n");
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
                if (isFoundInTree(treePtr, key))
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
                deleteNodeFromTree(treePtr, key);
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
