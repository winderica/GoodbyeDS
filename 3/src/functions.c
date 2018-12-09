#include "functions.h"

/**
 * Initialize an binaryTree
 * @param {BinaryTree *} binaryTree - pointer to a binaryTree
 * @return {Status} - execution status
 */
Status initializeBinaryTree(BinaryTree *binaryTree) {
    if (binaryTree->initialized) { // already exists
        return ERROR;
    }

    // initialize
    binaryTree->root = NULL;
    binaryTree->initialized = TRUE;
    return OK;
}

/**
 * Traverses a tree pre-orderly
 * @param {TreeNode *} node - pointer to a node
 * @param {void (*)(ElemType)} visitor - visit function
 * @return {void}
 */
void preOrderTraverse(TreeNode *node, void (*visitor)(TreeNode *)) {
    if (node) {
        visitor(node);
        preOrderTraverse(node->leftChild, visitor);
        preOrderTraverse(node->rightChild, visitor);
    }
}

/**
 * Traverses a tree in-orderly
 * @param {TreeNode *} node - pointer to a node
 * @param {void (*)(ElemType)} visitor - visit function
 * @return {void}
 */
void inOrderTraverse(TreeNode *node, void (*visitor)(TreeNode *)) {
    if (node) {
        inOrderTraverse(node->leftChild, visitor);
        visitor(node);
        inOrderTraverse(node->rightChild, visitor);
    }
}

/**
 * Traverses a tree post-orderly
 * @param {TreeNode *} node - pointer to a node
 * @param {void (*)(ElemType)} visitor - visit function
 * @return {void}
 */
void postOrderTraverse(TreeNode *node, void (*visitor)(TreeNode *)) {
    if (node) {
        postOrderTraverse(node->leftChild, visitor);
        postOrderTraverse(node->rightChild, visitor);
        visitor(node);
    }
}

/**
 * Traverses a tree level-orderly
 * @param {TreeNode *} node - pointer to a node
 * @param {int} length - length of node
 * @param {void (*)(ElemType)} visitor - visit function
 * @return {void}
 */
void levelOrderTraverse(TreeNode **list, int length, void (*visitor)(TreeNode *)) {
    if (length <= 0) { // recurse until list length is 0
        return;
    }
    TreeNode **newList = (TreeNode **) malloc(sizeof(TreeNode *) * length * 2);
    int newLength = 0;
    // push children into list if exist
    for (int i = 0; i < length; i++) {
        visitor(list[i]);
        if (list[i]->leftChild) {
            newList[newLength] = list[i]->leftChild;
            newLength++;
        }
        if (list[i]->rightChild) {
            newList[newLength] = list[i]->rightChild;
            newLength++;
        }
    }
    levelOrderTraverse(newList, newLength, visitor);
}

/**
 * Traverse the binaryTree and print items
 * @param {BinaryTree *} binaryTree - pointer to binaryTree
 * @param {TraversalOrder} traversalOrder - traversal order
 * @param {void (*)(ElemType)} visitor - print function
 * @return {Status} - execution status
 */
Status binaryTreeTraverse(BinaryTree *binaryTree, TraversalOrder traversalOrder, void (*visitor)(TreeNode *)) {
    if (!binaryTree->initialized) { // binaryTree doesn't exist
        return ERROR;
    }
    TreeNode *root = binaryTree->root;
    switch (traversalOrder) {
        case PRE_ORDER: // traverse pre-orderly
            preOrderTraverse(root, visitor);
            break;
        case IN_ORDER: // traverse in-orderly
            inOrderTraverse(root, visitor);
            break;
        case POST_ORDER: // traverse post-orderly
            postOrderTraverse(root, visitor);
            break;
        case LEVEL_ORDER: // traverse level-orderly
            levelOrderTraverse(&root, root ? 1 : 0, visitor);
            break;
        default:
            return ERROR;
    }
    return OK;
}


/**
 * Helper function to free node
 * @param {TreeNode *} node - node
 * @return {void}
 */
void freeHelper(TreeNode *node) {
    free(node);
}

/**
 * Helper function to get index of item in array
 * @param {ElemType} item - item
 * @param {ElemType *} array - array of items
 * @param {int} length - list length
 * @return {int} - index
 */
int indexOf(ElemType item, ElemType *array, int length) {
    for (int i = 0; i < length; i++) {
        if (array[i].key == item.key) {
            return i;
        }
    }
    return -1;
}

/**
 * Helper function to create tree
 * @param {ElemType} item - item
 * @param {ElemType *} array - array of items
 * @param {int} length - list length
 * @return {TreeNode *}
 */
