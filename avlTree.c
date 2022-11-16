#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct Node
{
    int key;
    char* string;
    int height;
    struct Node* leftChildPtr;
    struct Node* rightChildPtr;
} Node;

typedef struct Tree
{
    Node* rootPtr;
} Tree;

int createTree(Tree** treePtrPtr)
{
    *treePtrPtr = calloc(1, sizeof(Tree));
    if (*treePtrPtr == NULL)
    {
        return -1;
    }
    return 0;
}

int getHeight(Node* nodePtr)
{
    if (nodePtr == NULL)
    {
        return -1; // !!!
    }
    return nodePtr->height;
}

int getBalanceFactor(Node* nodePtr)
{
    if (nodePtr == NULL)
    {
        return 0;
    }
    return getHeight(nodePtr->leftChildPtr) - getHeight(nodePtr->rightChildPtr);
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

void updateHeight(Node* nodePtr)
{
    int heightLeft = getHeight(nodePtr->leftChildPtr);
    int heightRight = getHeight(nodePtr->rightChildPtr);
    nodePtr->height = max(heightLeft, heightRight) + 1;
}

Node* littleRightRotate(Node* yPtr)
{
    Node* xPtr = yPtr->leftChildPtr;
    Node* xRightPtr = xPtr->rightChildPtr;

    xPtr->rightChildPtr = yPtr;
    yPtr->leftChildPtr = xRightPtr;

    updateHeight(yPtr);
    updateHeight(xPtr);

    return xPtr;
}

Node* littleLeftRotation(Node* xPtr)
{
    Node* yPtr = xPtr->rightChildPtr;
    Node* yLeftPtr = yPtr->leftChildPtr;

    yPtr->leftChildPtr = xPtr;
    xPtr->rightChildPtr = yLeftPtr;

    updateHeight(xPtr);
    updateHeight(yPtr);

    return yPtr;
}

Node* balance(Node* nodePtr)
{
    if (nodePtr == NULL)
    {
        return nodePtr;
    }
    updateHeight(nodePtr);
    if (getBalanceFactor(nodePtr) == 2) // левое дерево выше
    {
        if (getBalanceFactor(nodePtr->leftChildPtr) < 0) // правый ребенок левого ребенка выше -> нужно сделать малое левое вращение
        {
            nodePtr->leftChildPtr = littleLeftRotation(nodePtr->leftChildPtr);
        }
        return littleRightRotate(nodePtr);
    }
    if (getBalanceFactor(nodePtr) == -2) // правое дерево выше
    {
        if (getBalanceFactor(nodePtr->rightChildPtr) > 0) // левый ребенок правого ребенка выше -> нужно сделать малое правое вращение
        {
            nodePtr->rightChildPtr = littleRightRotate(nodePtr->rightChildPtr);
        }
        return littleLeftRotation(nodePtr);
    }
    return nodePtr; // если баланс -1, 0, 1, то с узлом ничего не делаем
}

Node* insertNode(Node* nodePtr, int key, char* string)
{
    if (nodePtr == NULL)
    {
        Node* newNode = calloc(1, sizeof(Node));
        newNode->key = key;
        newNode->string = string;
        return newNode;
    }
    if (key < nodePtr->key)
    {
        nodePtr->leftChildPtr = insertNode(nodePtr->leftChildPtr, key, string);
    }
    else if (key > nodePtr->key)
    {
        nodePtr->rightChildPtr = insertNode(nodePtr->rightChildPtr, key, string);
    }
    else // key == nodePtr->key
    {
        free(nodePtr->string);
        nodePtr->string = string;
        return nodePtr;
    }
    nodePtr = balance(nodePtr);
    return nodePtr;
}

int addKeyAndString(Tree* treePtr, int key, char* string)
{
    if (treePtr == NULL || string == NULL)
    {
        return -2;
    }
    char* newString = calloc(strlen(string) + 1, sizeof(char));
    if (newString == NULL)
    {
        return -1;
    }
    strcpy(newString, string);
    treePtr->rootPtr = insertNode(treePtr->rootPtr, key, newString);
    return 0;
}

Node* minKeyNode(Node* nodePtr)
{
    Node* currentNodePtr = nodePtr;
    while (currentNodePtr->leftChildPtr != NULL) // идём по левым веткам пока не наткнёмся на нул
    {
        currentNodePtr = currentNodePtr->leftChildPtr;
    }
    return currentNodePtr;
}

void transferData(Node* destinationNode, Node* sourceNode)
{
    free(destinationNode->string);
    destinationNode->key = sourceNode->key;
    destinationNode->string = calloc(strlen(sourceNode->string) + 1, sizeof(char));
    strcpy(destinationNode->string, sourceNode->string);
}

void deleteNode(Node** nodePtrPtr, int key)
{
    if (*nodePtrPtr == NULL) // не нашли узел с нужным ключом
    {
        return;
    }
    if (key < (*nodePtrPtr)->key)
    {
        deleteNode(&(*nodePtrPtr)->leftChildPtr, key);
    }
    else if (key > (*nodePtrPtr)->key)
    {
        deleteNode(&(*nodePtrPtr)->rightChildPtr, key);
    }
    else // key == nodePtr->key - нашли узел который нужно удалить
    {
        if ((*nodePtrPtr)->leftChildPtr == NULL && (*nodePtrPtr)->rightChildPtr == NULL)
        {
            free((*nodePtrPtr)->string);
            free(*nodePtrPtr);
            *nodePtrPtr = NULL; // чтобы в дереве не остался указатель на этот узел, который после освобождения памяти хранит в себе мусор
        }
        else if ((*nodePtrPtr)->leftChildPtr != NULL && (*nodePtrPtr)->rightChildPtr == NULL)
        {
            Node* tempPtr = (*nodePtrPtr)->leftChildPtr;
            free(*nodePtrPtr);
            *nodePtrPtr = tempPtr;
        }
        else if ((*nodePtrPtr)->leftChildPtr == NULL && (*nodePtrPtr)->rightChildPtr != NULL)
        {
            Node* tempPtr = (*nodePtrPtr)->rightChildPtr;
            free(*nodePtrPtr);
            *nodePtrPtr = tempPtr;
        }
        else if ((*nodePtrPtr)->leftChildPtr != NULL && (*nodePtrPtr)->rightChildPtr != NULL)
        {
            Node* tempNodePtr = minKeyNode((*nodePtrPtr)->rightChildPtr);
            transferData(*nodePtrPtr, tempNodePtr);
            deleteNode(&(*nodePtrPtr)->rightChildPtr, (*nodePtrPtr)->key);
        }
    } // после того как вставили новый узел и рекурсивно вернулись, балансируем все узлы выше
    (*nodePtrPtr) = balance(*nodePtrPtr);
}

int deleteNodeFromTree(Tree* treePtr, int key)
{
    if (treePtr == NULL)
    {
        return -2;
    }
    deleteNode(&(treePtr->rootPtr), key);
    return 0;
}

char* getStringFromNode(Node* nodePtr, int key)
{
    if (nodePtr == NULL)
    {
        return NULL;
    }
    if (key == nodePtr->key)
    {
        char* newString = calloc(strlen(nodePtr->string) + 1, sizeof(char));
        strcpy(newString, nodePtr->string);
        return newString;
    }
    if (key < nodePtr->key)
    {
        return getStringFromNode(nodePtr->leftChildPtr, key);
    } // key > nodePtr->key
    return getStringFromNode(nodePtr->rightChildPtr, key);
}

int getStringFromTree(Tree* treePtr, int key, char** destinationStringPtr)
{
    if (treePtr == NULL)
    {
        return -2;
    }
    *destinationStringPtr = getStringFromNode(treePtr->rootPtr, key);
    return 0;
}

bool isFoundInNode(Node* nodePtr, int key)
{
    if (nodePtr == NULL)
    {
        return false;
    }
    if (key < nodePtr->key)
    {
        return isFoundInNode(nodePtr->leftChildPtr, key);
    }
    if (key > nodePtr->key)
    {
        return isFoundInNode(nodePtr->rightChildPtr, key);
    } // key == nodePtr->key;
    return true;
}

bool isFoundInTree(Tree* treePtr, int key)
{
    return isFoundInNode(treePtr->rootPtr, key);
}

void printNode(Node* nodePtr)
{
    if (nodePtr == NULL)
    {
        return;
    }
    printf(" (%d %s)", nodePtr->key, nodePtr->string);
    printNode(nodePtr->leftChildPtr);
    printNode(nodePtr->rightChildPtr);
}

void printTreeInPreOrder(Tree* treePtr)
{
    if (treePtr == NULL || treePtr->rootPtr == NULL)
    {
        return;
    }
    printNode(treePtr->rootPtr);
    printf("\n");
}

void freeNode(Node* nodePtr)
{
    if (nodePtr == NULL)
    {
        return;
    }
    freeNode(nodePtr->leftChildPtr);
    freeNode(nodePtr->rightChildPtr);
    free(nodePtr->string);
    free(nodePtr);
}

void freeTree(Tree* treePtr)
{
    if (treePtr == NULL)
    {
        return;
    }
    freeNode(treePtr->rootPtr);
    free(treePtr);
}






