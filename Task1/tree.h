#pragma once

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node Node;

typedef struct Tree Tree;

int createTree(Tree** treePtrPtr);

int addTree(Tree* treePtr, int key, char* string);

int getTree(Tree* treePtr, int key, char** destinationStringPtr);

bool findTree(Tree* treePtr, int key);

void destroyTree(Tree* treePtr);

int deleteFromTree(Tree* treePtr, int key);

void printTree(Tree* treePtr);