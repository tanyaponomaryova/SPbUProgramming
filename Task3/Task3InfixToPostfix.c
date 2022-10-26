#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../stack/stack.h"

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
    if (operation == ')')
    {
        return 3;
    }
    return -1; // не символ операции или скобка
}

int main()
{
    printf("Enter arithmetic expression in infix form: ");
    Stack* stackOfOperations = createStack();
    Stack* outputStack = createStack();
    for (char scannedSymbol = getchar(); scannedSymbol != '\n'; scannedSymbol = getchar())
    {
        if (scannedSymbol - '0' <= 9 && scannedSymbol - '0' >= 0) // проверяем что введенный символ это цифра
        {
            push(outputStack, scannedSymbol); // цифра в любом случае сразу отправляется в выходную строку
        }
        switch (scannedSymbol) {
            case '+':
            case '-':
            case '*':
            case '/':
            {
                while (!isEmpty(stackOfOperations))
                {
                    int topOfStack;
                    pop(stackOfOperations, &topOfStack); // достали верхушку
                    if (priority(scannedSymbol) <= priority((char)topOfStack)) // если введённая операция <= по приоритету достанной верхушки то верхушку кладём в выходную строку
                    {
                        push(outputStack, topOfStack); //положили верхушку в выходную строку
                    }
                    else // засунем верхушку обратно и выйдем из while
                    {
                        push(stackOfOperations, topOfStack);
                        break;
                    }
                }
                push(stackOfOperations, scannedSymbol); // когда введенный символ вытеснил тех кто >= его по приоритету он сам залез в стек
            break;
            }
            case '(':
                push(stackOfOperations, scannedSymbol);
                break;
            case ')':
            {
                int topOfStack;
                pop(stackOfOperations, &topOfStack); // достали верхний элемент из стека
                while (topOfStack != '(') // он открывающая скобка? нет - значит кладём его в выходную строку и достаём следующий из стека операций
                {
                    push(outputStack, topOfStack);
                    pop(stackOfOperations, &topOfStack);
                }
                break;
            }
        }
    }
    while(!isEmpty(stackOfOperations)) // достаём оставшиеся операции из стека операций
    {
        int topOfStack;
        pop(stackOfOperations, &topOfStack);
        push(outputStack, topOfStack);
    }
    // скопируем outputStack в строку, но в обратном порядке
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
    return 0;
}