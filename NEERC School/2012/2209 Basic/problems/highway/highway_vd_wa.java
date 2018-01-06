import java.io.*;
import java.util.*;
import static java.lang.Math.*;

public class highway_vd_wa {

	void count() throws IOException {
		int W = nextInt();
		int H = nextInt();
		int n = nextInt();
		int[] update = new int[W + 1];
		for (int i = 0; i < n; i++) {
			int x1 = nextInt();
			int y1 = nextInt();
			int x2 = nextInt();
			int y2 = nextInt();
			int left = Math.min(x1, x2) + Math.min(y1, y2);
			int right = Math.max(x1, x2) + Math.max(y1, y2);
			right = right - W * (left / W);
			left = left % W;
			/*
			 * if (right - W - 1 > W) { right = 2 * W + 1; }
			 */
			if (left < right - 1) {
				if (right <= W) {
					update[left]--;
					update[right - 1]++;
				} else {
					update[left]--;
					update[W]++;
					update[right - W - 1]++;
				}
			}
		}
		int sum = 0;
		for (int i = W; i >= 0; i--) {
			sum += update[i];
			if (sum == 0) {
				out.println("Yes");
				out.println(W - i);
				return;
			}
		}
		out.println("No");
	}

	BufferedReader in;
	PrintWriter out;
	StringTokenizer str;
	String readline;

	String nextToken() throws IOException {
		while (str == null || !str.hasMoreTokens()) {
			readline = in.readLine();
			if (readline == null) {
				return null;
			} else {
				str = new StringTokenizer(readline);
			}
		}
		return str.nextToken();
	}

	int nextInt() throws IOException {
		return Integer.parseInt(nextToken());
	}

	long nextLong() throws IOException {
		return Long.parseLong(nextToken());
	}

	double nextDouble() throws IOException {
		return Double.parseDouble(nextToken());
	}

	void run() throws IOException {
		in = new BufferedReader(new FileReader("highway.in"));
		out = new PrintWriter("highway.out");
		count();
		out.close();
	}

	public static void main(String[] args) throws IOException {
		new highway_vd_wa().run();
	}
}