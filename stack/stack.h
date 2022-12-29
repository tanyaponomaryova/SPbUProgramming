#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Коды ошибок: 0 - ок, -1 - ошибка выделения памяти, -2 - аргумент функции NULL

// Структура стек
typedef struct Stack Stack;

// Создание стека, функция принимает указатель на указатель на стек
int createStack(Stack** stackPtrPtr);

// Добавление нового элемента на вершину стека, функция принимает указатель на стек и значение элемента
int push(Stack* stackPtr, int value);

//Показывает, какой элемент на вершине стека, функция принимает адрес стека и адрес переменной, куда положить значение с вершины
int top(Stack* stackPtr, int* value);

// Удаляет элемент с вершины стека и кладёт его значение в переменную value, функция принимает указатель на стек и адрес value
int pop(Stack* stackPtr, int* value);

// Распечатать стек, функция принимает адрес стека
int printStack(Stack* stackPtr);

// Длина стека, функция принимает адрес стека и адрес переменной, куда положить длину
int lengthOfStack(Stack* stackPtr, int* lengthPtr);

// Удаление стека, функция принимает адрес стека
void freeStack(Stack* stackPtr);

// Проверка стек пустой или NULL, функция принимает указатель на стек
bool isEmptyOrNull(Stack* stackPtr);



