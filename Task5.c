#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getString()
{
    int strLength = 0;
    int strCapacity = 1; // place for '\0' 
    char* string = malloc(sizeof(char));
    char scannedChar = getchar();
    while (scannedChar != '\n')
    {
        string[strLength] = scannedChar;
        strLength++;
        if (strLength >= strCapacity)
        {
            strCapacity *= 2;
            string = realloc(string, strCapacity * sizeof(char));
        }
        scannedChar = getchar();
    }
    string[strLength] = '\0';
    return string;
}

int bracketsType(char bracket1, int bracket2)
{
    if (bracket1 == '(' && bracket2 == ')')
        return 1;
    if (bracket1 == '{' && bracket2 == '}')
        return 1;
    if (bracket1 == '[' && bracket2 == ']')
        return 1;
    if (bracket1 == '<' && bracket2 == '>')
        return 1;
    return 0;
}

int main()
{
    printf("Enter string to check balance of brackets: ");
    char* string = getString();
    int strLength = strlen(string);
    char* scannedBrackets = malloc((strLength + 1) * sizeof(char));
    if (scannedBrackets == NULL)
    {
        printf("Error allocating memory for array");
        free(string);
        return -1;
    }
    int pointer = 1;
    scannedBrackets[0] = 'w'; //random character in case there are more closing brackets than opening ones
    int flag = 1;
    for (int i = 0; i < strLength; i++)
    {
        if (string[i] == '(' || string[i] == '[' || string[i] == '{' || string[i] == '<')
        {
            scannedBrackets[pointer + 1] = string[i];
            pointer++;
        }
        else if (string[i] == ')' || string[i] == ']' || string[i] == '}' || string[i] == '>')
        {
            if (bracketsType(scannedBrackets[pointer], string[i]))
                pointer--;
            else 
            {
                flag = 0;
                break;
            }
        }
    }
    if (flag == 0 || pointer > 1)
        printf("Entered string is unbalanced with brackets");
    else
        printf("Entered string is balanced with brackets");
    return 0;
}