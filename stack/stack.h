#pragma once

typedef struct Stack Stack; // структура которая содержит только адрес последнего элемента стэка

Stack* createStack();

int push(Stack* stackAdress, int value); // добавляет элемент в стек

int isEmpty(Stack* stackAdress);

int top(Stack* stackAdress, int* value); // принимает адрес стека и адрес переменной куда положить значение с верхушки стека

int pop(Stack* stackAdress, int* value); // кладет в даваемый адрес значение последнего элемета стека а из самого стека удаляет последний элемент

int printStack(Stack* stackAdress);

int lengthOfStack(Stack* stackAdress, int* lengthAdress);

int freeStack(Stack* stackAdress);


