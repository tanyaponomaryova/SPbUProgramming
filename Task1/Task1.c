#include <stdio.h>
#include <stdbool.h>
#include "tree.h"

void begin()
{
    printf("Enter: \n0 - to exit, \n");
    printf("1 - to add value by key, \n");
    printf("2 - to get value by key, \n");
    printf("3 - to check for presence of a given key, \n");
    printf("4 - to remove given key with its value. \n");
}

int main()
{
    printf("Welcome to interactive dictionary! \n");
    Tree* treePtr = NULL;
    createTree(&treePtr);
    bool shouldGoOut = false;
    while (!shouldGoOut)
    {
        begin();
        int input = 0;
        bool isScanned = scanf("%d", &input);
        while (isScanned == false || input < 0 || input > 4)
        {
            scanf("%*[^\n]");
            printf("Incorrect input, try again: ");
            isScanned = scanf("%d", &input);
        }
        switch (input)
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
                printf("Enter value: ");
                char value[1000] = {0};
                scanf("%s", value);
                addTree(treePtr, key, value);
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
                char* value = NULL;
                getTree(treePtr, key, &value);
                if (value == NULL)
                {
                    printf("Entered key is not found :( \n");
                }
                else
                {
                    printf("Found value: %s \n", value);
                }
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
                if (findTree(treePtr, key))
                {
                    printf("Entered key exists. \n");
                } else
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
                int isDeleted = deleteFromTree(treePtr, key);
                if (isDeleted == 0)
                {
                    printf("Entered key and its value deleted!");
                }
                else
                {
                    printf("Entered key is not found :(");
                }
                break;
            }
        }
    }
}