using System;
using System.Collections;
using System.Collections.Generic;


class Sol : IComparable {
	int N, E, S, W;
	public Sol(int N, int E, int S, int W) {
		this.N = N; this.E = E; this.S = S; this.W = W;
	}
	public int CompareTo(object arg0o) {
		Sol arg0 = (Sol)arg0o;
		if (N != arg0.N) return (N - arg0.N);
		if (E != arg0.E) return (E - arg0.E);
		if (S != arg0.S) return (S - arg0.S);
		return (W - arg0.W);
	}
	
	public void print() {
		System.Console.WriteLine(N + " " + E + " " + S + " " + W);
	}
	
	public override bool Equals(object o) {
		return this.CompareTo(o) == 0;
	}
	
	public override int GetHashCode() {
		return 1337;
	}
}

public class UFS {
	long L, W, B;
	long sx, sy, fx, fy;
	HashSet<Sol> Q;
	
	public void run() {
		string[] line = System.Console.ReadLine().Split();
		L = long.Parse(line[0]); W = long.Parse(line[1]); B = long.Parse(line[2]);
		line = System.Console.ReadLine().Split();
		sx = long.Parse(line[0]); sy = long.Parse(line[1]);
		line = System.Console.ReadLine().Split();
		fx = long.Parse(line[0]); fy = long.Parse(line[1]);
		Q = new HashSet<Sol>();
		long minDist = long.MaxValue;
		long curx = (B%2 == 0 ? fx : L-fx), cury = fy;
		long Bx = -B, By = 0;
		while (Bx <= B) {
			long dx = sx - (Bx * L + curx), dy1 = sy - (By * W + cury), dy2 = sy - (cury - By * W);
			long d1 = dx * dx + dy1 * dy1;
			long d2 = dx * dx + dy2 * dy2;
			if (d1 <= minDist) {
				if (d1 < minDist) {
					minDist = d1; Q.Clear();
				}
				Q.Add(new Sol((int)(By+1)/2, (int)(Bx > 0 ? (Bx+1)/2 : -Bx/2), (int)By/2, (int)(Bx > 0 ? Bx/2 : (-Bx+1)/2)));
			}
			if (d2 <= minDist) {
				if (d2 < minDist) {
					minDist = d2; Q.Clear();
				}
				Q.Add(new Sol((int)By/2, (int)(Bx > 0 ? (Bx+1)/2 : -Bx/2), (int)(By+1)/2, (int)(Bx > 0 ? Bx/2 : (-Bx+1)/2)));
			}
			if (Bx >= 0) By--;
			else By++;
			Bx++;
			curx = L - curx; cury = W - cury;
		}
		
		List<Sol> QQ = new List<Sol>();
		
		foreach (Sol s in Q) {
			QQ.Add(s);
		}
		
		QQ.Sort();
		
		foreach (Sol s in QQ) {
			s.print();
		}
		
		System.Console.WriteLine("0");
	}
	
	public static void Main() {
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) new UFS().run();
	}

}