TreeNode *createHelper(ElemType *preOrder, ElemType *inOrder, int index, int start, int end) {
    int i = indexOf(preOrder[index], inOrder + start, end - start);
    if (i < 0) {
        return NULL;
    } else {
        i += start;
    }
    TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
    node->data.key = preOrder[index].key;
    node->data.value = preOrder[index].value;
    index += 1;
    node->leftChild = createHelper(preOrder, inOrder, index, start, i);
    node->rightChild = createHelper(preOrder, inOrder, index + i - start, i + 1, end);
    return node;
}

/**
 * Helper function of scanf/fscanf
 * @param {int} length - list length
 * @param {FILE *} fp - file pointer
 * @return {ElemType *}
 */
ElemType *scanHelper(int length, FILE *fp) {
    ElemType *list = (ElemType *) malloc(sizeof(ElemType) * length);
    int key, value;
    int i = 0;
    while (i < length) {
        if (fp) {
            fscanf(fp, "%d %d", &key, &value);
        } else {
            scanf("%d %d", &key, &value);
        }
        list[i].key = key;
        list[i].value = value;
        i++;
    }
    return list;
}

/**
 * Create an binaryTree
 * @param {BinaryTree *} binaryTree - pointer to a binaryTree
 * @param {ElemType *} preOrderDefinition - pre order definition
 * @param {ElemType *} inOrderDefinition - in order definition
 * @param {int} length - list length
 * @return {Status} - execution status
 */
Status createBinaryTree(BinaryTree *binaryTree, ElemType *preOrderDefinition, ElemType *inOrderDefinition, int length) {
    if (!binaryTree->initialized) { // binaryTree doesn't exist
        return ERROR;
    }
    if (binaryTree->root) {
        return ERROR;
    }
    int index = 0;
    binaryTree->root = createHelper(preOrderDefinition, inOrderDefinition, index, 0, length);
    return OK;
}

/**
 * Destroy an binaryTree
 * @param {BinaryTree *} binaryTree - pointer to a binaryTree
 * @return {Status} - execution status
 */
Status destroyBinaryTree(BinaryTree *binaryTree) {
    if (!binaryTree->initialized) { // binaryTree doesn't exist
        return ERROR;
    }
    postOrderTraverse(binaryTree->root, freeHelper);
    free(binaryTree->root);
    binaryTree->initialized = FALSE;
    return OK;
}

/**
 * Clear an binaryTree
 * @param {BinaryTree *} binaryTree - pointer to a binaryTree
 * @return {Status} - execution status
 */
Status clearBinaryTree(BinaryTree *binaryTree) {
    if (!binaryTree->initialized) { // binaryTree doesn't exist
        return ERROR;
    }
    postOrderTraverse(binaryTree->root, freeHelper);
    binaryTree->root = NULL;
    return OK;
}

/**
 * Is a binaryTree empty
 * @param {BinaryTree *} binaryTree - pointer to binaryTree
 * @return {Boolean}
 */
Boolean isBinaryTreeEmpty(BinaryTree *binaryTree) {
    if (!binaryTree->initialized) { // binaryTree doesn't exist
        return ERROR;
    }

    return binaryTree->root ? FALSE : TRUE;
}

/**
 * Helper function to get depth
 * @param {TreeNode *} node - pointer to binaryTree
 * @param {int} depth - depth
 * @return {int}
 */
int getDepthHelper(TreeNode *node, int depth) {
    if (node == NULL) {
        return depth;
    }
    int left = getDepthHelper(node->leftChild, depth + 1);
    int right = getDepthHelper(node->rightChild, depth + 1);
    return left > right ? left : right;
}

/**
 * Get binaryTree depth
 * @param {BinaryTree *} binaryTree - pointer to binaryTree
 * @return {int}
 */
int binaryTreeDepth(BinaryTree *binaryTree) {
    if (!binaryTree->initialized) { // binaryTree doesn't exist
        return ERROR;
    }
    return getDepthHelper(binaryTree->root, 0);
}

/**
 * Get root of a binary tree
 * @param {BinaryTree *} binaryTree - pointer to binaryTree
 * @return {TreeNode *} - pointer to root
 */
TreeNode *getRoot(BinaryTree *binaryTree) {
    if (!binaryTree->initialized) { // binaryTree doesn't exist
        return NULL;
    }

    return binaryTree->root;
}

/**
 * Helper function to get parent
 * @param {TreeNode *} node - pointer to binaryTree
 * @param {int} key - key
 * @return {TreeNode *}
 */
