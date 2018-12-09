#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#ifdef WIN32
#include <winbase.h>
#include <wincon.h>
#else
#include <sys/ioctl.h>
#include <string.h>
#endif

/* type definitions */
// status type
typedef int Status;
#define OK 1
#define ERROR -1
#define OVERFLOW -2

// boolean type
typedef int Boolean;
#define TRUE 1
#define FALSE 0

// traversal order type
typedef int TraversalOrder;
#define PRE_ORDER 0
#define IN_ORDER 1
#define POST_ORDER 2
#define LEVEL_ORDER 3

// number of binaryTrees
#define TOTAL_TREES 100

typedef int Value;

typedef struct ElemType {
    int key;
    Value value;
} ElemType;

typedef struct TreeNode {
    ElemType data;
    struct TreeNode *leftChild;
    struct TreeNode *rightChild;
} TreeNode;

typedef struct BinaryTree {
    TreeNode *root;
    Boolean initialized;
} BinaryTree;

TreeNode *createHelper(ElemType *preOrder, ElemType *inOrder, int index, int start, int end);
TreeNode *getLeftChild(BinaryTree *binaryTree, int key);
TreeNode *getLeftSibling(BinaryTree *binaryTree, int key);
TreeNode *getNode(BinaryTree *binaryTree, int key);
TreeNode *getParentHelper(TreeNode *node, int key);
TreeNode *getParent(BinaryTree *binaryTree, int key);
TreeNode *getRightChild(BinaryTree *binaryTree, int key);
TreeNode *getRightSibling(BinaryTree *binaryTree, int key);
TreeNode *getRoot(BinaryTree *binaryTree);
ElemType *scanHelper(int length, FILE *fp);
int binaryTreeDepth(BinaryTree *binaryTree);
Status binaryTreeTraverse(BinaryTree *binaryTree, TraversalOrder traversalOrder, void (*visitor)(TreeNode *));
Status clearBinaryTree(BinaryTree *binaryTree);
Status createBinaryTree(BinaryTree *binaryTree, ElemType *preOrderDefinition, ElemType *inOrderDefinition, int length);
Status deleteSubtree(BinaryTree *binaryTree, TreeNode *node, Boolean isLeft);
Status destroyBinaryTree(BinaryTree *binaryTree);
void freeHelper(TreeNode *node);
int getDepthHelper(TreeNode *node, int depth);
int getValue(BinaryTree *binaryTree, int key);
int indexOf(ElemType item, ElemType *array, int length);
Status initializeBinaryTree(BinaryTree *binaryTree);
Status insertSubtree(BinaryTree *binaryTree, TreeNode *node, Boolean isLeft, BinaryTree *newTree);
Boolean isBinaryTreeEmpty(BinaryTree *binaryTree);
Status loadData(BinaryTree *binaryTree);
int printHelper(TreeNode *node, Boolean isLeft, int offset, int depth, char** buffer);
Status print(BinaryTree *binaryTree);
Status saveData(BinaryTree *binaryTree);
void saveHelper(TreeNode *node);
Status selectBinaryTree(BinaryTree **currentBinaryTree, BinaryTree *nextBinaryTree);
Status setValue(BinaryTree *binaryTree, int key, Value value);
void showElement(TreeNode *e);
void showMenu();