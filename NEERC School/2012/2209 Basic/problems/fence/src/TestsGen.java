import static java.lang.Math.cos;
import static java.lang.Math.min;
import static java.lang.Math.sin;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

public class TestsGen {

	static final Random rand = new Random(58);
	static final int MAXC = 100000000;
	static final int MAXN = 100000;

	static class Point {
		int x;
		int y;

		public Point(int x, int y) {
			this.x = x;
			this.y = y;
		}

		Point subtract(Point p) {
			return new Point(x - p.x, y - p.y);
		}

		long vect(Point p) {
			return (long) x * p.y - (long) y * p.x;
		}
	}

	static class Test {
		Point[] p;
		Point q;

		public Test(Point[] p, Point q) {
			this.p = p;
			this.q = q;
		}

	}

	static boolean strictlyInside(Point[] p, Point q) {
		int n = p.length;
		for (int i = 0; i < n; i++) {
			Point v1 = p[i].subtract(q);
			Point v2 = p[(i + 1) % n].subtract(q);
			if (v1.vect(v2) <= 0) {
				return false;
			}
		}
		return true;
	}

	static int curTest;

	static Point randPoint(int maxx, int maxy) {
		return new Point(rand.nextInt(2 * maxx + 1) - maxx,
				rand.nextInt(2 * maxy + 1) - maxy);
	}

