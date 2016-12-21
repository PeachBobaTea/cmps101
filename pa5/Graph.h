//Graph header file by Richard Selmon
//Pa5 Graph.h
#ifndef _Graph_H_INCLUDE_
#define _Graph_H_INCLUDE_

#include "List.h"
//constant macros
#define NIL 0
#define INF -1
#define UNDEF -1
#define WHITE 1
#define GRAY 2
#define BLACK 3

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
int getDiscover(Graph G, int u);    //pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u);      
void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
void DFS(Graph G, List S);          //pre: length(S) == getOrder(G)

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif
