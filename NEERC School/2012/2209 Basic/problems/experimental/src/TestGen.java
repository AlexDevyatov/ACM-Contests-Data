import java.io.*;
import java.util.*;

public class TestGen {
	public static void main(String[] args) {
		new TestGen().run();
	}

	BufferedReader br;
	StringTokenizer in;
	PrintWriter out;

	public String nextToken() throws IOException {
		while (in == null || !in.hasMoreTokens()) {
			in = new StringTokenizer(br.readLine());
		}
		return in.nextToken();
	}

	public int nextInt() throws IOException {
		return Integer.parseInt(nextToken());
	}

	public long nextLong() throws IOException {
		return Long.parseLong(nextToken());
	}

	public double nextDouble() throws IOException {
		return Double.parseDouble(nextToken());
	}

	int tNumber;

	Random rnd;

	void printt(int n, int[][] a, int m, int[] b) throws IOException {
		if (tNumber < 10) {
			out = new PrintWriter("../tests/0" + tNumber);
		} else {
			out = new PrintWriter("../tests/" + tNumber);
		}
		tNumber++;
		out.println(n + " " + m);
		for (int i = 0; i < n; i++) {
			out.println(a[i][0] + " " + a[i][1]);
		}
		for (int i = 0; i < m - 1; i++) {
			out.print(b[i] + " ");
		}
		out.println(b[m - 1]);
		out.close();
	}

	void print(int n, int[][] a, int m, int[] b) throws IOException {
		if (tNumber < 10) {
			out = new PrintWriter("../tests/0" + tNumber);
		} else {
			out = new PrintWriter("../tests/" + tNumber);
		}
		tNumber++;
		ArrayList<Integer> shuff = new ArrayList<Integer>();
		for (int i = 0; i < n; i++) {
			shuff.add(i);
		}
		Collections.shuffle(shuff, rnd);
		out.println(n + " " + m);
		for (int i = 0; i < n; i++) {
			out.println((a[shuff.get(i)][0] + 1) + " "
					+ (a[shuff.get(i)][1] + 1));
		}
		for (int i = 0; i < m - 1; i++) {
			out.print(b[i] + " ");
		}
		out.println(b[m - 1]);
		out.close();
	}

	void genOk(int n, int m) throws IOException {
		int[][] a = new int[n][2];
		int[] b = new int[m];

		for (int i = 0; i < n; i++) {
			while (a[i][0] == a[i][1]) {
				a[i][0] = rnd.nextInt(m);
				a[i][1] = rnd.nextInt(m);
			}
			b[a[i][rnd.nextInt(2)]]++;
		}
		print(n, a, m, b);
	}

	void genFail1(int n, int m) throws IOException {
		int[][] a = new int[n][2];
		int[] b = new int[m];
		for (int i = 0; i < n; i++) {
			while (a[i][0] == a[i][1]) {
				a[i][0] = rnd.nextInt(m);
				a[i][1] = rnd.nextInt(m);
			}
			b[a[i][rnd.nextInt(2)]]++;
		}
		int v = rnd.nextInt(m);
		while (b[v] == 0) {
			v = rnd.nextInt(m);
		}
		b[v]--;
		for (int i = 0; i < m; i++) {
			if (b[i] > 0) {
				b[i] -= rnd.nextInt(b[i] + 1);
			}
		}
		print(n, a, m, b);
	}

	void genFail2(int n, int m) throws IOException {
		int[][] a = new int[n][2];
		int[] b = new int[m];
		int k = n;
		while (k * 2 > n) {
			k = rnd.nextInt(n) + 1;
		}
		for (int i = 0; i < k; i++) {
			a[i][0] = 0;
			a[i][1] = 1;
			b[0]++;
			b[1]++;
		}
		int left = n - 2 * k;
		for (int i = k; i < n; i++) {
			while (a[i][0] == a[i][1]) {
				a[i][0] = rnd.nextInt(m - 2) + 2;
				a[i][1] = rnd.nextInt(m - 2) + 2;
			}
			if (left > 0) {
				b[a[i][rnd.nextInt(2)]]++;
				left--;
			}
		}
		print(n, a, m, b);
	}

	public void solve() throws IOException {
		tNumber = 1;
		int[][] a = { { 1, 2 }, { 1, 3 }, { 2, 3 } };
		int[] b = { 1, 2, 0 };
		printt(3, a, 3, b);
		int[] c = { 1, 1, 0 };
		printt(3, a, 3, c);
		rnd = new Random(31);
		genOk(1, 2);
		for (int i = 0; i < 10; i++) {
			genOk(2 + rnd.nextInt(9), 2 + rnd.nextInt(9));
		}
		genFail2(2, 4);
		genFail1(2 + rnd.nextInt(9), 4 + rnd.nextInt(9));
		genFail2(2 + rnd.nextInt(9), 4 + rnd.nextInt(9));
		for (int i = 0; i < 10; i++) {
			genOk(rnd.nextInt(900) + 5, rnd.nextInt(900) + 5);
		}
		for (int i = 0; i < 5; i++) {
			genOk(900 + rnd.nextInt(101), 900 + rnd.nextInt(101));
		}
		genOk(1000, 1000);
		genFail1(900 + rnd.nextInt(101), 900 + rnd.nextInt(101));
		genFail2(900 + rnd.nextInt(101), 900 + rnd.nextInt(101));
		genFail1(900 + rnd.nextInt(101), rnd.nextInt(101));
		genFail2(900 + rnd.nextInt(101), rnd.nextInt(101));
		for (int i = 0; i < 5; i++) {
			genOk(900 + rnd.nextInt(101), rnd.nextInt(10) + 2);
		}

	}

	public void run() {
		try {
			br = new BufferedReader(new InputStreamReader(System.in));
			out = new PrintWriter(System.out);

			solve();

			out.close();
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
		}
	}
}