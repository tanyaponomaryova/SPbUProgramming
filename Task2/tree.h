#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node Node;

typedef struct Tree Tree;

int createTree(Tree** treePtrPtr);

bool isOperation(char symbol);

int number(char* string, int* indexPtr);

Node* newNode(char* string, int* indexPtr);

int build(Tree** treePtrPtr, char* string);

void printNode(Node* nodePtr);

void printTree(Tree* treePtr);

int calculateSubtree(Node* nodePtr);

int calculate(Tree* treePtr, int* resultPtr);

void destroyChildren(Node* nodePtr);

void destroyTree(Tree* treePtr);