//
// Created by winderica on 11/18/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* type defines*/
// status type
typedef int Status;
#define OK 1
#define ERROR -1
#define OVERFLOW -2

// boolean type
typedef int Boolean;
#define TRUE 1
#define FALSE 0

// number of lists
#define TOTAL_LISTS 100

typedef int ElemType;

typedef struct LinkNode {
    ElemType value;
    struct LinkNode *next;
} LinkNode;

typedef struct {
    LinkNode *head;
    int length;
    Boolean initialized;
} LinkList;

/**
 * Initialize an list
 * @param {LinkList *} list - pointer to a list
 * @return {Status} - execution status
 */
Status initializeList(LinkList *list) {

    if (list->initialized) { // already exists
        return ERROR;
    }

    // initialize
    list->head = NULL;
    list->length = 0;
    list->initialized = TRUE;
    return OK;
}

/**
 * Traverse the list and print items
 * @param {LinkList *} list - pointer to list
 * @param {void (*)(ElemType)} visitor - print function
 * @return {Status} - execution status
 */
Status listTraverse(LinkList *list, void (*visitor)(LinkNode *)) {
    if (!list->initialized) { // list doesn't exist
        return ERROR;
    }
    LinkNode *node = list->head;
    while (node) {
        LinkNode *next = node->next; // save the pointer to next node in case `visitor` function free this node
        visitor(node);
        node = next;
    }
    return OK;
}

/**
 * Helper function to free node
 * @param {LinkNode *} node - node
 * @return {void}
 */
void freeHelper(LinkNode *node) {
    free(node);
}

/**
 * Destroy an list
 * @param {LinkList *} list - pointer to a list
 * @return {Status} - execution status
 */
Status destroyList(LinkList *list) {
    if (!list->initialized) { // list doesn't exist
        return ERROR;
    }
    listTraverse(list, freeHelper); // use `listTraverse` function to free nodes of the list

    // destroy head node
    free(list->head);
    list->length = 0;
    list->initialized = FALSE;
    return OK;
}

/**
 * Empty an list
 * @param {LinkList *} list - pointer to a list
 * @return {Status} - execution status
 */
Status clearList(LinkList *list) {
    if (!list->initialized) { // list doesn't exist
        return ERROR;
    }
    listTraverse(list, freeHelper); // use `listTraverse` function to free nodes of the list

    // reinitialize head node
    list->head = NULL;
    list->length = 0;
    return OK;
}

/**
 * Is a list empty
 * @param {LinkList *} list - pointer to list
 * @return {Boolean}
 */
Boolean isListEmpty(LinkList *list) {
    if (!list->initialized) { // list doesn't exist
        return ERROR;
    }

    return list->head == NULL ? TRUE : FALSE;
}

/**
 * Get list length
 * @param {LinkList *} list - pointer to list
 * @return {int}
 */
int listLength(LinkList *list) {
    if (!list->initialized) { // list doesn't exist
        return ERROR;
    }
    return list->length;
}

/**
 * Get element's value on specified index
 * @param {LinkList *} list - pointer to list
 * @param {int} i - index
 * @param {ElemType *} e - pointer to element
 * @return {Status} - execution status
 */
Status getElem(LinkList *list, int i, ElemType *e) {
    if (!list->initialized) { // list doesn't exist
        return ERROR;
    }

    if (i < 1 || i > list->length) { // index is illegal
        return ERROR;
    }

    LinkNode *node = list->head;
    // loop until index `i`
    for (int j = 1; j < i; j++) {
        node = node->next;
    }
    *e = node->value;
    return OK;
}

/**
 * Get element's index by function `compare`
 * @param {LinkList *} list - pointer to list
 * @param {int} e - value to be compared
 * @param {Status (*)(ElemType, ElemType)} compare - function of comparing
 * @return {int} - index of the element
 */
int locateElem(LinkList *list, ElemType e, Status (*compare)(ElemType, ElemType)) {
    if (!list->initialized) { // list doesn't exist
        return ERROR;
    }

    int i = 1;
    LinkNode *node = list->head;
    // find until the element is located or come to the end of list
    while (node && compare(e, node->value) == FALSE) {
        i++;
        node = node->next;
    }

    return i > listLength(list) ? 0 : i;
}

