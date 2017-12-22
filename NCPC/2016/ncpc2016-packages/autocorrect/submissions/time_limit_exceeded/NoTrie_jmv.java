public class NoTrie_jmv {

	public static void main(String[] args) {
		java.util.Scanner in = new java.util.Scanner(System.in);
		int n = in.nextInt(), m = in.nextInt();
		String[] d = new String[n];
		for (int i = 0; i < n; i++) {
			d[i] = in.next();
		}
		for (int j = 0; j < m; j++) {
			String q = in.next();
			int i = 0, t = 0;
			for (String s : d) {
				int c = 0;
				while (c < q.length() && c < s.length() && q.charAt(c) == s.charAt(c)) {
					c++;
				}
				if (c > i) {
					t += Math.min(c - i, s.length() + 2 - c);
					i = c;
				}
			}
			System.out.println(t + q.length() - i);
		}
	}
}
