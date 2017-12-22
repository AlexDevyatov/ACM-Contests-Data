public class Jonmv {
    public static void main(String[] args) {
		java.util.Scanner in = new java.util.Scanner(System.in);
		for (int F = in.nextInt(); --F >= 0; ) {
			final int T = in.nextInt();
			
			Boolean[] ok = new Boolean[T + 1], dok = new Boolean[T + 1];
			java.util.Arrays.fill(ok, true);
			for (int N = in.nextInt(); --N >= 0; ) {
				final int l = -in.nextInt() + in.nextInt();
				Boolean any = false;
				for (int i = 0; i <= T; i++) {
					any |= dok[i] = (i - l >= 0 ? ok[i - l] : false) | (i + l <= T ? ok[i + l] : false);
				}
				if (!any) {
					System.out.println("impossible");
					return;
				}
				Boolean[] t = ok; ok = dok; dok = t;
			}
		}
		System.out.println("possible");
	}
}

