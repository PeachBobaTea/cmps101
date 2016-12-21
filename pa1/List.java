//-----------------------------------------------------------------------------
//  List.java
//  An integer List ADT
// 
//  This file constitutes the solution to the first excercise in the ADT handout. 
//  Recall that all ADT operations must state their own preconditions in a comment 
//  block, then check that those conditions are satisfied.  If a precondition is 
//  violated, the ADT operation should cause the program to quit with a useful error
//  message.  See functions getFront() and DeList() below for examples on how to do
//  this. Observe that we've added two other operations called equals() and copy().
//
//-----------------------------------------------------------------------------
//List written by Richard Selmon for pa1
class List{

   private class Node{
      // Fields
      int data;
      Node next;
      Node prev;
      
      // Constructor
      Node(int data) { this.data = data; next = null; prev = null;}
      
      // toString():  overrides Object's toString() method
      public String toString() { 
         return String.valueOf(data); 
      }
      
      // equals(): overrides Object's equals() method
      public boolean equals(Object x){
         boolean eq = false;
         Node that;
         if(x instanceof Node){
            that = (Node) x;
            eq = (this.data==that.data);
         }
         return eq;
      }
   }

   // Fields
   private Node front;
   private Node back;
   private Node cursor;
   private int length;
   private int index;
   // Constructor
   List() { 
      front = back = cursor = null; 
      length = 0;
      index = -1; 
   }


   // Access Functions --------------------------------------------------------
   int index(){
      if(cursor != null){
         return this.index;
      }else{
         return -1;
      }
   }
   // isEmpty()
   // Returns true if this List is empty, false otherwise.
   boolean isEmpty() { 
      return length==0; 
   }

   // getLength()
   // Returns length of this List.
   int length() { 
      return length; 
   }

   // getFront() 
   // Returns front element.
   // Pre: !this.isEmpty()
   int front(){
      if( this.length <= 0 ){
         throw new RuntimeException(
            "List Error: front() called on empty List");
      }
      return front.data;
   }

   //back()
   //returns back element
   //Pre: length()>0
   int back(){
      if (this.length <= 0){
         throw new RuntimeException("List Error: back() called on empty List");
      }
      return back.data;
   }
 
   //get()
   //returns cursor element. Pre: length()>0, index()>=0
   int get(){
      if(cursor == null){
         throw new RuntimeException("List Error: get() called on null cursor");
      }
      return this.cursor.data; 
   }

   // Manipulation Procedures -------------------------------------------------
   
   //clear() resets list to its original empty state
   void clear(){
      front = back = cursor = null; 
      length = 0;  
   }

   //moveFront() moves cursor to front of list if list is not empty
   void moveFront(){
      if(this.length <= 0){
         throw new RuntimeException("List Error: moveFront called on empty list");
      }
      this.cursor = front;
      this.index = 0;
   }
   
   //moveBack()
   void moveBack(){
      if(this.length <= 0){
         throw new RuntimeException("List Error: moveback called on empty list");
      }
      this.cursor = back;
      this.index = (length-1);
   }

   //movePrev() moves you "prev" towards the front of the list if you are not null or at front 
   void movePrev(){
      if((cursor != null) && (cursor != front)){
         cursor = cursor.prev;
         this.index--;
      }else if(cursor == front){
         cursor = null;
      }
   }
   //moveNext() moves you "next" towards backof the list
   void moveNext(){
      if((cursor != null) && (cursor != back)){
         cursor = cursor.next;
         this.index++;
      }else if(cursor == back){
         cursor = null;
      }
   }

   //prepend() insert new element into list before front element if non empty
   void prepend(int data){
      Node N = new Node(data);
      if ( this.isEmpty() ){
         front = back = N;
      }else{
         front.prev = N;
         N.next = front;
         N.prev = null;
         front = N;
      }
      length++;
      if(cursor != null){
         index++;
      }
   }
   // EnList() == append
   // Appends data to back of this List.
   void append(int data){
      Node N = new Node(data);
      if( this.isEmpty() ) { 
         front = back = N;
      }else{ 
         back.next = N;
         N.prev = back;
         N.next = null;
         back = N; 
      }
      //System.out.println("DEBUG LIST APPEND:" + toString());
      length++;
   }

