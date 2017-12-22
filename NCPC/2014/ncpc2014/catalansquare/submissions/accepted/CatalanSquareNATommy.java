/*
 * Solution for Catalan Square
 */

import java.util.*;
import java.io.*;
import java.math.*;

public class CatalanSquareNATommy {

  public static void main(String args[]) {
    int i, t;
    Scanner in = new Scanner(System.in);

    int n = in.nextInt();
    n++;
    
    BigInteger cat = new BigInteger("1");
    for (i = 1; i <= 2*n; i++) {
      cat = cat.multiply(new BigInteger("" + i));
    }
    for (t = 0; t < 2; t++) {
      for (i = 1; i <= n; i++) {
	cat = cat.divide(new BigInteger("" + i));
      }
    }
    cat = cat.divide(new BigInteger("" + (n + 1)));

    System.out.println(cat);
  }
}
