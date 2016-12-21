//Matrix.java written by Richard Selmon
//rselmon
//pa3
class Matrix{

   private class Entry{
      int column;
      double value;

      //constructor for entry
      Entry(int column, double value){
         this.column = column;
         this.value = value;
      }
      public boolean equals(Entry that){
         if((this.column == that.column) && (this.value == that.value)){
            return true;
         }
         return false;
      }

      public String toString(){
         String entry = "(" + this.column + ", " + this.value + ") ";
         return entry;  
      }
   }

   //Fields
   private int n;       
   private List[] row;

   //Constructor creates new nxn zero matrix
   Matrix(int n){
      if(n < 1){
         throw new RuntimeException("Matrix error: Matrix created with size less than 1");
      }
      this.n = n;

      row = new List[n+1];
      for(int i=1; i<=n; i++){
         row[i] = new List();
      }
   }
   //Access functions
   //getSize() returns n, number of rows and columns of this matrix
   int getSize(){
      return n;   
   }

   //getNNZ() returns number of non zero entries in matrix
   int getNNZ(){
      int nnz = 0;
      for(int i=1; i<=n; i++){
         nnz += row[i].length();
      }
      return nnz;
   }

   //equals() overrides Objects equals() method
   public boolean equals(Object x){
      boolean eq = false;
      Matrix Q;
      if(x instanceof Matrix){
         Q = (Matrix) x;
         if(this.getSize() != Q.getSize()){System.out.println("!sameSize");  return false;}

         for(int i = 1; i <= this.getSize(); i++){
           // if( !(this.row[i].equals(Q.row[i])) ){System.out.println(this.row[i].toString() + Q.row[i].toString() + "!sameRow"); return false;}
            if(!(this.row[i].isEmpty()) && !(Q.row[i].isEmpty())){
               this.row[i].moveFront();
               Q.row[i].moveFront();
               if(this.row[i].length() == Q.row[i].length()){
                  while((this.row[i].index() >= 0) && (Q.row[i].index() >= 0)){
                     if(!((Entry)this.row[i].get()).equals(((Entry)Q.row[i].get()))){
                        return false;  
                     }
                  this.row[i].moveNext();
                  Q.row[i].moveNext();
                  }
               }
            }else if(this.row[i].length() != Q.row[i].length()){
                  return false;
            }
         }
         return true;
      }
      return eq;
   }

   //Manipulation functions
   //makeZero() sets this matrix to the zero state
   void makeZero(){
      for(int i=1; i<=this.getSize(); i++){
         row[i].clear();
      }
   }

   //returns a new matrix having same entries as this matrix
   Matrix copy(){
      n = this.getSize();
      Matrix Q = new Matrix(n);

      for(int i = 1; i<=n; i++){
         if(!(this.row[i].isEmpty())){
            for(this.row[i].moveFront(); this.row[i].index() >= 0; this.row[i].moveNext()){
               Entry E = new Entry(((Entry) this.row[i].get()).column, ((Entry) this.row[i].get()).value);
               //Q.row[i].append((Entry) this.row[i].get());
               Q.row[i].append(E);
            }
         }
      }
      return Q;
   }

   //changeEntry changes ith row jth column of this matrix to x
   //pre 1<=i<=getSize(), 1<=j<=getSize
   void changeEntry(int i, int j, double x){
      //if(!((1 <= i) && (i <= this.getSize())) || !(1 <= j <= this.getSize())){
      if((i<1) || (i>this.getSize()) || (j<1) || (j>this.getSize())){  
         throw new RuntimeException("Matrix Error: changeEntry called with incorrect i or j values.");
      }
      /*row[i].moveFront();
        while((Entry) row[i].get().column < j){
        row[i].moveNext();
        }*/
      if(!row[i].isEmpty()){
         for(row[i].moveFront();(row[i].index() >= 0) && (((Entry)row[i].get()).column < j); row[i].moveNext()){
            //navigate to or just past the target column
         }
         if(row[i].index() >= 0){
            if(((Entry) row[i].get()).column == j){
               if(x != 0){
                  ((Entry)row[i].get()).value = x;
               }else if(x == 0){
                  row[i].delete();
               }
            }else if(((Entry)row[i].get()).column > j){
               if(x != 0){
                  Entry E = new Entry(j, x); 
                  row[i].insertBefore(E);
               }

            }
         }else{
            if(x != 0){
               Entry E = new Entry(j, x);
               row[i].append(E);
            }
         }
      }else{
         if(x != 0){
            Entry E = new Entry(j, x);
            row[i].append(E);
         }
      }
   }
   //matrix scalurMult() returns a new matrix that is the scalar
   //product of this matrix with x
   Matrix scalarMult(double x){
      Matrix M = this.copy();
      for(int i=1; i<=n; i++){
         if(!(M.row[i].isEmpty())){
            for(M.row[i].moveFront(); M.row[i].index() >= 0; M.row[i].moveNext()){
               ((Entry) M.row[i].get()).value = ((Entry) M.row[i].get()).value * x;
            }
         }
      }
      return M;
   }

