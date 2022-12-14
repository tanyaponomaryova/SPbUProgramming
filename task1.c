#include <stdio.h>
#include <stdbool.h>
#define BUFFER_SIZE 1000

int main()
{
    printf("This program counts total cost of order in file order.txt \n");
    printf("(file should not contain empty lines, there should be no spaces in price and amount of product) \n");
    FILE* file = fopen("order.txt", "r");
    if (file == NULL)
    {
        printf("Error opening order.txt.");
        return -1;
    }
    int totalCost = 0;
    char curString[BUFFER_SIZE] = {0};
    bool isStringRead = fgets(curString, BUFFER_SIZE, file);
    int stringNumber = 1;
    while (isStringRead)
    {
        int i = 0;
        int j = 0;
        int k = 0;
        int amount = 0;
        int price = 0;
        for (i = 0; curString[i] != '\t' && curString[i] != '\0'; i++);
        if (i == 0 && curString[i] != '\0' || i != 0 && curString[i] == '\0') // нет наименования, или только наименование, или пустая строка
        {
            printf("Incorrect structure of input file in %d string. :(", stringNumber);
            return -1;
        }
        if (i != 0 && curString[i] != '\0')
        {
            for (j = i + 1; curString[j] != '\t' && curString[j] != '\0'; j++)
            {
                if (curString[j] <= '9' && curString[j] >= '0')
                {
                    amount = amount * 10 + (int)curString[j] - (int)'0';
                }
                else
                {
                    printf("Incorrect structure of input file in %d string. :(", stringNumber);
                    return  -1;
                }
            }
            if (j == i + 1 || curString[j] == '\0')
            {
                printf("Incorrect structure of input file in %d string. :(", stringNumber);
                return -1;
            }
            for (k = j + 1; curString[k] != '\0' && curString[k] != '\n'; k++)
            {
                if (curString[k] <= '9' && curString[k] >= '0')
                {
                    price = price * 10 + (int)curString[k] - (int)'0';
                }
                else
                {
                    printf("Incorrect structure of input file in %d string. :(", stringNumber);
                    return  -1;
                }
            }
            if (k == j + 1)
            {
                printf("Incorrect structure of input file in %d string. :(", stringNumber);
                return -1;
            }
            totalCost += amount * price;
        }
        isStringRead = fgets(curString, BUFFER_SIZE, file);
        stringNumber++;
    }
    fclose(file);
    printf("Total cost of order: %d", totalCost);
    return 0;
}