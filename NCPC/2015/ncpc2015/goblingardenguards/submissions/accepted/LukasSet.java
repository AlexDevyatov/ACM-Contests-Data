import java.io.*;
import java.util.*;

public class LukasSet {

  static double pytag(double r, double x) {
    return Math.sqrt(r * r - x * x);
  }

  public static void main (String[] args) {
    Kattio io = new Kattio(System.in, System.out);

    int n = io.getInt();
    List<TreeSet<Integer>> columns = new ArrayList<TreeSet<Integer>> (10001);
    List<HashMap<Integer, Integer>> count = new ArrayList<HashMap<Integer, Integer>> (10001);
    for (int i = 0; i <= 10000; i++) {
      columns.add(new TreeSet<Integer>());
      count.add(new HashMap<Integer, Integer> ());
    }

    for (int i = 0; i < n; i++) {
      int x = io.getInt(), y = io.getInt();
      if (!columns.get(x).contains(y)) {
        columns.get(x).add(y);
        count.get(x).put(y, 1);
      }
      else
        count.get(x).put(y, count.get(x).get(y) + 1);
    }

    int q = io.getInt();
    for (int i = 0; i < q; i++) {
      int x = io.getInt(), y = io.getInt(), r = io.getInt();
      for (int j = Math.max(0, x - r); j <= x + r; j++)
        if (j < columns.size() && columns.get(j).size() > 0) {
          int d = Math.abs(x - j);
          int down = (int)Math.ceil(y - pytag(r, d));
          int up = 2 * y - down;
          for (int w : columns.get(j).subSet(down, true, up, true).toArray(new Integer[0]))
            columns.get(j).remove(w);
        }
    }

    int res = 0;
    for (int i = 0; i <= 10000; i++)
      for (int j : columns.get(i))
        res += count.get(i).get(j);
    io.println(res);

    io.close();
  }
}


/** Simple yet moderately fast I/O routines.
 *
 * Example usage:
 *
 * Kattio io = new Kattio(System.in, System.out);
 *
 * while (io.hasMoreTokens()) {
 *    int n = io.getInt();
 *    double d = io.getDouble();
 *    double ans = d*n;
 *
 *    io.println("Answer: " + ans);
 * }
 *
 * io.close();
 *
 *
 * Some notes:
 *
 * - When done, you should always do io.close() or io.flush() on the
 *   Kattio-instance, otherwise, you may lose output.
 *
 * - The getInt(), getDouble(), and getLong() methods will throw an
 *   exception if there is no more data in the input, so it is generally
 *   a good idea to use hasMoreTokens() to check for end-of-file.
 *
 * @author: Kattis
 */


class Kattio extends PrintWriter {
  public Kattio(InputStream i) {
    super(new BufferedOutputStream(System.out));
    r = new BufferedReader(new InputStreamReader(i));
  }
  public Kattio(InputStream i, OutputStream o) {
    super(new BufferedOutputStream(o));
    r = new BufferedReader(new InputStreamReader(i));
  }

  public boolean hasMoreTokens() {
    return peekToken() != null;
  }

  public int getInt() {
    return Integer.parseInt(nextToken());
  }

  public double getDouble() {
    return Double.parseDouble(nextToken());
  }

  public long getLong() {
    return Long.parseLong(nextToken());
  }

  public String getWord() {
    return nextToken();
  }


  private BufferedReader r;
  private String line;
  private StringTokenizer st;
  private String token;

  private String peekToken() {
    if (token == null)
      try {
        while (st == null || !st.hasMoreTokens()) {
          line = r.readLine();
          if (line == null) return null;
          st = new StringTokenizer(line);
        }
        token = st.nextToken();
      } catch (IOException e) { }
    return token;
  }

  private String nextToken() {
    String ans = peekToken();
    token = null;
    return ans;
  }
}
