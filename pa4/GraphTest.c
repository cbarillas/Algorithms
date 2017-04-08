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

int main(int argc, char* argv[]) {
  Graph a = newGraph(4);
  printf("%d\n", getSize(a)); // 0

  //addEdge(a, 1, 2);
  //printf("%d\n", getSize(a)); // 1

  addArc(a, 1, 2);
  printf("%d\n", getSize(a)); // 1

  addArc(a, 2, 3);
  printf("%d\n", getSize(a)); // 2

  freeGraph(&a);
}

/*  Graph a = newGraph(4);
  printf("%d \n", getOrder(a));//4
  printf("%d \n", getSize(a));//0
  
  addArc(a, 2, 3);
  printf("%d \n", getOrder(a));//4
  printf("%d \n", getSize(a));//1

  makeNull(a);
  printf("%d \n", getOrder(a));//4
  printf("%d \n", getSize(a));//0

  freeGraph(&a);
}
*/
/*
  Graph a = newGraph(4);
  printf("%d \n", getOrder(a));//4
  printf("%d \n", getSize(a));//0

  addEdge(a, 2, 3);
  printf("%d \n", getOrder(a));//4
  printf("%d \n", getSize(a));//1

  makeNull(a);
  printf("%d \n", getOrder(a));//4
  printf("%d \n", getSize(a));//0

  freeGraph(&a);
}
*/
/*
  //Graph is from CLRS pg 596 Third edition
  //[r,s,t,u,v,w,x,y] = [1,2,3,4,5,6,7,8]
  //BUT there is no vertex between (t and u) and (r, v)
  Graph a = newGraph(8);
  addEdge(a, 1, 2);//r-s
  //addEdge(a, 1, 5);//r-v
  addEdge(a, 2, 6);//s-w
  addEdge(a, 6, 3);//w-t
  addEdge(a, 6, 7);//w-x
  addEdge(a, 3, 7);//t-x
  //addEdge(a, 3, 4);//t-u
  addEdge(a, 4, 7);//u-x
  addEdge(a, 4, 8);//u-y
  addEdge(a, 7, 8);//x-y

  List l = newList();
  BFS(a, 2);
  clear(l);
  getPath(l, a, 4);
  printList(stdout, l);// 2 6 7 4
  printf("\n");             

  clear(l);
  getPath(l, a, 2);
  printList(stdout, l);// 2
  printf("\n");

  clear(l);
  getPath(l, a, 8);
  printList(stdout, l);// 2 6 7 8
  printf("\n");

  clear(l);
  getPath(l, a, 5);
  printf("%d\n", length(l));// 1
  printf("%d\n", front(l) == NIL);//1

  freeList(&l);
  freeGraph(&a);
}
*/

/*
 Graph a = newGraph(8);

  addEdge(a, 1, 2);//r-s
  addEdge(a, 1, 5);//r-v
  addEdge(a, 2, 6);//s-w
  addEdge(a, 6, 3);//w-t
  addEdge(a, 6, 7);//w-x
  addEdge(a, 3, 7);//t-x
  addEdge(a, 3, 4);//t-u
  addEdge(a, 4, 7);//u-x
  addEdge(a, 4, 8);//u-y
  addEdge(a, 7, 8);//x-y
  
  List l = newList();
  printList(stdout, l);//
  printf("%d\n", length(l));//0

  BFS(a, 2);
  clear(l);
  getPath(l, a, 4);
  printList(stdout, l);// 2 6 3 4
  printf("\n");

  clear(l);
  getPath(l, a, 8);
  printList(stdout, l);// 2 6 7 8
  printf("\n");

  clear(l);
  getPath(l, a, 5);
  printList(stdout, l);// 2 1 5
  printf("\n");

  freeList(&l);
  freeGraph(&a);
}
*/

/*
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
*/
