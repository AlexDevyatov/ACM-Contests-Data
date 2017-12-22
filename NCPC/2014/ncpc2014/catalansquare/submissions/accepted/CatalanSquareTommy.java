/*
 * Solution for Catalan Square
 */

import java.util.*;
import java.io.*;
import java.math.*;

public class CatalanSquareTommy {

  public static void main(String args[]) {
    int i;
    Scanner in = new Scanner(System.in);
    BigInteger[] cat = new BigInteger[10002];

    // Calculate Catalan numbers by one of many recursive formulas
    cat[0] = new BigInteger("1");
    for (i = 0; i < 10001; i++) {
      cat[i+1] = cat[i];
      cat[i+1] = cat[i+1].multiply(new BigInteger(""
						  + ((2*i + 1) * (2*i + 2))));
      cat[i+1] = cat[i+1].divide(new BigInteger(""
						    + ((i + 2) * (i + 1))));
    }

    while (in.hasNextInt()) {
      int n = in.nextInt();
      System.out.println(cat[n+1]);
    }
  }
}
