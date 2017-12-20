import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class UpsideDownPhilipp {
	public static void main(String[] args) {
		FastScanner sc = new FastScanner(System.in);
		long N = sc.nextLong();
		if (N == 1) {
			System.out.println("no");
			return;
		}
		// find square root
		int root = (int) Math.ceil(Math.sqrt(N));
		boolean[] nonPrimes = new boolean[root + 1];
		erathostenes(nonPrimes);
		long turn = turn(N);
		if (turn == -1) {
			System.out.println("no");
			return;
		}
		if (isPrime(N, nonPrimes) && isPrime(turn, nonPrimes)) {
			System.out.println("yes");
			return;
		}
		System.out.println("no");
	}

	private static long turn(long N) {
		long ret = 0;
		while (N > 0) {
			ret *= 10;
			long last = N % 10;
			N /= 10;
			if (last == 0 || last == 1 || last == 2 || last == 5 || last == 8) {
				ret += last;
			} else if (last == 6) {
				ret += 9;
			} else if (last == 9) {
				ret += 6;
			} else {
				return -1;
			}
		}
		return ret;
	}

	private static boolean isPrime(long n, boolean[] nonPrimes) {
		for (int i = 0; i < nonPrimes.length; i++) {
			if (!nonPrimes[i] && n % i == 0 && i < n) {
				return false;
			}
		}
		return true;
	}

	private static void erathostenes(boolean[] nonPrimes) {
		nonPrimes[0] = true;
		nonPrimes[1] = true;
		for (int i = 2; i * i < nonPrimes.length; i++) {
			if (!nonPrimes[i]) {
				for (int j = i; j * i < nonPrimes.length; j++) {
					nonPrimes[i * j] = true;
				}
			}
		}
	}

	static class FastScanner {
		BufferedReader br = null;
		StringTokenizer st = null;

		FastScanner(InputStream in) {
			br = new BufferedReader(new InputStreamReader(System.in));
		}

		public String next() {
			while (st == null || !st.hasMoreTokens()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			return st.nextToken();
		}

		public int nextInt() {
			return Integer.parseInt(next());
		}

		public long nextLong() {
			return Long.parseLong(next());
		}
	}
}
