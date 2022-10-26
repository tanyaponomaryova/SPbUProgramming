#include <stdio.h>
#include <stdlib.h>
#include "../stack/stack.h"

void performArithmeticOperation(Stack* stackPtr, char operation)
{
    int operand2 = 0;
    int operand1 = 0;
    int result = 0;
    pop(stackPtr,&operand2);
    pop(stackPtr,&operand1);
    if (operation == '+')
    {
        result = operand1 + operand2;
    }
    else if (operation == '-')
    {
        result = operand1 - operand2;
    }
    else if (operation == '*')
    {
        result = operand1 * operand2;
    }
    else if (operation == '/')
    {
        result = operand1 / operand2;
    }
    push(stackPtr, result);
}

int main()
{
    Stack* stackPtr = createStack();
    printf("Enter postfix expression: ");
    for (char scannedSymbol = getchar(); scannedSymbol != '\n'; scannedSymbol = getchar())
    {
        if (scannedSymbol - '0' <= 9 && scannedSymbol - '0' >= 0) // проверка что прочитанный символ это символ цифры: коды цифр в аски - это 48-57
        {
            push(stackPtr, scannedSymbol - '0'); // добавили int
        }
        else if (scannedSymbol == '+' || scannedSymbol == '-' || scannedSymbol == '*' || scannedSymbol == '/')
        {
            performArithmeticOperation(stackPtr, scannedSymbol);
        }
        // в других случаях просто прочитали символ и проигнорировали его
    }
    // выводим ответ
    int result = 0;
    top(stackPtr, &result);
    printf("%d", result);
    return 0;
}