/**
 * Comparing function
 * @param {ElemType} x
 * @param {ElemType} y
 * @return {Boolean}
 */
Boolean equal(ElemType x, ElemType y) {
    return x == y;
}

/**
 * Get element's previous element
 * @param {LinkList *} list - pointer to list
 * @param {ElemType} curr - current element
 * @param {ElemType *} prev - pointer to previous element
 * @return {Status} - execution status
 */
Status priorElem(LinkList *list, ElemType curr, ElemType *prev) {

    if (!list->initialized) { // list doesn't exist
        return ERROR;
    }

    int i = 1;
    LinkNode *node = list->head;
    // find until the element is located or come to the end of list
    while (node && node->next && node->next->value != curr) {
        i++;
        node = node->next;
    }

    if (i >= listLength(list)) {
        return ERROR;
    }

    *prev = node->value;
    return OK;
}

/**
 * Get element's next element
 * @param {LinkList *} list - pointer to list
 * @param {ElemType} curr - current element
 * @param {ElemType *} next - pointer to next element
 * @return {Status} - execution status
 */
Status nextElem(LinkList *list, ElemType curr, ElemType *next) {
    if (!list->initialized) { // list doesn't exist
        return ERROR;
    }

    int i = 1;
    LinkNode *node = list->head;
    // find until the element is located or come to the end of list
    while (node && node->value != curr) {
        i++;
        node = node->next;
    }

    if (i >= listLength(list)) {
        return ERROR;
    }

    *next = node->next->value;
    return OK;
}

/**
 * Insert an element to a list
 * @param {LinkList *} list - pointer to list
 * @param {int} i - index of element to be inserted
 * @param {ElemType} e - the element to be inserted
 * @return {Status} - execution status
 */
Status listInsert(LinkList *list, int i, ElemType e) {
    if (!list->initialized) { // list doesn't exist
        return ERROR;
    }

    if (i < 1 || i > list->length + 1) { // index is illegal
        return ERROR;
    }

    LinkNode *newNode = (LinkNode *) malloc(sizeof(LinkNode));
    newNode->value = e;
    if (i == 1) { // insert to index 1
        newNode->next = list->head;
        list->head = newNode;
    } else { // insert to other index
        LinkNode *node = list->head;
        for (int j = 1; j < i - 1; j++) { // go to previous node
            node = node->next;
        }
        // change pointer to next
        newNode->next = node->next;
        node->next = newNode;
    }
    list->length++;
    return OK;
}

/**
 * Delete the specified element from a list
 * @param {LinkList *} list - pointer to list
 * @param {int} i - index of element to be deleted
 * @param {ElemType *} e - the element to be deleted
 * @return {Status} - execution status
 */
Status listDelete(LinkList *list, int i, ElemType *e) {
    if (!list->initialized) { // list doesn't exist
        return ERROR;
    }

    if (i < 1 || i > list->length) { // index is illegal
        return ERROR;
    }
    LinkNode *nodeToBeDeleted;
    if (i == 1) { // delete index 1
        nodeToBeDeleted = list->head;
        list->head = nodeToBeDeleted->next;
    } else { // delete other index
        LinkNode *node = list->head;
        for (int j = 1; j < i - 1; j++) { // go to previous node
            node = node->next;
        }
        // change pointer to next
        nodeToBeDeleted = node->next;
        node->next = nodeToBeDeleted->next;
    }
    *e = nodeToBeDeleted->value;
    free(nodeToBeDeleted);
    list->length--;
    return OK;
}

/**
 * Select a list
 * @param {LinkList **} currentList - pointer to `LinkList *currentList`
 * @param {LinkList *} nextList - pointer to nextList
 * @return {Status} - execution status
 */
Status selectList(LinkList **currentList, LinkList *nextList) {
    *currentList = nextList;
    return OK;
}

/**
 * Load data from a file
 * @param {LinkList *} list - list
 * @return {Status} - execution status
 */
