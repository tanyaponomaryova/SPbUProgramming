#include <stdio.h>
int isSameTypeBrackets(char bracket1, int bracket2)
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
    printf("Enter string(no more than 100 symbols): \a");
    char string[100];
    int pointer = 1;
    char scannedBrackets[101];
    scannedBrackets[0] = 'w';
    scanf("%s", string);
    int flag = 1;
    for (int i = 0; i < 100; i++)
    {
        if (string[i] == '(' || string[i] == '[' || string[i] == '{' || string[i] == '<')
        {
            scannedBrackets[pointer+1] = string[i];
            pointer++;
        }
        else if (string[i] == ')' || string[i] == ']' || string[i] == '}' || string[i] == '>')
        {
            if (isSameTypeBrackets(scannedBrackets[pointer], string[i]))
                pointer--;
            else 
            {
                flag = 0;
                break;
            }
        }
        else
            continue;
    }
    if (flag == 0 || pointer > 1)
        printf("Unbalanced");
    else
        printf("Balanced");
}