#include <stdio.h>
#include <stdbool.h>
#include "../stack/stack.h"

typedef enum Error
{
    MemoryAllocationError,
    Balanced,
    Unbalanced
} Error;

bool isMatchingBrackets(char openingBracket, char closingBracket)
{
    if (openingBracket == '(' && closingBracket == ')')
        return true;
    if (openingBracket == '{' && closingBracket == '}')
        return true;
    if (openingBracket == '[' && closingBracket == ']')
        return true;
    return false;
}

Error isStringBalanced()
{
    Stack* stackPtr = NULL;
    createStack(&stackPtr);
    if (stackPtr == NULL)
    {
        return MemoryAllocationError;
    }
    printf("Enter string to check brackets balance: ");
    for (char scannedSymbol = getchar(); scannedSymbol != '\n'; scannedSymbol = getchar())
    {
        switch (scannedSymbol)
        {
            case '(':
            case '{':
            case '[':
            {
                int errorCode = push(stackPtr, scannedSymbol);
                if (errorCode == -1)
                {
                    freeStack(stackPtr);
                    return MemoryAllocationError;
                }
                break;
            }
            case ')':
            case '}':
            case ']':
            {
                if (isEmptyOrNull(stackPtr)) // если пустой, то точно нет пары для закрывающей скобки
                {
                    freeStack(stackPtr);
                    return Unbalanced;
                }
                int topOfStack;
                pop(stackPtr, &topOfStack);
                if (!isMatchingBrackets((char)topOfStack, scannedSymbol))
                {
                    freeStack(stackPtr);
                    return Unbalanced;
                }
                break;
            } // если любой другой символ, то его просто игнорируем
        }
    } // все символы обработали и до сих пор не вернули результат
    if (isEmptyOrNull(stackPtr)) // если стек пустой - баланс, если в нём остались ещё какие-то скобки - не баланс
    {
        freeStack(stackPtr);
        return Balanced;
    }
    freeStack(stackPtr);
    return Unbalanced;
}

int main()
{
    Error result = isStringBalanced();
    if (result == Balanced)
    {
        printf("Entered string is balanced :)");
    }
    else if (result == Unbalanced)
    {
        printf("Entered string is unbalanced :(");
    }
    else
    {
        printf("Memory allocation error :0");
    }
    return 0;
}