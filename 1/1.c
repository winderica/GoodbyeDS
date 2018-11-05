//
// Created by winderica on 11/04/2018.
//

/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* type defines*/
typedef int Status;
#define OK 1
#define ERROR -1
#define OVERFLOW -2

typedef int Boolean;
#define TRUE 1
#define FALSE 0

// initial size
#define LIST_SIZE_INITIAL 100
// increment of size
#define LIST_SIZE_INCREMENT 10

typedef struct {
    int value;
} ElemType;

typedef struct {
    ElemType *elem;
    int length;
    int listSize;
} SqList;

/**
 * Initialize an list
 * @param {SqList *} list - pointer to a list
 * @return {Status} - execution status
 */
Status initializeList(SqList *list) {

    if (list->elem) { // already exists
        return ERROR;
    }

    list->elem = (ElemType *) malloc(LIST_SIZE_INITIAL * sizeof(ElemType));

    if (!list->elem) { // failed to malloc
        return OVERFLOW;
    }

    list->length = 0;
    list->listSize = LIST_SIZE_INITIAL;
    return OK;
}

/**
 * Destroy an list
 * @param {SqList *} list - pointer to a list
 * @return {Status} - execution status
 */
Status destroyList(SqList *list) {
    if (!list->elem) { // list doesn't exist
        return ERROR;
    }

    free(list->elem); // free the memory
    list->elem = NULL;
    return OK;
}

/**
 * Empty an list
 * @param {SqList *} list - pointer to a list
 * @return {Status} - execution status
 */
Status clearList(SqList *list) {
    if (!list->elem) { // list doesn't exist
        return ERROR;
    }

    list->length = 0;
    return OK;
}

/**
 * Is a list empty
 * @param {SqList} list - list
 * @return {Boolean}
 */
Boolean isListEmpty(SqList list) {
    if (!list.elem) { // list doesn't exist
        return ERROR;
    }

    return list.length == 0 ? TRUE : FALSE;
}

/**
 * Get list length
 * @param {SqList} list - list
 * @return {int}
 */
int listLength(SqList list) {
    if (!list.elem) { // list doesn't exist
        return ERROR;
    }

    return list.length;
}

/**
 * Get element's value on specified index
 * @param {SqList} list - list
 * @param {int} i - index
 * @param {ElemType *} e - pointer to element
 * @return {Status} - execution status
 */
Status getElem(SqList list, int i, ElemType *e) {
    if (!list.elem) { // list doesn't exist
        return ERROR;
    }

    if (i < 1 || i > list.length) { // index is illegal
        return ERROR;
    }

    *e = list.elem[i - 1];
    return OK;
}

/**
 * Get element's index by function `compare`
 * @param {SqList} list - list
 * @param {int} e - value to be compared
 * @param {Status (*)(ElemType, ElemType)} compare - function of comparing
 * @return {int} - index of the element
 */
