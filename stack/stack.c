#include "../stack/stack.h"

typedef struct StackElement
{
    int value;
    struct StackElement* nextElementPtr;
} StackElement;

typedef struct Stack
{
    StackElement* lastElementPtr;
} Stack;

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

int top(Stack* stackPtr, int* value)
{
    if (stackPtr == NULL || stackPtr->lastElementPtr == NULL || value == NULL)
    {
        return -1;
    }
    *value = stackPtr->lastElementPtr->value;
    return 0;
}

int pop(Stack* stackPtr, int* value)
{
    if (stackPtr == NULL || stackPtr->lastElementPtr == NULL || value == NULL)
    {
        return -1;
    }
    *value = stackPtr->lastElementPtr->value;
    StackElement* PtrTolastElementToFree = stackPtr->lastElementPtr;
    stackPtr->lastElementPtr = stackPtr->lastElementPtr->nextElementPtr;
    free(PtrTolastElementToFree);
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

int lengthOfStack(Stack* stackPtr, int* lengthPtr)
{
    if (stackPtr == NULL || lengthPtr == NULL)
    {
        return -1;
    }
    *lengthPtr = 0;
    StackElement* currentElementPtr = stackPtr->lastElementPtr;
    while (currentElementPtr != NULL)
    {
        (*lengthPtr)++;
        currentElementPtr = currentElementPtr->nextElementPtr;
    }
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
bool isEmptyOrNull(Stack* stackPtr)
{
    return stackPtr == NULL || stackPtr->lastElementPtr == NULL;
}