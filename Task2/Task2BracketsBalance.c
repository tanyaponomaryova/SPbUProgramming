#include <stdio.h>
#include <stdbool.h>
#include "../stack/stack.h"

#define STRING_LENGTH 100

typedef enum Error
{
    MemoryAllocationError,
    Balanced,
    Unbalanced
} Error;

bool isMatchingBrackets(char openingBracket, char closingBracket)
{
    return openingBracket == '(' && closingBracket == ')' ||
           openingBracket == '{' && closingBracket == '}' ||
           openingBracket == '[' && closingBracket == ']';
}

Error isStringBalanced(char *string)
{
    Stack *stackPtr = NULL;
    createStack(&stackPtr);
    if (stackPtr == NULL)
    {
        return MemoryAllocationError;
    }
    for (int i = 0; string[i] != '\0'; i++)
    {
        switch (string[i])
        {
            case '(':
            case '{':
            case '[':
            {
                int errorCode = push(stackPtr, string[i]);
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
                int topOfStack = 0;
                pop(stackPtr, &topOfStack);
                if (!isMatchingBrackets((char) topOfStack, string[i]))
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

bool test()
{
    char *string1 = "{}((hello))[wo],({rld})!";
    char *string2 = "{}((hello)[wo],(rld})!";
    Error result1 = isStringBalanced(string1);
    Error result2 = isStringBalanced(string2);
    return result1 == Balanced && result2 == Unbalanced;
}

int main()
{
    if (!test())
    {
        printf("Test is failed :(");
        return -1;
    }
    printf("Enter string to check brackets balance: ");
    char string[STRING_LENGTH] = {0};
    scanf("%s", string);
    Error result = isStringBalanced(string);
    if (result == Balanced)
    {
        printf("Entered string is balanced :)");
    } else if (result == Unbalanced)
    {
        printf("Entered string is unbalanced :(");
    } else
    {
        printf("Memory allocation error :0");
    }
    return 0;
}