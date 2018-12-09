#include "src/functions.h"

int main() {
    BinaryTree *binaryTreeArray = (BinaryTree *) malloc(TOTAL_TREES * sizeof(BinaryTree)); // array of binaryTrees
    for (int i = 0; i < TOTAL_TREES; i++) { // reset initialization status to false
        binaryTreeArray[i].initialized = FALSE;
    }
    int currentBinaryTreeIndex = 0; // current index
    BinaryTree *currentBinaryTree = &binaryTreeArray[currentBinaryTreeIndex]; // pointer to current binaryTree
    int option; // user option
    do {
        showMenu();
        printf("Current binaryTree: T%d\n", currentBinaryTreeIndex);
        printf("Please input your option[0-23]:\n");
        int isValid = scanf("%d", &option);
        if (!isValid) {
            printf("You entered an invalid value!\n");
            while (getchar() != '\n');
        } else {
            if (option == 0) {
                break;
            }
            switch (option) {
                case 1: { // initializeBinaryTree
                    printf("You've chosen function initializeBinaryTree(), which initializes a binaryTree\n");
                    Status status = initializeBinaryTree(currentBinaryTree);
                    printf(status == OK ? "Initialized successfully!\n" : "Failed to initialize!\n");
                    getchar();
                    break;
                }
                case 2: { // destroyBinaryTree
                    printf("You've chosen function destroyBinaryTree(), which destroys a binaryTree\n");
                    Status status = destroyBinaryTree(currentBinaryTree);
                    printf(status == OK ? "Destroyed successfully!\n" : "Failed to destroy!\n");
                    getchar();
                    break;
                }
                case 3: { // createBinaryTree
                    printf("You've chosen function createBinaryTree(), which creates a binaryTree\n");
                    printf("Please input the number of nodes:\n");
                    int length;
                    if (!scanf("%d", &length) || length <= 0) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    printf("Please input the keys and values in preOrder:\n");
                    ElemType *preOrder = scanHelper(length, NULL);
                    printf("Please input the keys and values in inOrder:\n");
                    ElemType *inOrder = scanHelper(length, NULL);
                    Status status = createBinaryTree(currentBinaryTree, preOrder, inOrder, length);
                    printf(status == OK ? "Created successfully!\n" : "Failed to create!\n");
                    getchar();
                    break;
                }
                case 4: { // clearBinaryTree
                    printf("You've chosen function clearBinaryTree(), which empties a binaryTree\n");
                    Status status = clearBinaryTree(currentBinaryTree);
                    printf(status == OK ? "Cleared successfully!\n" : "Failed to clear!\n");
                    getchar();
                    break;
                }
                case 5: { // isBinaryTreeEmpty
                    printf("You've chosen function isBinaryTreeEmpty(), which shows whether a binaryTree is empty\n");
                    Status status = isBinaryTreeEmpty(currentBinaryTree);
                    printf(status == ERROR ? "The binaryTree has not been initialized\n"
                                           : status == TRUE ? "The binaryTree is empty\n"
                                                            : "The binaryTree is not empty\n");
                    getchar();
                    break;
                }
                case 6: { // binaryTreeDepth
                    printf("You've chosen function binaryTreeDepth(), which shows the depth of a binaryTree\n");
                    int depth = binaryTreeDepth(currentBinaryTree);
                    depth >= 0 ? printf("The depth of binaryTree is %d\n", depth)
                               : printf("Failed to get the depth!\n");
                    getchar();
                    break;
                }
                case 7: { // getRoot
                    printf("You've chosen function getRoot(), which gets the root's value\n");
                    TreeNode *root = getRoot(currentBinaryTree);
                    root ? printf("The value of root is: %d\n", root->data.value)
                         : printf("Failed to get the root!\n");
                    getchar();
                    break;
                }
                case 8: { // getValue
                    printf("You've chosen function getValue(), which gets the specified element's value\n");
                    printf("Please input the key of the element:\n");
                    int key;
                    if (!scanf("%d", &key)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    int value = getValue(currentBinaryTree, key);
                    value <= 0 ? printf("This element doesn't exist!\n")
                               : printf("The value of this element is: %d\n", value);
                    getchar();
                    break;
                }
                case 9: { // setValue
                    printf("You've chosen function setValue(), which sets the specified element's value\n");
                    printf("Please input the key of the element:\n");
                    int key, value;
                    if (!scanf("%d", &key)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    printf("Please input the value of the element:\n");
                    if (!scanf("%d", &value)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    Status status = setValue(currentBinaryTree, key, value);
                    printf(status == OK ? "Set successfully!\n" : "Failed to set!\n");
                    getchar();
                    break;
                }
                case 10: { // getParent
                    printf("You've chosen function getParent(), which gets the parent of a node\n");
                    printf("Please input the key of the node:\n");
                    int key;
                    if (!scanf("%d", &key)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    TreeNode *parent = getParent(currentBinaryTree, key);
                    parent ? printf("The key, value of parent is: \nkey: %d, value: %d\n", parent->data.key, parent->data.value)
                           : printf("This node doesn't have parent!\n");
                    getchar();
                    break;
                }
                case 11: { // getLeftChild
                    printf("You've chosen function getLeftChild(), which gets the left child of a node\n");
                    printf("Please input the key of the node:\n");
                    int key;
                    if (!scanf("%d", &key)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    TreeNode *leftChild = getLeftChild(currentBinaryTree, key);
                    leftChild ? printf("The left child's key, value is: \nkey: %d, value: %d\n", leftChild->data.key, leftChild->data.value)
                              : printf("This node doesn't have left child!\n");
                    getchar();
                    break;
                }
                case 12: { // getRightChild
                    printf("You've chosen function getRightChild(), which gets the right child of a node\n");
                    printf("Please input the key of the node:\n");
                    int key;
                    if (!scanf("%d", &key)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    TreeNode *rightChild = getRightChild(currentBinaryTree, key);
                    rightChild ? printf("The right child's key, value is: \nkey: %d, value: %d\n", rightChild->data.key, rightChild->data.value)
                               : printf("This node doesn't have right child!\n");
                    getchar();
                    break;
                }
                case 13: { // getLeftSibling
                    printf("You've chosen function getLeftSibling(), which gets the left sibling of a node\n");
                    printf("Please input the key of the node:\n");
                    int key;
                    if (!scanf("%d", &key)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    TreeNode *leftSibling = getLeftSibling(currentBinaryTree, key);
                    leftSibling ? printf("The left sibling's key, value is: \nkey: %d, value: %d\n", leftSibling->data.key, leftSibling->data.value)
                                : printf("This node doesn't have left sibling!\n");
                    getchar();
                    break;
                }
                case 14: { // getRightSibling
                    printf("You've chosen function getRightSibling(), which gets the right sibling of a node\n");
                    printf("Please input the key of the node:\n");
                    int key;
                    if (!scanf("%d", &key)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    TreeNode *rightSibling = getRightSibling(currentBinaryTree, key);
                    rightSibling ? printf("The right sibling's key, value is: \nkey: %d, value: %d\n", rightSibling->data.key,
                                          rightSibling->data.value)
                                 : printf("This node doesn't have right sibling!\n");
                    getchar();
                    break;
                }
                case 15: { // insertSubtree
                    printf("You've chosen function insertSubtree(), which inserts a subtree to a tree\n");
                    printf("Please input the number of nodes:\n");
                    int length;
                    if (!scanf("%d", &length) || length <= 0) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    printf("Please input the keys and values in preOrder:\n");
                    ElemType *preOrder = scanHelper(length, NULL);
                    printf("Please input the keys and values in inOrder:\n");
                    ElemType *inOrder = scanHelper(length, NULL);
                    BinaryTree *newTree = (BinaryTree *) malloc(sizeof(BinaryTree));
                    newTree->initialized = FALSE;
                    if (initializeBinaryTree(newTree) != OK) {
                        printf("Failed to initialize!\n");
                        break;
                    }
                    if (createBinaryTree(newTree, preOrder, inOrder, length) != OK) {
                        printf("Failed to create!\n");
                        break;
                    }
                    printf("Please input the key of node you want to insert:\n");
                    int key;
                    if (!scanf("%d", &key)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    getchar();
                    printf("Insert left or right? (L: left, R: right)\n");
                    char isLeft;
                    scanf("%c", &isLeft);
                    Status status;
                    if (isLeft == 'L' || isLeft == 'l') {
                        status = insertSubtree(currentBinaryTree, getNode(currentBinaryTree, key), TRUE, newTree);
                    } else if (isLeft == 'R' || isLeft == 'r') {
                        status = insertSubtree(currentBinaryTree, getNode(currentBinaryTree, key), FALSE, newTree);
                    } else {
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    printf(status == OK ? "Inserted successfully!\n" : "Failed to insert!\n");
                    getchar();
                    break;
                }
                case 16: { // deleteSubtree
                    printf("You've chosen function deleteSubtree(), which deletes a subtree from a tree\n");
                    printf("Please input the key of node you want to delete:\n");
                    int key;
                    if (!scanf("%d", &key)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    getchar();
                    printf("Delete left or right? (L: left, R: right)\n");
                    char isLeft;
                    scanf("%c", &isLeft);
                    Status status;
                    if (isLeft == 'L' || isLeft == 'l') {
                        status = deleteSubtree(currentBinaryTree, getNode(currentBinaryTree, key), TRUE);
                    } else if (isLeft == 'R' || isLeft == 'r') {
                        status = deleteSubtree(currentBinaryTree, getNode(currentBinaryTree, key), FALSE);
                    } else {
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    printf(status == OK ? "Deleted successfully!\n" : "Failed to delete!\n");
                    getchar();
                    break;
                }
                case 17: { // preOrderTraverse
                    printf("You've chosen function preOrderTraverse(), which traverses a tree pre-orderly\n");
                    Status status = binaryTreeTraverse(currentBinaryTree, PRE_ORDER, showElement);
                    status != OK && printf("Failed to traverse!\n");
                    getchar();
                    break;
                }
                case 18: { // inOrderTraverse
                    printf("You've chosen function inOrderTraverse(), which traverses a tree in-orderly\n");
                    Status status = binaryTreeTraverse(currentBinaryTree, IN_ORDER, showElement);
                    status != OK && printf("Failed to traverse!\n");
                    getchar();
                    break;
                }
                case 19: { // postOrderTraverse
                    printf("You've chosen function postOrderTraverse(), which traverses a tree post-orderly\n");
                    Status status = binaryTreeTraverse(currentBinaryTree, POST_ORDER, showElement);
                    status != OK && printf("Failed to traverse!\n");
                    getchar();
                    break;
                }
                case 20: { // levelOrderTraverse
                    printf("You've chosen function levelOrderTraverse(), which traverses a tree level-orderly\n");
                    Status status = binaryTreeTraverse(currentBinaryTree, LEVEL_ORDER, showElement);
                    status != OK && printf("Failed to traverse!\n");
                    getchar();
                    break;
                }
                case 21: { // selectBinaryTree
                    printf("You've chosen function selectTree(), which selects a list\n");
                    printf("Please input the index of list (from 0 to 99):\n");
                    int index;
                    if (!scanf("%d", &index) || index >= TOTAL_TREES || index < 0) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    } else {
                        currentBinaryTreeIndex = index;
                    }
                    Status status = selectBinaryTree(&currentBinaryTree, &binaryTreeArray[currentBinaryTreeIndex]);
                    printf(status == OK ? "Selected successfully!\n" : "Failed to select!\n");
                    getchar();
                    break;
                }
                case 22: { // saveData
                    printf("You've chosen function saveData(), which saves a binaryTree to a file\n");
                    printf("Please input the index of binaryTree which has NOT been initialized (from 0 to 99):\n");
                    int index;
                    if (!scanf("%d", &index) || index >= TOTAL_TREES || index < 0) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    Status status = saveData(&binaryTreeArray[index]);
                    printf(status == OK ? "Saved successfully to `data.txt`!\n" : "Failed to save!\n");
                    getchar();
                    break;
                }
                case 23: { // loadData
                    printf("You've chosen function loadData(), which loads a binaryTree from a file\n");
                    printf("Please prepare `data.txt` in current directory!\n");
                    printf("Please input the index of binaryTree which has NOT been initialized (from 0 to 99):\n");
                    int index;
                    if (!scanf("%d", &index) || index >= TOTAL_TREES || index < 0) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    Status status = loadData(&binaryTreeArray[index]);
                    printf(status == OK ? "Loaded successfully!\n" : "Failed to load!\n");
                    getchar();
                    break;
                }
                case 24: { // printTree
                    Status status = print(currentBinaryTree);
                    printf(status == OK ? "Printed successfully!\n" : "Failed to print!\n");
                    getchar();
                    break;
                }
                default: { // invalid input
                    printf("You entered an invalid value!\n");
                    getchar();
                    break;
                }
            }
        }
        printf("\nType anything to go back\n");
        while (getchar() != '\n');
#ifdef WIN32
        system("cls"); // clear console in windows
#else
        system("clear"); // clear console in *nix
#endif
    } while (option);
    printf("\n--------------------Welcome again!--------------------\n");
    getchar();
}
