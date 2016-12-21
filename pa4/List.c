//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
//List.c written by Richard selmon for pa4
#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* prev;
   struct NodeObj* next;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}


// freeList()
// Frees all heap memory associated with List *pQ, and sets *pQ to NULL.S
void freeList(List* pQ){
   if(pQ!=NULL && *pQ!=NULL) { 
      while( !isEmpty(*pQ) ) { 
         deleteFront(*pQ); 
      }
      free(*pQ);
      *pQ = NULL;
   }
}


// Access functions -----------------------------------------------------------
//int index() returns index of cursor
int index(List L){
   if(L == NULL){
      printf("List Error: calling index() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor != NULL){
      return L->index;
   }
   return -1;
}
// getFront()
// Returns the value at the front of Q.
// Pre: !isEmpty(Q)
int front(List L){
   if( L==NULL ){
      printf("List Error: calling getFront() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling getFront() on an empty List\n");
      exit(1);
   }
   return(L->front->data);
}

int back(List L){
   if( L==NULL ){
      printf("List Error: calling back on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling getFront() on an empty List\n");
      exit(1);
   }
   return(L->back->data);
}

// getLength()
// Returns the length of Q.
int length(List L){
   if( L==NULL ){
      printf("List Error: calling getLength() on NULL List reference\n");
      exit(1);
   }
   return(L->length);
}

// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
int isEmpty(List L){
   if( L==NULL ){
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(1);
   }
   
   return(L->length==0);
   
}

int get(List L){
   if(L == NULL){
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }else if(L->cursor == NULL){
      printf("List Error: calling get() on cursor List reference\n");
      exit(1);
   }
   return L->cursor->data;
}

// Manipulation procedures ----------------------------------------------------

//clear() resets list to its empty state
void clear(List L){
   Node N = NULL;
   if( L==NULL ){
      printf("List Error: calling clear() on NULL List reference\n");
      exit(1);
   }
   N = L->front;
   while(N != NULL){
      Node temp = N->next;
      freeNode(&N);
      N = temp;
   }
   L->length = 0;
   L->index = -1;
   L->cursor = L->front = L->back = NULL;
}
// EnList()
// Places new data element at the back of Q
void append(List L, int data){
   Node N = newNode(data);
   if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ) { 
      L->front = L->back = N; 
   }else{ 
      N->prev = L->back;
      N->next = NULL;
      L->back->next = N; 
      L->back = N; 
   }
   L->length++;
}

//inserts before front of list
void prepend(List L, int data){
   Node N = newNode(data);
   if( L==NULL ){
      printf("List Error: calling prepend on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ) {
      L->front = L->back = N;
   }else{
      N->next = L->front;
      N->prev = NULL;
      L->front->prev = N;
      L->front = N;
   }
   L->length++;
   if(L->cursor != NULL){
      L->index++;
   }
}

//insertBefore the cursor
void insertBefore(List L, int data){
   if( L==NULL ){
      printf("List Error: calling insertBefore on NULL List reference\n");
      exit(1);
   }
   if(L->cursor == NULL){
      printf("List Error: calling insertBefore on null cursor\n");
      exit(1);
   }
   Node N = newNode(data);
   if (L->index > 0){
      N->next = L->cursor;
      N->prev = L->cursor->prev;
      L->cursor->prev->next = N;
      L->cursor->prev = N;
   }else if(L->index == 0){
      L->cursor->prev = N;
      N->next = L->cursor;
      N->prev = NULL;
      L->front = N;
   }
   L->index++;
   L->length++;   
}
//insertAfter
void insertAfter(List L, int data){
   if( L==NULL ){
      printf("List Error: calling insertAfter on NULL List reference\n");
      exit(1);
   }
   if(L->cursor == NULL){
      printf("List Error: calling insertAfter on null cursor\n");
      exit(1);
   }
   Node N = newNode(data);
   if(L->index == (L->length-1)){
      N->next = NULL;
      N->prev = L->cursor;
      L->cursor->next = N;
      L->back = N;
   }else{
      //Node temp = L->cursor;
      N->next = L->cursor->next;
      N->prev = L->cursor;
      L->cursor->next->prev = N;
      L->cursor->next = N;
   }
   L->length++;
}


// deleteFront() formerly Delist/Dequeue
// Deletes element at front of Q
// Pre: !isEmpty(Q)
void deleteFront(List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteFront on an empty List\n");
      exit(1);
   }
   N = L->front;
   if( length(L)>1 ) { 
      L->front = L->front->next;
      L->front->prev = NULL; 
   }else{ 
      L->front = L->back = NULL; 
   }
   
   if(L->index == 0) L->cursor = NULL;
   
   if(L->cursor != NULL){
      L->index--;
   }
   L->length--;
   freeNode(&N);
}
//deleteBack deletes element at back of the list
void deleteBack(List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteBack on an empty List\n");
      exit(1);
   }
   N = L->back;
   if( length(L)>1 ) {
      L->back = L->back->prev;
      L->back->next = NULL;
   }else{
      L->front = L->back = NULL;
   }
   if(L->index == (L->length -1)) L->cursor = NULL;
   L->length--;
   freeNode(&N);
}

//delete() deletes element in list and makes cursor undefined
void delete(List L){
   if( L==NULL ){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling delete() on an empty List\n");
      exit(1);
   }
   if( L->cursor == NULL){
      printf("List Error: calling delete() on a null cursor\n");
      exit(1);
   }
   if( L->index == 0){
      deleteFront(L);
   }else if(L->index == (L->length-1)){
      deleteBack(L);
   }else{
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
      L->length--;
      
      Node N = NULL;
      N = L->cursor;
      freeNode(&N);
   }
   
   L->cursor = NULL;
}

//moveFront moves cursor to the front of the list
void moveFront(List L){
   if( L==NULL ){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling moveFront() on an empty List\n");
      exit(1);
   }
   L->cursor = L->front;
   L->index = 0;
}

//moveBack moves cursor to back of the list
void moveBack(List L){
   if( L==NULL ){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling moveBack() on an empty List\n");
      exit(1);
   }
   L->cursor = L->back;
   L->index = L->length - 1;
}

//movePrev() moves cursor to previous and makes cursor null if it moves off the list
void movePrev(List L){
   if(L->cursor != NULL){
      if(L->index == 0){
         L->cursor = NULL;
      }else{
         L->cursor = L->cursor->prev;
         L->index--;
      }
   } 
}

//moveNext() moves cursor to next node and makes cursor null if it moves off the list
void moveNext(List L){
   if(L->cursor != NULL){
      if(L->index == (L->length-1)){
         L->cursor = NULL;
      }else{
         L->cursor = L->cursor->next;
         L->index++;
      }
   }
}


// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in Q on a single line to stdout.
void printList(FILE* out, List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }

   for(N = L->front; N != NULL; N = N->next){
      fprintf(out, "%d ", N->data);
   }
   //printf("\n");
}

//copylist returns new list with same integer sequence and no cursor
List copyList(List L){
   List B = newList();
   Node N = NULL;
   if( L==NULL ){
      printf("List Error: calling copyList() on NULL List reference\n");
      exit(1);
   } 
   
   for (N = L->front; N != NULL; N=N->next){
      append(B, N->data);
   }
   return B;
}


// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B){
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}
