#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node Node;

typedef struct Tree Tree;

int createTree(Tree** treePtrPtr);

int addKeyAndString(Tree* treePtr, int key, char* string);

int deleteNodeFromTree(Tree* treePtr, int key);

int getStringFromTree(Tree* treePtr, int key, char** destinationStringPtr);

bool isFoundInTree(Tree* treePtr, int key);

void printTreeInPreOrder(Tree* treePtr);

void freeTree(Tree* treePtr);
