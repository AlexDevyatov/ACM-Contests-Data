using System.Collections;

class Edge {
	public int v, L;
	public Edge(int v, int L) {
		this.v = v; this.L = L;
	}
}

class Node {
	public ArrayList adj;
	public int dist, parent;
	public bool sentry;
	public Node() {
		adj = new ArrayList();
		dist = int.MaxValue;
		parent = -1;
		sentry = false;
	}
	public void remEdge(int v) {
		for (int i = 0; i < adj.Count; i++) {
			if (((Edge)adj[i]).v == v) {
				adj.RemoveAt(i);
				return;
			}
		}
	}
	public void changeWeight(int v, int w) {
		for (int i = 0; i < adj.Count; i++) {
			if (((Edge)adj[i]).v == v) {
				((Edge)adj[i]).L = w;
				return;
			}
		}
		adj.Add(new Edge(v, w));
	}	
}

public class InAndOut {
	int N, R, S, N2;
	Node[] V;
	
	public void BF() {
		for (int i = 0; i < N2; i++) {
			for (int j = 0; j < N2; j++) {
				for (int k = 0; k < V[j].adj.Count; k++) {
					Edge e = (Edge)V[j].adj[k];
					if (V[j].dist == int.MaxValue) continue;
					if (V[j].dist + e.L < V[e.v].dist) {
						V[e.v].dist = V[j].dist + e.L; V[e.v].parent = j;
					}
				}
			}
		}
	}
	
	public void run() {
		string[] line = System.Console.ReadLine().Split();
		N = int.Parse(line[0]); R = int.Parse(line[1]);
		V = new Node[N+100];
		for (int i = 0; i < N; i++) V[i] = new Node();
		for (int i = 0; i < R; i++) {
			line = System.Console.ReadLine().Split();
			int a = int.Parse(line[0]); a--;
			int b = int.Parse(line[1]); b--;
			int l = int.Parse(line[2]);
			V[a].adj.Add(new Edge(b, l));
			V[b].adj.Add(new Edge(a, l));
		}
		S = int.Parse(System.Console.ReadLine());
		N2 = N;
		line = System.Console.ReadLine().Split();
		for (int i = 0; i < S; i++) {
			int s = int.Parse(line[i]); s--;
			V[N2] = new Node();
			V[N2].adj = (ArrayList)V[s].adj.Clone();
			V[s].adj.Clear(); V[s].adj.Add(new Edge(N2, 0)); V[N2++].adj.Add(new Edge(s, 0));
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
		for (int i = 0; i < N2; i++) V[i].dist = int.MaxValue;
		V[0].dist = 0;
		BF();
		if (V[N-1].dist == int.MaxValue) System.Console.WriteLine("No safe route");
		else System.Console.WriteLine(total + V[N-1].dist);
	}
	
	static void Main() {
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) new InAndOut().run();
	}
}


