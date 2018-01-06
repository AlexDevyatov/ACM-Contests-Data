import java.util.*;
import java.io.*;

public class viruses_bm {
	FastScanner in;
	PrintWriter out;

	public void solve() throws IOException {
		int n = in.nextInt();
        assert n <= 5000 && n > 1;
		int[] a = new int[n];
		for (int i = 0; i < n; i++) {
			a[i] = in.nextInt();
            assert 1 <= a[i] && a[i] <= (int)1e9;
        }
		for (int k = 1; k < n; k++) {
			boolean ok = true;
			for (int i = n - 1; i > 0; i--) {
				if (a[(i - 1) / k] < a[i]) {
					ok = false;
					break;
				}
			}
			if (ok) {
				out.println(k);
				return;
			}
		}
		out.println(0);
	}

	public void run() {
		try {
			in = new FastScanner(new File("viruses.in"));
			out = new PrintWriter(new File("viruses.out"));

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
		new viruses_bm().run();
	}
}