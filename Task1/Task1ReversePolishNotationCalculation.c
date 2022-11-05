#include <stdio.h>
#include <stdbool.h>
#include "../stack/stack.h"

typedef enum Error // ошибки выполнения функции calculateInReversePolishNotation
{
    Ok,
    MemoryAllocationError,
    InvalidCharacters,
    DivisionByZero,
    LackOfOperands,
    LackOfOperationSigns
} Error;

void performArithmeticOperation(Stack* stackPtr, char operation)
{
    int operand2 = 0;
    int operand1 = 0;
    int result = 0;
    pop(stackPtr, &operand2);
    pop(stackPtr, &operand1);
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
    push(stackPtr, result);
}

Error calculateInReversePolishNotation(int* resultPtr)
{
    Stack* stackPtr = NULL;
    bool isCreated = !createStack(&stackPtr);
    if (!isCreated)
    {
        return MemoryAllocationError;
    }
    printf("Enter postfix expression: ");
    for (char scannedSymbol = getchar(); scannedSymbol != '\n'; scannedSymbol = getchar())
    {
        if (scannedSymbol - '0' <= 9 && scannedSymbol - '0' >= 0) // проверка, что прочитанный символ это символ цифры: коды цифр в аски - это 48-57
        {
            push(stackPtr, (int)(scannedSymbol - '0')); // добавили int в стек
        }
        else if (scannedSymbol == '+' || scannedSymbol == '-' || scannedSymbol == '*' || scannedSymbol == '/')
        {
            if (isEmptyOrNull(stackPtr)) // в стеке нет цифр, над которыми можно было бы провести введенную операцию
            {
                freeStack(stackPtr);
                return LackOfOperands;
            }
            int topValue = 0;
            pop(stackPtr, &topValue); // достали вершину
            if (isEmptyOrNull(stackPtr)) // проверка, что стек не пуст после того, как мы достали вершину (то есть там хотя бы две цифры)
            {
                freeStack(stackPtr);
                return LackOfOperands;
            }
            if ((scannedSymbol == '/' && topValue == 0)) // проверка, что не происходит деление на ноль
            {
                freeStack(stackPtr);
                return DivisionByZero;
            }
            push(stackPtr, topValue); // положили вершину обратно
            performArithmeticOperation(stackPtr, scannedSymbol);
        }
        else // прочитанный символ - это не цифра и не знак операции
        {
            freeStack(stackPtr);
            return InvalidCharacters;
        }
    }
    pop(stackPtr, resultPtr);
    if (!isEmptyOrNull(stackPtr)) // если после того, как мы достали вершину стека, в нем ещё что-то осталось
    {
        freeStack(stackPtr);
        return LackOfOperationSigns;
    }
    freeStack(stackPtr);
    return Ok;
}

int main()
{
    int result = 0;
    Error errorType = calculateInReversePolishNotation(&result);
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