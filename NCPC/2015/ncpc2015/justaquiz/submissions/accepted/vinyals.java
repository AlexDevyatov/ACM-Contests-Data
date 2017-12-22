import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.OutputStream;

import java.util.HashMap;
import java.util.Arrays;

class trie {
  public static int T;
  public static trie questions;
  HashMap<String,trie> x;
  HashMap<String,Integer> ans;
  double[] dp;
  int size;
  double chance;

  trie() {
    x = new HashMap<String,trie>();
    ans = new HashMap<String,Integer>();
    dp = new double[T+1];
    Arrays.fill(dp,-1);
    size=0;
  }
  
  double expect(int t) {
    double e=dp[t];
    if (e!=-1) return e;
    if (t==0) return dp[t]=0;
    // Lenient time
    //if (t==1) return dp[t]=1;
    // Strict time
    if (t==1) return dp[t]=chance;
    double answer = chance + questions.expect(t-1);
    if (chance==1) return dp[t]=answer;
    double pass = 0;
    for (trie node : x.values()) {
      if (node != null) pass += node.expect(t-1)*node.size;
      else pass += 1 + questions.expect(t-2);
    }
    pass/=size;
    return dp[t]=Math.max(answer,pass);
  }
  
  void update_chance() {
    int most=0;
    for (int it : ans.values()) most=Math.max(most,it);
    chance=((double)most)/size;
    for (trie node : x.values()) {
      if (node != null) node.update_chance();
    }
  }

  String read (Kattio io) {
    size++;
    String s = io.getWord();
    trie ts = x.get(s);
    String qans;
    if (s.charAt(s.length() - 1)=='?') {
      qans = io.getWord();
    }
    else {
      if (ts==null) {
        ts = new trie();
      }
      qans = ts.read(io);
    }
    x.put(s,ts);
    Integer meh = ans.get(qans);
    if (meh==null) meh=0;
    ans.put(qans,meh+1);
    return qans;
  }
  
};

public class vinyals {
  public static void main(String[] argv) {
    Kattio io = new Kattio(System.in, System.out);
    trie.T = io.getInt();
    int n = io.getInt();
    trie.questions = new trie();

    for (int i=0; i<n; ++i) trie.questions.read(io);
    trie.questions.update_chance();
    io.println(trie.questions.expect(trie.T));
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
