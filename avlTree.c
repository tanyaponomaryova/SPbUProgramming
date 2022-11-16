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

Node* littleRightRotation(Node* yPtr)
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
    if (getBalanceFactor(nodePtr) == 2) // левое дерево выше (это значит, что оно точно есть и в нём как минимум 2 узла)
    {
        if (getBalanceFactor(nodePtr->leftChildPtr) < 0) // правый ребенок левого ребенка выше -> нужно сделать малое левое вращение
        {
            nodePtr->leftChildPtr = littleLeftRotation(nodePtr->leftChildPtr);
        }
        return littleRightRotation(nodePtr);
    }
    if (getBalanceFactor(nodePtr) == -2) // правое дерево выше (это значит, что оно точно есть и в нём как минимум 2 узла)
    {
        if (getBalanceFactor(nodePtr->rightChildPtr) > 0) // левый ребенок правого ребенка выше -> нужно сделать малое правое вращение
        {
            nodePtr->rightChildPtr = littleRightRotation(nodePtr->rightChildPtr);
        }
        return littleLeftRotation(nodePtr);
    }
    return nodePtr; // если баланс -1, 0, 1, то с узлом ничего не делаем
}

Node* insertNode(Node* nodePtr, int key, char* string, int* errorCode)
{
    if (nodePtr == NULL)
    {
        Node* newNode = calloc(1, sizeof(Node));
        if (newNode == NULL)
        {
            *errorCode = -1;
            return NULL;
        }
        newNode->key = key;
        newNode->string = string;
        return newNode;
    }
    if (key < nodePtr->key)
    {
        nodePtr->leftChildPtr = insertNode(nodePtr->leftChildPtr, key, string, errorCode);
    }
    else if (key > nodePtr->key)
    {
        nodePtr->rightChildPtr = insertNode(nodePtr->rightChildPtr, key, string, errorCode);
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
    int errorCode = 0;
    treePtr->rootPtr = insertNode(treePtr->rootPtr, key, newString, &errorCode);
    return errorCode;
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

void transferData(Node* destinationNode, Node* sourceNode, int* errorCode)
{
    *errorCode = 0;
    free(destinationNode->string);
    destinationNode->key = sourceNode->key;
    destinationNode->string = calloc(strlen(sourceNode->string) + 1, sizeof(char));
    if (destinationNode->string == NULL)
    {
        *errorCode = -1;
        return;
    }
    strcpy(destinationNode->string, sourceNode->string);
}

void deleteNode(Node** nodePtrPtr, int key, int* errorCode, bool* isDeleted)
{
    *errorCode = 0;
    *isDeleted = true;
    if (*nodePtrPtr == NULL) // не нашли узел с нужным ключом
    {
        *isDeleted = false;
        return;
    }
    if (key < (*nodePtrPtr)->key)
    {
        deleteNode(&(*nodePtrPtr)->leftChildPtr, key, errorCode, isDeleted);
    }
    else if (key > (*nodePtrPtr)->key)
    {
        deleteNode(&(*nodePtrPtr)->rightChildPtr, key, errorCode, isDeleted);
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
            int errorCodeTransferData = 0;
            transferData(*nodePtrPtr, tempNodePtr, &errorCodeTransferData);
            if (errorCodeTransferData != 0)
            {
                *errorCode = errorCodeTransferData;
                return;
            }
            deleteNode(&(*nodePtrPtr)->rightChildPtr, (*nodePtrPtr)->key, errorCode, isDeleted);
        }
    } // после того как вставили новый узел и рекурсивно вернулись, балансируем все узлы выше
    (*nodePtrPtr) = balance(*nodePtrPtr);
}

int deleteNodeFromTree(Tree* treePtr, int key, bool* isDeleted)
{
    int errorCode = 0;
    if (treePtr == NULL)
    {
        return -2;
    }
    deleteNode(&(treePtr->rootPtr), key, &errorCode, isDeleted);
    return errorCode; // -1 если произошла ошибка выделения памяти при вызове каллока в transferData(), 0 если всё норм
}

char* getStringFromNode(Node* nodePtr, int key, int* errorCode)
{
    if (nodePtr == NULL) // не нашли нужный узел с ключом
    {
        return NULL;
    }
    if (key == nodePtr->key)
    {
        char* newString = calloc(strlen(nodePtr->string) + 1, sizeof(char));
        if (newString == NULL)
        {
            *errorCode = -1;
            return NULL;
        }
        strcpy(newString, nodePtr->string);
        return newString;
    }
    if (key < nodePtr->key)
    {
        return getStringFromNode(nodePtr->leftChildPtr, key, errorCode);
    } // key > nodePtr->key
    return getStringFromNode(nodePtr->rightChildPtr, key, errorCode);
}

int getStringFromTree(Tree* treePtr, int key, char** destinationStringPtr) // принимает на вход строку, под которую выделяет память и копирует строку из нужного узла
{
    if (treePtr == NULL)
    {
        return -2;
    }
    int errorCode = 0;
    *destinationStringPtr = getStringFromNode(treePtr->rootPtr, key, &errorCode);
    return errorCode;
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

int isFoundInTree(Tree* treePtr, int key, bool* isFound)
{
    if (treePtr == NULL)
    {
        return -2;
    }
    *isFound = isFoundInNode(treePtr->rootPtr, key);
    return 0;
}

void printNode(Node* nodePtr)
{
    if (nodePtr == NULL)
    {
        return;
    }
    printf(" (%d, %s)", nodePtr->key, nodePtr->string);
    printNode(nodePtr->leftChildPtr);
    printNode(nodePtr->rightChildPtr);
}

void printTreeInPreOrder(Tree* treePtr)
{
    if (treePtr == NULL)
    {
        printf("Tree is a null pointer. :( \n");
        return;
    }
    if (treePtr->rootPtr == NULL)
    {
        printf("Tree is empty. \n");
        return;
    }
    printf("Tree: ");
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