Status loadData(LinkList *list) {
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL) { // file doesn't exist
        printf("File doesn't exist!\n");
        return ERROR;
    }
    Status result = initializeList(list);
    if (result == ERROR) {
        printf("This list has ALREADY been initialized!\n");
        fclose(fp);
        return ERROR;
    } else if (result == OVERFLOW) {
        printf("Overflow!\n");
        fclose(fp);
        return ERROR;
    } else {
        ElemType element;
        int i = 1, length;
        /* fscanf: read as ascii */
        fscanf(fp, "%d\n\n", &length);
        if (length < 0) {
            printf("Length is illegal!\n");
            return ERROR;
        }
        printf("Loading list of length %d...\n", length);

        while (fscanf(fp, "%d\n", &element) != EOF) { // while element value exists
            listInsert(list, i, element); // insert into the end of list
            i++;
        }

        fclose(fp);
        return OK;
    }
}

/**
 * Save data to a file
 * @param {LinkList *} list - list
 * @return {Status} - execution status
 */
Status saveData(LinkList *list) {
    if (!list->initialized) { // list doesn't exist
        return ERROR;
    }

    FILE *fp = fopen("data.txt", "w");
    if (fp == NULL) { // file doesn't exist
        fp = fopen("data.txt", "wb"); // create it first
    }
    /* fprintf: write in ascii */
    fprintf(fp, "%d\n\n", list->length);
    LinkNode *node = list->head;
    while (node) {
        fprintf(fp, "%d\n", node->value);
        node = node->next;
    }
    fclose(fp);
    return OK;
}

/**
 * show the value of element
 * @param {LinkNode *} e
 * @return {void}
 */
void showElement(LinkNode *e) {
    printf("%d ", e->value);
}

/**
 * show the menu
 * @param {void}
 * @return {void}
 */
void showMenu() {
    printf("\n       Menu of Linear Table On Linked Structure     \n");
    printf("------------------------------------------------------\n");
    printf("    	  1. initializeList  8.  priorElem\n");
    printf("    	  2. destroyList     9.  nextElem\n");
    printf("    	  3. clearList       10. listInsert\n");
    printf("    	  4. isListEmpty     11. listDelete\n");
    printf("    	  5. listLength      12. listTraverse\n");
    printf("    	  6. getElem         13. selectList\n");
    printf("    	  7. locateElem      14. saveData\n");
    printf("    	                     15. loadData\n");
    printf("    	  0. exit\n");
    printf("------------------------------------------------------\n");
}

