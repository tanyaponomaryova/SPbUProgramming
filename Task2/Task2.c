#include <stdio.h>
#include "stack.h"

void printCommands()
{
    printf("Enter: \n");
    printf("0 - to exit, \n");
    printf("1 - to add integer number to stack, \n");
    printf("2 - to get number from stack and delete this number, \n");
    printf("3 - to sum first two numbers from stack and to put result to stack, \n");
    printf("4 - to print stack. \n");
}

int main() {
    Stack* stackPtr = NULL;
    int errorCode = createStack(&stackPtr);
    if (errorCode != 0)
    {
        printf("Error allocating memory for stack :(");
        return -1;
    }
    bool shouldGoOut = false;
    while (!shouldGoOut)
    {
        printCommands();
        int input = 0;
        bool isScanned = scanf("%d", &input);
        while (isScanned == false || input < 0 || input > 4)
        {
            scanf("%*[^\n]");
            printf("Incorrect input, try again: ");
            isScanned = scanf("%d", &input);
        }
        switch (input) {
            case 0:
                shouldGoOut = true;
                break;
            case 1:
            {
                printf("Enter integer number: ");
                int number = 0;
                isScanned = scanf("%d", &number);
                while (isScanned == false)
                {
                    scanf("%*[^\n]");
                    printf("Incorrect input, try again: ");
                    isScanned = scanf("%d", &number);
                }
                errorCode = push(stackPtr, number);
                if (errorCode == 0)
                {
                    printf("Number successfully added! \n");
                }
                else
                {
                    printf("Error allocating memory for new stack element :(");
                    freeStack(stackPtr);
                    return -1;
                }
                break;
            }
            case 2:
            {
                int number = 0;
                errorCode = pop(stackPtr, &number);
                if (errorCode == 0)
                {
                    printf("Number %d is deleted from stack. \n", number);
                }
                else
                {
                    printf("Stack is empty. \n");
                }
                break;
            }
            case 3:
            {
                errorCode = add(stackPtr);
                if (errorCode == 0)
                {
                    printf("Sum of first two numbers of stack is added to stack. \n");
                }
                else
                {
                    printf("There are less than two numbers in stack. \n");
                }
                break;
            }
            case 4:
            {
                printStack(stackPtr);
            }
        }
    }
    freeStack(stackPtr);
    return 0;
}