//Graph.c written by Richard Selmon for pa4
//implementation file for Graph ADT
#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

//structs

typedef struct GraphObj{
   List* neighbor;
   char* color;
   int* parent;
   int* distance; 

   int order;  //number of vertices
   int size;   //number of edges
   int source; //label of vertex most recently used as source for BFS
   
}GraphObj;

//constructors-Destructors

Graph newGraph(int n){
   Graph G = malloc(sizeof(GraphObj));
   G->order = n;
   G->size = 0;
   G->source = NIL;
   
   G->neighbor = calloc(n+1, sizeof(List));
   G->color = calloc(n+1, sizeof(char));
   G->parent = calloc(n+1, sizeof(int));
   G->distance = calloc(n+1, sizeof(int));

   for(int i=1; i<=n; i++){
      G->neighbor[i] = newList();
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->distance[i] = INF;
   }
   return G;
}

void freeGraph(Graph* pG){
   for(int i=0; i <= (*pG)->order; i++){
      freeList(&(*pG)->neighbor[i]);
   }   
   free((*pG)->neighbor);
   free((*pG)->color);
   free((*pG)->parent);
   free((*pG)->distance);
   free(*pG);
   pG = NULL;
} 

//access functions
int getOrder(Graph G){
   if(G == NULL){
      fprintf(stderr, "getOrder() called on NULL graph\n");
      exit(1); 
   }
   return G->order;
}

int getSize(Graph G){
   if(G == NULL){
      fprintf(stderr, "getSize() called on NULL graph\n");
      exit(1); 
   }
   return G->size;
}

int getSource(Graph G){
   if(G == NULL){
      fprintf(stderr, "getSource() called on NULL graph\n");
      exit(1); 
   }
   return G->source;
}

int getParent(Graph G, int u){
   if(G == NULL){
      fprintf(stderr, "getParent() called on NULL graph\n");
      exit(1);
   }
   if((u<=0) || (u > G->order)){
      fprintf(stderr, "getParent() called on u that is 0, negative, or greater than order\n");
      exit(1);
   }
   return G->parent[u];
}

int getDist(Graph G, int u){
   if(G == NULL){
      fprintf(stderr, "getDist() called on NULL graph\n");
      exit(1);
   }
   if((u<=0) || (u > G->order)){
      fprintf(stderr, "getDist() called on u that is 0, negative, or greater than order\n");
      exit(1);
   }
   return G->distance[u];
}

void getPath(List L, Graph G, int u){
   if(G == NULL){
      fprintf(stderr, "getPath() called on NULL graph\n");
      exit(1);
   }
   if(G->source == NIL){
      fprintf(stderr, "getPath() called on NIL source graph\n");
      exit(1);
   }
   if((u<=0) || (u > G->order)){
      fprintf(stderr, "getPath() called on u that is 0, negative, or greater than order\n");
      exit(1);
   }
   //check if path exists
   if(G->distance[u] == INF){
      //printf("no %d-%d path exists\n", G->source, u);
      return;
   }
   //meat
   if(G->source == u) append(L, G->source);
   else{ 
      getPath(L,G, G->parent[u]);
      append(L, u);
   }
}

//Manipulation Procedures
void makeNull(Graph G){
   if(G == NULL){
      fprintf(stderr, "makeNull() called on NULL graph\n");
      exit(1);
   }
   for(int i=1; i <= G->order; i++){
      clear(G->neighbor[i]);
   }
}

void addEdge(Graph G, int u, int v){
   if(G == NULL){
      fprintf(stderr, "addEdge() called on NULL graph\n");
      exit(1);
   }
   if((u<=0) || (u > G->order)){
      fprintf(stderr, "addEdge() called on u that is 0, negative, or greater than order\n");
      exit(1);
   }
   if((v<=0) || (v > G->order)){
      fprintf(stderr, "addEdge() called on v that is 0, negative, or greater than order\n");
      exit(1);
   }
   addArc(G,u,v);
   addArc(G,v,u);
   G->size--;
}

void addArc(Graph G, int u, int v){
   if(G == NULL){
      fprintf(stderr, "addArc() called on NULL graph\n");
      exit(1);
   }
   if((u<=0) || (u > G->order)){
      fprintf(stderr, "addArc() called on u that is 0, negative, or greater than order\n");
      exit(1);
   }
   if((v<=0) || (v > G->order)){
      fprintf(stderr, "addArc() called on v that is 0, negative, or greater than order\n");
      exit(1);
   }
   if(!isEmpty(G->neighbor[u])){ 
      for(moveFront(G->neighbor[u]); (index(G->neighbor[u])>=0) && (v > get(G->neighbor[u])); moveNext(G->neighbor[u])){
         //navigating
      }   
   }
   if(index(G->neighbor[u]) >= 0) insertBefore(G->neighbor[u], v);
   else append(G->neighbor[u], v);
   G->size++;
}

void BFS(Graph G, int s){
   if(G == NULL){
      fprintf(stderr, "BFS() called on NULL graph\n");
      exit(1);
   }
   if((s<=0) || (s > G->order)){
      fprintf(stderr, "BFS() called on s that is 0, negative, or greater than order\n");
      exit(1);
   }
   //BFS initialization stuff
   G->source = s;
   for(int i=1; i<=G->order; i++){
      if(i != s){
         G->color[i] = WHITE;
         G->distance[i] = INF;
         G->parent[i] = NIL;
      }
   }
   G->color[s] = GRAY;
   G->distance[s] = 0;
   G->parent[s] = NIL;
   List Q = newList();
   append(Q,s);
   
   while(!isEmpty(Q)){
      moveFront(Q);  //psuedo dequeue
      int x = get(Q);
      delete(Q);
      //process adjacenty list of x
      if(!isEmpty(G->neighbor[x])){
         for(moveFront(G->neighbor[x]); index(G->neighbor[x])>=0; moveNext(G->neighbor[x])){
            int y = get(G->neighbor[x]);
            if(G->color[y] == WHITE){
               G->color[y] = GRAY;
               G->distance[y] = G->distance[x] + 1;
               G->parent[y] = x;
               append(Q, y);
            }
         }
      }
      G->color[x] = BLACK;
   }
}

void printGraph(FILE* out, Graph G){
   if(G == NULL){
      fprintf(stderr, "printGraph() called on nULL graph");
   }
   for(int i=1; i <= G->order; i++){
      fprintf(out, "%d: ", i);
      printList(out, G->neighbor[i]);
      if(i != G->order) fprintf(out,"\n");
   }
}