   //insertBefore() 
   void insertBefore(int data){
      if((this.length() <= 0) || (index() < 0)){
         throw new RuntimeException("List Error: insertBefore() called on null cursor or empty list");
      }
      
      Node N = new Node(data);
    
      if(index() > 0){
         //Node temp = cursor.prev;
         N.next = cursor;
         N.prev = cursor.prev;
         cursor.prev.next = N;
         cursor.prev = N;
      }else if(index() == 0){
         cursor.prev = N;
         N.next = cursor;
         N.prev = null;
         front = N;
      }
      this.index++;
      length++; 
   }

   //insertAfter() inserts after cursor
   void insertAfter(int data){
      if((this.length()) <= 0 || (this.index() < 0)){
         throw new RuntimeException("List Error: insertAfter called on null cursor or empty list");
      }
      Node N = new Node(data);
      Node temp = cursor.next;
      if(cursor == back){
         N.next = null;
         N.prev = cursor;
         cursor.next = N;
         back = N;
      }else{
         N.next = cursor.next;
         N.prev = cursor;
         cursor.next.prev = N;
         cursor.next = N;
      }
      length++;
   }

   // DeList()
   // Deletes front element from this List.
   // Pre: !this.isEmpty()
   void deleteFront(){
      if(this.length() <= 0){
         throw new RuntimeException(
            "List Error: deleteFront() called on empty List");
      }
      if(this.length() > 1){
         front = front.next;
         front.prev = null;
         if (cursor != null){
            index--;
         }
      }else{
         front = back = null;
      }
      length--;
   }

   // deleteBack() deletes back elemtn from list
   void deleteBack(){
      if(this.length() <= 0){
          throw new RuntimeException(
            "List Error: deleteBack() called on empty List");
      }
      if (this.length() > 1){
         back = back.prev;
         back.next = null;
      }else{
         front = back = null;
      }
      length--;
   }

   //delete() deletes cursor element making cursor undefined;
   void delete(){
      if((length <= 0) || (index < 0)){
         throw new RuntimeException("List Error: delete() called on empty list or undefined cursor");
      }
      if(cursor == front){
         deleteFront();
      }else if(cursor == back){
         deleteBack();
      }else{
      Node before = cursor.prev; 
      Node after = cursor.next; 
      before.next = after;
      after.prev = before;
      length--;
      cursor = null;
      }
   }

   // Other Functions ---------------------------------------------------------
   
   // toString()
   // Overides Object's toString() method.
   public String toString(){
      StringBuffer sb = new StringBuffer();
      Node N = front;
      while(N!=null){
         if(N != this.front){
            sb.append(" ");
         }
         sb.append(N.toString());
         N = N.next;
      }
      return new String(sb);
   }

   // equals()
   // Overrides Object's equals() method.  Returns true if x is a List storing
   // the same integer sequence as this List, false otherwise.
   public boolean equals(Object x){
      boolean eq  = false;
      List Q;
      Node N, M;

      if(x instanceof List){
         Q = (List) x;
         N = this.front;
         M = Q.front;
         eq = (this.length==Q.length);
         while( eq && N!=null ){
            eq = N.equals(M);
            N = N.next;
            M = M.next;
         }
      }
      return eq;
   }

   // copy()
   // Returns a new List identical to this List.
   List copy(){
      List Q = new List();
      Node N = this.front;

      while( N!=null ){
         Q.append(N.data);
         N = N.next;
      }
      return Q;
   }
   
   //List concat(List L) Returns a new List which is the concatenation of this list followed by L 
   //cursor undefined
   List concat(List L){
      List Q = new List();
      Node N = this.front;
      while( N != null){
         Q.append(N.data);
         N = N.next;
      }
      N = L.front; 
      while( N != null){
         Q.append(N.data);
         N = N.next;
      }
      Q.cursor = null;
      return Q;
   }
}
