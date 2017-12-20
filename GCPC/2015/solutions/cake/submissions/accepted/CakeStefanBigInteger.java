import java.math.BigInteger;
import java.util.Locale;
import java.util.Scanner;

/**
 * @author Stefan Toman (toman@tum.de)
 */
public class CakeStefanBigInteger {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		sc.useLocale(Locale.US);

		// read input
		double a = sc.nextDouble();
		long aq = 1;
		while(Math.round(a) != a) {
			a *= 10;
			aq *= 10;
		}
		Rational aRational = new Rational((long) a, aq);
		int n = sc.nextInt();

		Point[] vertices = new Point[n];
		for (int j = 0; j < n; j++) {
			int x = sc.nextInt();
			int y = sc.nextInt();
			vertices[j] = new Point(new Rational(x), new Rational(y));
		}

		Rational sqr = new Rational(4).multiply(cutAreaRatio(vertices, new Rational(2)).divide(new Rational(1).subtract(aRational)));
		System.out.println(Math.sqrt(sqr.p.doubleValue()/sqr.q.doubleValue()));

		sc.close();
	}

	public static Rational area(Point a, Point b, Point c) {
		return a.x.multiply(b.y).add(a.y.multiply(c.x)).add(b.x.multiply(c.y))
				.subtract(a.x.multiply(c.y)).subtract(a.y.multiply(b.x))
				.subtract(b.y.multiply(c.x)).divide(2).abs();
	}

	public static Point between(Point a, Point b, Rational ratio) {
		return new Point(
				ratio.subtract(1).multiply(a.x).add(b.x).divide(ratio), ratio
						.subtract(1).multiply(a.y).add(b.y).divide(ratio));
	}

	static class Point {
		Rational x, y;

		public Point(Rational x, Rational y) {
			super();
			this.x = x;
			this.y = y;
		}
	}

	static class Rational implements Comparable<Rational> {
		BigInteger p, q;

		public Rational(long p, long q) {
			this.p = BigInteger.valueOf(p);
			this.q = BigInteger.valueOf(q);
			simplify();
		}

		public Rational(long p) {
			this(p, 1);
		}

		public Rational(BigInteger p, BigInteger q) {
			this.p = p;
			this.q = q;
		}

		public void simplify() {
			BigInteger gcd = p.gcd(q);
			if(gcd.compareTo(BigInteger.ZERO) == 0) return;
			p = p.divide(gcd);
			q = q.divide(gcd);
		}

		public Rational add(Rational r) {
			Rational ret = new Rational(p.multiply(r.q).add(r.p.multiply(q)),
					q.multiply(r.q));
			ret.simplify();
			return ret;
		}

		public Rational add(long r) {
			return add(new Rational(r));
		}

		public Rational subtract(Rational r) {
			return add(r.multiply(-1));
		}

		public Rational subtract(long r) {
			return subtract(new Rational(r));
		}

		public Rational multiply(Rational r) {
			Rational ret = new Rational(p.multiply(r.p), q.multiply(r.q));
			ret.simplify();
			return ret;
		}

		public Rational multiply(long r) {
			return multiply(new Rational(r));
		}

		public Rational divide(Rational r) {
			Rational ret = new Rational(p.multiply(r.q), q.multiply(r.p));
			ret.simplify();
			return ret;
		}

		public Rational divide(long r) {
			return divide(new Rational(r));
		}
		
		public Rational abs() {
			return new Rational(p.abs(), q.abs());
		}

		public String toString() {
			simplify();
			return p + "/" + q;
		}

		@Override
		public int compareTo(Rational arg) {
			return p.multiply(arg.q).subtract(q.multiply(arg.p)).compareTo(BigInteger.ZERO);
		}
	}

	public static Rational vertexArea(Point[] vertices, Rational s) {
		Rational vertexArea = new Rational(0);
		for (int j = 1; j <= vertices.length; j++) {
			vertexArea = vertexArea.add(area(
					between(vertices[j % vertices.length], vertices[j - 1], s),
					between(vertices[j % vertices.length], vertices[(j + 1)
							% vertices.length], s), vertices[j
							% vertices.length]));
		}
		return vertexArea;
	}

	public static Rational cutAreaRatio(Point[] vertices, Rational s) {
		Rational area = new Rational(0);
		for (int j = 1; j < vertices.length - 1; j++) {
			area = area.add(area(vertices[0], vertices[j], vertices[j + 1]));
		}

		return vertexArea(vertices, s).divide(area);
	}
}

