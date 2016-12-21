//Lex.c written by richard Selmon for pa2


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#define MAX_LEN 160

int main(int argc, char * argv[]){

   int n, count=0;
   FILE *in, *out;
   char line[MAX_LEN];
   //char tokenlist[MAX_LEN];
   //char* token;

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   while( fgets(line, MAX_LEN, in) != NULL)  {
      count++;
   }

   char* lines[count];
   rewind(in);
   /* read each line of input file, then count and print tokens */
   while( fgets(line, MAX_LEN, in) != NULL)  {
      int length = strlen(line); 
      lines[n] = calloc(sizeof(char), (length + 1));
      strcpy(lines[n], line);
      lines[n][length] = '\0';
      n++;
   }
   //print out lines[] to check for monsters
   for(int i; i < count; i++){
      //fprintf(stdout, lines[i]);
   }
   //NOW WE HAVE LINES[] WE CAN SORT 
   //initialize "sorted" list
	List sorted = newList();
   if(lines != NULL) append(sorted, 0);
   moveFront(sorted);
   
	//perform pseudo insert sort
	for( int j = 1; j<count; j++){
      for(moveFront(sorted); (index(sorted) >= 0) && (strcmp(lines[j],lines[get(sorted)]) > 0); moveNext(sorted)){
         //navigation .. no breathing 
      }
		//insert accordingly 
      if (index(sorted) >= 0){
         insertBefore(sorted, j);
      }else{
         append(sorted, j);   
      }
		//jump back after inserting
      moveFront(sorted); 
   }

   for(moveFront(sorted); index(sorted) >= 0; moveNext(sorted)){
      fprintf(out, lines[get(sorted)]);
   }
   
   //free up lists and array
   for(int k = 0; k < count; k++){
      free(lines[k]);
   }
 
   clear(sorted);
   freeList(&sorted);
 
   /* close files */
   fclose(in);
   fclose(out);

   return(0);
}
