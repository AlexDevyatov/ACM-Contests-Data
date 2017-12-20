using System;
using System.Collections.Generic;
using System.Collections; 

class Interval : IComparable {
	public double ang1, ang2;
	public Interval(int x, int y, int r) {
		double mid = System.Math.Atan2(y, x);
		double dist = System.Math.Sqrt(x * x + y * y);
		double dif = System.Math.Asin((double)r / dist);
		ang1 = mid - dif;
		if (ang1 < -System.Math.PI) ang1 += 2.0 * System.Math.PI;
		ang2 = mid + dif;
		if (ang2 >= System.Math.PI) ang2 -= 2.0 * System.Math.PI;		
	}
	public bool contains(double ang) {
		if (ang1 <= ang2) return (ang1 <= ang && ang <= ang2);
		else return (ang1 <= ang || ang <= ang2);
	}
	
	public int CompareTo(object obj) {
		Interval i = (Interval)obj;
		if (this.ang2 < i.ang2) {
			return -1;
		} else if (this.ang2 > i.ang2) {
			return 1;
		} else {
			return 0;
		}
	}
}

public class Popping {
	int N;
	ArrayList I = new ArrayList();
	
	public void run() {
		N = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < N; i++) {
			string[] line = System.Console.ReadLine().Split();
			I.Add(new Interval(int.Parse(line[0]), int.Parse(line[1]), int.Parse(line[2])));
		}
		I.Sort();
		
		int opt = N;
		for (int i = 0; i < N; i++) {
			int count = 1;
			double ang = ((Interval)I[i]).ang2;
			for (int j = (i+1)%N; j != i; j = (j+1)%N) {
				if (!((Interval)I[j]).contains(ang)) {
					count++; ang = ((Interval)I[j]).ang2;
				}
			}
			opt = System.Math.Min(opt, count);
		}
		System.Console.WriteLine(opt);
	}
	
	public static void Main() {
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) new Popping().run();
	}

}