TreeNode *getParentHelper(TreeNode *node, int key) {
    if (node == NULL || (node->leftChild && node->leftChild->data.key == key) || (node->rightChild && node->rightChild->data.key == key)) {
        return node;
    }
    TreeNode *parent = getParentHelper(node->leftChild, key);
    if (parent == NULL) {
        parent = getParentHelper(node->rightChild, key);
    }
    return parent;
}

/**
 * Get parent of a node
 * @param {BinaryTree *} binaryTree - pointer to binaryTree
 * @param {int} key - key
 * @return {TreeNode *} - pointer to parent
 */
TreeNode *getParent(BinaryTree *binaryTree, int key) {
    if (!binaryTree->initialized || !binaryTree->root || binaryTree->root->data.key == key) { // binaryTree doesn't exist
        return NULL;
    }
    return getParentHelper(binaryTree->root, key);
}

/**
 * Get node of a key
 * @param {BinaryTree *} binaryTree - pointer to binaryTree
 * @param {int} key - key
 * @return {TreeNode *} - pointer to node
 */
TreeNode *getNode(BinaryTree *binaryTree, int key) {
    if (!binaryTree->initialized) { // binaryTree doesn't exist
        return NULL;
    }

    if (binaryTree->root && binaryTree->root->data.key == key) {
        return binaryTree->root;
    }
    TreeNode *parent = getParent(binaryTree, key);
    if (parent == NULL) {
        return NULL;
    }
    if (parent->leftChild && parent->leftChild->data.key) {
        return parent->leftChild;
    } else {
        return parent->rightChild;
    }
}

/**
 * Get value of a node
 * @param {BinaryTree *} binaryTree - pointer to binaryTree
 * @param {int} key - key
 * @return {int} - value of a node
 */
int getValue(BinaryTree *binaryTree, int key) {
    if (!binaryTree->initialized) { // binaryTree doesn't exist
        return ERROR;
    }

    TreeNode *node = getNode(binaryTree, key);
    if (node == NULL) {
        return ERROR;
    }
    return node->data.value;
}

/**
 * Set value of a node
 * @param {BinaryTree *} binaryTree - pointer to binaryTree
 * @param {int} key - key
 * @param {Value} value - value
 * @return {Status} - execution status
 */
Status setValue(BinaryTree *binaryTree, int key, Value value) {
    if (!binaryTree->initialized) { // binaryTree doesn't exist
        return ERROR;
    }

    TreeNode *node = getNode(binaryTree, key);
    if (node == NULL) {
        return ERROR;
    }
    node->data.value = value;
    return OK;
}

/**
 * Get left child of a node
 * @param {BinaryTree *} binaryTree - pointer to binaryTree
 * @param {int} key - key
 * @return {TreeNode *} - left child
 */
TreeNode *getLeftChild(BinaryTree *binaryTree, int key) {
    if (!binaryTree->initialized) { // binaryTree doesn't exist
        return NULL;
    }

    TreeNode *node = getNode(binaryTree, key);
    if (node == NULL) {
        return NULL;
    }
    return node->leftChild;
}

/**
 * Get right child of a node
 * @param {BinaryTree *} binaryTree - pointer to binaryTree
 * @param {int} key - key
 * @return {TreeNode *} - right child
 */
TreeNode *getRightChild(BinaryTree *binaryTree, int key) {
    if (!binaryTree->initialized) { // binaryTree doesn't exist
        return NULL;
    }
    TreeNode *node = getNode(binaryTree, key);
    if (node == NULL) {
        return NULL;
    }
    return node->rightChild;
}

/**
 * Get left sibling of a node
 * @param {BinaryTree *} binaryTree - pointer to binaryTree
 * @param {int} key - key
 * @return {TreeNode *} - left sibling
 */
TreeNode *getLeftSibling(BinaryTree *binaryTree, int key) {
    if (!binaryTree->initialized) { // binaryTree doesn't exist
        return NULL;
    }

    TreeNode *parent = getParent(binaryTree, key);
    if (!parent) {
        return NULL;
    }
    TreeNode *left = parent->leftChild;

    if (!left) {
        return NULL;
    }
    return left->data.key != key ? left : NULL;
}

/**
 * Get right sibling of a node
 * @param {BinaryTree *} binaryTree - pointer to binaryTree
 * @param {int} key - key
 * @return {TreeNode *} - right sibling
 */
