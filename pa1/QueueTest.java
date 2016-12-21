//-----------------------------------------------------------------------------
// QueueTest.java
// A test client for the Queue ADT
//-----------------------------------------------------------------------------

class QueueTest{
   public static void main(String[] args){
      Queue A = new Queue();
      Queue B = new Queue();
      Queue C;

      for(int i=1; i<=10; i++){
         A.Enqueue(i);
         B.Enqueue(11-i);
      }
      System.out.println("A = " + A);
      System.out.println("B = " + B);

      for(int i=1; i<=6; i++){
         A.Enqueue(B.getFront());
         B.Dequeue();
      }
      System.out.println("A = " + A);
      System.out.println("B = " + B);
      C = A.copy();
      System.out.println("C = " + C);
      System.out.println("A " + (A.equals(B)?"equals":"does not equal") + " B");
      System.out.println("A " + (A.equals(C)?"equals":"does not equal") + " C");
   }
}


