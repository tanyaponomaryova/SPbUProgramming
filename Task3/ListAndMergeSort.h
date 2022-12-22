#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Ошибки: 0 - всё ок, -1 - указатель на null, -2 - ошибка выделения памяти

// Узел списка (содержит имя, номер, указатель на следующий узел)
typedef struct Entry Entry;

// Сам список (содержит длину, указатель на первый и последний элемент списка)
typedef struct List List;

// Создать список
int createList(List **ptrToListPtr);

// Добавить запись
int addEntry(List *listPtr, char *name, char *phone);

// Очистить список
void freeList(List *listPtr);

// Распечатать список
void printList(List *listPtr);

// Сортировка слиянием (принимает на вход адрес указателя на список и параметр сортировки (false - по номеру, true - по имени))
int mergeSort(List **listPtr, bool sortByName);