#include "functions.h"

void depthFirstSearchHelper(Graph *graph, GraphVertex *vertex, int *visited, void visitor(GraphVertex *)) {
    visited[vertex->data.key - 1] = 1;
    visitor(vertex);
    AdjacentVertex *adjacentVertex = vertex->adjacency;
    while (adjacentVertex) {
        if (!visited[adjacentVertex->key - 1]) {
            depthFirstSearchHelper(graph, findVertex(graph, adjacentVertex->key), visited, visitor);
        }
        adjacentVertex = adjacentVertex->next;
    }
}
/**
 * Traverses a graph pre-orderly
 * @param {GraphVertex *} node - pointer to a node
 * @param {void (*)(ElemType)} visitor - visit function
 * @return {void}
 */
Status depthFirstSearch(Graph *graph, void visitor(GraphVertex *)) {
    if (!graph->initialized || !graph->vertices) {
        return ERROR;
    }
    int max = 0;
    GraphVertex *vertex = graph->vertices;
    while (vertex) {
        if (vertex->data.key > max) {
            max = vertex->data.key;
        }
        vertex = vertex->next;
    }
    int visited[max];
    for (int i = 0; i < max; i++) {
        visited[i] = 0;
    }
    depthFirstSearchHelper(graph, graph->vertices, visited, visitor);
    return OK;
}

void breadthFirstSearchHelper(Graph *graph, GraphVertex *vertex, int *visited, void visitor(GraphVertex *)) {
    int length = 0;
    int start = 0;
    int vertices = graph->verticesNumber;
    GraphVertex **queue = (GraphVertex **) malloc(vertices * sizeof(GraphVertex *));
    queue[start] = vertex;
    length++;
    visited[vertex->data.key - 1] = 1;
    while (length) {
        visitor(queue[start]);
        length--;
        AdjacentVertex *adjacentVertex = queue[start]->adjacency;
        start++;
        while (adjacentVertex) {
            if (!visited[adjacentVertex->key - 1]) {
                visited[adjacentVertex->key - 1] = 1;
                queue[start + length] = findVertex(graph, adjacentVertex->key);
                length++;
            }
            adjacentVertex = adjacentVertex->next;
        }
    }
}

Status breadthFirstSearch(Graph *graph, void visitor(GraphVertex *)) {
    if (!graph->initialized || !graph->vertices) {
        return ERROR;
    }
    int max = 0;
    GraphVertex *vertex = graph->vertices;
    while (vertex) {
        if (vertex->data.key > max) {
            max = vertex->data.key;
        }
        vertex = vertex->next;
    }
    int visited[max];
    for (int i = 0; i < max; i++) {
        visited[i] = 0;
    }
    breadthFirstSearchHelper(graph, graph->vertices, visited, visitor);
    return OK;
}

/**
 * Create an graph
 * @param {Graph *} graph - pointer to a graph
 * @param {ElemType *} preOrderDefinition - pre order definition
 * @param {ElemType *} inOrderDefinition - in order definition
 * @param {int} length - list length
 * @return {Status} - execution status
 */
Status createGraph(Graph *graph, ElemType *vertices, Arc *arcs, int verticesNumber, int arcsNumber) {
    if (graph->initialized) {
        return ERROR;
    }
    graph->initialized = TRUE;
    int status = OK;
    // insert vertices
    for (int i = 0; i < verticesNumber; i++) {
        status = insertVertex(graph, vertices[i]);
    }
    // insert arcs
    for (int i = 0; i < arcsNumber; i++) {
        status = insertArc(graph, arcs[i].from, arcs[i].to);
    }
    if (status != OK) {
        graph->initialized = FALSE;
        graph->vertices = NULL;
        return status;
    }
    graph->verticesNumber = verticesNumber;
    graph->arcsNumber = arcsNumber;
    return status;
}

void freeAdjacency(Graph *graph, GraphVertex *vertex) {
    AdjacentVertex *adjacentVertex = vertex->adjacency;
    while (adjacentVertex) {
        AdjacentVertex *prevVertex = adjacentVertex;
        adjacentVertex = adjacentVertex->next;
        free(prevVertex);
        graph->arcsNumber--;
    }
}

