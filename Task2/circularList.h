#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>

// Структура циклический список (содержит указатели на элемент, который добавили первым, и на элемент, который добавили последним)
typedef struct List List;

// Создать список
// Ошибки: 0 - всё ок, -2 - ошибка выделения памяти под список
int createList(List **ptrToListPtr);

// Список пуст или нулевой указатель
bool isListEmptyOrNull(List *listPtr);

// Список не нулевой указатель, не пуст и в нём ровно один элемент
bool isSingleNodeInList(List *listPtr);

// Кладёт значение первого элемента списка по данному адресу
// Ошибки: 0 - всё ок, -1 - даны нулевые указатели или список пуст
int headOfList(List *listPtr, int *valuePtr);

// Добавить значение в список
// Ошибки: 0 - всё ок, -1 - дан нулевой указатель на список, -2 - ошибка выделения памяти для нового элемента
int addToList(List *listPtr, int value);

// Удалить значение на определенной позиции из списка
int deleteValueFromList(List *listPtr, int position);

// Удалить список
void freeList(List *listPtr);

// Распечатать список
void printList(List *listPtr);