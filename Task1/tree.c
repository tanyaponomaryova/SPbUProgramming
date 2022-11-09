#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node
{
    int key;
    char* string;
    struct Node* leftNodePtr;
    struct Node* rightNodePtr;
} Node;

typedef struct Tree
{
    Node* rootPtr;
} Tree;

int createTree(Tree** treePtrPtr)
{
    *treePtrPtr = calloc(1, sizeof(Tree));
    if (treePtrPtr == NULL)
    {
        return -1;
    }
    return 0;
}

int add(Node* nodePtr, int key, char* string)
{
    if (nodePtr == NULL || string == NULL)
    {
        return -2;
    }
    if (nodePtr->key == key)
    {
        free(nodePtr->string); // удаляем старое
        nodePtr->string = string; // записываем новое
        return 0;
    }
    if (key < nodePtr->key)
    { // идем налево
        if (nodePtr->leftNodePtr == NULL)
        { // нет левого ребенка
            Node* newNodePtr = calloc(1, sizeof(Node));
            if (newNodePtr == NULL)
            {
                return -1;
            }
            newNodePtr->key = key;
            newNodePtr->string = string;
            nodePtr->leftNodePtr = newNodePtr; // теперь есть левый ребенок
            return 0;
        }
        return add(nodePtr->leftNodePtr, key, string); // если у текущего узла есть левый ребенок, то теперь рекурсивно вставляем новый узел в него
    }
    if (key > nodePtr->key)
    { // идем направо
        if (nodePtr->rightNodePtr == NULL)
        {
            Node* newNodePtr = calloc(1, sizeof(Node));
            if (newNodePtr == NULL)
            {
                return -1;
            }
            newNodePtr->key = key;
            newNodePtr->string = string;
            nodePtr->rightNodePtr = newNodePtr;
            return 0;
        }
        return add(nodePtr->rightNodePtr, key, string);
    }
}

int addTree(Tree* treePtr, int key, char* string)
{
    char* newString = calloc(strlen(string) + 1, sizeof(char));
    if (newString == NULL)
    {
        return -1;
    }
    strcpy(newString, string);
    if (treePtr->rootPtr == NULL) // дерево пустое
    {
        Node* newNodePtr = calloc(1, sizeof(Node));
        if (newNodePtr == NULL)
        {
            free(newString);
            return -1;
        }
        newNodePtr->key = key;
        newNodePtr->string = newString;
        treePtr->rootPtr = newNodePtr;
        return 0;
    }
    return add(treePtr->rootPtr, key, newString);
}

int get(Node* nodePtr, int key, char** destinationString)
{
    if (nodePtr == NULL) // не нашли узел с нужным ключом
    {
        *destinationString = NULL;
        return 0;
    }
    if (key == nodePtr->key) // нашли
    {
        free(*destinationString);
        *destinationString = calloc(strlen(nodePtr->string) + 1, sizeof(char));
        // так как strlen не считает '\0', то надо + 1, чтобы для него осталось
        // место при копировании строк strcpy (эта функция копирует всю строку вместе с '\0')
        if (*destinationString == NULL)
        {
            return -1;
        }
        strcpy(*destinationString, nodePtr->string);
        return 0;
    }
    if (key < nodePtr->key) // налево
    {
        return get(nodePtr->leftNodePtr, key, destinationString); // отправляемся рекурсивно искать в левой ветке
    }
    // иначе отправляемся рекурсивно искать в правой ветке
    return get(nodePtr->rightNodePtr, key, destinationString);
}

int getTree(Tree* treePtr, int key, char** destinationStringPtr)
{
     if (treePtr == NULL)
     {
         return -1;
     }
    return get(treePtr->rootPtr, key, destinationStringPtr);
}

bool find(Node* nodePtr, int key)
{
    if (nodePtr == NULL)
    {
        return false;
    }
    if (key == nodePtr->key)
    {
        return true;
    }
    if (key < nodePtr->key)
    {
        return find(nodePtr->leftNodePtr, key);
    }
    return find(nodePtr->rightNodePtr, key);
}

bool findTree(Tree* treePtr, int key)
{
    return  find(treePtr->rootPtr, key);
}

