using System;
using System.Collections;
using System.Collections.Generic;

public class Island {
	public int x, y;
	public Island(int x, int y) {
		this.x = x; this.y = y;
	}
}

public class View : IComparable {
	public int i, j;
	public double a, b;
	public View(int i, int j, Island i1, Island i2) {
		this.i = i; this.j = j;
		a = (double)(i2.y - i1.y) / (double)(i2.x - i1.x);
		b = a * i1.x - i1.y;
	}
	public int CompareTo(object obj) {
		View o = (View)obj;
		if (this.a < o.a) {
			return -1;
		} else if (this.a > o.a) {
			return 1;
		} else {
			return 0;
		}
	}
	
	static public int Compare(View x, View y) {
	    int result = 1;
	    if (x != null && x is View &&
	        y != null && y is View)
	    {
	        View viewX = (View)x;
	        View viewY = (View)y;
	        result = viewX.CompareTo(viewY);
	    }
	    return result;
	}
}

public class FindTreasure {
	int N, M;
	Island[] L;
	ArrayList V1, V2;
	
	public double getTurn(Object ov1, Object ov2, Object ov3) { // right < 0, left > 0
		View v1 = (View)ov1;
		View v2 = (View)ov2;
		View v3 = (View)ov3;
		return ((v2.a - v1.a) * (v3.b - v2.b) - (v2.b - v1.b) * (v3.a - v2.a));
	}
	
	public void InsertionSort<T>( ArrayList list, Comparison<T> comparison) {
	    if (list == null)
	        throw new ArgumentNullException( "list" );
	    if (comparison == null)
	        throw new ArgumentNullException( "comparison" );
	
	    int count = list.Count;
	    for (int j = 1; j < count; j++)
	    {
	        T key = (T)list[j];
	
	        int i = j - 1;
	        for (; i >= 0 && comparison((T)list[i], key ) > 0; i--)
	        {
	            list[i + 1] = list[i];
	        }
	        list[i + 1] = key;
	    }
	}
	
	public void run() {
		N = int.Parse(System.Console.ReadLine());
		L = new Island[N];
		for (int i = 0; i < N; i++) {
			string[] line = System.Console.ReadLine().Split();
			L[i] = new Island(int.Parse(line[0]), int.Parse(line[1]));
		}
		int K = int.Parse(System.Console.ReadLine());
		for (int k = 0; k < K; k++) {
			M = int.Parse(System.Console.ReadLine());
			V1 = new ArrayList(); V2 = new ArrayList();
			for (int i = 0; i < M; i++) {
				string[] line = System.Console.ReadLine().Split();
				int l = int.Parse(line[0]); l--;
				int r = int.Parse(line[1]); r--;
				View v = new View(l, r, L[l], L[r]);
				if (L[l].x < L[r].x) V1.Add(v);
				else V2.Add(v);
			}
			InsertionSort<View>(V1, View.Compare);
			InsertionSort<View>(V2, View.Compare);
			
			// bottom
			ArrayList Q1 = new ArrayList();
			if (V1.Count > 0) Q1.Add(V1[0]);
			if (V1.Count > 1) Q1.Add(V1[1]);
			for (int i = 2; i < V1.Count; i++) {
				while (Q1.Count >= 2 && getTurn(Q1[Q1.Count - 2], Q1[Q1.Count - 1], V1[i]) > 0.0) Q1.RemoveAt(Q1.Count - 1);
				Q1.Add(V1[i]);
			}
			// top
			ArrayList Q2 = new ArrayList();
			if (V2.Count > 0) Q2.Add(V2[0]);
			if (V2.Count > 1) Q2.Add(V2[1]);
			for (int i = 2; i < V2.Count; i++) {
				while (Q2.Count >= 2 && getTurn(Q2[Q2.Count - 2], Q2[Q2.Count - 1], V2[i]) < 0.0) Q2.RemoveAt(Q2.Count - 1);
				Q2.Add(V2[i]);
			}
			
			for (int i = 0; i < N; i++) {
				double A = L[i].x;
				double B = -L[i].y;
				if (Q1.Count > 0) {
					int x = -1, y = Q1.Count - 1;
					while (x + 1 < y) {
						int h = (x+y)/2;
						if ((((View)Q1[h+1]).b - ((View)Q1[h]).b) >= A * (((View)Q1[h+1]).a - ((View)Q1[h]).a)) x = h;
						else y = h;
					}
					if (A * ((View)Q1[y]).a + B <= ((View)Q1[y]).b || ((View)Q1[y]).i == i || ((View)Q1[y]).j == i) continue;
				}
				if (Q2.Count > 0) {
					int x = -1, y = Q2.Count - 1;
					while (x + 1 < y) {
						int h = (x+y)/2;
						if ((((View)Q2[h+1]).b - ((View)Q2[h]).b) <= A * (((View)Q2[h+1]).a - ((View)Q2[h]).a)) x = h;
						else y = h;
					}
					if (A * ((View)Q2[y]).a + B >= ((View)Q2[y]).b || ((View)Q2[y]).i == i || ((View)Q2[y]).j == i) continue;
				}
				System.Console.WriteLine(i+1);
			}
			System.Console.WriteLine("0");
		}
	}
	
	public static void Main() {
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) {
			new FindTreasure().run();
		}
	}

}