TreeNode *getRightSibling(BinaryTree *binaryTree, int key) {
    if (!binaryTree->initialized) { // binaryTree doesn't exist
        return NULL;
    }

    TreeNode *parent = getParent(binaryTree, key);
    if (!parent) {
        return NULL;
    }
    TreeNode *right = parent->rightChild;

    if (!right) {
        return NULL;
    }
    return right->data.key != key ? right : NULL;
}

/**
 * Insert a subtree to a tree
 * @param {BinaryTree *} binaryTree - pointer to binaryTree
 * @param {TreeNode *} node - node to insert to
 * @param {Boolean} isLeft - insert to left or tight
 * @param {BinaryTree *} newTree - pointer to newTree
 * @return {Status} - execution status
 */
Status insertSubtree(BinaryTree *binaryTree, TreeNode *node, Boolean isLeft, BinaryTree *newTree) {
    if (!binaryTree->initialized || !newTree->initialized || !node) { // binaryTree doesn't exist
        return ERROR;
    }

    TreeNode *root = newTree->root;
    free(newTree);

    if (root->rightChild) {
        return ERROR;
    }

    if (isLeft) {
        root->rightChild = node->leftChild;
        node->leftChild = root;
    } else {
        root->rightChild = node->rightChild;
        node->rightChild = root;
    }
    return OK;
}

/**
 * Delete a subtree from a tree
 * @param {BinaryTree *} binaryTree - pointer to binaryTree
 * @param {TreeNode *} node - node to delete from
 * @param {Boolean} isLeft - insert to left or tight
 * @return {Status} - execution status
 */

Status deleteSubtree(BinaryTree *binaryTree, TreeNode *node, Boolean isLeft) {
    if (!binaryTree->initialized || !node) { // binaryTree doesn't exist
        return ERROR;
    }

    TreeNode *subTree = isLeft ? node->leftChild : node->rightChild;
    postOrderTraverse(subTree, freeHelper);
    if (isLeft) {
        node->leftChild = NULL;
    } else {
        node->rightChild = NULL;
    }
    return OK;
}

/**
 * Select a binaryTree
 * @param {BinaryTree **} currentBinaryTree - pointer to `BinaryTree *currentBinaryTree`
 * @param {BinaryTree *} nextBinaryTree - pointer to nextBinaryTree
 * @return {Status} - execution status
 */
Status selectBinaryTree(BinaryTree **currentBinaryTree, BinaryTree *nextBinaryTree) {
    *currentBinaryTree = nextBinaryTree;
    return OK;
}

/**
 * Load data from a file
 * @param {BinaryTree *} binaryTree - binaryTree
 * @return {Status} - execution status
 */
Status loadData(BinaryTree *binaryTree) {
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL) { // file doesn't exist
        printf("File doesn't exist!\n");
        return ERROR;
    }
    Status result = initializeBinaryTree(binaryTree);
    if (result == ERROR) {
        printf("This binaryTree has ALREADY been initialized!\n");
        fclose(fp);
        return ERROR;
    } else if (result == OVERFLOW) {
        printf("Overflow!\n");
        fclose(fp);
        return ERROR;
    } else {
        int key, value;
        /* fscanf: read as ascii */
        int length = 0;
        while (fscanf(fp, "%d %d\n", &key, &value) != EOF) { // while element value exists
            length++;
        }
        if (length == 0) {
            printf("There are no data!\n");
            fclose(fp);
            return ERROR;
        }
        length /= 2;
        rewind(fp);

        ElemType *preOrder = scanHelper(length, fp);
        ElemType *inOrder = scanHelper(length, fp);

        fclose(fp);

        Status status = createBinaryTree(binaryTree, preOrder, inOrder, length);
        return status;
    }
}

/**
 * Helper function to save data
 * @param {TreeNode *} node - node
 * @return {void}
 */
void saveHelper(TreeNode *node) {
    FILE *fp = fopen("data.txt", "a");
    fprintf(fp, "%d %d\n", node->data.key, node->data.value);
    fclose(fp);
}

/**
 * Save data to a file
 * @param {BinaryTree *} binaryTree - binaryTree
 * @return {Status} - execution status
 */
Status saveData(BinaryTree *binaryTree) {
    if (!binaryTree->initialized) { // binaryTree doesn't exist
        return ERROR;
    }

    FILE *fp = fopen("data.txt", "w+");
    fclose(fp);
    preOrderTraverse(binaryTree->root, saveHelper);
    fp = fopen("data.txt", "a");
    fprintf(fp, "\n");
    fclose(fp);
    inOrderTraverse(binaryTree->root, saveHelper);
    return OK;
}

