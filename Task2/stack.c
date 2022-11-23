#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "stack.h"

int createStack(Stack** stackPtrPtr)
{
    *stackPtrPtr = calloc(1, sizeof(Stack));
    if (*stackPtrPtr == NULL)
    {
        return -1;
    }
    return 0;
}

int push(Stack* stackPtr, int value)
{
    if (stackPtr == NULL)
    {
        return -2;
    }
    StackElement* newElementPtr = calloc(1, sizeof(StackElement));
    if (newElementPtr == NULL)
    {
        return -1;
    }
    newElementPtr->nextElementPtr = stackPtr->lastElementPtr;
    newElementPtr->value = value;
    stackPtr->lastElementPtr = newElementPtr;
    return 0;
}

int pop(Stack* stackPtr, int* value)
{
    if (stackPtr == NULL || stackPtr->lastElementPtr == NULL)
    {
        return -1;
    }
    *value = stackPtr->lastElementPtr->value;
    StackElement* PtrTolastElementToFree = stackPtr->lastElementPtr;
    stackPtr->lastElementPtr = stackPtr->lastElementPtr->nextElementPtr;
    free(PtrTolastElementToFree);
    return 0;
}

int add(Stack* stackPtr)
{
    if (stackPtr == NULL)
    {
        return -2;
    }
    int firstNumber = 0;
    int secondNumber = 0;
    int firstErrorCode = pop(stackPtr, &firstNumber);
    if (firstErrorCode == -1)
    {
        return -3;
    }
    int secondErrorCode = pop(stackPtr, &secondNumber);
    if (secondErrorCode == -1)
    {
        push(stackPtr, firstNumber);
        return -3;
    }
    push(stackPtr, firstNumber + secondNumber);
    return 0;
}

int printStack(Stack* stackPtr)
{
    if (stackPtr == NULL)
    {
        return -1;
    }
    StackElement* currentElementPtr = stackPtr->lastElementPtr;
    if (currentElementPtr == NULL)
    {
        printf("Stack is empty. \n");
    }
    printf("Stack: ");
    while (currentElementPtr != NULL)
    {
        printf("%d ", currentElementPtr->value);
        currentElementPtr = currentElementPtr->nextElementPtr;
    }
    printf("\n");
    return 0;
}

void freeStack(Stack* stackPtr)
{
    if (stackPtr == NULL)
    {
        return;
    }
    StackElement* currentElementPtr = stackPtr->lastElementPtr;
    while (currentElementPtr != NULL)
    {
        stackPtr->lastElementPtr = currentElementPtr->nextElementPtr;
        free(currentElementPtr);
        currentElementPtr = stackPtr->lastElementPtr;
    }
    free(stackPtr);
}