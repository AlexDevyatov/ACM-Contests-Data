import java.util.*;

public class tobi {
	static ArrayList<Integer> adj[] = new ArrayList[2000];
	static int pred[] = new int[2000], N, K, to;
	static boolean mark[] = new boolean[2000];

	static boolean match(int n) {
		if (n == -1) return true;
		for (int to : adj[n]) {
			if (mark[to]) continue;
			mark[to] = true;
			if (match(pred[to])) {
				pred[to] = n;
				return true;
			}
		}
		return false;
	}

	static int maxmatch() {
		Arrays.fill(pred, -1);
		int ret = 0;
		for (int i = 0; i < N; i++) {
			Arrays.fill(mark, false);
			if (match(i)) ret++;
		}
		return ret;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		for (int i = 0; i < N; i++) {
			K = sc.nextInt();
			adj[i] = new ArrayList<>();
			for (int j = 0; j < K; j++) adj[i].add(sc.nextInt());
		}
		System.out.println(N-maxmatch());
	}
}
