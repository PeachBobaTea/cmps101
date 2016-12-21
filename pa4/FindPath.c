//Richard Selmon pa4
//FindPath.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

#define MAX_LEN 160
#define one 1
#define two 2

int main(int argc, char* argv[]){
   FILE *in, *out;
   char line[MAX_LEN];
   char *token;
   char delimit[] = " \t\r\n\f";
   int phase = one;
   int count = 1;
   Graph G = NULL;
   List L = NULL;
   //check args
   if( argc != 3){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   
   //check input files
   if(in == NULL){
      fprintf(stderr, "Unable to open %s for reading\n", argv[1]);
      exit(1);
   }
   if(out == NULL){
      fprintf(stderr, "Unable to open %s for writing\n", argv[2]);
      exit(1);
   }
   
   while( fgets(line, MAX_LEN, in) != NULL){
      if(count == 1){
         int order = atoi(line);
         G = newGraph(order);
      }
      
      if((phase == one) && (count > 1)){
         //get first int x and second int y
         token = strtok(line, delimit);
         int x = atoi(token);
         token = strtok(NULL, delimit);
         int y = atoi(token);
         //add edges for phase 1 and check your not on the dummy line
         if((x != 0)&&(y != 0)) addEdge(G, x, y);
         //if 0 0 begin phase 2
         if((x == 0)&&(y == 0)){
            phase = two;
            printGraph(out, G);
            fprintf(out, "\n");
         }
      }else if(phase == two){
         //get first int x and second int y
         token = strtok(line, delimit);
         int x = atoi(token);
         token = strtok(NULL, delimit);
         int y = atoi(token);
         
         if((x != 0)&&(y != 0)){
            BFS(G, x);
            L = newList();
            getPath(L, G, y);
            int dist = getDist(G, y);
            if(dist != INF){         
               fprintf(out, "\n");
               fprintf(out, "The distance from %d to %d is %d\nA shortest %d-%d path is: ", x, y, dist, x , y);
               printList(out, L);
               fprintf(out, "\n");
            }else if(dist == INF){
               fprintf(out, "\n");
               fprintf(out, "The distance from %d to %d is infinity\nNo %d-%d path exists", x, y, x , y);
               printList(out, L);
               fprintf(out, "\n");
            }
         }
         if((x == 0)&&(y == 0)){
            break;
         }
          
      }
      count++;
   }
   //free / close stuff
   fclose(in);
   fclose(out);
   freeGraph(&G);
   freeList(&L);
}
