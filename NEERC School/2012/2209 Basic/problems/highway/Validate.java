import java.io.*;

public class Validate {
	public void run() {
		StrictScanner inf = new StrictScanner(System.in);

		int W = inf.nextInt(), H = inf.nextInt();
		inf.nextLine();
		ensureLimits(W, 4, 10000, "W");
		ensureLimits(H, 4, 10000, "H");

		int n = inf.nextInt();
		inf.nextLine();
		ensureLimits(n, 1, 100000, "n");

		int[][] color = new int[W + 2][H + 2];

		for (int i = 0; i < n; i++) {
			int x1 = inf.nextInt();
			ensureLimits(x1, 0, W, "x1");
			int y1 = inf.nextInt();
			ensureLimits(y1, 0, H, "y1");
			int x2 = inf.nextInt();
			ensureLimits(x2, 0, W, "x2");
			int y2 = inf.nextInt();
			ensureLimits(y2, 0, H, "y2");
			ensure(x1 != x2, "Equals x1 and x2");
			ensure(y1 != y2, "Equals y1 and y2");
			if (x2 < x1) {
				int tmp = x1;
				x1 = x2;
				x2 = tmp;
			}
			if (y2 < y1) {
				int tmp = y1;
				y1 = y2;
				y2 = tmp;
			}
			for (int x = x1; x <= x2; x++)
				for (int y = y1; y <= y2; y++) {
					ensure(color[x][y] == 0, "Intersection of rectangle "
							+ color[x][y] + " with rectangle " + (i + 1));
					color[x][y] = i + 1;
				}
			inf.nextLine();
		}
		inf.close();
	}

	public static void main(String[] args) {
		new Validate().run();
	}

	public class StrictScanner {
		private final BufferedReader in;
		private String line = "";
		private int pos;
		private int lineNo;

		public StrictScanner(InputStream source) {
			in = new BufferedReader(new InputStreamReader(source));
			nextLine();
		}

		public void close() {
			ensure(line == null, "Extra data at the end of file");
			try {
				in.close();
			} catch (IOException e) {
				throw new AssertionError("Failed to close with " + e);
			}
		}

		public void nextLine() {
			ensure(line != null, "EOF");
			ensure(pos == line.length(), "Extra characters on line " + lineNo);
			try {
				line = in.readLine();
			} catch (IOException e) {
				throw new AssertionError("Failed to read line with " + e);
			}
			pos = 0;
			lineNo++;
		}

		public String next() {
			ensure(line != null, "EOF");
			ensure(line.length() > 0, "Empty line " + lineNo);
			if (pos == 0)
				ensure(line.charAt(0) > ' ', "Line " + lineNo
						+ " starts with whitespace");
			else {
				ensure(pos < line.length(), "Line " + lineNo + " is over");
				ensure(line.charAt(pos) == ' ', "Wrong whitespace on line "
						+ lineNo);
				pos++;
				ensure(pos < line.length(), "Line " + lineNo + " is over");
				ensure(line.charAt(0) > ' ', "Line " + lineNo
						+ " has double whitespace");
			}
			StringBuilder sb = new StringBuilder();
			while (pos < line.length() && line.charAt(pos) > ' ')
				sb.append(line.charAt(pos++));
			return sb.toString();
		}

		public int nextInt() {
			String s = next();
			ensure(s.length() == 1 || s.charAt(0) != '0',
					"Extra leading zero in number " + s + " on line " + lineNo);
			ensure(s.charAt(0) != '+', "Extra leading '+' in number " + s
					+ " on line " + lineNo);
			try {
				return Integer.parseInt(s);
			} catch (NumberFormatException e) {
				throw new AssertionError("Malformed number " + s + " on line "
						+ lineNo);
			}
		}

		public double nextDouble() {
			String s = next();
			ensure(s.length() == 1 || s.startsWith("0.") || s.charAt(0) != '0',
					"Extra leading zero in number " + s + " on line " + lineNo);
			ensure(s.charAt(0) != '+', "Extra leading '+' in number " + s
					+ " on line " + lineNo);
			try {
				return Double.parseDouble(s);
			} catch (NumberFormatException e) {
				throw new AssertionError("Malformed number " + s + " on line "
						+ lineNo);
			}
		}
	}

	void ensure(boolean b, String message) {
		if (!b) {
			throw new AssertionError(message);
		}
	}

	void ensureLimits(int n, int from, int to, String name) {
		ensure(from <= n && n <= to, name + " must be from " + from + " to "
				+ to);
	}

}