int main() {
    LinkList *listArray = (LinkList *) malloc(TOTAL_LISTS * sizeof(LinkList)); // array of lists
    for (int i = 0; i < TOTAL_LISTS; i++) { // reset initialization status to false
        listArray[i].initialized = FALSE;
    }
    int currentListIndex = 0; // current index
    LinkList *currentList = &listArray[currentListIndex]; // pointer to current list
    int option; // user option
    do {
        int input; // user input
        int prevIndex = currentListIndex;
        ElemType element, queryElement;
        Status status;
        showMenu();
        printf("Current list: L%d\n", currentListIndex);
        printf("Please input your option[0-15]:\n");
        int isValid = scanf("%d", &option);
        if (!isValid) {
            printf("You entered an invalid value!\n");
            while (getchar() != '\n');
        } else {
            if (option == 0) {
                break;
            }
            switch (option) {
                case 1: // initializeList
                    printf("You've chosen function initializeList(), which initializes a list\n");
                    status = initializeList(currentList);
                    printf(status == OK ? "Initialized successfully!\n" : "Failed to initialize!\n");
                    getchar();
                    break;
                case 2: // destroyList
                    printf("You've chosen function destroyList(), which destroys a list\n");
                    status = destroyList(currentList);
                    printf(status == OK ? "Destroyed successfully!\n" : "Failed to destroy!\n");
                    getchar();
                    break;
                case 3: // clearList
                    printf("You've chosen function clearList(), which empties a list\n");
                    status = clearList(currentList);
                    printf(status == OK ? "Cleared successfully!\n" : "Failed to clear!\n");
                    getchar();
                    break;
                case 4: // isListEmpty
                    printf("You've chosen function isListEmpty(), which shows whether a list is empty\n");
                    status = isListEmpty(currentList);
                    printf(status == ERROR ? "The list has not been initialized\n"
                                           : status == TRUE ? "The list is empty\n"
                                                            : "The list is not empty\n");
                    getchar();
                    break;
                case 5: // listLength
                    printf("You've chosen function listLength(), which shows the length of a list\n");
                    listLength(currentList) >= 0 ? printf("The length of list is %d\n", listLength(currentList))
                                                 : printf("Failed to get the length!\n");
                    getchar();
                    break;
                case 6: // GetElem
                    printf("You've chosen function GetElem(), which gets the specified element's value\n");
                    printf("Please input the index of the element:\n");
                    if (!scanf("%d", &input)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    status = getElem(currentList, input, &element);
                    status == OK ? printf("The value of this element is: %d\n", element)
                                 : printf("Failed to query!\n");
                    getchar();
                    break;
                case 7: // locateElem
                    printf("You've chosen function locateElem(), which gets the specified element's index\n");
                    printf("Please input the value of the element:\n");
                    if (!scanf("%d", &queryElement)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    int index = locateElem(currentList, queryElement, equal);
                    index <= 0 ? printf("This element doesn't exist!\n")
                               : printf("The index of this element is: %d\n", index);
                    getchar();
                    break;
                case 8: // priorElem
                    printf("You've chosen function priorElem(), which gets the previous element of an element\n");
                    printf("Please input the value of the element:\n");
                    if (!scanf("%d", &queryElement)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    status = priorElem(currentList, queryElement, &element);
                    status == OK ? printf("The previous element is: %d\n", element)
                                 : printf("This element doesn't have previous element!\n");
                    getchar();
                    break;
                case 9: // nextElem
                    printf("You've chosen function nextElem(), which gets the next element of an element\n");
                    printf("Please input the value of the element:\n");
                    if (!scanf("%d", &queryElement)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    status = nextElem(currentList, queryElement, &element);
                    status == OK ? printf("The next element is: %d\n", element)
                                 : printf("This element doesn't have next element!\n");
                    getchar();
                    break;
                case 10: // listInsert
                    printf("You've chosen function listInsert(), which inserts an element into a list\n");
                    printf("Please input the index of element to be inserted:\n");
                    if (!scanf("%d", &input)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    printf("Please input the value of it:\n");
                    if (!scanf("%d", &element)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    status = listInsert(currentList, input, element);
                    status == OK ? printf("Succeeded to insert element %d!\n", element)
                                 : printf("Failed to insert!\n");
                    getchar();
                    break;
                case 11: // listDelete
                    printf("You've chosen function listDelete(), which deletes an element from a list\n");
                    printf("Please input the index of element to be deleted:\n");
                    if (!scanf("%d", &input)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    status = listDelete(currentList, input, &element);
                    status == OK ? printf("Succeeded to delete element %d!\n", element)
                                 : printf("Failed to delete!\n");
                    getchar();
                    break;
                case 12: // listTraverse
                    printf("You've chosen function listTraverse(), which traverses a list\n");
                    status = listTraverse(currentList, showElement);
                    status != OK && printf("Failed to traverse!\n");
                    getchar();
                    break;
                case 13: // selectList
                    printf("You've chosen function selectList(), which selects a list\n");
                    printf("Please input the index of list (from 0 to 99):\n");
                    if (!scanf("%d", &currentListIndex) || currentListIndex >= TOTAL_LISTS || currentListIndex < 0) { // invalid input
                        printf("Invalid value!\n");
                        currentListIndex = prevIndex;
                        while (getchar() != '\n');
                        break;
                    }
                    status = selectList(&currentList, &listArray[currentListIndex]);
                    printf(status == OK ? "Selected successfully!\n" : "Failed to select!\n");
                    getchar();
                    break;
                case 14: // saveData
                    printf("You've chosen function saveData(), which saves a list to a file\n");
                    printf("Please input the index of list (from 0 to 99):\n");
                    if (!scanf("%d", &input) || input >= TOTAL_LISTS || input < 0) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    status = saveData(&listArray[input]);
                    printf(status == OK ? "Saved successfully to `data.txt`!\n" : "Failed to save!\n");
                    getchar();
                    break;
                case 15: // loadData
                    printf("You've chosen function loadData(), which loads a list from a file\n");
                    printf("Please prepare `data.txt` in current directory!\n");
                    printf("Please input the index of list which has NOT been initialized (from 0 to 99):\n");
                    if (!scanf("%d", &input) || input >= TOTAL_LISTS || input < 0) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    status = loadData(&listArray[input]);
                    printf(status == OK ? "Loaded successfully!\n" : "Failed to load!\n");
                    getchar();
                    break;
                default: // invalid input
                    printf("You entered an invalid value!\n");
                    getchar();
                    break;
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
