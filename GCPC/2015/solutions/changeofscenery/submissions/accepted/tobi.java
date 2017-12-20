import java.util.*;

class T {
	int i, d;
	T(int i, int d) { this.i = i; this.d = d; }
}
public class tobi {
	public static ArrayList<Integer> adjList[] = new ArrayList[10000], costList[] = new ArrayList[10000];
	public static int N, M, K, dist[] = new int[10000];
	public static boolean done[] = new boolean[10000], poss[] = new boolean[10000];

	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt(); M = sc.nextInt(); K = sc.nextInt();
		for (int i = 0; i < N; i++) {
			adjList[i] = new ArrayList<>();
			costList[i] = new ArrayList<>();
			dist[i] = 1005*10000;
		}
		for (int i = 0; i < K; i++) sc.nextInt(); // old way is not interesting, it's shortest anyway // TODO: check?
		for (int i = 0; i < M; i++) {
			int from = sc.nextInt(), to = sc.nextInt(), cost = sc.nextInt();
			adjList[from-1].add(to-1);
			costList[from-1].add(cost);
			adjList[to-1].add(from-1);
			costList[to-1].add(cost);
		}

		dist[0] = 0;
		PriorityQueue<T> pq = new PriorityQueue<>(10000, new Comparator<T>() {
			public int compare(T a, T b) {
				return a.d - b.d;
			}
		});
		pq.add(new T(0,0));
		while (pq.size() > 0) {
			T t = pq.poll();
			int node = t.i;
			if (done[node]) continue;
			done[node] = true;
			for (int i = 0; i < adjList[node].size(); i++) {
				int next = adjList[node].get(i), nextCost = dist[node] + costList[node].get(i);
				if (dist[next] > nextCost) {
					dist[next] = dist[node] + costList[node].get(i);
					poss[next] = poss[node];
					pq.add(new T(next, dist[next]));
				} else if (dist[next] == nextCost) poss[next] = true;
			}
		}
		System.out.println(poss[N-1] ? "yes" : "no");
	}
}
