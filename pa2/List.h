//List header file by Richard Selmon

//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef _List_H_INCLUDE_
#define _List_H_INCLUDE_


// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object. 
List newList(void);

// freeList()
// Frees all heap memory associated with List *pQ, and sets *pQ to NULL.
void freeList(List* pQ);


// Access functions -----------------------------------------------------------
//returns index at cursor
int index( List L);

// getFront()
// Returns the value at the front of Q.
// Pre: !isEmpty(Q)
int front( List L);

int back( List L);

// getLength()
// Returns the length of Q.
int length( List L);

//int get returns the value at the cursor;
int get(List L);


// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
int isEmpty( List L);


// Manipulation procedures ----------------------------------------------------
//clears list L
void clear(List L);

void moveFront(List L);

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

// prepend
// Places new data element at the front of List L
void prepend( List L, int data);

// append
// places new data element at back of the list L
void append( List L, int data);

void insertBefore(List L, int data);

void insertAfter(List L, int data);

void deleteFront(List L);

void deleteBack(List L);

void delete(List L);

// DeList()
// Deletes element at front of Q
// Pre: !isEmpty(Q)
// changed to deleteFront which deletes front element
//void DeList( List L);


// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in Q on a single line to stdout.
void printList(FILE* out, List L);

//copyList();
//returns a new List representing the same integer sequence as the 
//list passed in. cursor in new list is undefined.
List copyList(List L);

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B);

#endif
