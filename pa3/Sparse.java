//Sparse.java written by Richard Selmon
//pa3
//rselmon
import java.io.*;
import java.util.Scanner;

class Sparse{
   public static void main(String[] args) throws IOException{
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      String[] token = null;

      int n = 0, a = 0, b = 0;
      int lineNumber = 0; 
      
      if (args.length != 2) {
         System.err.println("Usage: requires input file and output file as arguments");
         System.exit(1);
      }

      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));

      while(in.hasNextLine()){
         line = in.nextLine();
         lineNumber++;
         
         if(lineNumber == 1){
            String[] firstLine = line.split("\\s");
            n = Integer.valueOf(firstLine[0]);
            a = Integer.valueOf(firstLine[1]);
            b = Integer.valueOf(firstLine[2]);
            //System.out.println(n + " " + a + " " + b);
         }
      }
      //close file and reopen to get back to beginning
      
      in.close();
      in = new Scanner(new File(args[0]));
      lineNumber = 0;

      Matrix A = new Matrix(n);
      Matrix B = new Matrix(n);
      
      while(in.hasNextLine()){
         line = in.nextLine();
         lineNumber++;
         if ((lineNumber > 2) && (lineNumber < a+3)){
            String[] entry = line.split("\\s");
            int i = Integer.valueOf(entry[0]);
            int j = Integer.valueOf(entry[1]);
            double x = Double.parseDouble(entry[2]);           
            A.changeEntry(i, j, x);
         }else if(lineNumber > a+3){
            String[] entry = line.split("\\s");
            int i = Integer.valueOf(entry[0]);
            int j = Integer.valueOf(entry[1]);
            double x = Double.parseDouble(entry[2]);
            B.changeEntry(i, j, x);

         }
      }
      in.close();

		//print out stuff just like tantalo did
      out.println("A has" + " " + A.getNNZ() + " " +  "non-zero entries:");
      out.println(A);
      out.println();

      out.println("B has" + " " + B.getNNZ() + " " +  "non-zero entries:");
      out.println(B);
      out.println();

      out.println("(1.5)*A =");
      out.println(A.scalarMult(1.5));
      out.println();

      out.println("A+B =");
      out.println(A.add(B));
      out.println();

      out.println("A+A =");
      out.println(A.add(A));
      out.println();
     
      out.println("B-A =");
      out.println(B.sub(A));
      out.println();

      out.println("A-A =");
      out.println(A.sub(A));

      out.println("Transpose(A) =");
      out.println(A.transpose());
      out.println();

      out.println("A*B =");
      out.println(A.mult(B));
      out.println();

      out.println("B*B =");
      out.println(B.mult(B));
      out.println();
      out.close();

//      System.out.println(A);
//      System.out.println(B);
   }
}
