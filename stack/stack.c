#include <stdio.h>
#include <stdlib.h>
#include "../stack/stack.h"

typedef struct StackElement
{
    int value;
    struct StackElement* nextElementAdress; // адрес на следующую структуру StackElement
} StackElement;

typedef struct Stack // структура которая содержит только адрес последнего элемента стэка
{
    StackElement* lastElementAdress;
} Stack;

Stack* createStack() // возвращает адрес структуры стек в которой пока только NULL адрес на последний элемент
{
    return (Stack*)calloc(1, sizeof(Stack));
}
int push(Stack* stackAdress, int value) // добавляет элемент в стек
{
    if (stackAdress == NULL)
    {
        return -1;
    }
    StackElement* newElementAdress = calloc(1, sizeof(StackElement)); // адрес на новый элемент стека
    if (newElementAdress == NULL) // не удалось аллоцировать память для нового элемента
    {
        return -2;
    }
    newElementAdress->nextElementAdress = stackAdress->lastElementAdress;
    newElementAdress->value = value;
    stackAdress->lastElementAdress = newElementAdress;
    return 0;
}

int isEmpty(Stack* stackAdress)
{
    if (stackAdress == NULL)
    {
        return -1;
    }
    return (stackAdress->lastElementAdress == NULL); // если в стеке последний элемент ни на что не указывает значит он пуст - вернётся число отличное от нуля, иначе 0
}

int top(Stack* stackAdress, int* value) //принимает адрес стека и адрес переменной куда положить значение с верхушки стека
{
    if (stackAdress == NULL || isEmpty(stackAdress) || value == NULL)
    {
        return -1;
    }
    *value = stackAdress->lastElementAdress->value;

    return 0;
}

int pop(Stack* stackAdress, int* value) //кладет в даваемый адрес значение последнего элемета стека а из самого стека удаляет последний элемент
{
    if (stackAdress == NULL || isEmpty(stackAdress) || value == NULL)
    {
        return -1;
    }
    *value = stackAdress->lastElementAdress->value;
    StackElement* AdressOflastElementToFree = stackAdress->lastElementAdress;
    stackAdress->lastElementAdress = stackAdress->lastElementAdress->nextElementAdress;

    free(AdressOflastElementToFree);

    return 0;
}

int printStack(Stack* stackAdress)
{
    if (stackAdress == NULL)
    {
        return -1;
    }
    printf("Stack: ");
    StackElement* currentElementAdress = stackAdress->lastElementAdress;
    while (currentElementAdress != NULL)
    {
        printf("%d ", currentElementAdress->value);
        currentElementAdress = currentElementAdress->nextElementAdress;
    }
    printf("\n");
    return 0;
}

int lengthOfStack(Stack* stackAdress, int* lengthAdress)
{
    if (stackAdress == NULL || lengthAdress == NULL)
    {
        return -1;
    }
    *lengthAdress = 0;
    StackElement* currentElementAdress = stackAdress->lastElementAdress;
    while (currentElementAdress != NULL)
    {
        (*lengthAdress)++;
        currentElementAdress = currentElementAdress->nextElementAdress;
    }
    return 0;
}

int freeStack(Stack* stackAdress)
{
    if (stackAdress == NULL)
    {
        return -1;
    }
    StackElement* currentElementAdress = stackAdress->lastElementAdress;
    while (currentElementAdress != NULL)
    {
        stackAdress->lastElementAdress = currentElementAdress->nextElementAdress;
        free(currentElementAdress);
        currentElementAdress = stackAdress->lastElementAdress;
    }
    return 0;
}

