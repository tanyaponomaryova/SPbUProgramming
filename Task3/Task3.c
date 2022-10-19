#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BASESIZE 100
#define LEN 100

typedef struct
{
    char name[LEN];
    char phone[LEN];
} Entry;

int readAndCountEntriesFromFile(Entry arrayOfEntries[], char* filename)
{
    int entriesCounter = 0;
    FILE* file = fopen(filename, "a+");
    if (file == NULL)
    {
        return -1;
    }
    while (!feof(file))
    {
        if ((fscanf(file, "%s", arrayOfEntries[entriesCounter].name) != EOF))
        {
            fscanf(file, "%s", arrayOfEntries[entriesCounter].phone);
            entriesCounter++;
        }
    }
    fclose(file);
    return entriesCounter;
}

void begin()
{
    printf("\nEnter: \n 0 - to exit \n");
    printf(" 1 - to add entry (name and phone number) \n");
    printf(" 2 - to print all entries \n");
    printf(" 3 - to find phone number by name \n");
    printf(" 4 - to find name by phone number \n");
    printf(" 5 - save current data to file\n");
}

void addEntry(Entry arrayOfEntries[], int* entriesCounter)
{
    if (*entriesCounter == BASESIZE)
    {
        printf("There's no room for new entries in the database! \n");
    }
    else
    {
        printf("Enter name (without spaces): ");
        scanf("%s", &(arrayOfEntries[*entriesCounter].name));
        printf("Enter phone (without spaces): ");
        scanf("%s", &(arrayOfEntries[*entriesCounter].phone));

        (*entriesCounter)++;

        printf("Entry created! \n");
    }
}

void printAllEntries(Entry arrayOfEntries[], int entriesCounter)
{
    if (entriesCounter == 0)
    {
        printf("There's no entries in the database :0 \n");
    }
    else
    {
        for (int i = 0; i < entriesCounter; i++)
        {
            printf("%s %s \n", arrayOfEntries[i].name, arrayOfEntries[i].phone);
        }
    }
}

void findPhone(Entry arrayOfEntries[], int entriesCounter)
{
    printf("To find phone by name enter name (without spaces):");
    char name[LEN] = "";
    scanf("%s", name);

    bool isFound = false;
    for (int i = 0; i < entriesCounter; ++i)
    {
        if (strcmp(arrayOfEntries[i].name, name) == 0)
        {
            if (isFound == false)
            {
                printf("Entries found by name: \n");
            }
            printf("%s %s\n", arrayOfEntries[i].name, arrayOfEntries[i].phone);
            isFound = true;
        }
    }
    if (isFound == false)
    {
        printf("No entries found :( \n");
    }
}

void findName(Entry arrayOfEntries[], int entriesCounter)
{
    printf("To find name by phone enter phone number (without spaces):");
    char phone[LEN] = "";
    scanf("%s", phone);

    bool isFound = false;
    for (int i = 0; i < entriesCounter; ++i)
    {
        if (strcmp(arrayOfEntries[i].phone, phone) == 0)
        {
            if (isFound == false)
            {
                printf("Entries found by phone: \n");
            }
            printf("%s %s\n", arrayOfEntries[i].name, arrayOfEntries[i].phone);
            isFound = true;
        }
    }
    if (isFound == false)
    {
        printf("No entries found :( \n");
    }
}

void saveData(Entry arrayOfEntries[], int entriesCounter, char* filename)
{
    if (entriesCounter == 0)
    {
        printf("There's no entries to save :0");
        return;
    }
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file for saving data :( \n");
        return;
    }
    for (int i = 0; i < entriesCounter; i++)
    {
        fprintf(file, "%s %s \n", arrayOfEntries[i].name, arrayOfEntries[i].phone);
    }
    fclose(file);
    printf("Data saved! \n");
}

int main() {
    printf("Welcome to the Phonebook!");
    Entry* base = calloc(BASESIZE, sizeof(Entry));

    int entriesCounter = 0;

    entriesCounter = readAndCountEntriesFromFile(base, "database.txt");
    if (entriesCounter == -1)
    {
        printf("Error opening file :(");
        return -1;
    }
    bool shouldGoOut = false;
    while (!shouldGoOut)
    {
        begin();

        int input = 0;
        int scanned = scanf("%d", &input);
        while (scanned == 0 || input < 0 || input > 5)
        {
            scanf("%*[^\n]");
            printf("Incorrect input, try again: ");
            scanned = scanf("%d", &input);
        }

        if (input == 0)
        {
            shouldGoOut = true;
        }
        if (input == 1)
        {
            addEntry(base, &entriesCounter);
        }
        if (input == 2)
        {
            printAllEntries(base, entriesCounter);
        }
        if (input == 3)
        {
            findPhone(base, entriesCounter);
        }
        if (input == 4)
        {
            findName(base, entriesCounter);
        }
        if (input == 5)
        {
            saveData(base, entriesCounter, "database.txt");
        }
    }
    return 0;
}
