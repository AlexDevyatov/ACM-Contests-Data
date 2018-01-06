import java.util.*;
import java.io.*;

public class horses_akov {
	FastScanner in;
	PrintWriter out;
	
	public void solve() throws IOException {
		int n = in.nextInt();
        assert n >= 1 && n <= 5000;
		int[] a = new int[n];
		for (int i = 0; i < n; i++) {
            a[i] = in.nextInt();
		    assert a[i] >= 1 && a[i] <= (int)1e6;	
        }
		int[][] dp = new int[n + 1][n + 1];
		for (int i = 0; i <= n; i++) {
			Arrays.fill(dp[i], Integer.MAX_VALUE);
		}
		dp[0][0] = 1;
		for (int i = 0; i < n; i++) {
			int minH = -1;
			for (int j = 0; j <= i; j++) {
				if (dp[i][j] <= a[i]) {
					minH = j;
					break;
				}
			}
			if (minH == -1) continue;
			int time = 0;
			for (int j = 1; j <= n - i; j++) {
				time += j;
				if (dp[i + j][minH + 1] > a[i] + time) {
					dp[i + j][minH + 1] = a[i] + time;
				}
			}
		}
		int ans = -1;
		for (int i = 1; i <= n; i++) {
			if (ans == -1 || dp[n][i] < dp[n][ans]) {
				ans = i;
			}
		}
		out.println(dp[n][ans] + " " + (ans - 1));
	}

	public void run() {
		try {
			in = new FastScanner(new File("horses.in"));
			out = new PrintWriter(new File("horses.out"));

			solve();

			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	class FastScanner {
		BufferedReader br;
		StringTokenizer st;

		FastScanner(File f) {
			try {
				br = new BufferedReader(new FileReader(f));
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			}
		}

		String next() {
			while (st == null || !st.hasMoreTokens()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			return st.nextToken();
		}

		int nextInt() {
			return Integer.parseInt(next());
		}

		long nextLong() {
			return Long.parseLong(next());
		}

		double nextDouble() {
			return Double.parseDouble(next());
		}

	}

	public static void main(String[] arg) {
		new horses_akov().run();
	}
}