void destroy(Node* nodePtr)
{
    if (nodePtr == NULL)
    {
        return;
    }
    destroy(nodePtr->leftNodePtr);
    destroy(nodePtr->rightNodePtr);
    free(nodePtr->string);
    free(nodePtr);
}

void destroyTree(Tree* treePtr)
{
    if (treePtr == NULL)
    {
        return;
    }
    destroy(treePtr->rootPtr);
    free(treePtr);
}

int copyData(Node* destNode, Node* sourceNode)
{
    if (destNode == NULL || sourceNode == NULL)
    {
        return -2;
    }
    char* newString = calloc(strlen(sourceNode->string) + 1, sizeof(char));
    if (newString == NULL)
    {
        return -1;
    }
    strcpy(newString, sourceNode->string);
    destNode->key = sourceNode->key;
    destNode->string = newString;
    return 0;
}

int minNode(Node* nodePtr, Node** destNodePtrPtr) // в destNode запишем адрес узла с минимальным элементом
{
    if (nodePtr == NULL)
    {
        return -2;
    }
    while (nodePtr->leftNodePtr != NULL)
    {
        nodePtr = nodePtr->leftNodePtr;
    }
    *destNodePtrPtr = nodePtr;
    return 0;
}

int maxNode(Node* nodePtr, Node** destNodePtrPtr) // в destNode запишем адрес узла с максимальным элементом
{
    if (nodePtr == NULL)
    {
        return -2;
    }
    while (nodePtr->rightNodePtr != NULL)
    {
        nodePtr = nodePtr->rightNodePtr;
    }
    *destNodePtrPtr = nodePtr;
    return 0;
}

int deleteNode(Node** nodePtrPtr, int key)
{
    if ((*nodePtrPtr) == NULL)
    {
        return -1;
    }
    if (key == (*nodePtrPtr)->key) // нашли узел, который нужно удалить
    {
        if ((*nodePtrPtr)->leftNodePtr == NULL && (*nodePtrPtr)->rightNodePtr == NULL)
        { // узел без детей
            free((*nodePtrPtr)->string);
            free((*nodePtrPtr));
            *nodePtrPtr = NULL;
            return 0;
        }
        if ((*nodePtrPtr)->leftNodePtr != NULL && (*nodePtrPtr)->rightNodePtr == NULL)
        {
            Node* temp = (*nodePtrPtr)->leftNodePtr;
            free((*nodePtrPtr)->string);
            free((*nodePtrPtr));
            (*nodePtrPtr) = temp;
            return 0;
        }
        if ((*nodePtrPtr)->leftNodePtr == NULL && (*nodePtrPtr)->rightNodePtr != NULL)
        {
            Node* temp = (*nodePtrPtr)->rightNodePtr;
            free((*nodePtrPtr)->string);
            free((*nodePtrPtr));
            (*nodePtrPtr) = temp;
            return 0;
        }
        if ((*nodePtrPtr)->leftNodePtr != NULL && (*nodePtrPtr)->rightNodePtr != NULL) // есть оба ребёнка
        {
            Node* maxNodePtr = NULL;
            maxNode((*nodePtrPtr)->leftNodePtr, &maxNodePtr); // теперь в maxNodePtr хранится адрес максимального узла дерева с корнем *nodePtrPtr
            copyData(*nodePtrPtr, maxNodePtr);
            deleteNode(&(*nodePtrPtr)->leftNodePtr, (*nodePtrPtr)->key);
            return 0;
        }
    }
    if (key < (*nodePtrPtr)->key)
    {
        return deleteNode(&((*nodePtrPtr)->leftNodePtr), key);
    }
    return deleteNode(&((*nodePtrPtr)->rightNodePtr), key);
}

int deleteFromTree(Tree* treePtr, int key)
{
    if (treePtr == NULL)
    {
        return -2;
    }
    return deleteNode(&(treePtr->rootPtr), key);
}
void printNode(Node* nodePtr)
{
    if (nodePtr == NULL)
    {
        return;
    }
    printNode(nodePtr->leftNodePtr);
    printf("%d %s ", nodePtr->key, nodePtr->string);
    printNode(nodePtr->rightNodePtr);
}
void printTree(Tree* treePtr)
{
    if (treePtr == NULL)
    {
        return;
    }
    printNode(treePtr->rootPtr);
    printf("\n");
}