int locateElem(SqList list, ElemType e, Status (*compare)(ElemType, ElemType)) {
    if (!list.elem) { // list doesn't exist
        return ERROR;
    }

    int i = 1;

    // find until the element is located or come to the end of list
    while (i <= listLength(list) && compare(e, list.elem[i - 1]) == FALSE) {
        i++;
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
    return x.value == y.value;
}

/**
 * Get element's previous element
 * @param {SqList} list - list
 * @param {ElemType} curr - current element
 * @param {ElemType *} prev - pointer to previous element
 * @return {Status} - execution status
 */
Status priorElem(SqList list, ElemType curr, ElemType *prev) {

    if (!list.elem) { // list doesn't exist
        return ERROR;
    }

    int position = locateElem(list, curr, equal); // get element index

    if (position <= 1) { // position is illegal
        return ERROR;
    }

    *prev = list.elem[position - 2];
    return OK;
}

/**
 * Get element's next element
 * @param {SqList} list - list
 * @param {ElemType} curr - current element
 * @param {ElemType *} next - pointer to next element
 * @return {Status} - execution status
 */
Status nextElem(SqList list, ElemType curr, ElemType *next) {
    if (!list.elem) { // list doesn't exist
        return ERROR;
    }

    int position = locateElem(list, curr, equal); // get element index

    if (position == 0 || position == list.length) { // position is illegal
        return ERROR;
    }

    *next = list.elem[position];
    return OK;
}

/**
 * Insert an element to a list
 * @param {SqList *} list - pointer to list
 * @param {int} i - index of element to be inserted
 * @param {ElemType} e - the element to be inserted
 * @return {Status} - execution status
 */
Status listInsert(SqList *list, int i, ElemType e) {
    if (!list->elem) { // list doesn't exist
        return ERROR;
    }

    if (i < 1 || i > list->length + 1) { // index is illegal
        return ERROR;
    }

    if (list->length >= list->listSize) { // current list is full
        ElemType *newBase = (ElemType *) realloc(list->elem, (list->listSize + LIST_SIZE_INCREMENT) * sizeof(ElemType));

        if (!newBase) { // failed to reallocate
            return OVERFLOW;
        }

        list->elem = newBase;
        list->listSize += LIST_SIZE_INCREMENT;
    }

    for (int j = list->length; j >= i; j--) { // move elements
        list->elem[j] = list->elem[j - 1];
    }

    list->elem[i - 1] = e;
    list->length++;
    return OK;
}

/**
 * Delete the specified element from a list
 * @param {SqList *} list - pointer to list
 * @param {int} i - index of element to be deleted
 * @param {ElemType *} e - the element to be deleted
 * @return {Status} - execution status
 */
Status listDelete(SqList *list, int i, ElemType *e) {
    if (!list->elem) { // list doesn't exist
        return ERROR;
    }

    if (i < 1 || i > list->length) { // index is illegal
        return ERROR;
    }

    *e = list->elem[i - 1];

    for (int j = i; j < list->length; j++) { // move elements
        list->elem[j - 1] = list->elem[j];
    }

    list->length--;
    return OK;
}

/**
 * Traverse the list and print items
 * @param {SqList} list - list
 * @param {void (*)(ElemType)} visitor - print function
 * @return {Status} - execution status
 */
Status listTraverse(SqList list, void (*visitor)(ElemType)) {
    if (!list.elem) { // list doesn't exist
        return ERROR;
    }
    if (!list.length) { // list is empty
        printf("\nThe list is empty!\n");
    } else {
        printf("\nThe elements of current list are:\n");
        for (int i = 0; i < listLength(list); i++) {
            visitor(list.elem[i]);
        }
    }
    return OK;
}

/**
 * Load data from a file
 * @param {SqList *} list - list
 * @return {Status} - execution status
 */
Status loadData(SqList *list) {
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL) { // file doesn't exist
        printf("File doesn't exist!\n");
        return ERROR;
    }

    ElemType element;
    int i = 1, length, listSize;
    /* fscanf: read as ascii */
    fscanf(fp, "%d\n\n", &length);
    fscanf(fp, "%d\n\n", &listSize);
    printf("Loading list of length %d and size %d...\n", length, listSize);
    list->length = 0;
    list->listSize = LIST_SIZE_INITIAL;

    while (fscanf(fp, "%d\n", &element.value) != EOF) { // while element value exists
        listInsert(list, i, element); // insert into the end of list
        i++;
    }

    fclose(fp);
    return OK;
}

/**
 * Save data to a file
 * @param {SqList} list - list
 * @return {Status} - execution status
 */
Status saveData(SqList list) {
    FILE *fp = fopen("data.txt", "w");
    if (fp == NULL) { // file doesn't exist
        fp = fopen("data.txt", "wb"); // create it first
    }

    if (list.elem) {
        /* fprintf: write in ascii */
        fprintf(fp, "%d\n\n", list.length);
        fprintf(fp, "%d\n\n", list.listSize);
        for (int i = 0; i < listLength(list); i++) {
            fprintf(fp, "%d\n", list.elem[i].value);
        }
        fclose(fp);
        return OK;
    } else { // list doesn't exist
        fclose(fp);
        return ERROR;
    }
}

/**
 * show the value of element
 * @param {ElemType} e
 * @return {void}
 */
void showElement(ElemType e) {
    printf("%d ", e.value);
}

/**
 * show the menu
 * @param {void}
 * @return {void}
 */
