using System.Collections;

class Pirate {
	public int x, y, v;
	public ArrayList adj;
	public bool visit;
	public Pirate(int x, int y, int v) {
		this.x = x; this.y = y; this.v = v;
		adj = new ArrayList(); visit = false;
	}
	public double timeTo(Tentacle t) {
		return System.Math.Sqrt(((double)x - (double)t.x) * ((double)x - (double)t.x) + ((double)y - (double)t.y) * ((double)y - (double)t.y))/(double)v;
	}
}

class Tentacle {
	public int x, y, match;
	public Tentacle(int x, int y) {
		this.x = x; this.y = y; match = -1;
	}
}

class Attack {
	int N, K;
	Tentacle[] T;
	Pirate[] P;
	Pirate cap;
	Tentacle head;
	
	bool aug(int p) {
		if (P[p].visit) return false;
		P[p].visit = true;
		for (int i = 0; i < P[p].adj.Count; i++) {
			int t = (int)P[p].adj[i];
			if (T[t].match == -1 || aug(T[t].match)) {
				T[t].match = p;
				return true;
			}
		}
		return false;
	}
	
	void run() {
		string[] line = System.Console.ReadLine().Split();
		N = int.Parse(line[0]);
		K = int.Parse(line[1]);
		T = new Tentacle[N];
		P = new Pirate[K];
		line = System.Console.ReadLine().Split();
		cap = new Pirate(int.Parse(line[0]), int.Parse(line[1]), int.Parse(line[2]));
		for (int i = 0; i < K; i++) {
			line = System.Console.ReadLine().Split();
			P[i] = new Pirate(int.Parse(line[0]), int.Parse(line[1]), int.Parse(line[2]));
		}
		line = System.Console.ReadLine().Split();
		head = new Tentacle(int.Parse(line[0]), int.Parse(line[1]));
		for (int i = 0; i < N; i++) {
			line = System.Console.ReadLine().Split();
			T[i] = new Tentacle(int.Parse(line[0]), int.Parse(line[1]));
		}
		
		ArrayList L = new ArrayList();
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < N; j++) {
				L.Add(P[i].timeTo(T[j]));
			}
		}
		L.Sort();
		int x = -1, y = L.Count - 1;
		while (x + 1 < y) {
			int h = (x+y)/2;
			for (int i = 0; i < K; i++) {
				P[i].adj.Clear();
				for (int j = 0; j < N; j++) {
					if (P[i].timeTo(T[j]) <= (double)L[h]) {
						P[i].adj.Add(j);
					}
				}
			}
			for (int j = 0; j < N; j++) T[j].match = -1;
			int M = 0;
			for (int i = 0; i < K; i++) {
				for (int j = 0; j < K; j++) P[j].visit = false;
				if (aug(i)) M++;
			}
			if (M == N) y = h;
			else x = h;
		}
		System.Console.WriteLine((double)L[y] + cap.timeTo(head));
	}
	
	static void Main() {
		System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) new Attack().run();
	}

}


