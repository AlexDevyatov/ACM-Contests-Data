import java.util.*;

class Edge {
	int v, L;
	public Edge(int v, int L) {
		this.v = v; this.L = L;
	}
}

class Node {
	ArrayList<Edge> adj;
	int dist, parent;
	boolean sentry;
	public Node() {
		adj = new ArrayList<Edge>();
		dist = Integer.MAX_VALUE;
		parent = -1;
		sentry = false;
	}
	public void remEdge(int v) {
		for (int i = 0; i < adj.size(); i++) {
			if (adj.get(i).v == v) {
				adj.remove(i);
				return;
			}
		}
	}
	public void changeWeight(int v, int w) {
		for (int i = 0; i < adj.size(); i++) {
			if (adj.get(i).v == v) {
				adj.get(i).L = w;
				return;
			}
		}
		adj.add(new Edge(v, w));
	}	
}

public class InAndOut {
	static Scanner sc = new Scanner(System.in);
	int N, R, S, N2;
	Node[] V;
	
	public void BF() {
		for (int i = 0; i < N2; i++) {
			for (int j = 0; j < N2; j++) {
				for (int k = 0; k < V[j].adj.size(); k++) {
					Edge e = V[j].adj.get(k);
					if (V[j].dist == Integer.MAX_VALUE) continue;
					if (V[j].dist + e.L < V[e.v].dist) {
						V[e.v].dist = V[j].dist + e.L; V[e.v].parent = j;
					}
				}
			}
		}
	}
	
	public void run() {
		N = sc.nextInt(); R = sc.nextInt();
		V = new Node[N+100];
		for (int i = 0; i < N; i++) V[i] = new Node();
		for (int i = 0; i < R; i++) {
			int a = sc.nextInt(); a--;
			int b = sc.nextInt(); b--;
			int l = sc.nextInt();
			V[a].adj.add(new Edge(b, l));
			V[b].adj.add(new Edge(a, l));
		}
		S = sc.nextInt();
		N2 = N;
		for (int i = 0; i < S; i++) {
			int s = sc.nextInt(); s--;
			V[N2] = new Node();
			V[N2].adj = (ArrayList<Edge>)V[s].adj.clone();
			V[s].adj.clear(); V[s].adj.add(new Edge(N2, 0)); V[N2++].adj.add(new Edge(s, 0));
			V[s].sentry = true;
		}
		
		int total = 0;
		V[0].dist = 0;
		BF();
		total += V[N-1].dist;
		int q = N-1;
		while (q != 0) {
			int q2 = V[q].parent;
			V[q].changeWeight(q2, V[q2].dist - V[q].dist);
			if (V[q2].sentry) V[q2].remEdge(q);
			q = q2;
		}
		for (int i = 0; i < N2; i++) V[i].dist = Integer.MAX_VALUE;
		V[0].dist = 0;
		BF();
		if (V[N-1].dist == Integer.MAX_VALUE) System.out.println("No safe route");
		else System.out.println(total + V[N-1].dist);
	}
	
	public static void main(String[] args) {
		int runs = sc.nextInt();
		for (int i = 0; i < runs; i++) new InAndOut().run();
	}
}


