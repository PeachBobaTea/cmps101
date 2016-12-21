//Lex.java written by Richard Selmon
//pa1, 9/30/16
import java.io.*;
import java.util.Scanner;

class Lex{
   public static void main(String[] args) throws IOException{ 
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      String[] token = null;
      int i, n=0;
      int lineNumber = 0;

      if (args.length != 2) {
         System.err.println("Usage: requires input file and output file as arguments");
         System.exit(1);
      }
      
		//dumb file IO poopery
      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));
      String line1=null;
      while( in.hasNextLine() ){   //count "n" lines
         n++;
	 		line1=in.nextLine();
      }
      
		in.close();
      String[] inLines = new String[n];
      in = new Scanner(new File(args[0]));
      
		while( in.hasNextLine() ){   //read in "n" lines and place in array
         line = in.nextLine();
         inLines[lineNumber] = line;
         lineNumber++;
      }
      in.close();
      
      //initialize the "sorted" list for insert sort
      List sorted = new List(); //
      if(inLines != null){
         sorted.append(0);
      }
      sorted.moveFront();

		//perform psuedo insert sort using list
      for (i=1; i<inLines.length; i++){    
         String temp = inLines[i];
         for(sorted.moveFront(); sorted.index() >= 0 && temp.compareTo(inLines[sorted.get()]) > 0; sorted.moveNext()){
         	//navigating to the end of the "unsorted" side of the array
			}
			//insert accordingly
         if(sorted.index() >= 0 ){
            sorted.insertBefore(i);
         }else{
            sorted.append(i);
         }
			//jump back to front of the list
			sorted.moveFront();
      }
		
		//print out elements of array in correct order
      for(sorted.moveFront(); sorted.index() >= 0; sorted.moveNext()){
         out.println(inLines[sorted.get()]);
      }
      out.close();
   }
}
