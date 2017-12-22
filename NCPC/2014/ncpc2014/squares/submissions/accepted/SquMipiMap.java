/*
 * Solution for Squares
 */

import java.util.*;
import java.io.*;
import java.math.*;

public class SquMipiMap {

  public static long gcd(long a,long b){
	if (b==0) return a; else return gcd(b,a%b);
  }

  public static class Functional implements Comparable<Functional>{
	long x;
	long y;
	long v;

	public Functional(long x1, long y1, long x2, long y2){
		y=x1-x2; x=y2-y1;

		if ((x<0)||(x==0 && y<0)){
			x=-x;
			y=-y;
		}
		long d = gcd(Math.abs(x),Math.abs(y));
		x/=d;
		y/=d;
	
		v=x*x1+y*y1;
	}

	public Functional(Functional f){x=f.x; y=f.y; v=f.v;}

	public int quadrant(){
		if (y>0) return 1; else return 0;
	}

	public int compareTo(Functional f) {
		long k = x*f.y-y*f.x;
		if (k!=0) return (k<0)?(1):(-1);
		if (v==f.v) return 0;
		return (v<f.v)?(-1):(1);
	}

	public boolean equals(Object o) {
		if (!(o instanceof Functional))
            		return false;
        	Functional f = (Functional) o;
		return (x==f.x && y==f.y && v==f.v);
	}

	public int hashCode(){
		return (int) x + (int) y +(int) v;
	}

	public boolean sameVec(Functional f){
		return (x==f.x && y==f.y);
	}

	long dotProd(Functional f){
		return (x*f.x+y*f.y);
	}
  }

  public static long countSquares(ArrayList<Long> r1,ArrayList<Long> r2){
	long ret=0;	
	HashMap<Long,Integer> p = new HashMap<Long,Integer>();
	for(int j=0;j<r1.size();j++) for(int i=0;i<j;i++){
		long d = r1.get(j)-r1.get(i);
		Integer val = p.get(d);
		if (val==null) p.put(d,1); else p.put(d,val+1);
	}
	for(int j=0;j<r2.size();j++) for(int i=0;i<j;i++){
		long d = r2.get(j)-r2.get(i);
		Integer val = p.get(d);				
		if (val!=null) ret+=val;
	}
	return ret;
  }

  public static void main(String args[]) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));

  	ArrayList<Functional> q0 = new ArrayList<Functional>();
  	ArrayList<Functional> q1 = new ArrayList<Functional>();

	String line=bf.readLine();
	StringTokenizer st = new StringTokenizer(line);

	int n = Integer.parseInt(st.nextToken());
	for(int i=0;i<n;i++){
		long x1,y1,x2,y2;
		line=bf.readLine();
		st = new StringTokenizer(line);
		x1 = Long.parseLong(st.nextToken());
		y1 = Long.parseLong(st.nextToken());
		x2 = Long.parseLong(st.nextToken());
		y2 = Long.parseLong(st.nextToken());
		Functional r = new Functional(x1,y1,x2,y2);
		if (r.quadrant()==1) {q1.add(r);} else {q0.add(r);}
	}
	Collections.sort(q0);
	Collections.sort(q1);

	long ret=0;

	int c=0,d=0;
	ArrayList<Long> r1 = new ArrayList<Long>();
	ArrayList<Long> r2 = new ArrayList<Long>();
	while(c<q0.size()){
		int cc=c+1;
		r1.clear(); r1.add(q0.get(c).v);
		for(;cc<q0.size();cc++){
			if (!q0.get(c).sameVec(q0.get(cc))) break; else r1.add(q0.get(cc).v);
		}
		int dd=d; r2.clear();
		for(;dd<q1.size();dd++){
			long u = q0.get(c).dotProd(q1.get(dd));
			if (u==0) r2.add(q1.get(dd).v);
			if (u<0) break;
		}
		ret+=countSquares(r1,r2);
		c=cc; d=dd;
	}
	System.out.println(ret);
 }
}