/**
 * Destroy an graph
 * @param {Graph *} graph - pointer to a graph
 * @return {Status} - execution status
 */
Status destroyGraph(Graph *graph) {
    if (!graph->initialized) { // graph doesn't exist
        return ERROR;
    }
    // free nodes
    GraphVertex *vertex = graph->vertices;
    while (vertex) {
        freeAdjacency(graph, vertex);
        GraphVertex *prevVertex = vertex;
        vertex = vertex->next;
        free(prevVertex);
    }

    graph->vertices = NULL;
    graph->initialized = FALSE;
    return OK;
}

/**
 * Get vertex of a key
 * @param {Graph *} graph - pointer to graph
 * @param {int} key - key
 * @return {GraphVertex *} - pointer to node
 */
GraphVertex *locateByValue(Graph *graph, int value) {
    if (!graph->initialized || !graph->vertices) { // graph doesn't exist
        return NULL;
    }
    GraphVertex *vertex = graph->vertices;
    while (vertex != NULL) {
        // find the vertex
        if (vertex->data.value == value) {
            return vertex;
        }
        vertex = vertex->next;
    }
    return NULL;
}

/**
 * Get value of a node
 * @param {Graph *} graph - pointer to graph
 * @param {int} key - key
 * @return {int} - value of a node
 */
GraphVertex *findVertex(Graph *graph, int key) {
    if (!graph->initialized || !graph->vertices) { // graph doesn't exist
        return NULL;
    }
    GraphVertex *vertex = graph->vertices;
    while (vertex != NULL) {
        // find the vertex
        if (vertex->data.key == key) {
            return vertex;
        }
        vertex = vertex->next;
    }
    return NULL;
}

void getValue(Graph *graph, int key) {
    GraphVertex *vertex = findVertex(graph, key);
    vertex == NULL ? printf("This vertex doesn't exist!\n")
                   : printf("The value of vertex is %d\n", vertex->data.value);
}

/**
 * Set value of a node
 * @param {Graph *} graph - pointer to graph
 * @param {int} key - key
 * @param {Value} value - value
 * @return {Status} - execution status
 */
Status setValue(Graph *graph, int key, Value value) {
    GraphVertex *vertex = findVertex(graph, key);
    if (vertex) {
        vertex->data.value = value;
        return OK;
    }
    return ERROR;
}

/**
 * Get left sibling of a node
 * @param {Graph *} graph - pointer to graph
 * @param {int} key - key
 * @return {GraphVertex *} - left sibling
 */
AdjacentVertex *getFirstVertex(Graph *graph, int key) {
    GraphVertex *vertex = findVertex(graph, key);
    if (vertex) {
        return vertex->adjacency;
    }
    return NULL;
}

/**
 * Get right sibling of a node
 * @param {Graph *} graph - pointer to graph
 * @param {int} key - key
 * @return {GraphVertex *} - right sibling
 */
AdjacentVertex *getNextVertex(Graph *graph, int key, int prevKey) {
    GraphVertex *vertex = findVertex(graph, key);
    if (vertex) {
        AdjacentVertex *adjacentVertex = vertex->adjacency;
        while (adjacentVertex) {
            if (adjacentVertex->key == prevKey) {
                return adjacentVertex->next;
            }
            adjacentVertex = adjacentVertex->next;
        }
    }
    return NULL;
}

/**
 * Insert a vertex to a graph
 * @param {Graph *} graph - pointer to graph
 * @param {GraphVertex *} node - node to insert to
 * @param {Boolean} isLeft - insert to left or tight
 * @param {Graph *} newGraph - pointer to newGraph
 * @return {Status} - execution status
 */
Status insertVertex(Graph *graph, ElemType vertexData) {
    if (!graph->initialized) { // graph doesn't exist
        return ERROR;
    }
    GraphVertex *vertex = findVertex(graph, vertexData.key);

    if (vertex) {
        return ERROR;
    }
    GraphVertex *newVertex = (GraphVertex *) malloc(sizeof(GraphVertex));
    if (newVertex == NULL) {
        return ERROR;
    }
    // set new vertex
    newVertex->data = vertexData;
    newVertex->adjacency = NULL;
    newVertex->next = NULL;
    if (graph->vertices == NULL) {
        graph->vertices = newVertex;
    } else {
        GraphVertex *graphVertex = graph->vertices;
        while (graphVertex->next) {
            graphVertex = graphVertex->next;
        }
        graphVertex->next = newVertex;
    }
    graph->verticesNumber++;
    return OK;
}

