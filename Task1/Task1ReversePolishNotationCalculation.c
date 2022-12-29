#include <stdio.h>
#include <stdbool.h>
#include "../stack/stack.h"

#define STRING_LENGTH 100

typedef enum Error // ошибки выполнения функции calculateInReversePolishNotation
{
    Ok,
    MemoryAllocationError,
    InvalidCharacters,
    DivisionByZero,
    LackOfOperands,
    LackOfOperationSigns
} Error;

int performArithmeticOperation(int operand1, int operand2, char operation)
{
    int result = 0;
    switch (operation)
    {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            result = operand1 / operand2;
    }
    return result;
}

Error calculateInReversePolishNotation(char *postfixExpression, int *resultPtr)
{
    Stack *stackPtr = NULL;
    int errorCode = createStack(&stackPtr);
    if (errorCode != 0)
    {
        return MemoryAllocationError;
    }
    for (int i = 0; postfixExpression[i] != '\n' && postfixExpression[i] != '\0'; i++)
    {
        if (postfixExpression[i] - '0' <= 9 && postfixExpression[i] - '0' >= 0) // проверка, что прочитанный символ это символ цифры: коды цифр в аски - это 48-57
        {
            errorCode = push(stackPtr, (int) (postfixExpression[i] - '0')); // добавили int в стек
            if (errorCode != 0)
            {
                freeStack(stackPtr);
                return errorCode;
            }
        } else if (postfixExpression[i] == '+' || postfixExpression[i] == '-' || postfixExpression[i] == '*' ||
                   postfixExpression[i] == '/')
        {
            if (isEmptyOrNull(stackPtr)) // в стеке нет цифр, над которыми можно было бы провести введенную операцию
            {
                freeStack(stackPtr);
                return LackOfOperands;
            }
            int operand1 = 0;
            int operand2 = 0;
            errorCode = pop(stackPtr, &operand2);
            if (errorCode != 0)
            {
                freeStack(stackPtr);
                return errorCode;
            }
            if (isEmptyOrNull(stackPtr))
            {
                freeStack(stackPtr);
                return LackOfOperands;
            }
            errorCode = pop(stackPtr, &operand1);
            if (errorCode != 0)
            {
                freeStack(stackPtr);
                return errorCode;
            }
            if (postfixExpression[i] == '/' && operand2 == 0) // проверка, что не происходит деление на ноль
            {
                freeStack(stackPtr);
                return DivisionByZero;
            }
            errorCode = push(stackPtr, performArithmeticOperation(operand1, operand2, postfixExpression[i]));
            if (errorCode != 0)
            {
                freeStack(stackPtr);
                return errorCode;
            }
        } else if (postfixExpression[i] != ' ')// текущий символ - это не цифра, не знак операции, не пробел
        {
            freeStack(stackPtr);
            return InvalidCharacters;
        }
    }
    errorCode = pop(stackPtr, resultPtr);
    if (errorCode != 0)
    {
        freeStack(stackPtr);
        return errorCode;
    }
    if (!isEmptyOrNull(stackPtr)) // если после того, как мы достали вершину стека, в нем ещё что-то осталось
    {
        freeStack(stackPtr);
        return LackOfOperationSigns;
    }
    freeStack(stackPtr);
    return Ok;
}

bool test()
{
    char *postfixExpression = "9 6 - 1 2 + * ";
    int result = 0;
    int errorCode = calculateInReversePolishNotation(postfixExpression, &result);
    if (errorCode != 0)
    {
        return false;
    }
    return result == 9;
}

int main()
{
    if (!test())
    {
        printf("Test failed :(");
        return -1;
    }
    printf("Enter postfix expression (no more than %d characters long): ", STRING_LENGTH);
    char postfixExpression[STRING_LENGTH] = {0};
    fgets(postfixExpression, STRING_LENGTH + 1, stdin);
    int result = 0;
    Error errorType = calculateInReversePolishNotation(postfixExpression, &result);
    switch (errorType)
    {
        case MemoryAllocationError:
            printf("Memory allocation error :(");
            break;
        case InvalidCharacters:
            printf("You entered invalid characters :(");
            break;
        case DivisionByZero:
            printf("You can't divide by zero :(");
            break;
        case LackOfOperands:
            printf("You entered not enough numbers :(");
            break;
        case LackOfOperationSigns:
            printf("You entered not enough operation signs :(");
            break;
        case Ok:
            printf("Result of calculation: %d :)", result);
    }
    return 0;
}