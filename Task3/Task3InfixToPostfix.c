#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../stack/stack.h"

#define STRING_LENGTH 100

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

Error convertToPostfix(char *infixExpression, char **postfixExpression)
{
    Stack *stackOfOperations = NULL;
    createStack(&stackOfOperations);
    Stack *outputStack = NULL;
    createStack(&outputStack);
    if (stackOfOperations == NULL || outputStack == NULL)
    {
        freeStack(outputStack);
        freeStack(stackOfOperations);
        return MemoryAllocationError;
    }
    Error errorCode = Ok;
    for (int i = 0; infixExpression[i] != '\n' && infixExpression[i] != '\0'; i++)
    {
        if (infixExpression[i] - '0' <= 9 && infixExpression[i] - '0' >= 0) // проверяем что введенный символ это цифра
        {
            errorCode = push(outputStack, infixExpression[i]); // цифра в любом случае сразу отправляется в выходную строку
            if (errorCode != Ok)
            {
                freeStack(outputStack);
                freeStack(stackOfOperations);
                return errorCode;
            }
        } else
        {
            switch (infixExpression[i])
            {
                case '+':
                case '-':
                case '*':
                case '/':
                {
                    while (!isEmptyOrNull(stackOfOperations))
                    {
                        int topOfStack = 0;
                        pop(stackOfOperations, &topOfStack); // достали верхушку
                        if (priority(infixExpression[i]) <= priority((char)topOfStack)) // если введённая операция <= по приоритету достанной верхушки, то верхушку кладём в выходную строку
                        {
                            errorCode = push(outputStack, topOfStack); //положили верхушку в выходную строку
                            if (errorCode != Ok)
                            {
                                freeStack(outputStack);
                                freeStack(stackOfOperations);
                                return errorCode;
                            }
                        } else // засунем верхушку обратно и выйдем из while
                        {
                            errorCode = push(stackOfOperations, topOfStack);
                            if (errorCode != Ok)
                            {
                                freeStack(outputStack);
                                freeStack(stackOfOperations);
                                return errorCode;
                            }
                            break;
                        }
                    }
                    errorCode = push(stackOfOperations, infixExpression[i]); // когда введенный символ вытеснил тех кто >= его по приоритету он сам залез в стек
                    if (errorCode != Ok)
                    {
                        freeStack(outputStack);
                        freeStack(stackOfOperations);
                        return errorCode;
                    }
                    break;
                }
                case '(':
                {
                    errorCode = push(stackOfOperations, infixExpression[i]);
                    if (errorCode != Ok)
                    {
                        freeStack(outputStack);
                        freeStack(stackOfOperations);
                        return errorCode;
                    }
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
                        errorCode = push(outputStack, topOfStack);
                        if (errorCode != Ok)
                        {
                            freeStack(outputStack);
                            freeStack(stackOfOperations);
                            return errorCode;
                        }
                        pop(stackOfOperations, &topOfStack);
                    }
                    break;
                }
                default: // любой другой символ кроме цифр, знаков операций, скобок и пробела
                {
                    if (infixExpression[i] != ' ')
                    {
                        freeStack(outputStack);
                        freeStack(stackOfOperations);
                        return IncorrectInput;
                    }
                }
            }
        }
    }
    while (!isEmptyOrNull(stackOfOperations)) // достаём оставшиеся операции из стека операций
    {
        int topOfStack = 0;
        pop(stackOfOperations, &topOfStack);
        if (topOfStack == '(') // если осталась открывающая скобка, значит для неё не хватило закрывающей
        {
            freeStack(outputStack);
            freeStack(stackOfOperations);
            return UnbalancedBrackets;
        }
        errorCode = push(outputStack, topOfStack);
        if (errorCode != Ok)
        {
            freeStack(outputStack);
            freeStack(stackOfOperations);
            return errorCode;
        }
    } // скопируем outputStack в строку postfixExpression, но в обратном порядке
    int length = 0;
    lengthOfStack(outputStack, &length);
    *postfixExpression = calloc(length * 2 + 1, sizeof(char));
    if (*postfixExpression == NULL)
    {
        return MemoryAllocationError;
    }
    for (int i = length * 2 - 1; i >= 0; i -= 2)
    {
        int topOfStack = 0;
        pop(outputStack, &topOfStack);
        (*postfixExpression)[i - 1] = (char) topOfStack;
        (*postfixExpression)[i] = ' ';
    }
    (*postfixExpression)[length * 2] = '\0';
    freeStack(outputStack);
    freeStack(stackOfOperations);
    return Ok;
}

bool test()
{
    char* infixExpression = "(1 + 1) * 2";
    char* postfixExpression = NULL;
    Error errorCode = convertToPostfix(infixExpression, &postfixExpression);
    if (errorCode != Ok)
    {
        free(postfixExpression);
        return false;
    }
    if (!strcmp(postfixExpression, "1 1 + 2 * "))
    {
        free(postfixExpression);
        return true;
    }
    return false;
}

int main()
{
    if (!test())
    {
        printf("Test is failed :(");
        return -1;
    }
    printf("Enter arithmetic expression in infix form to convert it to postfix form (no more than %d characters long): ", STRING_LENGTH);
    char infixExpression[STRING_LENGTH] = {0};
    fgets(infixExpression, STRING_LENGTH + 1, stdin);
    char *postfixExpression = NULL;
    Error errorCode = convertToPostfix(infixExpression, &postfixExpression);
    switch (errorCode)
    {
        case Ok:
            printf("Postfix expression: %s", postfixExpression);
            break;
        case MemoryAllocationError:
            printf("Memory allocation error :(");
            break;
        case UnbalancedBrackets:
            printf("Brackets are unbalanced in entered expression :(");
            break;
        case IncorrectInput:
            printf("You entered invalid characters :(");
    }
    free(postfixExpression);
    return 0;
}