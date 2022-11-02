#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int value;
    struct Node* nextNodePtr;
} Node;

typedef struct List
{
    Node* firstNodePtr;
} List;

int createList(List** ptrToListPtr);

bool isListEmpty(List* listPtr);

int addToList(List* listPtr, int value);

int deleteValue(List* listPtr, int value);

void printList(List* listPtr);

void freeList(List* listPtr);