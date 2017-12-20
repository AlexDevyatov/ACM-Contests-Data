using System.Collections;

public class Pos {
	public double x, y;
	public Pos(double x, double y) {
		this.x = x; this.y = y;
	}
	public double distTo(Pos p) {
		return System.Math.Sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	}
	public double getLength() {
		return System.Math.Sqrt(x * x + y * y);
	}
	public double getLengthSq() {
		return (x * x + y * y);
	}
	public void normalize() {
		double L = getLength();
		if (L == 0.0) return;
		x /= L; y /= L;
	}
}

public class Line {
	public Pos p1, p2;
	public bool segment;
	public Line(Pos p1, Pos p2, bool segment) {
		this.p1 = new Pos(p1.x, p1.y);
		this.p2 = new Pos(p2.x, p2.y);
		this.segment = segment;
	}
	public double distTo(Pos p) {
		double dp = (p.x - p1.x) * (p2.x - p1.x) + (p.y - p1.y) * (p2.y - p1.y);
		double u = dp / ((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
		if (segment) u = System.Math.Min(System.Math.Max(u, 0.0), 1.0);
		Pos cp = new Pos(p1.x + u * (p2.x - p1.x), p1.y + u * (p2.y - p1.y));
		return cp.distTo(p);
	}
	public Pos intersect(Line L) {
		Pos d1 = new Pos(p2.x - p1.x, p2.y - p1.y), d2 = new Pos(L.p2.x - L.p1.x, L.p2.y - L.p1.y);
		double D = d1.y * d2.x - d1.x * d2.y;
		if (D == 0.0) return null;
		double u = (d2.x * (L.p1.y - p1.y) - d2.y * (L.p1.x - p1.x)) / D;
		return new Pos(p1.x + u * d1.x, p1.y + u * d1.y);
	}
}

public class Base {
	ArrayList L = new ArrayList();
	ArrayList P = new ArrayList();
	int N;
	double maxR;
	
	public Line getBisector(Pos p1, Pos p2) {
		Pos mid = new Pos(0.5 * (p1.x + p2.x), 0.5 * (p1.y + p2.y));
		Pos perp = new Pos(p2.y - p1.y, p1.x - p2.x); perp.normalize();
		return new Line(mid, new Pos(mid.x + perp.x, mid.y + perp.y), false);
	}
	
	public Line getBisector(Line L1, Line L2) {
		Pos ix = L1.intersect(L2);
		Pos d1 = new Pos(L1.p2.x - L1.p1.x, L1.p2.y - L1.p1.y); d1.normalize();
		Pos d2 = new Pos(L2.p2.x - L2.p1.x, L2.p2.y - L2.p1.y); d2.normalize();
		if (ix == null) {
			Pos mid = new Pos(0.5 * (L1.p1.x + L2.p1.x), 0.5 * (L1.p1.y + L2.p1.y));
			return new Line(mid, new Pos(mid.x + d1.x, mid.y + d1.y), false);
		}
		else {
			Pos d = new Pos(d2.x - d1.x, d2.y - d1.y); d.normalize();
			return new Line(ix, new Pos(ix.x + d.x, ix.y + d.y), false);
		}
	}
	
	public bool pointInPoly(Pos p) {
		int c = 0;
		for (int i = 0; i < N; i++) {
			int i2 = (i+1)%N;
			Pos A = (Pos)P[i], B = (Pos)P[i2];
			if (A.y > B.y) {
				A = (Pos)P[i2]; B = (Pos)P[i];
			}
			if (p.y >= A.y && p.y < B.y && (B.y - A.y) * (p.x - A.x) - (B.x - A.x) * (p.y - A.y) >= 0) c++;
		}
		return (c%2 == 1);
	}
	
	public void check(Pos p) {
		if (p == null || !pointInPoly(p)) return;
		double R = double.MaxValue;
		for (int i = 0; i < N; i++) R = System.Math.Min(R, ((Line)L[i]).distTo(p));
		maxR = System.Math.Max(maxR, R);
	}
	
	public void solve(Pos p1, Pos p2, Pos p3) {
		Line b1 = getBisector(p1, p2);
		Line b2 = getBisector(p2, p3);
		check(b1.intersect(b2));
	}
	
	public void solve(Pos p1, Pos p2, Line L) {
		Line b = getBisector(p1, p2);
		Pos d = new Pos(b.p2.x - b.p1.x, b.p2.y - b.p1.y);
		Pos d2 = new Pos(b.p1.x - p1.x, b.p1.y - p1.y);
		Pos d3 = new Pos(L.p2.y - L.p1.y, L.p1.x - L.p2.x); d3.normalize();
		double Z = d3.x * L.p1.x + d3.y * L.p1.y;
		
		double A = d.getLengthSq() - (d.x * d.x * d3.x * d3.x + d.y * d.y * d3.y * d3.y + 2.0 * d.x * d.y * d3.x * d3.y);
		double B = 2.0 * (d2.x * d.x + d2.y * d.y) - (2.0 * d3.x * d3.x * b.p1.x * d.x + 2.0 * d3.y * d3.y * b.p1.y * d.y + 2.0 * d3.x * d3.y * (d.x * b.p1.y + d.y * b.p1.x) - 2.0 * Z * (d3.x * d.x + d3.y * d.y));
		double C = d2.getLengthSq() - (d3.x * d3.x * b.p1.x * b.p1.x + d3.y * d3.y * b.p1.y * b.p1.y + Z * Z + 2.0 * d3.x * d3.y * b.p1.x * b.p1.y - 2.0 * Z * (d3.x * b.p1.x + d3.y * b.p1.y));
		if (A == 0.0) {
			if (B == 0.0) return;
			else {
				double u = -C/B;
				check(new Pos(b.p1.x + u * d.x, b.p1.y + u * d.y));
			}
		}
		else {
			double D = B * B - 4.0 * A * C;
			if (D < 0.0) return;
			D = System.Math.Sqrt(D);
			double u = (-B + D)/(2.0 * A);
			double v = (-B - D)/(2.0 * A);
			check(new Pos(b.p1.x + u * d.x, b.p1.y + u * d.y));
			check(new Pos(b.p1.x + v * d.x, b.p1.y + v * d.y));
		}
	}
	
	public void solve(Pos p, Line L1, Line L2) {
		Line b = getBisector(L1, L2);
		Pos d = new Pos(b.p2.x - b.p1.x, b.p2.y - b.p1.y);
		Pos d2 = new Pos(b.p1.x - p.x, b.p1.y - p.y);
		Pos d3 = new Pos(L1.p2.y - L1.p1.y, L1.p1.x - L1.p2.x); d3.normalize();
		double Z = d3.x * L1.p1.x + d3.y * L1.p1.y;
		
		double A = d.getLengthSq() - (d.x * d.x * d3.x * d3.x + d.y * d.y * d3.y * d3.y + 2.0 * d.x * d.y * d3.x * d3.y);
		double B = 2.0 * (d2.x * d.x + d2.y * d.y) - (2.0 * d3.x * d3.x * b.p1.x * d.x + 2.0 * d3.y * d3.y * b.p1.y * d.y + 2.0 * d3.x * d3.y * (d.x * b.p1.y + d.y * b.p1.x) - 2.0 * Z * (d3.x * d.x + d3.y * d.y));
		double C = d2.getLengthSq() - (d3.x * d3.x * b.p1.x * b.p1.x + d3.y * d3.y * b.p1.y * b.p1.y + Z * Z + 2.0 * d3.x * d3.y * b.p1.x * b.p1.y - 2.0 * Z * (d3.x * b.p1.x + d3.y * b.p1.y));
		if (A == 0.0) {
			if (B == 0.0) return;
			else {
				double u = -C/B;
				check(new Pos(b.p1.x + u * d.x, b.p1.y + u * d.y));
			}
		}
		else {
			double D = B * B - 4.0 * A * C;
			if (D < 0.0) return;
			D = System.Math.Sqrt(D);
			double u = (-B + D)/(2.0 * A);
			double v = (-B - D)/(2.0 * A);
			check(new Pos(b.p1.x + u * d.x, b.p1.y + u * d.y));
			check(new Pos(b.p1.x + v * d.x, b.p1.y + v * d.y));
		}
	}	
	
	public void solve(Line L1, Line L2, Line L3) {
		Line b1 = getBisector(L1, L2);
		Line b2 = getBisector(L2, L3);
		check(b1.intersect(b2));
	}

	public void run() {
		N = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < N; i++) {
			string[] line = System.Console.ReadLine().Split();
			P.Add(new Pos(int.Parse(line[0]), int.Parse(line[1])));
		}
		for (int i = 0; i < N; i++) L.Add(new Line((Pos)P[i], (Pos)P[(i+1)%N], true));
		maxR = 0.0;
		
		for (int i = 0; i < N; i++) {
			for (int j = i+1; j < N; j++) {
				for (int k = j+1; k < N; k++) {
					solve((Pos)P[i], (Pos)P[j], (Pos)P[k]);
					if ((i+1)%N != j) solve((Pos)P[j], (Pos)P[k], (Line)L[i]);
					if ((j+1)%N != k) solve((Pos)P[i], (Pos)P[k], (Line)L[j]);
					if ((k+1)%N != i) solve((Pos)P[i], (Pos)P[j], (Line)L[k]);
					if ((j+1)%N != k) solve((Pos)P[k], (Line)L[i], (Line)L[j]);
					if ((i+1)%N != j) solve((Pos)P[j], (Line)L[i], (Line)L[k]);
					if ((k+1)%N != i) solve((Pos)P[i], (Line)L[j], (Line)L[k]);
					solve((Line)L[i], (Line)L[j], (Line)L[k]);
				}
			}
		}
		System.Console.WriteLine(maxR);
	}
	
	public static void Main() {
		System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) new Base().run();
	}
}


