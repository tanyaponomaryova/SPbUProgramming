#include <stdio.h>
#include <stdbool.h>

int changeState(char symbol, int previousState)
{
    switch (previousState)
    {
        case 0:
            if (symbol >= 'A' && symbol <= 'Z' || symbol >= 'a' && symbol <= 'z')
            {
                return 1;
            }
            return 2;
        case 1:
            if (symbol >= 'A' && symbol <= 'Z' || symbol >= 'a' && symbol <= 'z' || symbol == '_' ||
                symbol >= '0' && symbol <= '9')
            {
                return 1;
            }
            return 2;
    }
}

int main()
{
    printf("Enter a string to check if it matches a regular expression [A-Za-z]([A-Za-z]|[0-9]|_)* : ");
    int currentState = 0;
    bool isStringCorrect = true;
    char currentChar = getchar();
    while (currentChar != '\n')
    {
        currentState = changeState(currentChar, currentState);
        if (currentState == 2)
        {
            isStringCorrect = false;
        }
        currentChar = getchar();
    }
    if (currentState == 0)
    {
        isStringCorrect = false;
    }
    if (isStringCorrect)
    {
        printf("String matches a regular expression.");
    } else
    {
        printf("String does not match a regular expression.");
    }
    return 0;
}
