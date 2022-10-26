#include <stdio.h>
#include <stdbool.h>
#include "../stack/stack.h"

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

bool isStringBalanced()
{
    Stack* stackPtr = createStack();
    printf("Enter string to check brackets balance: ");
    for (char scannedSymbol = getchar(); scannedSymbol != '\n'; scannedSymbol = getchar())
    {
        switch (scannedSymbol)
        {
            case '(':
            case '{':
            case '[':
                push(stackPtr, scannedSymbol);
                break;
            case ')':
            case '}':
            case ']':
            {
                if (isEmpty(stackPtr)) // если пустой то точно нет пары для закрывающей скобки
                {
                    return false;
                }

                int topOfStack; // тип int потому что pop принимает на вход int*
                pop(stackPtr, &topOfStack);

                if (!isMatchingBrackets(topOfStack, scannedSymbol))
                {
                    return false;
                }
                break;
            }
        }
    }
    // все символы обработали и до сих пор не вернули результат
    bool isBalanced = isEmpty(stackPtr); //если пустой - значит баланс
    freeStack(stackPtr);
    return isBalanced; //ВЕЗДЕ ДОБАВИТЬ ФРИ СТЕК
}

int main()
{
    if (isStringBalanced())
    {
        printf("Entered string is balanced :) \n");
    }
    else
    {
        printf("Entered string is unbalanced :( \n");
    }
    return 0;
}