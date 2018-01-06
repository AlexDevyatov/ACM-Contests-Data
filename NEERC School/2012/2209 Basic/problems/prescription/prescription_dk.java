import java.util.*;
import java.io.*;

public class prescription_dk {
	BufferedReader br;
	PrintWriter out;
	StringTokenizer stok;

	String nextToken() throws IOException {
		while (stok == null || !stok.hasMoreTokens()) {
			String s = br.readLine();
			if (s == null) {
				return null;
			}
			stok = new StringTokenizer(s);
		}
		return stok.nextToken();
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

	char nextChar() throws IOException {
		return (char) (br.read());
	}

	String nextLine() throws IOException {
		return br.readLine();
	}
	
	void solve() throws IOException {
		String s = nextLine();
		char c = ' ';
		assert((1 <= s.length()) && (s.length() <= 1000000));
		for (int i = 0; i < s.length() - 1; i++) {
		        assert(('a' <= s.charAt(i)) && (s.charAt(i) <= 'z') || (s.charAt(i) == '_') || ('0' <= s.charAt(i)) && (s.charAt(i) <= '9'));
			assert(('a' <= s.charAt(i + 1)) && (s.charAt(i + 1) <= 'z') || (s.charAt(i + 1) == '_') || ('0' <= s.charAt(i + 1)) && (s.charAt(i + 1) <= '9'));
			if (s.charAt(i) > s.charAt(i+1)) {
				c = s.charAt(i);
				break;
			}
		}
		if (c == ' ') c = s.charAt(s.length() - 1);
		for (int i = 0; i <  s.length(); i++) {
			if  (s.charAt(i) != c) out.print(s.charAt(i));
		}
		out.println();
	}

	void run() throws IOException {
		br = new BufferedReader(new FileReader("prescription.in"));
		out = new PrintWriter("prescription.out");
		// br = new BufferedReader(new FileReader("input.txt"));
		// out = new PrintWriter("output.txt");
		// br = new BufferedReader(new InputStreamReader(System.in));
		// out = new PrintWriter(System.out);
		solve();
		br.close();
		out.close();
	}

	public static void main(String[] args) throws IOException {
		// Localea.setDefault(Locale.US);
		new prescription_dk().run();
	}
}