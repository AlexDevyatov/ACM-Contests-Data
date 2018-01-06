import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;

public class experimental_vd {
	BufferedReader in;
	StringTokenizer str;
	PrintWriter out;
	String SK;

	String next() throws IOException {
		while ((str == null) || (!str.hasMoreTokens())) {
			SK = in.readLine();
			if (SK == null)
				return null;
			str = new StringTokenizer(SK);
		}
		return str.nextToken();
	}

	int nextInt() throws IOException {
		return Integer.parseInt(next());
	}

	double nextDouble() throws IOException {
		return Double.parseDouble(next());
	}

	long nextLong() throws IOException {
		return Long.parseLong(next());
	}

	class Edge {
		int to;
		int flow;
		Edge rev;

		public Edge(int to, int cost) {
			this.to = to;
			this.flow = cost;
		}
	}

	void addEdge(int from, int to, int cost) {
		Edge e1 = new Edge(to, cost);
		Edge e2 = new Edge(from, 0);
		e1.rev = e2;
		e2.rev = e1;
		a[from].add(e1);
		a[to].add(e2);
	}

	int n, m;

	boolean dfs(int v, int par) {
		if (v == last) {
			return true;
		}
		was[v] = 1;
		for (Edge e : a[v]) {
			if (e.flow > 0 && was[e.to] == 0) {
				if (dfs(e.to, v)) {
					e.flow--;
					e.rev.flow++;
					if (v > m) {
						res[v - m - 1] = par;
					}
					return true;
				}
			}
		}
		return false;
	}

	int[] res;
	int[] was;

	ArrayList<Edge>[] a;

	int last;

	void solve() throws IOException {
		n = nextInt();
		assert n >= 1;
		assert n <= 1000;
		m = nextInt();
		assert m >= 2;
		assert m <= 1000;
		int[][] b = new int[n][2];
		for (int i = 0; i < n; i++) {
			b[i][0] = nextInt() - 1;
			b[i][1] = nextInt() - 1;
			assert b[i][0] >= 0;
			assert b[i][0] < m;
			assert b[i][1] >= 0;
			assert b[i][1] < m;

		}
		int[] end = new int[m];
		for (int i = 0; i < m; i++) {
			end[i] = nextInt();
			assert end[i] >= 0;
			assert end[i] <= n;
		}
		last = n + m + 1;
		a = new ArrayList[last + 1];
		for (int i = 0; i < last + 1; i++) {
			a[i] = new ArrayList<Edge>();
		}
		for (int i = 0; i < m; i++) {
			addEdge(0, i + 1, end[i]);
		}

		for (int i = m + 1; i < last; i++) {
			addEdge(i, last, 1);
		}
		for (int i = 0; i < n; i++) {
			addEdge(b[i][0] + 1, i + m + 1, 1);
			addEdge(b[i][1] + 1, i + m + 1, 1);
		}
		res = new int[n];
		was = new int[last + 1];
		Arrays.fill(res, -1);
		int k = 0;
		while (dfs(0, -1)) {
			was = new int[last + 1];
			k++;
		}
		if (k != n) {
			out.println(-1);
		} else {
			for (int i = 0; i < n - 1; i++) {
				out.print(res[i] + " ");
			}
			out.println(res[n - 1]);
		}
	}

	void run() throws IOException {
		in = new BufferedReader(new FileReader("experimental.in"));
		out = new PrintWriter("experimental.out");
		solve();
		out.close();
	}

	public static void main(String[] args) throws IOException {
		new experimental_vd().run();
	}

}