/**
 * Delete a vertex from a graph
 * @param {Graph *} graph - pointer to graph
 * @param {GraphVertex *} node - node to delete from
 * @param {Boolean} isLeft - insert to left or tight
 * @return {Status} - execution status
 */

Status deleteVertex(Graph *graph, int key) {
    if (!graph->initialized || !graph->vertices) { // graph doesn't exist
        return ERROR;
    }
    GraphVertex *vertex = graph->vertices;
    while (vertex) {
        if (vertex->data.key != key) {
            deleteArc(graph, vertex->data.key, key);
        }
        vertex = vertex->next;
    }
    vertex = graph->vertices;
    if (vertex->data.key == key) {
        graph->vertices = vertex->next;
        freeAdjacency(graph, vertex);
        free(vertex);
        graph->verticesNumber--;
        return OK;
    } else {
        while (vertex->next) {
            if (vertex->next->data.key == key) {
                GraphVertex *nextVertex = vertex->next;
                vertex->next = nextVertex->next;
                freeAdjacency(graph, nextVertex);
                free(nextVertex);
                graph->verticesNumber--;
                return OK;
            }
            vertex = vertex->next;
        }
    }
    return ERROR;
}

/**
 * Insert a arc to a graph
 * @param {Graph *} graph - pointer to graph
 * @param {GraphVertex *} node - node to insert to
 * @param {Boolean} isLeft - insert to left or tight
 * @param {Graph *} newGraph - pointer to newGraph
 * @return {Status} - execution status
 */
Status insertArc(Graph *graph, int from, int to) {
    GraphVertex *srcVertex = findVertex(graph, from);
    GraphVertex *dstVertex = findVertex(graph, to);
    if (!srcVertex || !dstVertex) {
        return ERROR;
    }
    AdjacentVertex *adjacentVertex = srcVertex->adjacency;
    if (!adjacentVertex) {
        srcVertex->adjacency = (AdjacentVertex *) malloc(sizeof(AdjacentVertex));
        srcVertex->adjacency->key = to;
        srcVertex->adjacency->next = NULL;
    } else {
        if (adjacentVertex->key == to) {
            return ERROR;
        }
        while (adjacentVertex->next) {
            if (adjacentVertex->next->key == to) {
                return ERROR;
            }
            adjacentVertex = adjacentVertex->next;
        }
        adjacentVertex->next = (AdjacentVertex *) malloc(sizeof(AdjacentVertex));
        adjacentVertex->next->key = to;
        adjacentVertex->next->next = NULL;
    }
    graph->arcsNumber++;
    return OK;
}

/**
 * Delete a arc from a graph
 * @param {Graph *} graph - pointer to graph
 * @param {GraphVertex *} node - node to delete from
 * @param {Boolean} isLeft - insert to left or tight
 * @return {Status} - execution status
 */

Status deleteArc(Graph *graph, int from, int to) {
    GraphVertex *srcVertex = findVertex(graph, from);
    GraphVertex *dstVertex = findVertex(graph, to);
    if (!srcVertex || !dstVertex) {
        return ERROR;
    }
    AdjacentVertex *adjacentVertex = srcVertex->adjacency;
    if (!adjacentVertex) {
        return ERROR;
    } else if (adjacentVertex->key == to) {
        srcVertex->adjacency = adjacentVertex->next;
        free(adjacentVertex);
        graph->arcsNumber--;
        return OK;
    } else {
        while (adjacentVertex->next) {
            if (adjacentVertex->next->key == to) {
                AdjacentVertex *nextVertex = adjacentVertex->next;
                adjacentVertex->next = nextVertex->next;
                free(nextVertex);
                graph->arcsNumber--;
                return OK;
            }
            adjacentVertex = adjacentVertex->next;
        }
    }
    return ERROR;
}

