/*
 * Carlos Barillas - cbarilla@ucsc.edu
 * CMPS101 - PA5 - GraphTest.c
 *
 * Test client for the Graph ADT
 */

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char *argv[]) {
  int i, n = 8;
  List S = newList();
  Graph G = newGraph(n);
  Graph T = NULL;

  for (i = 1; i <= n ; i++) append(S, i);
  addArc(G, 1, 2);
  addArc(G, 2, 3);
  addArc(G, 2, 5);
  addArc(G, 2, 6);
  addArc(G, 3, 4);
  addArc(G, 3, 7);
  addArc(G, 4, 3);
  addArc(G, 4, 8);
  addArc(G, 5, 1);
  addArc(G, 5, 6);
  addArc(G, 6, 7);
  addArc(G, 7, 6);
  addArc(G, 7, 8);
  addArc(G, 8, 8);

  printf("Graph G:\n");
  printGraph(stdout, G);

  printf("After running DFS on G\n");
  DFS(G, S);
  printf("\n");
  printf("x:  d  f  p\n");
  for (i = 1; i <= n; i++) {
    fprintf(stdout, "%d: %2d %2d %2d\n",
    i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
  }

  printf("Stack:\n");
  printList(stdout, S);
  printf("\n");

  printf("Transpose of graph G:\n");
  T = transpose(G);
  printGraph(stdout, T);
  printf("\n");

  printf("After running DFS on T\n");
  DFS(T, S);
  printf("\n");
  printf("x:  d  f  p\n");
  for (i = 1; i <= n; i++) {
    fprintf(stdout, "%d: %2d %2d %2d\n",
    i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
  }

  printf("Stack: \n");
  printList(stdout, S);
  printf("\n");
  freeList(&S);
  freeGraph(&G);
  freeGraph(&T);
  return(0);
}

