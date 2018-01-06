import java.util.*;

import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;
import ru.ifmo.testlib.Outcome.Type;

/**
 * Checker for problem fence. io-2012-2013. basic-01.
 * 
 * It was taken from achtung, io-2011-2012, basic-01, and modified.
 * 
 * Checker checks whether the polygon has self-intersections, contains only
 * points from input and has the area not smaller than jury's.
 * 
 * @author niyaz.nigmatullin
 * 
 */
public class Check implements ru.ifmo.testlib.Checker {

	@Override
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		int n = inf.nextInt();
		Point[] p = new Point[n];
		for (int i = 0; i < n; i++) {
			p[i] = new Point(inf.nextInt(), inf.nextInt());
		}
		Point q = new Point(inf.nextInt(), inf.nextInt());
		HashSet<Point> inputPoints = new HashSet<Point>();
		for (int i = 0; i < n; i++) {
			inputPoints.add(p[i]);
		}
		inputPoints.add(q);
		int nj = ans.nextInt();
		Point[] pj = new Point[nj];
		Set<Point> setJ = new HashSet<Point>();
		for (int i = 0; i < nj; i++) {
			pj[i] = new Point(ans.nextInt(), ans.nextInt());
			if (!inputPoints.contains(pj[i])) {
				return new Outcome(Type.FAIL,
						"jury's answer contain point with id = " + (i + 1)
								+ " that doesn't appear to be in input file");
			}
			if (!setJ.add(pj[i])) {
				return new Outcome(Type.FAIL,
						"duplicate points in answer file: (" + pj[i].x + ", "
								+ pj[i].y + ")");
			}
		}
		if (!setJ.contains(q)) {
			return new Outcome(Type.FAIL,
					"inner point isn't the side of the resulting polygon");
		}
		int np = ouf.nextInt();
		if (np < 0)
		    return new Outcome(Type.WA, "Negative answwer, participant is an idiot!");
		Point[] pp = new Point[np];
		Set<Point> setP = new HashSet<Point>();
		for (int i = 0; i < np; i++) {
			pp[i] = new Point(ouf.nextInt(), ouf.nextInt());
			if (!inputPoints.contains(pp[i])) {
				return new Outcome(Type.WA,
						"participant's answer contain point with id = "
								+ (i + 1)
								+ " that doesn't appear to be in input file");
			}
			if (!setP.add(pp[i])) {
				return new Outcome(Type.WA,
						"duplicate points in output file: (" + pp[i].x + ", "
								+ pp[i].y + ")");
			}
		}
		if (!setP.contains(q)) {
			return new Outcome(Type.WA,
					"inner point isn't the side of the resulting polygon");
		}
		Outcome outcome = null;
		if ((outcome = checkPolygon(pj)) != null) {
			return new Outcome(Type.FAIL,
					"jury's answer has segments intersection: "
							+ outcome.getComment());
		}
		if ((outcome = checkPolygon(pp)) != null) {
			return new Outcome(Type.WA,
					"participant's answer has segments intersection: "
							+ outcome.getComment());
		}
		long areaJ = doubledArea(pj);
		long areaP = doubledArea(pp);
		if (areaJ > areaP) {
			return new Outcome(Type.WA,
					"jury has better answer than participant");
		} else if (areaJ < areaP) {
			return new Outcome(Type.FAIL,
					"participant got better answer than jury");
		}
		return new Outcome(Type.OK, "Correct solution found");
	}

	long doubledArea(Point[] p) {
		long ret = 0;
		int n = p.length;
		for (int i = 0; i < n; i++) {
			Point cur = p[i];
			Point next = p[(i + 1) % n];
			ret += (long) cur.x * next.y - (long) cur.y * next.x;
		}
		return Math.abs(ret);
	}

	Outcome checkPolygon(Point[] p) {
		int n = p.length;
		Segment[] s = new Segment[n];
		for (int i = 0; i < n; i++) {
			s[i] = new Segment(p[i], p[(i + 1) % n], i);
		}
		Event[] events = new Event[2 * n];
		for (int i = 0; i < n; i++) {
			events[2 * i] = new Event(-1, s[i], s[i].p1);
			events[2 * i + 1] = new Event(1, s[i], s[i].p2);
		}
		Arrays.sort(events);

		TreeSet<Segment> ts = new TreeSet<Segment>();
		for (Event e : events) {
			position = e.p.x;
			if (e.type == -1) {
				Segment up = ts.ceiling(e.s);
				if (up != null && e.s.inter(up)) {
					return new Outcome(Type.WA, "Segments intersect: " + e.s
							+ " " + up);
				}
				Segment down = ts.floor(e.s);
				if (down != null && e.s.inter(down)) {
					return new Outcome(Type.WA, "Segments intersect: " + e.s
							+ " " + down);
				}
				ts.add(e.s);
			} else {
				ts.remove(e.s);
				Segment up = ts.ceiling(e.s);
				if (up != null && e.s.inter(up)) {
					return new Outcome(Type.WA, "Segments intersect: " + e.s
							+ " " + up);
				}
				Segment down = ts.floor(e.s);
				if (down != null && e.s.inter(down)) {
					return new Outcome(Type.WA, "Segments intersect: " + e.s
							+ " " + down);
				}
				if (down != null && up != null && up.inter(down)) {
					return new Outcome(Type.WA, "Segments intersect: " + down
							+ " " + up);
				}
			}
		}
		return null;
	}

	static int position;

	class Point implements Comparable<Point> {
		int x, y;

		Point(int x, int y) {
			this.x = x;
			this.y = y;
		}

		@Override
		public int compareTo(Point o) {
			if (x != o.x)
				return x - o.x;
			return y - o.y;
		}

		@Override
		public String toString() {
			return x + " " + y;
		}

		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			result = prime * result + getOuterType().hashCode();
			result = prime * result + x;
			result = prime * result + y;
			return result;
		}

		@Override
		public boolean equals(Object obj) {
			Point other = (Point) obj;
			if (!getOuterType().equals(other.getOuterType()))
				return false;
			if (x != other.x)
				return false;
			if (y != other.y)
				return false;
			return true;
		}

		private Check getOuterType() {
			return Check.this;
		}

	}

	class Segment implements Comparable<Segment> {
		Point p1, p2;
		long a, b, c;
		int num;

		Segment(Point p1, Point p2, int n) {
			num = n;
			if (p2.compareTo(p1) > 0) {
				this.p1 = p1;
				this.p2 = p2;
			} else {
				this.p1 = p2;
				this.p2 = p1;
			}
			a = p2.y - p1.y;
			b = p1.x - p2.x;
			c = -a * p1.x - b * p1.y;
		}

		@Override
		public boolean equals(Object o) {
			if (!(o instanceof Segment))
				return false;
			Segment s = (Segment) o;
			return p1.compareTo(s.p1) == 0 && p2.compareTo(s.p2) == 0;
		}

		int side(Point p) {
			return sign(a * p.x + b * p.y + c);
		}

		boolean inside(Point p) {
			if (side(p) != 0)
				return false;
			long sm1 = smul(p.x - p1.x, p.y - p1.y, p2.x - p1.x, p2.y - p1.y);
			long sm2 = smul(p.x - p2.x, p.y - p2.y, p1.x - p2.x, p1.y - p2.y);
			if (sm1 > 0 && sm2 > 0)
				return true;
			return false;
		}

		boolean inter(Segment s) {
			if (equals(s))
				return true;
			int s1 = side(s.p1) * side(s.p2);
			int s2 = s.side(p1) * s.side(p2);
			if (s1 < 0 && s2 < 0)
				return true;
			if (inside(s.p1) || inside(s.p2))
				return true;
			if (s.inside(p1) || s.inside(p2))
				return true;
			return false;
		}

		double getY() {
			if (p1.x == p2.x)
				return p1.y;
			return 1.0 * (position - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
		}

		@Override
		public int compareTo(Segment o) {
			int t = Double.compare(getY(), o.getY());
			if (t == 0) {
				return num - o.num;
			}
			return t;
		}

		@Override
		public String toString() {
			return p1 + " " + p2;
		}
	}

	class Event implements Comparable<Event> {
		int type;
		Point p;
		Segment s;

		public Event(int i, Segment segment, Point p1) {
			type = i;
			s = segment;
			p = p1;
		}

		@Override
		public int compareTo(Event o) {
			if (p.x != o.p.x) {
				return p.x - o.p.x;
			}
			return type - o.type;
		}
	}

	static int sign(long l) {
		if (l < 0)
			return -1;
		if (l > 0)
			return 1;
		return 0;
	}

	static long smul(long x1, long y1, int x2, int y2) {
		return x1 * x2 + y1 * y2;
	}

	static boolean inBound(int x, int l, int r) {
		return l <= x && x <= r;
	}
}
