/*
 * Carlos Barillas - cbarilla@ucsc.edu
 * CMPS101 - PA1 - Lex.java
 *  
 * Takes two command line arguments. Input file can be any text file, output 
 * file will be the input arranged in alphabetical order. Uses Insertion Sort
 * to indirectly sort the array by building a List of indices in a certain order.
 *
 */


import java.io.*;
import java.util.Scanner;

public class Lex {
  public static void main(String[] args) throws IOException {
      
    // Declaring variables
    Scanner in = null;
    PrintWriter out = null;
    String line = null;
    String[] array = null;
    List list = new List();
    int lines = 0;
      
    // Check if two arguments are passed
    if(args.length != 2) {
      System.err.println("Usage: Lex infile outfile");
      System.exit(1);
    }

    // Gets file from command line arg
    in = new Scanner(new File(args[0]));

    // Counts lines of file
    while(in.hasNextLine()) {
      ++lines;
      in.nextLine();
    }

    in.close();
    in = null;

    // Allocate enough space in an array
    array = new String[lines];
    // Scanning both the input file and output file
    in = new Scanner(new File(args[0]));
    out = new PrintWriter(new FileWriter(args[1]));

    // Add lines from file into array
    for (int i = 0; i < lines; i++){
      line = in.nextLine()+" ";   
      array[i] = line;
    } 		        		

    // Put first line of the input file into list (already sorted)
    list.append(0);
    // Insertion Sort Algorithm
    for (int i = 0; i < lines-1; i++) {
      list.moveFront();
      for (int j = -i ; j < 1; j++) {
        if (array[list.get()].compareTo(array[i+1])>0) {  
    	  list.insertBefore(i+1);
          j = 1;
        }
        else if (list.index() == list.length()-1) {
    	  list.append(i+1);
          j = 1;
        }		 
        else 
        list.moveNext(); 		  
      }  
    }

    // Reset index to the front of the List
    // Prints sorted list.
    list.moveFront();
    while(list.index() >= 0) {
      out.println(array[list.get()]);
      list.moveNext();
    }
    in.close();
    out.close();
  }
}