/**
 * Select a graph
 * @param {Graph **} currentGraph - pointer to `Graph *currentGraph`
 * @param {Graph *} nextGraph - pointer to nextGraph
 * @return {Status} - execution status
 */
Status selectGraph(Graph **currentGraph, Graph *nextGraph) {
    *currentGraph = nextGraph;
    return OK;
}

/**
 * Helper function to load data
 * @param {Graph *} graph - graph
 * @param {FILE *} fp - file pointer
 * @return {Status} - execution status
 */
Status loadHelper(Graph *graph, FILE *fp) {
    int verticesNumber;
    fscanf(fp, "%d", &verticesNumber);
    ElemType *vertices = (ElemType *) malloc(verticesNumber * sizeof(ElemType));
    int key, value;
    int i = 0;
    while (i < verticesNumber) {
        fscanf(fp, "%d %d", &key, &value);
        vertices[i].key = key;
        vertices[i].value = value;
        i++;
    }
    int arcsNumber;
    fscanf(fp, "%d", &arcsNumber);
    Arc *arcs = (Arc *) malloc(arcsNumber * sizeof(Arc));
    int from, to;
    int j = 0;
    while (j < arcsNumber) {
        fscanf(fp, "%d %d", &from, &to);
        arcs[j].from = from;
        arcs[j].to = to;
        j++;
    }
    Status status = createGraph(graph, vertices, arcs, verticesNumber, arcsNumber);
    return status;
}

/**
 * Load data from a file
 * @param {Graph *} graph - graph
 * @return {Status} - execution status
 */
Status loadData(Graph *graph) {
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL) { // file doesn't exist
        printf("File doesn't exist!\n");
        return ERROR;
    }
    if (graph->initialized) {
        printf("This binaryTree has ALREADY been initialized!\n");
        fclose(fp);
        return ERROR;
    }
    Status status = loadHelper(graph, fp);
    fclose(fp);
    return status;
}

/**
 * Save data to a file
 * @param {Graph *} graph - graph
 * @return {Status} - execution status
 */
Status saveData(Graph *graph) {
    if (!graph->initialized || !graph->vertices) { // binaryTree doesn't exist
        return ERROR;
    }

    FILE *fp = fopen("data.txt", "w+");
    fprintf(fp, "%d\n", graph->verticesNumber);
    GraphVertex *vertex = graph->vertices;
    while (vertex) {
        fprintf(fp, "%d %d\n", vertex->data.key, vertex->data.value);
        vertex = vertex->next;
    }
    fprintf(fp, "%d\n", graph->arcsNumber);
    vertex = graph->vertices;
    while (vertex) {
        AdjacentVertex *adjacentVertex = vertex->adjacency;
        if (adjacentVertex) {
            fprintf(fp, "%d %d\n", vertex->data.key, adjacentVertex->key);
            while (adjacentVertex->next) {
                fprintf(fp, "%d %d\n", vertex->data.key, adjacentVertex->next->key);
                adjacentVertex = adjacentVertex->next;
            }
        }
        vertex = vertex->next;
    }
    fclose(fp);
    return OK;
}

/**
 * show the value of element
 * @param {GraphVertex *} e
 * @return {void}
 */
void showElement(GraphVertex *e) {
    printf("%d ", e->data.value);
}

/**
 * show the menu
 * @param {void}
 * @return {void}
 */
void showMenu() {
    printf("\n                    Menu of Graph                    \n");
    printf("------------------------------------------------------\n");
    printf("    1: createGraph                2: destroyGraph\n");
    printf("    3: locateByValue              4: getValue\n");
    printf("    5: setValue                   6: getFirstVertex\n");
    printf("    7: getNextVertex              8: insertVertex \n");
    printf("    9: deleteVertex               10: insertArc\n");
    printf("    11: deleteArc                 12: depthFirstSearch\n");
    printf("    13: breadthFirstSearch        14: selectGraph\n");
    printf("    15: saveData                  16: loadData\n");
    printf("    0: quit\n");
    printf("------------------------------------------------------\n");
}
