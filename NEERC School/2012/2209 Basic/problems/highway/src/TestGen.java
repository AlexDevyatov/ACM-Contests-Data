import java.io.*;
import java.util.*;

public class TestGen {

	PrintWriter out;
	Random rnd;
	int tNumber;

	class Bus {
		int x1, x2, y1, y2;

		public Bus(int x1, int y1, int x2, int y2) {
			super();
			this.x1 = x1;
			this.x2 = x2;
			this.y1 = y1;
			this.y2 = y2;
			if (rnd.nextBoolean()) {
				int tmp = x1;
				x1 = x2;
				x2 = tmp;
			}
			if (rnd.nextBoolean()) {
				int tmp = y1;
				y1 = y2;
				y2 = tmp;
			}
		}

	}

	class Test {
		int w, h;
		ArrayList<Bus> buses;

		void printTest() throws IOException {
			System.err.println(tNumber);
			if (buses.size() == 0)
				return;
			if (tNumber < 10)
				out = new PrintWriter("../tests/0" + tNumber);
			else
				out = new PrintWriter("../tests/" + tNumber);
			tNumber++;
			out.println(w + " " + h);
			out.println(buses.size());
			for (Bus x : buses) {
				out.println(x.x1 + " " + x.y1 + " " + (x.x2) + " " + (x.y2));
			}
			out.close();
		}

		void genSampleTest() throws IOException {
			System.err.println(tNumber);
			if (tNumber < 10)
				out = new PrintWriter("../tests/0" + tNumber);
			else
				out = new PrintWriter("../tests/" + tNumber);
			tNumber++;
			out.println(8 + " " + 4);
			out.println(2);
			out.println("0 0 3 2");
			out.println("5 4 7 1");
			out.close();
		}

		void genLittleRandTest() throws IOException {
			w = 10 + rnd.nextInt(12) - 6;
			h = 10 + rnd.nextInt(12) - 6;
			int n = rnd.nextInt(10) + 10;
			boolean[][] was = new boolean[w][h];
			buses = new ArrayList<TestGen.Bus>();
			for (int i = 0; i < n; i++) {
				int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
				boolean fl = false;
				for (int t = 0; t < 1; t++) {
					x2 = rnd.nextInt(w - 3) + 2;
					x1 = rnd.nextInt(x2);
					y2 = rnd.nextInt(h - 3) + 2;
					y1 = rnd.nextInt(y2);
					if (check(was, x1, y1, x2, y2)) {
						fl = true;
						break;
					}
				}
				if (fl) {
					buses.add(new Bus(x1, y1, x2, y2));
					set(was, x1, y1, x2, y2);
				}
			}
			printTest();
		}

		void genBigRandTest() throws IOException {
			w = 10000 - rnd.nextInt(5);
			h = 10000 - rnd.nextInt(5);
			int n = 100000;
			boolean[][] was = new boolean[w][h];
			buses = new ArrayList<TestGen.Bus>();
			for (int i = 0; i < n; i++) {
				int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
				boolean fl = false;
				for (int t = 0; t < 5; t++) {
					x1 = rnd.nextInt(w - 6) + 2;
					x2 = x1 + 2 + rnd.nextInt(2);
					y1 = rnd.nextInt(h - 6) + 2;
					y2 = y1 + 2 + rnd.nextInt(2);
					if (check(was, x1, y1, x2, y2)) {
						fl = true;
						break;
					}
				}
				if (fl) {
					buses.add(new Bus(x1, y1, x2, y2));
					set(was, x1, y1, x2, y2);
				}
			}
			printTest();
		}

		private void set(boolean[][] was, int x1, int y1, int x2, int y2) {
			for (int i = x1; i <= x2; i++)
				for (int j = y1; j <= y2; j++)
					was[i][j] = true;
		}

		private boolean check(boolean[][] was, int x1, int y1, int x2, int y2) {
			if (x1 >= x2)
				return false;
			if (y1 >= y2)
				return false;
			if (x2 >= was.length)
				return false;
			if (y2 >= was[0].length)
				return false;
			for (int i = x1; i <= x2; i++)
				for (int j = y1; j <= y2; j++)
					for (int di = -1; di < 2; di++)
						for (int dj = -1; dj < 2; dj++) {
							if (i + di < 0)
								continue;
							if (i + di >= was.length)
								continue;
							if (j + dj < 0)
								continue;
							if (j + dj >= was[0].length)
								continue;
							if (was[i + di][j + dj])
								return false;
						}
			return true;
		}

