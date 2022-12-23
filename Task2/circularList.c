#include "circularList.h"

typedef struct Node
{
    int value;
    struct Node *nextNodePtr;
} Node;

struct List
{
    Node *headPtr;
    Node *tailPtr;
};

int createList(List **ptrToListPtr)
{
    *ptrToListPtr = calloc(1, sizeof(List));
    if (*ptrToListPtr == NULL)
    {
        return -2;
    }
    return 0;
}

bool isListEmptyOrNull(List *listPtr)
{
    return listPtr == NULL || listPtr->headPtr == NULL;
}

bool isSingleNodeInList(List *listPtr)
{
    return listPtr != NULL && listPtr->headPtr != NULL && listPtr->headPtr == listPtr->tailPtr;
}

int headOfList(List *listPtr, int *valuePtr)
{
    if (listPtr == NULL || valuePtr == NULL || listPtr->headPtr == NULL)
    {
        return -1;
    }
    *valuePtr = listPtr->headPtr->value;
    return 0;
}

int addToList(List *listPtr, int value)
{
    if (listPtr == NULL)
    {
        return -1;
    }
    if (listPtr->headPtr == NULL)
    {
        listPtr->headPtr = calloc(1, sizeof(Node));
        if (listPtr->headPtr == NULL)
        {
            return -2;
        }
        listPtr->headPtr->value = value;
        listPtr->headPtr->nextNodePtr = listPtr->headPtr;
        listPtr->tailPtr = listPtr->headPtr;
    } else
    {
        Node *newNodePtr = calloc(1, sizeof(Node));
        if (newNodePtr == NULL)
        {
            return -2;
        }
        newNodePtr->value = value;
        listPtr->tailPtr->nextNodePtr = newNodePtr;
        newNodePtr->nextNodePtr = listPtr->headPtr;
        listPtr->tailPtr = listPtr->tailPtr->nextNodePtr;
    }
    return 0;
}

int deleteValueFromList(List *listPtr, int position)
{
    if (listPtr == NULL || position < 1)
    {
        return -1;
    }
    Node *currentNodePtr = listPtr->headPtr;
    Node *previousNodePtr = listPtr->tailPtr;
    for (int i = 1; i < position; i++)
    {
        previousNodePtr = currentNodePtr;
        currentNodePtr = currentNodePtr->nextNodePtr;
    }
    listPtr->headPtr = currentNodePtr->nextNodePtr;
    previousNodePtr->nextNodePtr = currentNodePtr->nextNodePtr;
    listPtr->tailPtr = previousNodePtr;
    free(currentNodePtr);
    return 0;
}

void freeList(List *listPtr)
{
    while (listPtr->headPtr != listPtr->tailPtr)
    {
        deleteValueFromList(listPtr, 0);
    }
    free(listPtr->headPtr);
    free(listPtr);
}

void printList(List *listPtr)
{
    if (listPtr == NULL)
    {
        return;
    }
    Node *currentNodePtr = listPtr->headPtr;
    printf("{ ");
    while (1)
    {
        printf("%d ", currentNodePtr->value);
        currentNodePtr = currentNodePtr->nextNodePtr;
        if (currentNodePtr == listPtr->headPtr)
            break;
    }
    printf("}\n");
}