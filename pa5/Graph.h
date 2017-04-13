#ifndef GRAPH_H
#define GRAPH_H

#define UNDEF -1
#define NIL 0
#define WHITE 2
#define GRAY 4
#define BLACK 8
#include "List.h"

typedef struct GraphObj *Graph;

// Constructors-Destructors -------------------------------------------------

Graph newGraph(int n);

void freeGraph(Graph *pG);

// Access functions -------------------------------------------------------

int getOrder(Graph G);

int getSize(Graph G);

int getParent(Graph G, int u);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u); 

// Manipulation procedures ------------------------------------------------

void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void DFS(Graph G, List S);

// Other operations -------------------------------------------------------

void printGraph(FILE *out, Graph G);

Graph transpose(Graph G);

Graph copyGraph(Graph G);

#endif
