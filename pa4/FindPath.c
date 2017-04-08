/*
 * Carlos Barillas - cbarilla@ucsc.edu
 * CMPS101 - PA$ - FindPath.c 
 *
 * Reads input file, makes Graph, performs BFS on Graph. Then returns output 
 * file with graph and uses results of BFS to print out the distance from 
 * source to vertex and print out a shortest path from source to destination
 * compile : % make
 *           % FindPath input_file output_file
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "Graph.h"

#define MAX_LEN 256

int main(int argc, char* argv[]) {
   // check command line for correct number of arguments
   if (argc != 3) {
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   FILE* in = fopen(argv[1], "r");
   FILE* out = fopen(argv[2], "w");
  
   if(in==NULL){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if(out==NULL){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   // v is the number of vertices, initialze Graph
   int v;
   fscanf(in, "%d", &v);
   Graph G = newGraph(v);
   // add edges of new graph
   int x,y;
   while (fscanf(in, "%d %d", &x, &y) == 2) { 
   if (x == 0 && y == 0) break;
      addEdge(G,x,y);
   }
   // print the graph
   printGraph(out, G); 
   
   List L = newList();
   int src, dest;
   while (fscanf(in, "%d %d", &src, &dest)) {
      if (src == 0 && dest == 0) break;
         // perform a Breadth First Search (BFS) from the given source vertex
         BFS(G, src);
         // appends to the List L the vertices of a shortest path in G from 
         // source to dest, or appends to L the value NIL if no such path exist 
         getPath(L, G, dest);
         fprintf(out, "\nThe distance from %d to %d is ", src, dest);
      if (front(L) == 0) {
         fprintf(out, "infinity\nNo %d-%d path exists \n", src, dest);
      } 
      else {
         fprintf(out, "%d\n", getDist(G, dest));
         fprintf(out, "A shortest %d-%d path is: ", src, dest);
         printList(out, L);
         fprintf(out,"\n");
      }
      clear(L);
   }
   fprintf(out, "\n");
   // clear dynamic memory
   freeGraph(&G);
   freeList(&L);
   // close files
   fclose(in);
   fclose(out);
}

