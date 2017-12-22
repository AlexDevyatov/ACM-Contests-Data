import java.util.*;
import java.util.stream.*;
import java.io.*;

public class Lukas
{
  public static List<List<Integer>> gen(int n) {
    List<List<Integer>> res = new ArrayList<List<Integer>> ();
    if (n == 1) {
      List<Integer> tmp = new ArrayList<Integer> ();
      tmp.add(1);
      res.add(tmp);
      return res;
    }

    List<List<Integer>> next = gen(n - 1);
    boolean dir = false;
    for (List<Integer> o : next) {
      if (!dir) o.add(n);
      else o.add(0, n);
      res.add(o);

      int cur = dir ? 0 : n - 1;
      for (int i = 0; i < n - 1; i++) {
        int pos = cur + (dir ? 1 : -1);
        List<Integer> newo = new ArrayList<Integer> (o);

        int tmp = newo.get(cur);
        newo.set(cur, newo.get(pos));
        newo.set(pos, tmp);

        cur = pos;
        res.add(newo);
        o = newo;
      }
      dir = !dir;
    }
    return res;
  }

  public static void main(String[] args) {
    final int n = (new Scanner(System.in)).nextInt();
    PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    List<List<Integer>> res = gen(n);
    for (List<Integer> o : res) {
      for (int x : o)
        out.print(x + " ");
      out.println();
    }

    out.flush();
  }
}
