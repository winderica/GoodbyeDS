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

typedef int TraversalOrder;
#define DFS 1
#define BFS 2

// boolean type
typedef int Boolean;
#define TRUE 1
#define FALSE 0

// number of binaryGraphs
#define TOTAL_GRAPHS 100

typedef int Value;

typedef struct ElemType {
    int key;
    Value value;
} ElemType;

typedef struct Arc {
    int from;
    int to;
} Arc;

typedef struct AdjacentVertex {
    int key;
    struct AdjacentVertex *next;
} AdjacentVertex;

typedef struct GraphVertex {
    ElemType data;
    struct AdjacentVertex *adjacency;
    struct GraphVertex *next;
} GraphVertex;

typedef struct Graph {
    GraphVertex *vertices;
    int verticesNumber;
    int arcsNumber;
    Boolean initialized;
} Graph;

Status createGraph(Graph *graph, ElemType *vertices, Arc *arcs, int verticesNumber, int arcsNumber);

Status destroyGraph(Graph *G);

GraphVertex *locateByValue(Graph *graph, int value);

GraphVertex *findVertex(Graph *graph, int key);

void getValue(Graph *graph, int key);

Status setValue(Graph *graph, int key, Value value);

AdjacentVertex *getFirstVertex(Graph *graph, int key);

AdjacentVertex *getNextVertex(Graph *graph, int key, int prevKey);


Status insertVertex(Graph *graph, ElemType vertexData);

Status deleteVertex(Graph *graph, int key);


int insertArc(Graph *graph, int from, int to);


int deleteArc(Graph *graph, int from, int to);

Status depthFirstSearch(Graph *graph, void visitor(GraphVertex *));


Status breadthFirstSearch(Graph *graph, void visitor(GraphVertex *));

Status selectGraph(Graph **currentGraph, Graph *nextGraph);

Status loadData(Graph *graph);

Status saveData(Graph *graph);
void showElement(GraphVertex *e);

void showMenu();
