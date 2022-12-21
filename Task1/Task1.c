#include <stdio.h>
#define LENGTH_OF_BIN_NUMBER 256

int main()
{
    printf("Enter positive binary integer to convert it to octal integer: ");
    char binNumber[LENGTH_OF_BIN_NUMBER + 1] = {0}; // + 1 для '\0'
    int octalNumber[LENGTH_OF_BIN_NUMBER] = {0}; // длина восьмеричного числа точно не больше длины двоичного
    scanf("%s", binNumber);
    int lengthOfBinNumber = 0;
    for (lengthOfBinNumber; binNumber[lengthOfBinNumber] != '\0'; lengthOfBinNumber++)
    {
        if (binNumber[lengthOfBinNumber] != '1' && binNumber[lengthOfBinNumber] != '0')
        {
            printf("Incorrect input (positive binary number must contain only 0 and 1)");
            return -1;
        }
    }
    int lengthOfOctalNumber = 0;
    for (int i = lengthOfBinNumber - 1; i >= 2; i -= 3) // считываем по три разряда с конца в двоичном числе
    {
        octalNumber[lengthOfOctalNumber] = binNumber[i] - '0' + (binNumber[i-1] - '0') * 2 + (binNumber[i - 2] - '0') * 4;
        lengthOfOctalNumber++;
    }
    if (lengthOfBinNumber % 3 != 0) // если в начале остались разряды
    {
        for (int i = 0; i < lengthOfBinNumber % 3; i++)
        {
            octalNumber[lengthOfOctalNumber] = octalNumber[lengthOfOctalNumber] * 2 + binNumber[i] - '0';
        }
        lengthOfOctalNumber++;
    }
    printf("Octal representation of entered number: ");
    for (int i = lengthOfOctalNumber - 1; i >= 0; i--)
    {
        printf("%d", octalNumber[i]);
    }
    return 0;
}
