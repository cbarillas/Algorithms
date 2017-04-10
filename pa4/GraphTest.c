//-----------------------------------------------------------------------------
// Carlos Barillas - cbarilla@ucsc.edu
// SID: 1380581
// CMPS101
// PA4- GrphTest.c 
//----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "Graph.h"

int main(int argc, char *argv[]) {
  int n = 6;
  Graph G = NULL;
  List N = NULL;
   
  // Build graph G 
  G = newGraph(n);
  addEdge(G, 1, 2);
  addEdge(G, 1, 3);
  addEdge(G, 2, 4);
  addEdge(G, 2, 5);
  addEdge(G, 2, 6);
  addEdge(G, 3, 4);
  addEdge(G, 4, 5);
  addEdge(G, 5, 6);
  printf("\nG has %d vertices\n", getOrder(G));
  printf("G has %d edges\n\n", getSize(G));
  printGraph(stdout,G);
   
  printf("\n");

  BFS(G,2);
  printf("Performing BFS() with source vertex equal to %d\n", getSource(G));
  printf("The parent of vertex 1 is %d\n", getParent(G,1));
  printf("The parent of vertex 2 is %d\n", getParent(G,2));
  printf("The parent of vertex 3 is %d\n", getParent(G,3));
  printf("The parent of vertex 4 is %d\n", getParent(G,4));
  printf("The parent of vertex 5 is %d\n", getParent(G,5));
  printf("The parent of vertex 6 is %d\n\n", getParent(G,6));

  BFS(G,5);
  printf("Performing BFS() with source vertex equal to %d\n", getSource(G));
  printf("The parent of vertex 1 is %d\n", getParent(G,1));
  printf("The parent of vertex 2 is %d\n", getParent(G,2));
  printf("The parent of vertex 3 is %d\n", getParent(G,3));
  printf("The parent of vertex 4 is %d\n", getParent(G,4));
  printf("The parent of vertex 5 is %d\n", getParent(G,5));
  printf("The parent of vertex 6 is %d\n", getParent(G,6));
  printf("The distance from %d to 1 is %d\n\n", getSource(G), getDist(G,1));

  N = newList(); 
  //getPath(N,G,88); //prints error message
  getPath(N,G,1);
  printf("A shortest %d to 1 path is: ", getSource(G));
  printList(stdout, N);

  makeNull(G);
  printf("\n\nAfter calling makeNull() on G\n");
  printf("G has %d vertices\n", getOrder(G));
  printf("G has %d edges\n\n", getSize(G));
  printGraph(stdout,G);
   
  freeList(&N);
  freeGraph(&G);
}

