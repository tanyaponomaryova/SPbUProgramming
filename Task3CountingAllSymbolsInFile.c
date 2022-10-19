#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("This program shows frequencies of all symbols found in file input.txt!\n");
    FILE* file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file input.txt :(");
        return -1;
    }
    unsigned char arrayOfChars[256] = {};
    int arrayOfCounters[256] = {0};

    for (int i = 0; i < 256; i++)
    {
        arrayOfChars[i] = (unsigned char)i;
    }
    while(!feof(file))
    {
        unsigned char symbol = (unsigned char)fgetc(file);

        int codeOfSymbol = (int)symbol;
        arrayOfCounters[codeOfSymbol] += 1;

    }
    arrayOfCounters[255] = 0;

    for (int j = 0; j < 256; j++)
    {
        if (arrayOfCounters[j] != 0)
        {
            if (j == 10) // code of '\n'
            {
                printf("Symbol [new line] occured %d times in file.\n", arrayOfCounters[j]);
            }
            else if (j == 32) // code of ' '
            {
                printf("Symbol [space] occured %d times in file.\n", arrayOfCounters[j]);
            }
            else
            {
                printf("Symbol %c occured %d times in file.\n", arrayOfChars[j], arrayOfCounters[j]);
            }
        }
    }
    return 0;
}