void showMenu() {
    printf("\n     Menu for Linear Table On Sequence Structure    \n");
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
    SqList *listArray = (SqList *) malloc(LIST_SIZE_INITIAL * sizeof(SqList));
    for (int i = 0; i < LIST_SIZE_INITIAL; i++) {
        listArray[i].elem = NULL;
    }
    int currentListIndex = 0;
    SqList *currentList = &listArray[currentListIndex];
    int option;
    do {
        int input;
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
                case 1:
                    printf("You've chosen function initializeList(), which initializes a list\n");
                    status = initializeList(currentList);
                    printf(status == OK ? "Initialized successfully!\n" : "Failed to initialize!\n");
                    getchar();
                    break;
                case 2:
                    printf("You've chosen function destroyList(), which destroys a list\n");
                    status = destroyList(currentList);
                    printf(status == OK ? "Destroyed successfully!\n" : "Failed to destroy!\n");
                    getchar();
                    break;
                case 3:
                    printf("You've chosen function clearList(), which empties a list\n");
                    status = clearList(currentList);
                    printf(status == OK ? "Cleared successfully!\n" : "Failed to clear!\n");
                    getchar();
                    break;
                case 4:
                    printf("You've chosen function isListEmpty(), which shows whether a list is empty\n");
                    status = isListEmpty(*currentList);
                    printf(status == ERROR ? "The list has not been initialized"
                                           : status == TRUE ? "The list is empty\n"
                                                            : "The list is not empty\n");
                    getchar();
                    break;
                case 5:
                    printf("You've chosen function listLength(), which shows the length of a list\n");
                    listLength(*currentList) >= 0 ? printf("The length of list is %d\n", listLength(*currentList))
                                                  : printf("Failed to get the length!\n");
                    getchar();
                    break;
                case 6:
                    printf("You've chosen function GetElem(), which gets the specified element's value\n");
                    printf("Please input the index of the element:\n");
                    if (!scanf("%d", &input)) {
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    status = getElem(*currentList, input, &element);
                    status == OK ? printf("The value of this element is: %d\n", element.value)
                                 : printf("Failed to query!\n");
                    getchar();
                    break;
                case 7:
                    printf("You've chosen function locateElem(), which gets the specified element's index\n");
                    printf("Please input the value of the element:\n");
                    if (!scanf("%d", &queryElement.value)) {
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    int index = locateElem(*currentList, queryElement, equal);
                    index <= 0 ? printf("This element doesn't exist!\n")
                               : printf("The index of this element is: %d\n", index);
                    getchar();
                    break;
                case 8:
                    printf("You've chosen function priorElem(), which gets the previous element of an element\n");
                    printf("Please input the value of the element:\n");
                    if (!scanf("%d", &queryElement.value)) {
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    status = priorElem(*currentList, queryElement, &element);
                    status == OK ? printf("The previous element is: %d\n", element.value)
                                 : printf("This element doesn't have previous element!\n");
                    getchar();
                    break;
                case 9:
                    printf("You've chosen function nextElem(), which gets the next element of an element\n");
                    printf("Please input the value of the element:\n");
                    if (!scanf("%d", &queryElement.value)) {
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    status = nextElem(*currentList, queryElement, &element);
                    status == OK ? printf("The next element is: %d\n", element.value)
                                 : printf("This element doesn't have next element!\n");
                    getchar();
                    break;
                case 10:
                    printf("You've chosen function listInsert(), which inserts an element into a list\n");
                    printf("Please input the index of element to be inserted:\n");
                    if (!scanf("%d", &input)) {
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    printf("Please input the value of it:\n");
                    if (!scanf("%d", &element.value)) {
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    status = listInsert(currentList, input, element);
                    status == OK ? printf("Succeeded to insert element %d!\n", element.value)
                                 : printf("Failed to insert!\n");
                    getchar();
                    break;
                case 11:
                    printf("You've chosen function listDelete(), which deletes an element from a list\n");
                    printf("Please input the index of element to be deleted:\n");
                    if (!scanf("%d", &input)) {
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    status = listDelete(currentList, input, &element);
                    status == OK ? printf("Succeeded to delete element %d!\n", element.value)
                                 : printf("Failed to delete!\n");
                    getchar();
                    break;
                case 12:
                    printf("You've chosen function listTraverse(), which traverses a list\n");
                    status = listTraverse(*currentList, showElement);
                    status != OK && printf("Failed to traverse!\n");
                    getchar();
                    break;
                case 13:
                    printf("You've chosen function selectList(), which selects a list\n");
                    printf("Please input the index of list (from 0 to 99):\n");
                    if (!scanf("%d", &currentListIndex) || currentListIndex >= LIST_SIZE_INITIAL || currentListIndex < 0) {
                        printf("Invalid value!\n");
                        currentListIndex = prevIndex;
                        while (getchar() != '\n');
                        break;
                    }
                    currentList = &listArray[currentListIndex];
                    printf("Selected successfully!\n");
                    getchar();
                    break;
                case 14:
                    printf("You've chosen function saveData(), which saves a list to a file\n");
                    printf("Please input the index of list (from 0 to 99):\n");
                    if (!scanf("%d", &input) || input >= LIST_SIZE_INITIAL || input < 0) {
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    status = saveData(listArray[input]);
                    printf(status == OK ? "Saved successfully to `data.txt`!\n" : "Failed to save!\n");
                    getchar();
                    break;
                case 15:
                    printf("You've chosen function loadData(), which loads a list from a file\n");
                    printf("Please prepare `data.txt` in current directory!\n");
                    printf("Please input the index of list which has NOT been initialized (from 0 to 99):\n");
                    if (!scanf("%d", &input) || input >= LIST_SIZE_INITIAL || input < 0) {
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    if (initializeList(&listArray[input]) == ERROR) {
                        printf("This list has ALREADY been initialized!\n");
                    } else if (initializeList(&listArray[input]) == OVERFLOW) {
                        printf("Overflow!\n");
                    } else {
                        status = loadData(&listArray[input]);
                        printf(status == OK ? "Loaded successfully!\n" : "Failed to load!\n");
                    }
                    getchar();
                    break;
                default:
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
