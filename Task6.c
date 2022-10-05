#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    printf("This program counts number of occurrences of substring S1 in string S. \n");

    printf("Enter length of S (natural number): ");
    int lengths = 0;
    int scanned = scanf("%d", &lengths);
    while (scanned == 0 || lengths <= 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a correct number, try again: ");
        scanned = scanf("%d", &lengths);
    }
    char* s = calloc(lengths, sizeof(char));
    if (s == NULL)
    {
        printf("Error allocating memory for string");
        return -1;
    }
    printf("Enter S: ");
    scanf("%s", s);

    printf("Enter length of S1 (natural number): ");
    int lengths1 = 0;
    scanned = scanf("%d", &lengths1);
    while (scanned == 0 || lengths1 <= 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a correct number, try again: ");
        scanned = scanf("%d", &lengths1);
    }
    char* s1 = calloc(lengths1, sizeof(char));
    if (s1 == NULL)
    {
        printf("Error allocating memory for string");
        return -1;
    }
    printf("Enter S1: ");
    scanf("%s", s1);

    int counter = 0;
    for (int i = 0; i < lengths - lengths1 + 1; i++)
    {
        for (int j = 0; j < lengths1; j++)
        {
            if (s[i + j] != s1[j])
                break;
            else if (j == lengths1 - 1)
                counter++;
        }
    }
    printf("Substring S1 occurs %d times in string S.", counter);
    return 0;
}