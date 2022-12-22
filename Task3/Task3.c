#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "mergeSort.h"

#define STRING_LENGTH 100

int fillList(List *listPtr, char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return -3;
    }
    char name[STRING_LENGTH] = {0};
    char phone[STRING_LENGTH] = {0};
    while (!feof(file))
    {
        int errorCode1 = fscanf(file, "%s", name);
        int errorCode2 = fscanf(file, "%s", phone);
        if (errorCode1 == -1 || errorCode2 == -1)
        {
            return -4;
        }
        int errorCode = addEntry(listPtr, name, phone);
        if (errorCode != 0)
        {
            return errorCode;
        }
    }
    fclose(file);
    return 0;
}

int main()
{
    List *listPtr = NULL;
    createList(&listPtr);
    int errorCode = fillList(listPtr, "phonebook.txt");
    if (errorCode != 0)
    {
        switch (errorCode)
        {
            case -1:
                printf("Error allocating memory for list.");
                return -1;
            case -2:
                printf("Error allocating memory in addEntry function.");
                freeList(listPtr);
                return -1;
            case -3:
                printf("Error opening file phonebook.txt.");
                freeList(listPtr);
                return -1;
            case -4:
                printf("Incorrect file structure (empty file, empty lines or lack of names or phones)");
                freeList(listPtr);
                return -1;
        }
    }
    printf("List from file: \n");
    printList(listPtr);
    int sortByName = 0;
    printf("Enter: \n0 or any other characters - to sort by phone, \npositive or negative number - to sort by name: ");
    scanf("%d", &sortByName);
    errorCode = mergeSort(&listPtr, (bool)sortByName);
    if (errorCode != 0)
    {
        printf("Error allocating memory in mergeSort function.");
        freeList(listPtr);
        return -1;
    }
    if (sortByName)
    {
        printf("List sorted by name: \n");
    } else
    {
        printf("List sorted by phone: \n");
    }
    printList(listPtr);
    freeList(listPtr);
    return 0;
}