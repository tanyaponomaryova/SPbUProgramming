#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>

typedef struct Node Node;

typedef struct List List;

int createList(List** ptrToListPtr);

bool isListEmpty(List* listPtr);

bool isSingleNodeInList(List* listPtr);

int headOfList(List* listPtr, int* valuePtr);

int addToList(List* listPtr, int value);

int deleteValueInList(List* listPtr, int position);

void freeList(List* listPtr);

void printList(List* listPtr);




