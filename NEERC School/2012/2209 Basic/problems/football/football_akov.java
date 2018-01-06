import java.io.*;
import java.util.*;

public class football_akov {
	public static void main(String[] args) {
		new football_akov().run();
	}

	PrintWriter out;
	BufferedReader br;
	StringTokenizer st;

	String nextToken() throws IOException {
		while ((st == null) || (!st.hasMoreTokens()))
			st = new StringTokenizer(br.readLine());
		return st.nextToken();
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


	public void solve() throws IOException {
		int n = nextInt();
		for (int test = 0; test < n; test++) {
			String[] s = nextToken().split(":");
			int a = Integer.parseInt(s[0]);
			int b = Integer.parseInt(s[1]);
			int cntWin = 0;
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					int sa = a + i;
					int sb = b + j;
					if (sa > sb) {
						cntWin++;
					} else if (sa == sb) {
						if (i  > b) {
							cntWin++;
						}
					}
				}
			}
			out.println(cntWin + " " + (99 - cntWin));
		}
	}

	public void run() {
		try {
			//br = new BufferedReader(new InputStreamReader(System.in));
			//out = new PrintWriter(System.out);

			br = new BufferedReader(new FileReader("football.in"));
			out = new PrintWriter("football.out");

			solve();

			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
