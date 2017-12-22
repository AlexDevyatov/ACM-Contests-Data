import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.OutputStream;

import java.util.Vector;
import java.util.Queue;
import java.util.ArrayDeque;
import java.util.HashSet;
import java.util.Arrays;

public class vinyals {

static final double EPS=1e-9;
static final double INF=Double.POSITIVE_INFINITY;

static double sq(double x) { return x*x; }

// time <= 8\sqrt(4000) + \sum(red)/2 < 910
static final int TMAX = 910;
static final int SWITCHMAX = TMAX/40+2;

static int n;
static double[] Ti,g0,gi;

static int[][] green;
static int[] ngreens;
static int[][] red;
static int[] nreds;

static double normalize(int i, double t) { // return t \in [0, T_i)
  t+=EPS;
  t-=g0[i];
  t%=Ti[i];
  t+=Ti[i];
  t%=Ti[i];
  t-=EPS;
  return t;
}

static boolean isitgreen(int i, double t) {
  return normalize(i,t)-EPS<gi[i];
}

static double nextgreen(int i, double t) {
  double nt = normalize(i,t);
  return t+(Ti[i]-nt);
}

static class parabola {
  int crash() {
    for (int i=1;i<n;++i) {
      if (i*1000 < xstart + EPS) continue;
      if (isitgreen(i,t(i*1000))) continue;
      return i;
    }
    return n;
  }
  double xstart;
  double tstart;
  int iend;
  double tend;
  boolean feasible;
  Vector<Integer> pointers;

  void fromxstart(int igreen) {
    iend = crash();
    if (iend<igreen) {
      feasible = false; return;
    }
    else {
      feasible = true;
    }
    tend = t(iend*1000);
    if (iend!=n) tend = nextgreen(iend,tend);
  }

  void fromtstart(int igreen, int tgreen) {
    if (tstart<-EPS) { feasible = false; return; }
    double dt = tgreen-tstart;
    xstart = igreen*1000-sq(dt)/2;
    if (xstart<-EPS) { feasible = false; return; }
    fromxstart(igreen);
  }
  
  parabola(int igreen, int tgreen, int istart) {
    xstart = istart*1000;
    double dx=igreen*1000-xstart;
    double dt=Math.sqrt(2*dx);
    tstart = tgreen-dt;
    if (tstart<-EPS) { feasible = false; return; }
    fromxstart(igreen);
  }
  parabola(int igreen, int tgreen, int ired, int tred)  {
    double dx=(igreen-ired)*1000;
    double dt=tgreen-tred;
    tstart = (2*dx+sq(tred)-sq(tgreen))/(-2*dt);
    fromtstart(igreen, tgreen);
  }
  parabola(int igreen, int tgreen, parabola start) {
    double dx=(igreen*1000-start.xstart);
    double dt=(tgreen-start.tstart);
    double delta = 4*dx-sq(dt);
    if (delta<EPS) { feasible = false; return; }
    tstart = (tgreen+start.tstart+Math.sqrt(delta))/2;
    if (tstart+EPS>tgreen) { feasible = false; return; }
    fromtstart(igreen, tgreen);
}
  boolean canitgothere(double x) {
    return xstart < x + EPS && x - EPS < iend*1000;
  }
  double t(double x) {
    double dx=x-xstart;
    double dt=Math.sqrt(2*dx);
    return tstart+dt;
  }
  boolean canstartfrom(parabola p) {
    if (! p.canitgothere(xstart)) return false;
    double tp;
    if (xstart+EPS > p.iend*1000) tp = p.tend;
    else tp = p.t(xstart);
    return tp-EPS<tstart;
  }
};

static Vector<parabola> parabolas;
static int numoriginal;

static double best;
static void bfs() {
  parabola[] parabolas_ = new parabola[parabolas.size()];
  parabolas.toArray(parabolas_);
  best=INF;
  HashSet<Integer> unseen = new HashSet<Integer>(numoriginal);
  Vector<Integer> seen = new Vector<Integer>();
  for (int i=1;i<numoriginal;++i) unseen.add(i);
  Queue<Integer> q = new ArrayDeque<Integer>();
  q.add(0);
  Integer v;
  while((v=q.poll())!=null) {
    parabola p = parabolas_[v];
    if (p.iend==n) {
      best=Math.min(best,p.tend);
    }
    seen.removeAllElements();
    for (Integer u : unseen) {
      if (parabolas_[u].canstartfrom(p)) {
        q.add(u);
        seen.add(u);
      }
    }
    unseen.removeAll(seen);
    q.addAll(p.pointers);
  }
}

public static void main(String[] argv) {
  Kattio io = new Kattio(System.in, System.out);
  n = io.getInt();
  green = new int[n][SWITCHMAX];
  ngreens = new int[n];
  Arrays.fill(ngreens,0);
  red = new int[n][SWITCHMAX];
  nreds = new int[n];
  Arrays.fill(nreds,0);
  Ti = new double[n];
  g0 = new double[n];
  gi = new double[n];
  green[0][0] = 0;
  ngreens[0]=1;
  for (int i=1;i<n;++i) {
    int firstgreen,firstred,Tgreen,Tred,T;
    firstgreen = io.getInt();
    Tgreen = io.getInt();
    Tred = io.getInt();
    T=Tgreen+Tred;
    g0[i]=firstgreen;
    gi[i]=Tgreen;
    Ti[i]=T;
    firstred=firstgreen+Tgreen;
    firstred%=T;
    for (int t=firstgreen;t<=TMAX;t+=T) green[i][ngreens[i]++]=t;
    for (int t=firstred;t<=TMAX;t+=T) red[i][nreds[i]++]=t;
  }
  parabolas = new Vector<parabola>();
  for (int igreen=0;igreen<n;++igreen) {
    for (int o = 0; o<ngreens[igreen]; ++o) {
      int tgreen = green[igreen][o];
      for (int istart=0;istart<=igreen;++istart) {
        parabola p = new parabola(igreen,tgreen,istart);
        if (p.feasible) {
          p.pointers = new Vector<Integer>();
          parabolas.add(p);
        }
      }
      for (int ired=0;ired<igreen;++ired) {
        for (int O = 0; O<nreds[ired]; ++O) {
          int tred = red[ired][O];
          if (tred>=tgreen) break;
          parabola p = new parabola(igreen,tgreen,ired,tred);
          if (p.feasible) {
            p.pointers = new Vector<Integer>();
            parabolas.add(p);
          }
        }
      }
    }
  }
  numoriginal = parabolas.size();
  for (int igreen=0;igreen<n;++igreen) {
    Vector<parabola> extraparabolas = new Vector<parabola>();
    for (int o = 0; o<ngreens[igreen]; ++o) {
      int tgreen = green[igreen][o];
      for (parabola p : parabolas) {
        parabola q = new parabola(igreen,tgreen,p);
        if (q.feasible && q.canstartfrom(p)) {
          p.pointers.add(parabolas.size()+extraparabolas.size());
          q.pointers = new Vector<Integer>();
          extraparabolas.add(q);
        }
      }
    }
    for (int o = 0; o<nreds[igreen]; ++o) {
      int tgreen = red[igreen][o];
      for (parabola p : parabolas) {
        parabola q = new parabola(igreen,tgreen,p);
        if (q.feasible && q.canstartfrom(p)) {
          p.pointers.add(parabolas.size()+extraparabolas.size());
          q.pointers = new Vector<Integer>();
          extraparabolas.add(q);
        }
      }
    }
    parabolas.addAll(extraparabolas);
  }
  bfs();
  io.println(best);
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