	static void printTest(Test test) {
		System.err.println("[" + ++curTest + "]");
		try {
			PrintWriter out = new PrintWriter("../tests/" + curTest / 10 + ""
					+ curTest % 10);
			out.println(test.p.length);
			for (Point e : test.p) {
				out.println(e.x + " " + e.y);
			}
			out.println(test.q.x + " " + test.q.y);
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	static final int[][][] POLYGONS = {
			{ { -MAXC, -MAXC }, { MAXC, MAXC }, { -MAXC, MAXC } },
			{ { -MAXC, -MAXC }, { MAXC, MAXC }, { -MAXC, MAXC } },
			{ { -MAXC, -MAXC }, { MAXC, -MAXC }, { MAXC, MAXC },
					{ -MAXC, MAXC } },
			{ { -MAXC, -MAXC }, { MAXC, -MAXC }, { MAXC, MAXC },
					{ -MAXC, MAXC } } };

	static final int[][] POINTS = { { MAXC - 2, MAXC - 1 },
			{ -MAXC + 1, MAXC - 1 }, { 0, 0 }, { MAXC - 1, rand.nextInt(MAXC) } };

	public static void main(String[] args) {
		printTest(new Test(new Point[] { new Point(-1, -1), new Point(1, -1),
				new Point(1, 1), new Point(-1, 1) }, new Point(0, 0)));
		for (int i = 0; i < 5; i++) {
			printTest(getRandom(20, 30, 30));
		}
		for (int i = 0; i < POLYGONS.length; i++) {
			Point[] p = new Point[POLYGONS[i].length];
			for (int j = 0; j < p.length; j++) {
				p[j] = new Point(POLYGONS[i][j][0], POLYGONS[i][j][1]);
			}
			printTest(new Test(p, new Point(POINTS[i][0], POINTS[0][1])));
		}
		for (int i = 0; i < 3; i++) {
			printTest(getCircle(MAXN, MAXC, MAXC));
		}
		printTest(getCircle(MAXN, MAXC / 10, MAXC / 10));
		printTest(getCircle(MAXN, MAXC / 50, MAXC / 50));
		printTest(getCircle(MAXN, MAXC / 100, MAXC / 100));
		for (int i = 0; i < 10; i++) {
			printTest(getRandom(20 + i * 5, 30 + 5 * i, 30 + 5 * i));
		}
		for (int i = 0; i < 10; i++) {
			printTest(getRandom(40 + i * 5, 50 + 5 * i, 50 + 5 * i));
		}
		for (int i = 0; i < 10; i++) {
			printTest(getRandom(60 + i * 5, 300 + 5 * i, 300 + 5 * i));
		}

		for (int i = 0; i < 10; i++) {
			printTest(getRandom(100000 + i * 5, MAXC, MAXC));
		}
		for (int i = 0; i < 20; i++) {
			printTest(getCutCircle(MAXN, MAXC, MAXC, 2000 * (i + 1)));
		}
	}

	static Test getCutCircle(int n, int maxx, int maxy, int m) {
		ConvexHull.Point[] p = new ConvexHull.Point[10 * n];
		for (int i = 0; i < p.length; i++) {
			double angle = 2 * Math.PI * rand.nextDouble();
			p[i] = new ConvexHull.Point((int) (Math.round(cos(angle) * maxx)),
					(int) (Math.round(sin(angle) * maxy)));
		}
		p = ConvexHull.convexHull(p);
		List<Point> list = new ArrayList<Point>();
		for (ConvexHull.Point e : p) {
			if (rand.nextInt(n) < m) {
				list.add(new Point(e.x, e.y));
			}
		}
		Point[] ret = (Point[]) list.toArray(new Point[list.size()]);
		Point q;
		do {
			q = randPoint(maxx, maxy);
		} while (!strictlyInside(ret, q));
		return new Test(ret, q);
	}

	static Test getRandom(int n, int maxx, int maxy) {
		ConvexHull.Point[] p = new ConvexHull.Point[n];
		for (int i = 0; i < n; i++) {
			p[i] = new ConvexHull.Point(rand.nextInt(2 * maxx + 1) - maxx,
					rand.nextInt(2 * maxy + 1) - maxy);
		}
		p = ConvexHull.convexHull(p);
		Point[] ret = new Point[p.length];
		for (int i = 0; i < p.length; i++) {
			ret[i] = new Point(p[i].x, p[i].y);
		}
		Point q;
		do {
			q = randPoint(maxx, maxy);
		} while (!strictlyInside(ret, q));
		return new Test(ret, q);
	}

	static Test getCircle(int n, int maxx, int maxy) {
		ConvexHull.Point[] p = new ConvexHull.Point[10 * n];
		for (int i = 0; i < p.length; i++) {
			double angle = 2 * Math.PI * rand.nextDouble();
			p[i] = new ConvexHull.Point((int) (Math.round(cos(angle) * maxx)),
					(int) (Math.round(sin(angle) * maxy)));
		}
		p = ConvexHull.convexHull(p);
		Point[] ret = new Point[min(p.length, n)];
		for (int i = 0; i < ret.length; i++) {
			ret[i] = new Point(p[i].x, p[i].y);
		}
		Point q;
		do {
			q = randPoint(maxx, maxy);
		} while (!strictlyInside(ret, q));
		return new Test(ret, q);
	}

	static class ConvexHull {

		static class Point {
			int x, y;

			public Point(int x, int y) {
				super();
				this.x = x;
				this.y = y;
			}

			long vect(Point p1, Point p2) {
				return (long) (p1.x - x) * (p2.y - y) - (long) (p1.y - y)
						* (p2.x - x);
			}

			long dist2(Point p) {
				long dx = x - p.x;
				long dy = y - p.y;
				return dx * dx + dy * dy;
			}
		}

		static class ByAngle implements Comparator<Point> {
			Point p;

			public ByAngle(Point p) {
				this.p = p;
			}

			@Override
			public int compare(Point o1, Point o2) {
				long d = p.vect(o1, o2);
				long d1 = p.dist2(o1);
				long d2 = p.dist2(o2);
				return d > 0 ? -1 : d < 0 ? 1 : d1 < d2 ? -1 : d1 > d2 ? 1 : 0;
			}
		}

		static Point[] convexHull(Point[] p) {
			if (p.length < 3) {
				return p;
			}
			Stack<Point> stack = new Stack<Point>();
			for (int i = 1; i < p.length; i++) {
				if (p[i].x < p[0].x || (p[i].x == p[0].x && p[i].y < p[0].y)) {
					Point t = p[0];
					p[0] = p[i];
					p[i] = t;
				}
			}
			ByAngle c = new ByAngle(p[0]);
			Arrays.sort(p, 1, p.length, c);
			stack.add(p[0]);
			stack.add(p[1]);
			for (int i = 2; i < p.length; i++) {
				while (stack.size() > 1) {
					Point last2 = stack.pop();
					Point last = stack.peek();
					if (last.vect(last2, p[i]) > 0) {
						stack.add(last2);
						break;
					}
				}
				stack.add(p[i]);
			}
			Point[] hull = new Point[stack.size()];
			int cnt = 0;
			for (Point e : stack) {
				hull[cnt++] = e;
			}
			return hull;
		}

	}

}