   //add() returns a new matrix that is sum of this and M
   //pre getSize == M.getSize
   Matrix add(Matrix M){
      if(this.getSize() != M.getSize()){
         throw new RuntimeException("Matrix Error: add() called on matrices of differing size");
      }
      if(this.equals(M)){
         Matrix dub = this.scalarMult(2);
         return dub;
      }
      Matrix sum = M.copy();
      for(int i=1; i<=n; i++){
         if(!(this.row[i].isEmpty())){
         for(this.row[i].moveFront(); this.row[i].index() >= 0; this.row[i].moveNext()){
            // used to contain only this line:((Entry) sum.row[i].get()).value += ((Entry)this.row[i].get()).value;
            double a = ((Entry)this.row[i].get()).value;
            if(!(M.row[i].isEmpty())){
            for(M.row[i].moveFront();  M.row[i].index() >= 0; M.row[i].moveNext()){
               if( ((Entry)this.row[i].get()).column == ((Entry)M.row[i].get()).column){
                  a += ((Entry)M.row[i].get()).value;
                  break;
               }
            }
            }
            sum.changeEntry(i,((Entry)this.row[i].get()).column, a);
         }
         }
      }
      return sum;
   }

   //Matrix sub() returns matrix that is difference of this matrix and M
   //pre getsize == M.getsize
   Matrix sub(Matrix M){
      if(this.getSize() != M.getSize()){
         throw new RuntimeException("Matrix Error: sub() called on matrices of differing size");
      }
      Matrix neg = M.copy();
      neg = neg.scalarMult(-1);
      Matrix sub = this.add(neg);
      return sub;
   }

   //returns new matrix that is the transpose of this matrix
   Matrix transpose(){
      Matrix M = new Matrix(this.getSize());
      for(int i=1; i<=this.getSize(); i++){
         if(!this.row[i].isEmpty()){
            for(this.row[i].moveFront(); this.row[i].index() >= 0; this.row[i].moveNext()){
               //change entry(j,i,x)
               M.changeEntry(((Entry) this.row[i].get()).column, i, ((Entry) this.row[i].get()).value);
            }
         }
      }
      return M;
   }

   //Matrix mult(Matrix M) returns a new matrix that is the product of this and M
   //pre getsize() == M.getsize()
   Matrix mult(Matrix M){
      if(this.getSize() != M.getSize()){
         throw new RuntimeException("Matrix Error: mult() called on matrices of differing size");
      }
      Matrix T = M.transpose();
      Matrix product = new Matrix(this.getSize());
      for(int i = 1; i<=M.getSize(); i++){
         for(int j = 1; j<=T.getSize(); j++){
            double dotproduct = dot(this.row[i], T.row[j]);
            if(dotproduct != 0) product.changeEntry(i, j, dotproduct);
         }
      }
      return product;
   }

   //other functions
   //toString() overides objects tostring method
   public String toString(){
      StringBuffer sb = new StringBuffer();
      for(int i = 1; i<=this.getSize(); i++){

         if(row[i].isEmpty()){
            /*for(int k=0; k<n; k++){
              sb.append("0 ");
              }
              sb.append("\n");*/

         }else{
            sb.append(i + ": ");
            // int prev = 1;
            // int col = 0;
            for(this.row[i].moveFront(); this.row[i].index() >= 0; this.row[i].moveNext()){
               /* col = ((Entry)row[i].get()).column;
                  int dif= col - prev;
                  for(int j = 0; j<dif; j++){
                  sb.append("%d 0 ");
                  }
                  prev = col;*/
               sb.append(((Entry)row[i].get()).toString());
            }
            for(int j = i+1; j <= this.getSize(); j++){
               if(!(row[j].isEmpty())){
                  sb.append("\n");
                  break;
               }
            }
            //append 0's after last list element 
            /* for(int j = 0; j<(this.getSize() - col); j++){
               sb.append("0 ");
               }*/
         }
      }
      return new String(sb);
   } 

   //private helper funtions
   //dot product()
   private static double dot(List x, List y){
      double dot = 0;
      if(!x.isEmpty()){
      for(x.moveFront(); x.index()>=0; x.moveNext()){
         if(!y.isEmpty()){
         for(y.moveFront(); y.index()>=0; y.moveNext()){
            if(((Entry) x.get()).column == ((Entry) y.get()).column){
               dot += ((Entry) x.get()).value * ((Entry) y.get()).value;
            }
         }
         }
      }
      }
      return dot;
   }
   }
