//-----------------------------------------------------------------------------
//  Queue.java
//  An integer queue ADT
// 
//  This file constitutes the solution to the first excercise in the ADT handout. 
//  Recall that all ADT operations must state their own preconditions in a comment 
//  block, then check that those conditions are satisfied.  If a precondition is 
//  violated, the ADT operation should cause the program to quit with a useful error
//  message.  See functions getFront() and Dequeue() below for examples on how to do
//  this. Observe that we've added two other operations called equals() and copy().
//
//-----------------------------------------------------------------------------

class Queue{

   private class Node{
      // Fields
      int data;
      Node next;
      
      // Constructor
      Node(int data) { this.data = data; next = null; }
      
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
   private int length;

   // Constructor
   Queue() { 
      front = back = null; 
      length = 0; 
   }


   // Access Functions --------------------------------------------------------

   // isEmpty()
   // Returns true if this Queue is empty, false otherwise.
   boolean isEmpty() { 
      return length==0; 
   }

   // getLength()
   // Returns length of this Queue.
   int getLength() { 
      return length; 
   }

   // getFront() 
   // Returns front element.
   // Pre: !this.isEmpty()
   int getFront(){
      if( this.isEmpty() ){
         throw new RuntimeException(
            "Queue Error: getFront() called on empty Queue");
      }
      return front.data;
   }

   // Manipulation Procedures -------------------------------------------------

   // Enqueue()
   // Appends data to back of this Queue.
   void Enqueue(int data){
      Node N = new Node(data);
      if( this.isEmpty() ) { 
         front = back = N;
      }else{ 
         back.next = N; 
         back = N; 
      }
      length++;
   }

   // Dequeue()
   // Deletes front element from this Queue.
   // Pre: !this.isEmpty()
   void Dequeue(){
      if(this.isEmpty()){
         throw new RuntimeException(
            "Queue Error: Dequeue() called on empty Queue");
      }
      if(this.length>1){
         front = front.next;
      }else{
         front = back = null;
      }
      length--;
   }


   // Other Functions ---------------------------------------------------------

   // toString()
   // Overides Object's toString() method.
   public String toString(){
      StringBuffer sb = new StringBuffer();
      Node N = front;
      while(N!=null){
         sb.append(" ");
         sb.append(N.toString());
         N = N.next;
      }
      return new String(sb);
   }

   // equals()
   // Overrides Object's equals() method.  Returns true if x is a Queue storing
   // the same integer sequence as this Queue, false otherwise.
   public boolean equals(Object x){
      boolean eq  = false;
      Queue Q;
      Node N, M;

      if(x instanceof Queue){
         Q = (Queue)x;
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
   // Returns a new Queue identical to this Queue.
   Queue copy(){
      Queue Q = new Queue();
      Node N = this.front;

      while( N!=null ){
         Q.Enqueue(N.data);
         N = N.next;
      }
      return Q;
   }

}
