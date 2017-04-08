//-----------------------------------------------------------------------------
// Carlos Barillas - cbarilla@ucsc.edu
// SID: 1380581
// CMPS101
// PA3 - Matrix.java 
//-----------------------------------------------------------------------------

class Matrix{
   private class Entry{
      int column;
      double value;

      Entry(int column, double value){
         this.column = column;
         this.value = value;
      }
      // toString():  overrides Object's toString() method
      public String toString() {
         return "("+String.valueOf(column) + ", " + String.valueOf(value)+")";
      }

      public boolean equals(Object x){
         boolean eq = false;
         Entry that;
            if(x instanceof Entry){
             that = (Entry) x;
             eq = (this.column==that.column&&this.value==that.value);
         }
         return eq;
      }
   }

   // Fields
   private int size;
   private int NNZ;
   private List row[];  
   // Constructor
   // Makes a new n x n zero Matrix. pre: n>=1
   Matrix(int n){
      if(n<1) 
         throw new RuntimeException("Matrix Error: size must be >=1");

      this.size = n;
      this.NNZ = 0;
      this.row = new List[size+1];
      for(int i=1; i<=size; i++){
         row[i] = new List();
    }
   }
   
   // Access functions -------------------------------------------------------------------
   // Returns n, the number of rows and columns of this Matrix
   int getSize(){
      return size;
   }
    
   // Returns the number of non-zero entries in this Matrix
   int getNNZ(){
      int nnz=0;
      for(int i=1; i<=getSize(); i++){
         nnz += row[i].length();
      }
      return nnz;
   }
   
   // overrides Object's equals() method
   public boolean equals(Object x){
   Matrix M = null;
      if(x instanceof Matrix){
       M = (Matrix)x;
         if(this.getSize() == M.getSize()){
            for (int i=1; i<=getSize();i++){
               if(!(row[i].equals(M.row[i]))) 
                  return false;
               }
         } //return false; //if M.getSize()!=getSize()
      } return true;
   }
 
   // Manipulation procedures ------------------------------------------------------------
   
   // sets this Matrix to the zero state
   void makeZero(){
      for (int i =1; i<=getSize(); i++){
         row[i].clear();
      }
   }
   // returns a new Matrix having the same entries as this Matrix
   Matrix copy(){
      Matrix M = new Matrix(size+1);
      for(int i=1; i<=getSize(); i++){
         row[i].moveFront();
            while (row[i].index() != -1){
               Entry E = (Entry)row[i].get();
               M.changeEntry(i, E.column,E.value);
               row[i].moveNext();
            }
      } return M;
   }      
      
   
   // changes ith row, jth column of this Matrix to x
   // pre: 1<=i<=getSize(), 1<=j<=getSize()
   void changeEntry(int i, int j, double x){
      if ( i<1 || i>getSize() || j<1 || j>getSize() )
         throw new RuntimeException("Matrix Error: changeEntry() called on invalid row/col index");
      Entry entry = new Entry(j,x);
      row[i].moveFront();
      while (row[i].index() != -1){
         Entry E = (Entry)row[i].get();
         if (E.column < j) 
            row[i].moveNext();
         if (E.column == j){
            if(x==0){
               row[i].delete();
               NNZ--;
               return;   
            }
            else { 
               E.value = x;
               return;
            }
         }
      }
      if (x!=0){
         row[i].moveFront();
            if(row[i].length() == 0) {
               row[i].append(new Entry(j,x));
               return;
            } 
            else{
                 while(row[i].index() != -1 && ((Entry)row[i].get()).column < j) {
                    row[i].moveNext();
                 }
                 if(row[i].index() > -1) {
                    row[i].insertBefore(new Entry(j,x));
                    return;
                 } 
                 else {
                      row[i].append(new Entry(j,x));
                      return;
                 }         
         }
      }
   }     
   // returns a new Matrix that is the scalar product of this Matrix with x
   Matrix scalarMult(double x){
      Matrix M = new Matrix(size+1); 
         for(int i=1; i<=getSize(); i++){
            row[i].moveFront();
               while (row[i].index() != -1){
                  Entry E = (Entry)row[i].get();
                  M.changeEntry(i, E.column,(E.value*x));
                  row[i].moveNext();
               }
         } 
         return M;
   }