/**
 * show the value of element
 * @param {TreeNode *} e
 * @return {void}
 */
void showElement(TreeNode *e) {
    printf("%d ", e->data.value);
}

/**
 * Helper function to print tree
 * @param {TreeNode *} node - node
 * @param {Boolean} isLeft - print left or right
 * @param {int} offset - offset
 * @param {int} depth - current depth
 * @param {char **} buffer - buffer array
 * @return {int} - width of tree
 */
int printHelper(TreeNode *node, Boolean isLeft, int offset, int depth, char **buffer) {
    char b[20] = "";
    if (!node) {
        return 0;
    }
    int value = node->data.value;
    int digits = 1;
    while (value / 10) {
        value /= 10;
        digits++;
    }
    int width = 2 + digits;
    // insert to buffer
    sprintf(b, "[%d]", node->data.value);

    // width of left child
    int left = printHelper(node->leftChild, 1, offset, depth + 1, buffer);
    // width of right child
    int right = printHelper(node->rightChild, 0, offset + left + width, depth + 1, buffer);

    // element on root, which is in even row of `buffer`
    for (int i = 0; i < width; i++) {
        buffer[2 * depth][offset + left + i] = b[i];
    }

    // connection line
    if (depth) { // not root
        buffer[2 * depth - 1][offset + left + width / 2] = '+';
        if (isLeft) { // is left child
            for (int i = 1; i < width + right; i++)
                buffer[2 * depth - 1][offset + left + width / 2 + i] = '-';
            // get parent position
            buffer[2 * depth - 1][offset + left + width + right + width / 2] = '+';
        } else { // is right child
            for (int i = 0; i < left + width - 1; i++)
                buffer[2 * depth - 1][offset - width / 2 + i] = '-';
            // get parent position
            buffer[2 * depth - 1][offset - width / 2 - 1] = '+';
        }
    }

    return left + width + right;
}

/**
 * Print tree
 * @param {BinaryTree *} binaryTree - binaryTree
 * @return {Status} - execution status
 */
Status print(BinaryTree *binaryTree) {
    if (!binaryTree->initialized) { // binaryTree doesn't exist
        return ERROR;
    }
    int consoleWidth;
    // get console width
#ifdef WIN32
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info);
    consoleWidth = buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1;
#else
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    consoleWidth = w.ws_col;
#endif
    int height = 2 * binaryTreeDepth(binaryTree) - 1;
    for (int i = 0; i < consoleWidth; i++) {
        printf("-");
    }
    printf("\n");

    // initialize buffer
    char **s = malloc(sizeof(char *) * height);
    for (int i = 0; i < height; i++) {
        s[i] = malloc(sizeof(char) * consoleWidth);
        memset(s[i], ' ', sizeof(char) * consoleWidth);
        s[i][consoleWidth - 1] = '\0';
    }

    int finalWidth = printHelper(binaryTree->root, 0, 0, 0, s);
    if (finalWidth > consoleWidth) { // width exceeds
        printf("[WARNING: The width of console CANNOT show the whole tree!]\n");
        return ERROR;
    }

    for (int i = 0; i < height; i++) { // print items from buffer
        printf("%s\n", s[i]);
        free(s[i]); // free buffer item
    }
    free(s); // free buffer
    for (int i = 0; i < consoleWidth; i++) {
        printf("-");
    }
    printf("\n");
    return OK;
}

/**
 * show the menu
 * @param {void}
 * @return {void}
 */
void showMenu() {
    printf("\n                 Menu of Binary Tree                 \n");
    printf("------------------------------------------------------\n");
    printf("    1: initializeBinaryTree          2: destroyBinaryTree\n");
    printf("    3: createBinaryTree              4: clearBinaryTree\n");
    printf("    5: isBinaryTreeEmpty             6: binaryTreeDepth\n");
    printf("    7: getRoot                       8: getValue\n");
    printf("    9: setValue                      10: getParent\n");
    printf("    11: getLeftChild                 12: getRightChild\n");
    printf("    13: getLeftSibling               14: getRightSibling\n");
    printf("    15: insertSubtree                16: deleteSubtree\n");
    printf("    17: preOrderTraverse             18: inOrderTraverse\n");
    printf("    19: postOrderTraverse            20: levelOrderTraverse\n");
    printf("    21: selectBinaryTree             22: saveData\n");
    printf("    23: loadData                     24: printTree\n");
    printf("    0: quit\n");
    printf("------------------------------------------------------\n");
}
