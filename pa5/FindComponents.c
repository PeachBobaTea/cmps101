//Richard Selmon 
//pa5
//FindPath.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

#define MAX_LEN 160

int main(int argc, char* argv[]){
	FILE *in, *out;
	char line[MAX_LEN];
	char *token;
	char delimit[] = " \t\r\n\f";
	int count = 1;
	Graph G = NULL;
	Graph G_transpose = NULL;
	List vertices = NULL;
	List SCC = NULL;
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

	while(fgets(line, MAX_LEN, in)){
		if(count == 1){
			//printf("in first if, count=%d\n", count);
			int order = atoi(line);
			G = newGraph(order);
			count++;
		}else{
			//get x and y from input line "x y"
			token = strtok(line, delimit);
			int x = atoi(token);
			token = strtok(NULL, delimit);
			int y = atoi(token);

			if((x != 0) && (y != 0)) addArc(G, x, y);
			if((x + y) == 0) break;
			//printf("in second if, count=%d, x=%d, y=%d\n", count,x,y);
		}
	}
	fprintf(out,"Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out, "\n\n");
	//put |order| vertices into vertice list
	vertices = newList();
	for(int i=1; i<(getOrder(G) + 1); i++){
		append(vertices,i);
	}
	//compute SCCS of Graph G
	DFS(G, vertices);
	G_transpose = transpose(G);
	DFS(G_transpose, vertices);
	//printList(stdout, vertices);
	
	//extract SCC's from vertices
	//compute # of components
	int components = 0;
	for(moveFront(vertices); index(vertices)>=0; moveNext(vertices)){
		if(getParent(G_transpose, get(vertices)) == NIL) components++;
	}
	fprintf(out, "G contains %d strongly connected components:\n", components);
	SCC = newList();
	int j = 1;
	moveBack(vertices);
	while(j <= components){
		fprintf(out, "Component %d: ", j);	
		while(index(vertices) >= 0){
			int v = get(vertices);
			prepend(SCC, v);
			movePrev(vertices);
			deleteBack(vertices);
			if(getParent(G_transpose, v) == NIL) break;
		}
		printList(out, SCC);
		fprintf(out, "\n");
		clear(SCC);
		j++;
	}

	freeGraph(&G);
	freeGraph(&G_transpose);
	freeList(&vertices);
	freeList(&SCC);
}
