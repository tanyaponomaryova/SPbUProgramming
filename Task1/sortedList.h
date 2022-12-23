#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Структура сортированный список (содержит указатель на первый элемент списка)
typedef struct List List;

// Создать список
// Ошибки: 0 - всё ок, -2 - ошибка выделения памяти
int createList(List** ptrToListPtr);

// Добавить значение в список
// Ошибки: 0 - всё ок, -1 - указатель на список null, -2 - ошибка выделения памяти
int addToList(List* listPtr, int value);

// Удалить значение из списка
// Ошибки: -1 - указатель null, 0 - значение не найдено в списке, 1 - значение найдено и удалено из списка
int deleteValue(List* listPtr, int value);

// Распечатать список
void printList(List* listPtr);

// Удалить список
void freeList(List* listPtr);