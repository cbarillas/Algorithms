/*
 * Carlos Barillas - cbarilla@ucsc.edu
 * CMPS101 - PA3 - MatrixTest.java
 *
 * Test client for Matrix ADT
 */

class MatrixTest {
  public static void main(String[] args){
    int i, j, n = 100000;
    Matrix A = new Matrix(n);
    Matrix B = new Matrix(n);

    A.changeEntry(1, 1, 1);
    A.changeEntry(1, 2, 2);
    A.changeEntry(1, 3, 3);
    A.changeEntry(2, 1, 4);
    A.changeEntry(2, 2, 5);
    A.changeEntry(2, 3, 6);
    A.changeEntry(3, 1, 7);
    A.changeEntry(3, 2, 8);
    A.changeEntry(3, 3, 9);

    B.changeEntry(1, 1, 1);
    B.changeEntry(1, 2, 2);
    B.changeEntry(1, 3, 3);
    B.changeEntry(2, 1, 4);
    B.changeEntry(2, 2, 5);
    B.changeEntry(2, 3, 6);
    B.changeEntry(3, 1, 7);
    B.changeEntry(3, 2, 8);
    B.changeEntry(3, 3, 9);

    System.out.print("Matrix A: ");
    System.out.println(A.getNNZ());
    System.out.println(A);

    System.out.print("Matrix B: ");
    System.out.println(B.getNNZ());
    System.out.println(B);
     
    System.out.print("Matrix H: ");
    Matrix H = A.copy();
    System.out.println(H.getNNZ());
    System.out.println(H);
      
    System.out.print("Matrix C: ");
    Matrix C = A.scalarMult(2);
    System.out.println(C.getNNZ());
    System.out.println(C);
      
    System.out.print("Matrix F: ");
    Matrix F = B.transpose();
    System.out.println(F.getNNZ());
    System.out.println(F);
      
    System.out.print("Matrix D: ");
    Matrix D = A.add(F);
    System.out.println(D.getNNZ());
    System.out.println(D);
     
    System.out.print("Matrix E: ");
    Matrix E = A.sub(F);
    System.out.println(E.getNNZ());
    System.out.println(E);

    System.out.print("Matrix G: ");
    Matrix G = A.mult(B);
    System.out.println(G.getNNZ());
    System.out.println(G);
    System.out.println(A.equals(B));
  }
}

