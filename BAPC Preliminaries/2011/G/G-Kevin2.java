import java.util.*;

class Pos {
	double x, y;
	public Pos(double x, double y) {
		this.x = x; this.y = y;
	}
	public double distTo(Pos p) {
		return Math.sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	}
	public double getLength() {
		return Math.sqrt(x * x + y * y);
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

class Line {
	Pos p1, p2;
	boolean segment;
	public Line(Pos p1, Pos p2, boolean segment) {
		this.p1 = new Pos(p1.x, p1.y);
		this.p2 = new Pos(p2.x, p2.y);
		this.segment = segment;
	}
	public double distTo(Pos p) {
		double dp = (p.x - p1.x) * (p2.x - p1.x) + (p.y - p1.y) * (p2.y - p1.y);
		double u = dp / ((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
		if (segment) u = Math.min(Math.max(u, 0.0), 1.0);
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
	static Scanner sc = new Scanner(System.in);
	ArrayList<Line> L = new ArrayList<Line>();
	ArrayList<Pos> P = new ArrayList<Pos>();
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
	
	public boolean pointInPoly(Pos p) {
		int c = 0;
		for (int i = 0; i < N; i++) {
			int i2 = (i+1)%N;
			Pos A = P.get(i), B = P.get(i2);
			if (A.y > B.y) {
				A = P.get(i2); B = P.get(i);
			}
			if (p.y >= A.y && p.y < B.y && (B.y - A.y) * (p.x - A.x) - (B.x - A.x) * (p.y - A.y) >= 0) c++;
		}
		return (c%2 == 1);
	}
	
	public void check(Pos p) {
		if (p == null || !pointInPoly(p)) return;
		double R = Double.MAX_VALUE;
		for (int i = 0; i < N; i++) R = Math.min(R, L.get(i).distTo(p));
		maxR = Math.max(maxR, R);
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
			D = Math.sqrt(D);
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
			D = Math.sqrt(D);
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
		N = sc.nextInt();
		for (int i = 0; i < N; i++) P.add(new Pos(sc.nextInt(), sc.nextInt()));
		for (int i = 0; i < N; i++) L.add(new Line(P.get(i), P.get((i+1)%N), true));
		maxR = 0.0;
		
		for (int i = 0; i < N; i++) {
			for (int j = i+1; j < N; j++) {
				for (int k = j+1; k < N; k++) {
					solve(P.get(i), P.get(j), P.get(k));
					if ((i+1)%N != j) solve(P.get(j), P.get(k), L.get(i));
					if ((j+1)%N != k) solve(P.get(i), P.get(k), L.get(j));
					if ((k+1)%N != i) solve(P.get(i), P.get(j), L.get(k));
					if ((j+1)%N != k) solve(P.get(k), L.get(i), L.get(j));
					if ((i+1)%N != j) solve(P.get(j), L.get(i), L.get(k));
					if ((k+1)%N != i) solve(P.get(i), L.get(j), L.get(k));
					solve(L.get(i), L.get(j), L.get(k));
				}
			}
		}
		System.out.println(maxR);
	}
	
	public static void main(String[] args) {
		int runs = sc.nextInt();
		for (int i = 0; i < runs; i++) new Base().run();
	}
}


