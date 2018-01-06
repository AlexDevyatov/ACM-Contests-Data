import java.io.*;
import java.util.*;

/**
 * Solution for problem fence, io-2012-2013, basic-01.
 * 
 * Takes O(n) time, uses only integer numbers. The solution idea is to take all
 * the edges of the input polygon, build a triangle on this edge and an internal
 * point, find the least area triangle. That's the triangle that's going to be
 * removed from the polygon.
 * 
 * Solution validates the input.
 * 
 * @author niyaz.nigmatullin
 * 
 */
public class fence_nn_validate {

	static class Point {
		int x;
		int y;

		public Point(int x, int y) {
			this.x = x;
			this.y = y;
		}

		long vect(Point p) {
			return (long) x * p.y - (long) y * p.x;
		}
	}

	static long triangleArea(Point p1, Point p2, Point p3) {
		return Math.abs(p1.vect(p2) + p2.vect(p3) + p3.vect(p1));
	}

	static Point[] solve(Point[] p, Point q) {
		int n = p.length;
		ConvexHull.Point[] polygon = new ConvexHull.Point[n];
		for (int i = 0; i < n; i++) {
			polygon[i] = new ConvexHull.Point(p[i].x, p[i].y);
		}
		polygon = ConvexHull.convexHull(polygon);
		int minPoint = -1;
		for (int i = 0; i < n; i++) {
			if (minPoint < 0 || p[minPoint].x > p[i].x
					|| (p[minPoint].x == p[i].x && p[minPoint].y > p[i].y)) {
				minPoint = i;
			}
		}
		{
			Point[] z = new Point[n];
			System.arraycopy(p, minPoint, z, 0, n - minPoint);
			System.arraycopy(p, 0, z, n - minPoint, minPoint);
			p = z;
		}
		myAssert(n == polygon.length, "bad polygon");
		for (int i = 0; i < n; i++) {
			myAssert(polygon[i].x == p[i].x && polygon[i].y == p[i].y,
					"bad polygon");
		}
		for (int i = 0; i < n; i++) {
			Point v1 = new Point(p[i].x - q.x, p[i].y - q.y);
			Point v2 = new Point(p[(i + 1) % n].x - q.x, p[(i + 1) % n].y - q.y);
			myAssert(v1.vect(v2) > 0,
					"point doesn't lie strictly inside the polygon");
		}
		long bestArea = Long.MAX_VALUE;
		int removedEdge = -1;
		for (int i = 0; i < n; i++) {
			long area = triangleArea(p[i], p[(i + 1) % n], q);
			if (area < bestArea) {
				bestArea = area;
				removedEdge = i;
			}
		}
		Point[] answer = new Point[n + 1];
		for (int i = 0, j = 0; i < n; i++) {
			answer[j++] = p[i];
			if (i == removedEdge) {
				answer[j++] = q;
			}
		}
		return answer;
	}

	static int MAXX = 100000000;
	static int MAXN = 100000;

	public static void main(String[] args) throws IOException {
		Scanner in = new Scanner(new File("fence.in"));
		int n = in.nextInt();
		myAssert(1 <= n && n <= MAXN, "n = " + n + " is not in range [1, "
				+ MAXN + "]");
		Point[] p = new Point[n];
		for (int i = 0; i < n; i++) {
			p[i] = nextPoint(in, i);
		}
		Point q = nextPoint(in, -1);
		Point[] answer = solve(p, q);
		PrintWriter out = new PrintWriter("fence.out");
		out.println(n + 1);
		for (int i = 0; i <= n; i++) {
			out.println(answer[i].x + " " + answer[i].y);
		}
		out.close();
	}

	private static Point nextPoint(Scanner in, int id) {
		int x = in.nextInt();
		int y = in.nextInt();
		myAssert(-MAXX <= x && x <= MAXX && -MAXX <= y && y <= MAXX,
				"point with id = " + id + " is (" + x + "," + y
						+ " coordinates are not in range [" + -MAXX + ", "
						+ MAXX + "]");
		return new Point(x, y);
	}

	static void myAssert(boolean b, String string) {
		if (!b) {
			throw new AssertionError(string);
		}
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
				super();
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
