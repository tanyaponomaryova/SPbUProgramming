#include "sortedList.h"

typedef struct Node
{
    int value;
    struct Node *nextNodePtr;
} Node;

typedef struct List
{
    Node *firstNodePtr;
} List;

int createList(List **ptrToListPtr)
{
    (*ptrToListPtr) = calloc(1, sizeof(List));
    if (*ptrToListPtr == NULL)
    {
        return -2;
    }
    return 0;
}

int addToList(List *listPtr, int value)
{
    if (listPtr == NULL)
    {
        return -1;
    }
    Node *previousNodePtr = NULL;
    Node *currentNodePtr = listPtr->firstNodePtr;
    while (currentNodePtr != NULL && currentNodePtr->value < value) // пока значение в текущем узле меньше добавляемого значения идем дальше по списку
    {
        previousNodePtr = currentNodePtr;
        currentNodePtr = currentNodePtr->nextNodePtr;
    }
    // нужно поставить новый узел между previous и current
    Node *newNodePtr = calloc(1, sizeof(Node));
    if (newNodePtr == NULL)
    {
        return -2;
    }
    newNodePtr->value = value;
    newNodePtr->nextNodePtr = currentNodePtr;
    if (previousNodePtr == NULL) // элемент который мы добавляем в список меньше или равен первому значению в списке
    {
        listPtr->firstNodePtr = newNodePtr;
    } else
    {
        previousNodePtr->nextNodePtr = newNodePtr;
    }
    return 0;
}

int deleteValue(List *listPtr, int value)
{
    if (listPtr == NULL)
    {
        return -1;
    }
    Node *previousNodePtr = NULL;
    Node *currentNodePtr = listPtr->firstNodePtr;
    while (currentNodePtr != NULL && currentNodePtr->value != value)
    {
        previousNodePtr = currentNodePtr;
        currentNodePtr = currentNodePtr->nextNodePtr;
    }
    if (currentNodePtr == NULL)
    {
        return 0; // value нет в списке или список пустой
    }
    if (previousNodePtr == NULL) // value это первый элемент списка
    {
        listPtr->firstNodePtr = currentNodePtr->nextNodePtr;
    } else
    {
        previousNodePtr->nextNodePtr = currentNodePtr->nextNodePtr;
    }
    free(currentNodePtr);
    return 1; // value нашли и удалили
}

void printList(List *listPtr)
{
    if (listPtr == NULL)
    {
        return;
    }
    Node *currentNodePtr = listPtr->firstNodePtr;
    printf("List: { ");
    while (currentNodePtr != NULL)
    {
        printf("%d ", currentNodePtr->value);
        currentNodePtr = currentNodePtr->nextNodePtr;
    }
    printf("}\n");
}

void freeList(List *listPtr)
{
    if (listPtr == NULL)
    {
        return;
    }
    while (listPtr->firstNodePtr != NULL)
    {
        Node *temp = listPtr->firstNodePtr->nextNodePtr;
        free(listPtr->firstNodePtr);
        listPtr->firstNodePtr = temp;
    }
    free(listPtr);
}