import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

/**
 * 
 * @author Philipp Hoffmann
 *
 */
public class ChangeOfScenery1 {
	public static void main(String[] args) {
		FastScanner sc = new FastScanner(System.in);
		int n = sc.nextInt();
		int m = sc.nextInt();
		int k = sc.nextInt();
		int[] shortest = new int[k];
		for (int i = 0; i < shortest.length; i++) {
			shortest[i] = sc.nextInt();
		}
		Node[] graph = new Node[n];
		for (int i = 0; i < graph.length; i++) {
			graph[i] = new Node(i);
		}
		for (int i = 0; i < m; i++) {
			int start = sc.nextInt() - 1;
			int end = sc.nextInt() - 1;
			int length = sc.nextInt();
			graph[start].edges.add(new Edge(length, graph[end]));
			graph[end].edges.add(new Edge(length, graph[start]));
		}
		dijkstra(graph[0], graph[n - 1]);
		if (graph[n - 1].reachedMultiple) {
			System.out.println("yes");
		} else {
			System.out.println("no");
		}
	}

	public static int dijkstra(Node source, Node tar) {
		PriorityQueue<NodeWrapper> dijQueue = new PriorityQueue<>();
		source.dist = 0;
		dijQueue.add(new NodeWrapper(source));
		while (!dijQueue.isEmpty()) {
			NodeWrapper p = dijQueue.poll();
			Node v = p.n;
			if (v.finished) {
				continue;
			}
			v.finished = true;
			if (v == tar) {
				return v.dist;
			}
			for (Edge e : v.edges) {
				Node w = e.end;
				if (!w.finished) {
					if (v.dist + e.length < w.dist) {
						w.dist = v.dist + e.length;
						w.reachedMultiple = v.reachedMultiple;
						dijQueue.add(new NodeWrapper(w));
					} else if (v.dist + e.length == w.dist) {
						w.reachedMultiple = true;
					}
				}
			}
		}
		return Integer.MAX_VALUE;
	}

	private static class NodeWrapper implements Comparable<NodeWrapper> {
		Node n;
		int dist;

		NodeWrapper(Node n) {
			this.n = n;
			this.dist = n.dist;
		}

		@Override
		public int compareTo(NodeWrapper o) {
			return dist - o.dist;
		}
	}

	public static class Node implements Comparable<Node> {
		// dijkstra dist
		public int dist = Integer.MAX_VALUE;

		boolean reachedMultiple = false;

		public boolean finished = false;

		public int id;
		public HashSet<Edge> edges = new HashSet<>();

		public Node(int id) {
			this.id = id;
		}

		@Override
		public int compareTo(Node o) {
			return dist - o.dist;
		}

		@Override
		public String toString() {
			return "id: " + id + ", dist: " + dist;
		}
	}

	public static class Edge {
		int length;
		Node end;

		public Edge(int length, Node end) {
			this.length = length;
			this.end = end;
		}

		@Override
		public String toString() {
			return "length: " + length + ", end: " + end;
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
	}
}
