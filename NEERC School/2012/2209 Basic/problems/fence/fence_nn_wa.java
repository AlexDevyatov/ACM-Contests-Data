import java.io.*;
import java.util.Random;
import java.util.StringTokenizer;

/**
 * Wrong solution for problem fence, io-2012-2013, basic-01.
 * 
 * @author niyaz.nigmatullin
 * 
 */
public class fence_nn_wa {

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

	static final Random rand = new Random(58);

	static Point[] solve(Point[] p, Point q) {
		int n = p.length;
		int removedEdge = rand.nextInt(n);
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
		BufferedReader br = new BufferedReader(new FileReader("fence.in"));
		int n = Integer.parseInt(br.readLine());
		myAssert(1 <= n && n <= MAXN, "n = " + n + " is not in range [1, "
				+ MAXN + "]");
		Point[] p = new Point[n];
		for (int i = 0; i < n; i++) {
			p[i] = nextPoint(br, i);
		}
		Point q = nextPoint(br, -1);
		Point[] answer = solve(p, q);
		PrintWriter out = new PrintWriter("fence.out");
		out.println(n + 1);
		for (int i = 0; i <= n; i++) {
			out.println(answer[i].x + " " + answer[i].y);
		}
		out.close();
	}

	private static Point nextPoint(BufferedReader br, int id)
			throws IOException {
		StringTokenizer st = new StringTokenizer(br.readLine());
		int x = Integer.parseInt(st.nextToken());
		int y = Integer.parseInt(st.nextToken());
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
}
