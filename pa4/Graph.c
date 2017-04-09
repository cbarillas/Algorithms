/*
 * Carlos Barillas - cbarilla@ucsc.edu
 * CMPS101 - PA4 - Graph.c
 *
 * Implements a Graph ADT
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"


  //GraphObj
  typedef struct GraphObj {
    List *adjacent;
    int *color;
    int *parent;
    int *distance;
    int order;
    int size;
    int source;
  } GraphObj;

  // Constructors-Destructors ------------------------------------------------

  // newGraph()
  // returns a Graph pointing to a newly created GraphObj
  // with n vertices and no edges
  Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    assert(G != NULL);
    G->adjacent = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->distance = calloc(n+1, sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;
    for (int i = 1;i <= n; ++i) {
      G->adjacent[i] = newList();
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->distance[i] = INF;
    }
    return G;
  }

  // freeGraph()
  // frees all dynamic memory associated with the Graph *pG
  void freeGraph(Graph *pG) {
    if(pG == NULL || (*pG) == NULL)
      return;

    for (int i = 1;i <= getOrder(*pG); ++i) {
      freeList(&((*pG)->adjacent[i]));
    }
    free((*pG)->adjacent);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->distance);
    free(*pG);
    *pG = NULL; 
  }

  // Access functions --------------------------------------------------------

  // getOrder()
  // returns the order(# of vertices) of the graph
  int getOrder(Graph G) {
    if(G == NULL){
      printf("Graph Error: calling getOrder() on NULL Graph reference\n");
      exit(1);
    }
    return G->order;
  }

  // getSize()
  // returns the size(# of edges) of the graph
  int getSize(Graph G) {
    if(G == NULL){
      printf("Graph Error: calling getSize() on NULL Graph reference\n");
      exit(1);
    }
    return G->size;
  }

  // getSource()
  // returns the source vertex most recently used in function BFS(), or NIL if
  // BFS() has not yet been called
  int getSource(Graph G) {
   if(G == NULL){
     printf("Graph Error: calling getSource() on NULL Graph reference\n");
      exit(1);
   }
   return G->source;
  }

// getParent()
// return the parent of vertex u in the BreadthFirst
// tree created by BFS(), or NIL if BFS() has not yet been called
// pre: 1<=u<=getOrder(G)
int getParent(Graph G, int u){
   if(G==NULL){
      printf("Graph Error: calling getParent() on NULL Graph reference\n");
      exit(1);
   }
   if (u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getParent() with vertex out of bounds\n");
      exit(1);
   }
   return G->parent[u];
}

// getDist()
// returns the distance from the most recent BFS source to vertex u
// or INF if BFS() has not yet been called. 
// pre: 1<=u<=getOrder(G)
int getDist(Graph G, int u){
   if(G==NULL){
      printf("Graph Error: calling getDist() on NULL Graph reference\n");
      exit(1);
   }
   if (u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getDist() with vertex out of bounds\n");
      exit(1);
   }
   return G->distance[u];
}

// getPath()
// appends to the List L the vertices of a shortest path in G from 
// source to u, or appends to L the value NIL if no such path exists
// pre: getSource(G)!=NIL
// pre: 1<=u<=getOrder(G)
void getPath(List L, Graph G, int u){
   if(G==NULL){
      printf("Graph Error: calling getPath() on NULL Graph reference\n");
      exit(1);
   }
   if (u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getPath() with vertex out of bounds\n");
      exit(1);
   }
   if (getSource(G) == NIL){
      printf("Graph Error: calling getPath() with source set to NIL\n");
      exit(1);
   }

   if (u==getSource(G))
      append(L,u);
   else if (getParent(G,u) == NIL)
      append(L,NIL);
   else{
      getPath(L,G,getParent(G,u));
      append(L,u);
   }
}

/*** Manipulation procedures ***/
// makeNull()
// deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G){
   if(G==NULL){
      printf("Graph Error: calling makeNull() on NULL Graph reference\n");
      exit(1);
   }
   for(int i =1; i<=getOrder(G); i++){
      clear(G->adjacent[i]);
   }
   G->size = 0;
   G->source = NIL;
}

// addEdge()
// inserts a new edge joining u to v, i.e. u is added to the adjacency List
// of v, and v to the adjacency List of u
// pre: 1<=u<=getOrder(G)
// pre: 1<=v<=getOrder(G)
void addEdge(Graph G, int u, int v){
   if(G==NULL){
      printf("Graph Error: calling addEdge() on NULL Graph reference\n");
      exit(1);
   }
   if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
      printf("Graph Error: calling addEdge() with vertex out of bounds\n");
   }
   addArc(G,u,v);
   addArc(G,v,u);
   G->size++;   
}
// addArc()
// inserts a new directed edge joining u to v, i.e. v is added to the 
// adjacency List of u (but not u to the adjacency List of v)
// pre: 1<=u<=getOrder(G)
// pre: 1<=v<=getOrder(G)
void addArc(Graph G, int u, int v){
   if(G==NULL){
      printf("Graph Error: calling addArc() on NULL Graph reference\n");
      exit(1);
   }
   if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
      printf("Graph Error: calling addArc() with vertex out of bounds\n");
      exit(1);
   }
  List adj = G->adjacent[u];
  if(length(adj)==0){
     append(adj,v);
     return;
  }
  // move to front of G->adjacent[u]
  moveFront(adj);
  while(index(adj)!=-1){
     if (v == get(adj)) //if v already exists in the list, return.
        return;
     else if (v > get(adj)) //if v > current vertex in adj, move next
        moveNext(adj);
      else{ // if v < current vertex in adj, insert before 
        insertBefore(adj,v);
        return;
     }
  } 
   //if we have reached the end of the list
   append(adj,v);
   

}

// BFS()
// runs the BFS algorithm on the Graph G with source s, setting the color, 
// distance, parent, and source fields of G accordingly
void BFS(Graph G, int s){
   if(G==NULL){
      printf("Graph Error: calling BFS() on NULL Graph reference\n");
      exit(1);
   }
   if (s < 1 || s > getOrder(G)){
      printf("Graph Error: calling BFS() with vertex out of bounds\n");
      exit(1);
   }
   for(int i = 1; i <= getOrder(G); i++){
      G->parent[i] = NIL;
      G->distance[i] = INF;
      G->color[i] = WHITE;
   }
   G->source = s;
   G->color[s] = GRAY;
   G->distance[s] = 0;
   List Q = newList();
   append(Q,s);
   while(!isEmpty(Q)){
      int u = front(Q);
      deleteFront(Q);
      List adjacent = G->adjacent[u];
      moveFront(adjacent);
      while(index(adjacent) > -1){
         int v = get(adjacent);
         if(G->color[v] == WHITE){
            G->color[v] = GRAY;
            G->distance[v] = G->distance[u]+1;
            G->parent[v] = u;
            append(Q,v);
         }
         moveNext(adjacent);
      }
      G->color[u] = BLACK; 
   }
   freeList(&Q);
}
     
/*** Other operations ***/

// printGraph()
// prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G){
   if(G == NULL || out == NULL) {
      printf("Graph Error: called printGraph() on NULL Graph reference");
      exit(1);
   }
   for(int i = 1; i <= getOrder(G); ++i) {
      fprintf(out, "%d: ", i);
      printList(out, G->adjacent[i]);
      fprintf(out, "\n");
   }
}
