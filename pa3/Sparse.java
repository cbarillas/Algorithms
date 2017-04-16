/*
 * Carlos Barillas - cbarilla@ucsc.edu
 * CMPS101 - PA3 - Sparse.java 
 *
 * Builds matrix from input file, prints matrix operations to outfile.
 */

import java.io.*;
import java.util.Scanner;
   
class Sparse{
  public static void main(String[] args) throws IOException {
    Scanner in = null;
    PrintWriter out = null;

    if (args.length < 2) {
      System.err.println("Usage: Sparse infile outfile");
      System.exit(1);
    }
      
    in = new Scanner(new File(args[0]));
    out = new PrintWriter(new FileWriter(args[1]));
    int size = in.nextInt();
    int a_nnz = in.nextInt();
    int b_nnz = in.nextInt();
    Matrix A = new Matrix(size);
    Matrix B = new Matrix(size);
    in.nextLine();
    for (int i = 0; i < a_nnz; i++) {
      int row = in.nextInt();
      int column = in.nextInt();
      double value = in.nextDouble();
      A.changeEntry(row,column,value);
    }
    in.nextLine();
    for (int i = 0; i < b_nnz; i++) {
      int row = in.nextInt();
      int column = in.nextInt();
      double value = in.nextDouble();
      B.changeEntry(row, column, value);
    }
    out.println("A has " + A.getNNZ() + " non-zero entries:");
    out.println(A.toString());
     
    out.println("B has " + B.getNNZ() + " non-zero entries:");
    out.println(B);

    out.println("(1.5)*A =");
    out.println(A.scalarMult(1.5));
      
    out.println("A+B =");
    out.println(A.add(B));

    out.println("A+A =");
    out.println(A.add(A));

    out.println("B-A =");
    out.println(B.sub(A));

    out.println("A-A =");
    out.println(A.sub(A));

    out.println("Transpose(A) =");
    out.println(A.transpose());

    out.println("A*B = ");
    out.println(A.mult(B));

    out.println("B*B = ");
    out.println(B.mult(B));

    in.close();
    out.close();
  }
}