		public void genBigTest(int maxW, int maxH, int maxL, int maxh, int N)
				throws IOException {
			w = maxW - rnd.nextInt(10);
			h = maxH - rnd.nextInt(10);
			int n = N;
			buses = new ArrayList<TestGen.Bus>();
			int goodX = rnd.nextInt(w);
			int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
			boolean[][] was = new boolean[w][h];
			for (int i = 0; i < n; i++) {
				boolean fl = false;

				for (int t = 0; t < 10; t++) {
					x1 = rnd.nextInt(maxW - maxL - 1) + 2;
					x2 = x1 + 1 + rnd.nextInt(maxL);
					y1 = rnd.nextInt(maxH - maxh - 1) + 2;
					y2 = y1 + 1 + rnd.nextInt(maxh);
					if (check(was, x1, y1, x2, y2)
							&& (doubleCheck(goodX, x1, y1, x2, y2, w, h))) {
						fl = true;
						break;
					}
				}
				if (fl) {
					buses.add(new Bus(x1, y1, x2, y2));
					set(was, x1, y1, x2, y2);
					/*
					 * if ((tNumber == 14) && (buses.size() % 1000 == 0))
					 * System.err.println(buses.size());
					 */
				}
			}

			System.err.println(goodX);
			printTest();
		}

		public void genBigTest2(int maxW, int maxH, int maxL, int maxh, int N)
				throws IOException {
			w = maxW - rnd.nextInt(10);
			h = maxH - rnd.nextInt(10);
			int n = N;
			buses = new ArrayList<TestGen.Bus>();
			int goodX = rnd.nextInt(w);
			int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
			boolean[][] was = new boolean[w][h];
			for (int i = 0; i < n; i++) {
				boolean fl = false;

				for (int t = 0; t < 10; t++) {
					x1 = rnd.nextInt(maxW - maxL - 1) + 2;
					x2 = x1 + 1 + rnd.nextInt(maxL);
					y1 = rnd.nextInt(maxH - maxh - 1) + 2;
					y2 = y1 + 1 + rnd.nextInt(maxh);
					if (check(was, x1, y1, x2, y2)) {
						fl = true;
						break;
					}
				}
				if (fl) {
					buses.add(new Bus(x1, y1, x2, y2));
					set(was, x1, y1, x2, y2);
					/*
					 * if ((tNumber == 14) && (buses.size() % 1000 == 0))
					 * System.err.println(buses.size());
					 */
				}
			}

			System.err.println(goodX);
			printTest();
		}

		boolean doubleCheck(int t, int x1, int y1, int x2, int y2, int W, int H) {
			double nx1 = x1 + t + y1 % W;
			double nx2 = x2 + t + y1 % W;

			while (nx1 > W - 1e-7) {
				nx1 -= W;
				nx2 -= W;
			}
			if ((nx2 > W + 1e-7) && (nx1 < W - 1e-7))
				return false;
			if ((nx1 + (y2 - y1) > W + 1e-7) && (nx1 < W + 1e-7)) {
				return false;
			}
			if ((nx2 + (y2 - y1) > W + 1e-7) && (nx2 < W + 1e-7)) {
				return false;
			}
			return true;
		}
	}

	public void solve() throws IOException {
		tNumber = 1;
		rnd = new Random(31);
		Test t = new Test();
		t.genSampleTest();
		for (int i = 0; i < 10; i++)
			t.genLittleRandTest();
		for (int i = 0; i < 3; i++)
			t.genBigRandTest();
		for (int i = 0; i < 3; i++)
			t.genBigTest(10000, 10000, 3, 3, 100000);
		for (int i = 0; i < 3; i++)
			t.genBigTest(10000, 100, 3, 3, 1000);
		for (int i = 0; i < 3; i++)
			t.genBigTest(100, 10000, 3, 3, 1000);

		for (int i = 0; i < 3; i++)
			t.genBigTest2(10000, 100, 1000, 10, 10);
		for (int i = 0; i < 3; i++)
			t.genBigTest2(100, 10000, 10, 1000, 10);

		for (int i = 0; i < 3; i++)
			t.genBigTest(10000, 10000, 100, 100, 100);
		for (int i = 0; i < 3; i++)
			t.genBigTest(10000, 10000, 9000, 9000, 20);

	}

	public void run() {
		try {

			solve();

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		new TestGen().run();
	}
}
