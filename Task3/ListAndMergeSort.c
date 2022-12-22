#include "ListAndMergeSort.h"

struct Entry
{
    char *name;
    char *phone;
    struct Entry *nextEntryPtr;
};

struct List
{
    int length;
    Entry *headPtr;
    Entry *tailPtr;
};

int createList(List **ptrToListPtr)
{
    *ptrToListPtr = calloc(1, sizeof(List));
    if (*ptrToListPtr == NULL)
        return -2;
    return 0;
}

int addEntry(List *listPtr, char *name, char *phone)
{
    if (listPtr == NULL || name == NULL || phone == NULL)
    {
        return -1;
    }
    Entry *newEntryPtr = calloc(1, sizeof(Entry));
    char *newName = calloc(strlen(name) + 1, sizeof(char)); // + 1 это место для '\0', так как strlen его не учитывает
    char *newPhone = calloc(strlen(phone) + 1, sizeof(char));
    if (newEntryPtr == NULL || newName == NULL || newPhone == NULL)
    {
        free(newEntryPtr);
        free(newName);
        free(newPhone);
        return -2;
    }
    strcpy(newName, name);
    strcpy(newPhone, phone);
    newEntryPtr->name = newName;
    newEntryPtr->phone = newPhone;
    listPtr->length++;
    if (listPtr->headPtr == NULL)
    {
        listPtr->headPtr = newEntryPtr;
        listPtr->tailPtr = listPtr->headPtr;
        return 0;
    }
    listPtr->tailPtr->nextEntryPtr = newEntryPtr;
    listPtr->tailPtr = listPtr->tailPtr->nextEntryPtr;
    return 0;
}

void freeList(List *listPtr)
{
    if (listPtr == NULL)
    {
        return;
    }
    while (listPtr->headPtr != NULL)
    {
        Entry *temp = listPtr->headPtr->nextEntryPtr;
        free(listPtr->headPtr->name);
        free(listPtr->headPtr->phone);
        free(listPtr->headPtr);
        listPtr->headPtr = temp;
    }
    free(listPtr);
}

void printList(List *listPtr)
{
    if (listPtr == NULL || listPtr->headPtr == NULL)
    {
        printf("Pointer to list is null or list is empty. \n");
        return;
    }
    Entry *currentEntryPtr = listPtr->headPtr;
    while (currentEntryPtr != NULL)
    {
        printf("%s %s \n", currentEntryPtr->name, currentEntryPtr->phone);
        currentEntryPtr = currentEntryPtr->nextEntryPtr;
    }
}

char *returnNameFromHead(List *listPtr)
{
    if (listPtr == NULL)
    {
        return NULL;
    }
    return listPtr->headPtr->name;
}

char *returnPhoneFromHead(List *listPtr)
{
    if (listPtr == NULL)
    {
        return NULL;
    }
    return listPtr->headPtr->phone;
}

int deleteHead(List *listPtr)
{
    if (listPtr == NULL || listPtr->headPtr == NULL)
    {
        return -1;
    }
    listPtr->length--;
    Entry *temp = listPtr->headPtr->nextEntryPtr;
    free(listPtr->headPtr->name);
    free(listPtr->headPtr->phone);
    free(listPtr->headPtr);
    listPtr->headPtr = temp;
    return 0;
}

int transferElements(List *sourceListPtr, List *destinationListPtr, int quantity)
{
    for (int i = 0; i < quantity; i++)
    {
        int errorCode = addEntry(destinationListPtr, returnNameFromHead(sourceListPtr),
                                 returnPhoneFromHead(sourceListPtr));
        if (errorCode != 0)
        {
            return errorCode;
        }
        errorCode = deleteHead(sourceListPtr);
        if (errorCode != 0)
        {
            return errorCode;
        }
    }
    return 0;
}

int merge(List *firstList, List *secondList, bool sortByName, List **ResultList)
{
    int errorCode = 0;
    while (firstList->length != 0 && secondList->length != 0)
    {
        int stringComparisonResult = 0; // если 0, отрицательное число (строки совпадают или первая строка меньше) - берём первую строку; если положительное число (вторая строка меньше) - берём вторую строку
        if (sortByName)
        {
            stringComparisonResult = strcmp(returnNameFromHead(firstList), returnNameFromHead(secondList));
        } else
        {
            stringComparisonResult = strcmp(returnPhoneFromHead(firstList), returnPhoneFromHead(secondList));
        }
        if (stringComparisonResult < 0)
        {
            errorCode = transferElements(firstList, *ResultList, 1);
            if (errorCode != 0)
            {
                return errorCode;
            }
        } else
        {
            errorCode = transferElements(secondList, *ResultList, 1);
            if (errorCode != 0)
            {
                return errorCode;
            }
        }
    }
    if (firstList->length != 0) // остатки
    {
        errorCode = transferElements(firstList, *ResultList, firstList->length);
        if (errorCode != 0)
        {
            return errorCode;
        }
    } else
    {
        errorCode = transferElements(secondList, *ResultList, secondList->length);
        if (errorCode != 0)
        {
            return errorCode;
        }
    }
    freeList(firstList);
    freeList(secondList);
    return 0;
}

int mergeSort(List **listPtr, bool sortByName)
{
    if (*listPtr == NULL)
    {
        return -1;
    }
    int length = (*listPtr)->length;
    if (length <= 1)
    {
        return 0;
    }
    List *leftListPtr = NULL;
    int errorCode = createList(&leftListPtr);
    if (errorCode != 0)
    {
        return errorCode;
    }
    transferElements(*listPtr, leftListPtr, length / 2);
    List *rightListPtr = NULL;
    errorCode = createList(&rightListPtr);
    if (errorCode != 0)
    {
        freeList(leftListPtr);
        return errorCode;
    }
    transferElements(*listPtr, rightListPtr, length - length / 2);
    errorCode = mergeSort(&leftListPtr, sortByName);
    if (errorCode != 0)
    {
        freeList(rightListPtr);
        freeList(leftListPtr);
        return errorCode;
    }
    errorCode = mergeSort(&rightListPtr, sortByName);
    if (errorCode != 0)
    {
        freeList(rightListPtr);
        freeList(leftListPtr);
        return errorCode;
    }
    errorCode = merge(leftListPtr, rightListPtr, sortByName, listPtr);
    if (errorCode != 0)
    {
        freeList(rightListPtr);
        freeList(leftListPtr);
        return errorCode;
    }
    return 0;
}