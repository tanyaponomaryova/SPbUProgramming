#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct StackElement
{
    int value;
    struct StackElement* nextElementPtr;
} StackElement;

typedef struct Stack
{
    StackElement* lastElementPtr;
} Stack;

int createStack(Stack** stackPtrPtr);

int push(Stack* stackPtr, int value);

int pop(Stack* stackPtr, int* value);

int add(Stack* stackPtr);

int printStack(Stack* stackPtr);

void freeStack(Stack* stackPtr);

