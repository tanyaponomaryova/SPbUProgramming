#include "tree.h"

typedef struct Node
{
    char operation;
    int number;
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

bool isOperation(char symbol)
{
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

int number(char* string, int* indexPtr)
{
    int number = 0;
    while (string[*indexPtr] >= '0' && string[*indexPtr] <= '9')
    {
        number = number * 10 + (string[*indexPtr] - '0');
        (*indexPtr)++;
    }
    return number;
}

Node* newNode(char* string, int* indexPtr)
{
    (*indexPtr)++;
    while (string[*indexPtr] == ' ' || string[*indexPtr] == '(' || string[*indexPtr] == ')')
    {
        (*indexPtr)++;
    }
    Node* newNodePtr = calloc(1, sizeof(Node));
    if (isOperation(string[*indexPtr]))
    {
        newNodePtr->operation = string[*indexPtr];
        newNodePtr->leftNodePtr = newNode(string, indexPtr);
        newNodePtr->rightNodePtr = newNode(string, indexPtr);
    }
    else
    {
        newNodePtr->number = number(string, indexPtr);
    }
    return newNodePtr;
}

int build(Tree** treePtrPtr, char* string)
{
    int errorCode = createTree(treePtrPtr);
    if (errorCode != 0)
    {
        return errorCode;
    }
    int index = -1;
    (*treePtrPtr)->rootPtr = newNode(string, &index);
    return 0;
}

void printNode(Node* nodePtr)
{
    if (nodePtr->leftNodePtr == NULL && nodePtr->rightNodePtr == NULL) // если лист
    {
        printf("%d ", nodePtr->number);
        return;
    }
    printf("%c ", nodePtr->operation);
    printNode(nodePtr->leftNodePtr);
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

int calculateSubtree(Node* nodePtr)
{
    if (nodePtr->leftNodePtr == NULL && nodePtr->rightNodePtr == NULL) // если лист
    {
        return nodePtr->number;
    }
    int operand1 = calculateSubtree(nodePtr->leftNodePtr);
    int operand2 = calculateSubtree(nodePtr->rightNodePtr);
    char operation = nodePtr->operation;
    if (operation == '+')
    {
        return operand1 + operand2;
    }
    if (operation == '-')
    {
        return operand1 - operand2;
    }
    if (operation == '*')
    {
        return operand1 * operand2;
    }
    return operand1 / operand2; // if (operation == '/')
}

int calculate(Tree* treePtr, int* resultPtr)
{
    if (treePtr == NULL)
    {
        return -2;
    }
    *resultPtr = calculateSubtree(treePtr->rootPtr);
    return 0;
}

void destroyChildren(Node* nodePtr)
{
    if (nodePtr == NULL)
    {
        return;
    }
    destroyChildren(nodePtr->leftNodePtr);
    destroyChildren(nodePtr->rightNodePtr);
    free(nodePtr);
}

void destroyTree(Tree* treePtr)
{
    if (treePtr == NULL)
    {
        return;
    }
    destroyChildren(treePtr->rootPtr);
    free(treePtr);
}