#include "src/functions.h"

int main() {
    Graph *graphArray = (Graph *) malloc(TOTAL_GRAPHS * sizeof(Graph)); // array of graphs
    for (int i = 0; i < TOTAL_GRAPHS; i++) {
        graphArray[i].initialized = FALSE;
        graphArray[i].vertices = NULL;
    }
    int currentGraphIndex = 0; // current index
    Graph *currentGraph = &graphArray[currentGraphIndex]; // pointer to current graph
    int option; // user option
    do {
        showMenu();
        printf("Current graph: G%d\n", currentGraphIndex);
        printf("Please input your option[0-16]:\n");
        int isValid = scanf("%d", &option);
        if (!isValid) {
            printf("You entered an invalid value!\n");
            while (getchar() != '\n');
        } else {
            if (option == 0) {
                break;
            }
            switch (option) {
                case 1: { // createGraph
                    printf("You've chosen function createGraph(), which creates a graph\n");
                    printf("Please input the number of vertices:\n");
                    int verticesNumber;
                    if (!scanf("%d", &verticesNumber) || verticesNumber <= 0) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    printf("Please input the key and value of vertices:\n");
                    ElemType *vertices = (ElemType *) malloc(verticesNumber * sizeof(ElemType));
                    int key, value;
                    int i = 0;
                    while (i < verticesNumber) {
                        scanf("%d %d", &key, &value);
                        vertices[i].key = key;
                        vertices[i].value = value;
                        i++;
                    }
                    printf("Please input the number of arcs:\n");
                    int arcsNumber;
                    if (!scanf("%d", &arcsNumber) || arcsNumber <= 0) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    printf("Please input the start and end of arcs:\n");
                    Arc *arcs = (Arc *) malloc(arcsNumber * sizeof(Arc));
                    int from, to;
                    int j = 0;
                    while (j < arcsNumber) {
                        scanf("%d %d", &from, &to);
                        arcs[j].from = from;
                        arcs[j].to = to;
                        j++;
                    }
                    Status status = createGraph(currentGraph, vertices, arcs, verticesNumber, arcsNumber);
                    printf(status == OK ? "Created successfully!\n" : "Failed to create!\n");
                    free(arcs);
                    free(vertices);
                    getchar();
                    break;
                }
                case 2: { // destroyGraph
                    printf("You've chosen function destroyGraph(), which destroys a graph\n");
                    Status status = destroyGraph(currentGraph);
                    printf(status == OK ? "Destroyed successfully!\n" : "Failed to destroy!\n");
                    getchar();
                    break;
                }
                case 3: { // findVertex
                    printf("You've chosen function findVertex(), which finds a vertex\n");
                    printf("Please input the value of vertex:\n");
                    int value;
                    if (!scanf("%d", &value)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    GraphVertex *vertex = locateByValue(currentGraph, value);
                    vertex == NULL ? printf("This vertex doesn't exist!\n")
                                    : printf("The key of vertex is %d\n", vertex->data.key);
                    getchar();
                    break;
                }
                case 4: { // getValue
                    printf("You've chosen function getValue(), which gets the value of a vertex\n");
                    printf("Please input the key of vertex:\n");
                    int key;
                    if (!scanf("%d", &key)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    getValue(currentGraph, key);
                    getchar();
                    break;
                }
                case 5: { // setValue
                    printf("You've chosen function setValue(), which sets the value of a vertex\n");
                    printf("Please input the key, value of vertex:\n");
                    int key, value;
                    if (!scanf("%d %d", &key, &value)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    Status status = setValue(currentGraph, key, value);
                    printf(status == OK ? "Set successfully!\n" : "Failed to set!\n");
                    getchar();
                    break;
                }
                case 6: { // getFirstVertex
                    printf("You've chosen function getFirstVertex(), which gets the first adjacent vertex\n");
                    printf("Please input the key of vertex:\n");
                    int key;
                    if (!scanf("%d", &key)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    AdjacentVertex *vertex= getFirstVertex(currentGraph, key);
                    vertex == NULL ? printf("This vertex doesn't have adjacent vertex!\n")
                                   : printf("The key of vertex is %d\n", vertex->key);
                    getchar();
                    break;
                }
                case 7: { // getNextVertex
                    printf("You've chosen function getNextVertex(), which gets the next adjacent vertex\n");
                    printf("Please input the key, previous key of vertex:\n");
                    int key, prevKey;
                    if (!scanf("%d %d", &key, &prevKey)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    AdjacentVertex *vertex= getNextVertex(currentGraph, key, prevKey);
                    vertex == NULL ? printf("This vertex doesn't have adjacent vertex!\n")
                                   : printf("The key of vertex is %d\n", vertex->key);
                    getchar();
                    break;
                }
                case 8: { // insertVertex
                    printf("You've chosen function insertVertex(), which inserts a vertex\n");
                    printf("Please input the key, value of vertex:\n");
                    int key, value;
                    if (!scanf("%d %d", &key, &value)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    ElemType element;
                    element.key = key;
                    element.value = value;
                    int status = insertVertex(currentGraph, element);
                    printf(status == OK ? "Inserted successfully!\n" : "Failed to insert!\n");
                    getchar();
                    break;
                }
                case 9: { // deleteVertex
                    printf("You've chosen function deleteVertex(), which deletes a vertex\n");
                    printf("Please input the key of vertex:\n");
                    int key;
                    if (!scanf("%d", &key)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    Status status = deleteVertex(currentGraph, key);
                    printf(status == OK ? "Deleted successfully!\n" : "Failed to delete!\n");
                    getchar();
                    break;
                }
                case 10: { // insertArc
                    printf("You've chosen function insertArc(), which inserts an arc\n");
                    printf("Please input the start, end of arc:\n");
                    int from, to;
                    if (!scanf("%d %d", &from, &to)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    Status status = insertArc(currentGraph, from, to);
                    printf(status == OK ? "Inserted successfully!\n" : "Failed to insert!\n");
                    getchar();
                    break;
                }
                case 11: { // deleteArc
                    printf("You've chosen function deleteArc(), which deletes an arc\n");
                    printf("Please input the start, end of arc:\n");
                    int from, to;
                    if (!scanf("%d %d", &from, &to)) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    Status status = deleteArc(currentGraph, from, to);
                    printf(status == OK ? "Deleted successfully!\n" : "Failed to delete!\n");
                    getchar();
                    break;
                }
                case 12: { // depthFirstSearch
                    printf("You've chosen function depthFirstSearch(), which which traverses a graph depth-first\n");

                    depthFirstSearch(currentGraph, showElement);
                    getchar();
                    break;
                }
                case 13: { // breadthFirstSearch
                    printf("You've chosen function breadthFirstSearch(), which traverses a graph breadth-first\n");
                    breadthFirstSearch(currentGraph, showElement);
                    getchar();
                    break;
                }
                case 14: { // selectGraph
                    printf("You've chosen function selectGraph(), which selects a graph\n");
                    printf("Please input the index of list (from 0 to 99):\n");
                    int index;
                    if (!scanf("%d", &index) || index >= TOTAL_GRAPHS || index < 0) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    } else {
                        currentGraphIndex = index;
                    }
                    Status status = selectGraph(&currentGraph, &graphArray[currentGraphIndex]);
                    printf(status == OK ? "Selected successfully!\n" : "Failed to select!\n");
                    getchar();
                    break;
                }
                case 15: { // saveData
                    printf("You've chosen function saveData(), which saves a graph to a file\n");
                    printf("Please input the index of graph which has NOT been initialized (from 0 to 99):\n");
                    int index;
                    if (!scanf("%d", &index) || index >= TOTAL_GRAPHS || index < 0) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    Status status = saveData(&graphArray[index]);
                    printf(status == OK ? "Saved successfully to `data.txt`!\n" : "Failed to save!\n");
                    getchar();
                    break;
                }
                case 16: { // loadData
                    printf("You've chosen function loadData(), which loads a graph from a file\n");
                    printf("Please prepare `data.txt` in current directory!\n");
                    printf("Please input the index of graph which has NOT been initialized (from 0 to 99):\n");
                    int index;
                    if (!scanf("%d", &index) || index >= TOTAL_GRAPHS || index < 0) { // invalid input
                        printf("Invalid value!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    Status status = loadData(&graphArray[index]);
                    printf(status == OK ? "Loaded successfully!\n" : "Failed to load!\n");
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