   // returns a new Matrix that is the sum of this Matrix with M
   // pre: getSize()==M.getSize()      
   Matrix add(Matrix M){
      if(getSize() != M.getSize())
         throw new RuntimeException("Matrix Error: add() called on matrices of unequal size");
      if (this.equals(M))
         return this.scalarMult(2.0);
      
      Matrix result = new Matrix(size+1);
         for(int i=1; i<=getSize(); i++){
            List R1 = this.row[i];
            List R2 = M.row[i];
               for (R1.moveFront(),R2.moveFront();R1.index()!=-1&&R2.index()!=-1; ){
                  Entry temp1 = (Entry)R1.get();
                  Entry temp2 = (Entry)R2.get();
                  if( temp1.column == temp2.column){
                     result.changeEntry(i, temp1.column, temp1.value+temp2.value);
                     R1.moveNext();
                     R2.moveNext();
                     continue;
                  }
                  if( temp1.column > temp2.column){
                     result.changeEntry(i, temp2.column, temp2.value);
                     R2.moveNext();
                  }
                  else{ 
                     result.changeEntry(i, temp1.column, temp1.value);
                     R1.moveNext();
                  } 
               }
         }
         return result;

   }    
   // returns a new Matrix that is the difference of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix sub(Matrix M){
      if(this.getSize() != M.getSize())
         throw new RuntimeException("Matrix Error: sub() called on matrices of unequal size");
      if (this.equals(M))
         return this.scalarMult(0.0);

      Matrix result = new Matrix(size+1);
         for(int i=1; i<=getSize(); i++){
            List R1 = this.row[i];
            List R2 = M.row[i];
               for (R1.moveFront(),R2.moveFront();R1.index()!=-1&&R2.index()!=-1; ){
                  Entry temp1 = (Entry)R1.get();
                  Entry temp2 = (Entry)R2.get();
                  if( temp1.column == temp2.column){
                     result.changeEntry(i, temp1.column, temp1.value-temp2.value);
                     R1.moveNext();
                     R2.moveNext();
                     continue;
                  }
                  if( temp1.column > temp2.column){
                     result.changeEntry(i, temp2.column, temp2.value);
                     R2.moveNext();
                  }
                  else{
                     result.changeEntry(i, temp1.column, temp1.value);
                     R1.moveNext();
                  }
               }
         }
         return result;
   }

   // returns a new Matrix that is the transpose of this Matrix
   Matrix transpose(){
      Matrix M = new Matrix(size+1);
         for(int i=1; i<=getSize(); i++){
            row[i].moveFront();
               while (row[i].index() != -1){
                  Entry E = (Entry)row[i].get();
                  M.changeEntry(E.column, i, E.value);
                  row[i].moveNext();
               }
         }
         return M;
   }
   
   // returns a new Matrix that is the product of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix mult (Matrix M){
      if(this.getSize()!= M.getSize())
         throw new RuntimeException("mult() called on two matrices of unequal size");
      
      Matrix N = new Matrix(size);
      Matrix transposeM = M.transpose();
      for(int i=1; i<=getSize(); i++){
         if(row[i].length()>0){
            for( int j=1; j<=getSize();j++){
               if(transposeM.row[j].length()>0)
                  N.changeEntry(i,j,dot(row[i],transposeM.row[j]));
            }
         }
      }
      return N;
   }
   // Other functions--------------------------------------------------------------------------

   // overrides Object's toString() method
   public String toString(){ 
      String str = "";
      for (int i=1; i<=getSize(); i++){
         if (row[i].length() > 0) 
         str+=i+": "+row[i].toString()+"\n";
      }
      return str;
   }

   //  helper fuction for mult()
   // adds the values in P and Q
   private double dot(List P, List Q){
	Entry x;
	Entry y;
	double temp=0;
	if (P==null||Q==null){
	   return 0;
	}
	P.moveFront();
	Q.moveFront();
        while (P.index()!=-1 && Q.index()!=-1){
	   x = (Entry)P.get();
	   y = (Entry)Q.get();
	      if (x.column < y.column)
	         P.moveNext();
              else if ( x.column == y.column){
	         temp += (x.value*y.value);
	         P.moveNext();
	         Q.moveNext();
	      } 
              else Q.moveNext();	
	}
	return temp;
   }
   
}
