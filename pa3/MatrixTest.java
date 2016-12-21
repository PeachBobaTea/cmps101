//MatrixTest.java written by Richard Selmon for pa3 - rselmon
class MatrixTest{
   public static void main(String[] args){
      Matrix A = new Matrix(3);
      Matrix B = new Matrix(3);
       System.out.println(A.getSize());
      int count = 0;
      for(int i = 1; i<=3; i++){
         for(int j = 1; j<=3; j++){
            count++;
            A.changeEntry(i,j,count);
            B.changeEntry(i,j,0);
         }
      }
      B.changeEntry(1,1,1);
      B.changeEntry(1,2,3);
      B.changeEntry(1,3,-1);
      B.changeEntry(2,2,-6);
      //System.out.println(B);
      Matrix C = A.add(A);
      System.out.println(A); 
      System.out.println(C);
      System.out.println(C.equals(A.scalarMult(2)));
      /*System.out.println("A number of non zeros" + A.getNNZ());
      Matrix D = new Matrix(3);
      Matrix E = new Matrix(3);
      D.changeEntry(1,1,1);
      E.changeEntry(2,2,2);
      E.changeEntry(1,1,5);
      D.changeEntry(3,1,5);
      Matrix F = D.add(E);
      Matrix G = F.scalarMult(-1);
      Matrix B = new Matrix(10);
      B = A.transpose();
      B.changeEntry(1,1,0);
      B.changeEntry(1,2,0);
      B.changeEntry(1,3,0);
      B.makeZero();
      System.out.println("B number of non zeros" + B.getNNZ());
      System.out.println(B.equals(A));
      Matrix C = A.transpose();
      System.out.println(A);
      System.out.println(B);

      System.out.println("\n\n\n\n cccccc");
      //System.out.println(D);
      System.out.println(C);

      //System.out.println(A.toString());
      //System.out.println(A.add(B));*/
   }
}
