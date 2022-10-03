#include <stdio.h>
#include <string.h>
int main()
{
    char s[1000];
    char s1[1000];
    int counter = 0;
    printf("Enter S (no more than 1000 symbols): ");
    scanf("%s", s);
    printf("Enter S1 (no more than 1000 symbols): ");
    scanf("%s", s1);
    int lengths = strlen(s);
    int lengths1 = strlen(s1);
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