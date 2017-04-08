//-----------------------------------------------------------------------------
// Carlos Barillas - cbarilla@ucsc.edu
// SID: 1380581
// CMPS101
// PA5 - Graph.c
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

void DFSVisit(Graph G, List S, int u);

//GraphObj
typedef struct GraphObj{
   List *adjacent;
   int *color;
   int *parent;
   int *discover;
   int *finish;
   int order;
   int size;
   int time;
}GraphObj;

/*** Constructors-Destructors ***/

// newGraph()
// returns a Graph pointing to a newly created GraphObj
// with n vertices and no edges
Graph newGraph(int n){
   Graph G = malloc(sizeof(GraphObj));
   assert(G!=NULL);
   G->adjacent = calloc(n+1, sizeof(List));
   G->color = calloc(n+1, sizeof(int));
   G->parent = calloc(n+1, sizeof(int));
   G->discover = calloc(n+1, sizeof(int));
   G->finish = calloc(n+1, sizeof(int));
   G->order = n;
   G->size = 0;
   G->time = 0;
   for(int i=1;i<=n;++i) {
      G->adjacent[i] = newList();
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
   }
   return G;
}

// freeGraph()
// frees all dynamic memory associated with the Graph *pG
void freeGraph(Graph* pG){
   if(pG==NULL||(*pG)==NULL)
      return;

   for(int i=1;i<=getOrder(*pG);++i) {
      freeList(&((*pG)->adjacent[i]));
   }
   free((*pG)->adjacent);
   free((*pG)->color);
   free((*pG)->parent);
   free((*pG)->discover);
   free((*pG)->finish);
   free(*pG);
   *pG = NULL;
   
}

/*** Access functions ***/

// getOrder()
// returns the order(# of vertices) of the graph
int getOrder(Graph G){
   if(G==NULL){
      printf("Graph Error: calling getOrder() on NULL Graph reference\n");
      exit(1);
   }
   return G->order;
}

// getSize()
// returns the size(# of edges) of the graph
int getSize(Graph G){
   if(G==NULL){
      printf("Graph Error: calling getSize() on NULL Graph reference\n");
      exit(1);
   }
   return G->size;
}

// getParent()
// return the parent of vertex u in the DepthFirstSearch
// tree created by DFS(), or NIL if DFS() has not yet been called
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

// getDiscover()
// returns the discovery time after DFS() 
// or UNDEF if DFS() has not yet been called. 
// pre: 1<=u<=getOrder(G)
int getDiscover(Graph G, int u){
   if(G==NULL){
      printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
      exit(1);
   }
   if (u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getDiscover() with vertex out of bounds\n");
      exit(1);
   }
   return G->discover[u];
}

// getFinish()
// returns the finish time after DFS()
// or UNDEF if DFS() has not yet been called.
// pre: 1<=u<=getOrder(G)
int getFinish(Graph G, int u){
   if(G==NULL){
      printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
      exit(1);
   }
   if (u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getDiscover() with vertex out of bounds\n");
      exit(1);
   }
   return G->finish[u];
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
  
  if(length(G->adjacent[u])==0){
     append(G->adjacent[u],v);
     return;
  }
  moveFront(G->adjacent[u]);
  while(index(G->adjacent[u])!=-1){
     if (v == get(G->adjacent[u]))      //if v already exists in the list, return.
        return;
     else if (v > get(G->adjacent[u]))  //if v > current vertex in adj, move next
        moveNext(G->adjacent[u]);
      else{                             // if v < current vertex in adj, insert before 
        insertBefore(G->adjacent[u],v);
        return;
     }
  }
   //if we have reached the end of the list
   append(G->adjacent[u],v);

}

// DFS()
// runs the DFS algorithm on the Graph G, setting the color, 
// parent, and time fields of G accordingly
void DFS(Graph G, List S){
   if(G==NULL||S==NULL){
      printf("Graph Error: calling DFS() on NULL Graph/List reference\n");
      exit(1);
   }
   if (length(S) != getOrder(G)){
      printf("Graph Error: calling DFS() with list length != graph order\n");
      exit(1);
   }
   for(int i = 1; i <= getOrder(G); i++){
      G->color[i] = WHITE;
      G->parent[i] = NIL;
   }
   // List S defines the order in which vertices will be processed
   // clear S so we can prepend the vertices in order of decreasing finish times
   List temp = copyList(S);
   clear(S);
   for(moveFront(temp); index(temp) != -1; moveNext(temp)){
      int u = get(temp);
      if (G->color[u] == WHITE){
         DFSVisit(G,S,u);
      }
   }
   freeList(&temp);
}

// DFSVisit()
void DFSVisit(Graph G, List S, int u){
   if(G==NULL||S==NULL){
      printf("Graph Error: calling DFS() on NULL Graph/List reference\n");
      exit(1);
   }
   // white vertex u has just been discovered
   G->time++;
   G->color[u] = GRAY;
   G->discover[u] = G->time;
   // explore edge (u,v) / adjacency list of u
   for(moveFront(G->adjacent[u]); index(G->adjacent[u])!= -1; moveNext(G->adjacent[u])) {
      int v = get(G->adjacent[u]);
      if (G->color[v]==WHITE){
         G->parent[v] = u;
         DFSVisit(G,S,v);
      }
   }
   // blacken u; it is finished
   G->color[u] = BLACK;
   G->time++;
   G->finish[u] = G->time;
   prepend(S,u);
}

/*** Other operations ***/

// transpose()
// returns the transpose of a Graph G
Graph transpose(Graph G){
   if(G==NULL){
      printf("Graph Error: calling DFS() on NULL Graph reference\n");
      exit(1);
   }
   Graph converse = newGraph(getOrder(G));
   for(int i = 1; i <= getOrder(G); ++i) {
      moveFront(G->adjacent[i]);
      while(index(G->adjacent[i]) != -1) {
         addArc(converse, get(G->adjacent[i]), i);
         moveNext(G->adjacent[i]);  
      }
   }
   return converse;
}

// copyGraph()
// only copy the adjacency information, 
// not information relating to recent calls to DFS().
Graph copyGraph(Graph G){
   if(G==NULL){
      printf("Graph Error: calling DFS() on NULL Graph reference\n");
      exit(1);
   }
   Graph clone = newGraph(getOrder(G));
   for(int i = 1; i <= getOrder(G); ++i) {
      moveFront(G->adjacent[i]);
      while(index(G->adjacent[i]) != -1) {
         addArc(clone,i,get(G->adjacent[i]));
         moveNext(G->adjacent[i]);
      }
   }
   return clone;
}

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
