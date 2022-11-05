#include <stdio.h>
#include <stdlib.h>
#include "../stack/stack.h"

typedef enum Error
{
    Ok,
    MemoryAllocationError,
    UnbalancedBrackets,
    IncorrectInput
} Error;

int priority(char operation)
{
    if (operation == '+' || operation == '-')
    {
        return 1;
    }
    if (operation == '*' || operation == '/')
    {
        return 2;
    }
    if (operation == '(')
    {
        return 0;
    }
    return 3; // if operation == ')'
}

Error convertToPostfix()
{
    printf("Enter arithmetic expression in infix form: ");
    Stack* stackOfOperations = NULL;
    createStack(&stackOfOperations);
    Stack* outputStack = NULL;
    createStack(&outputStack);
    if (stackOfOperations == NULL || outputStack == NULL)
    {
        freeStack(outputStack);
        freeStack(stackOfOperations);
        return MemoryAllocationError;
    }
    for (char scannedSymbol = (char)getchar(); scannedSymbol != '\n'; scannedSymbol = (char)getchar())
    {
        if (scannedSymbol - '0' <= 9 && scannedSymbol - '0' >= 0) // проверяем что введенный символ это цифра
        {
            push(outputStack, scannedSymbol); // цифра в любом случае сразу отправляется в выходную строку
        }
        else {
            switch (scannedSymbol)
            {
                case '+':
                case '-':
                case '*':
                case '/':
                {
                    while (!isEmptyOrNull(stackOfOperations))
                    {
                        int topOfStack;
                        pop(stackOfOperations, &topOfStack); // достали верхушку
                        if (priority(scannedSymbol) <= priority((char)topOfStack)) // если введённая операция <= по приоритету достанной верхушки, то верхушку кладём в выходную строку
                        {
                            push(outputStack, topOfStack); //положили верхушку в выходную строку
                        } else // засунем верхушку обратно и выйдем из while
                        {
                            push(stackOfOperations, topOfStack);
                            break;
                        }
                    }
                    push(stackOfOperations, scannedSymbol); // когда введенный символ вытеснил тех кто >= его по приоритету он сам залез в стек
                    break;
                }
                case '(':
                {
                    push(stackOfOperations, scannedSymbol);
                    break;
                }
                case ')':
                {
                    int topOfStack;
                    pop(stackOfOperations, &topOfStack); // достали верхний элемент из стека
                    while (topOfStack != '(') // он открывающая скобка? нет - значит кладём его в выходную строку и достаём следующий из стека операций
                    {
                        if (isEmptyOrNull(stackOfOperations)) // ещё не нашли открывающую скобку, но стек уже пуст
                        {
                            freeStack(outputStack);
                            freeStack(stackOfOperations);
                            return UnbalancedBrackets;
                        }
                        push(outputStack, topOfStack);
                        pop(stackOfOperations, &topOfStack);
                    }
                    break;
                }
                default: // любой другой символ кроме цифр, знаков операций и скобок
                    freeStack(outputStack);
                    freeStack(stackOfOperations);
                    return IncorrectInput;
            }
        }
    }
    while(!isEmptyOrNull(stackOfOperations)) // достаём оставшиеся операции из стека операций
    {
        int topOfStack;
        pop(stackOfOperations, &topOfStack);
        if (topOfStack == '(') // если осталась открывающая скобка, значит для неё не хватило закрывающей
        {
            freeStack(outputStack);
            freeStack(stackOfOperations);
            return UnbalancedBrackets;
        }
        push(outputStack, topOfStack);
    } // скопируем outputStack в строку, но в обратном порядке
    int length = 0;
    lengthOfStack(outputStack, &length);
    char* string = calloc(length, sizeof(char));
    for (int i = length - 1; i >= 0; i--)
    {
        int topOfStack;
        pop(outputStack, &topOfStack);
        string[i] = (char)topOfStack;
    }
    printf("Postfix expression: ");
    for (int i = 0; i < length; i++)
    {
        printf("%c ", string[i]);
    }
    freeStack(outputStack);
    freeStack(stackOfOperations);
    return Ok;
}

int main()
{
    Error errorCode = convertToPostfix();
    switch (errorCode)
    {
        case MemoryAllocationError:
            printf("Memory allocation error :(");
            break;
        case UnbalancedBrackets:
            printf("Brackets are unbalanced in entered expression :(");
            break;
        case IncorrectInput:
            printf("You entered invalid characters :(");
    }
}