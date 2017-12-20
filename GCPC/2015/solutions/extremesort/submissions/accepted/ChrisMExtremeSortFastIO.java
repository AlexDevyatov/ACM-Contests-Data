import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/**
 * @author Christian Müller, TU Munich
 */
public class ChrisMExtremeSortFastIO {

	public static void main(String[] args) {
		FastScanner sc = new FastScanner(System.in);
		
		int n = sc.nextInt();
		
		boolean sorted = true;
		int x = sc.nextInt();
		for (int i = 0; i < n - 1; i++) {
			int y = sc.nextInt();
			if (x > y) {
				sorted = false;
			}
			x = y;
		}
		
		System.out.println(sorted? "yes" : "no");
	}

	/**
	 * @author Philipp Hoffmann, TU Munich
	 */
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
	}
}
