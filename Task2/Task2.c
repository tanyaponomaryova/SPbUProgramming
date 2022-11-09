#include <stdio.h>
#include "tree.h"
#define LEN 1000

int main()
{
    FILE* file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("File input.txt not found :(");
        return -1;
    }
    char impression[LEN] = {0};
    fgets(impression, LEN, file);
    printf("%s", impression);
    fclose(file);
    Tree* treePtr = NULL;
    int errorCode = build(&treePtr, impression);
    if (errorCode != 0)
    {
        return errorCode;
    }
    int resultOfCalculation = 0;
    calculate(treePtr, &resultOfCalculation);
    printf("Impression from file: ");
    printTree(treePtr);
    printf("Result of calculation: %d", resultOfCalculation);
    return 0;
}
