import java.util.*;

class Pirate {
	int x, y, v;
	ArrayList<Integer> adj;
	boolean visit;
	public Pirate(int x, int y, int v) {
		this.x = x; this.y = y; this.v = v;
		adj = new ArrayList<Integer>(); visit = false;
	}
	public double timeTo(Tentacle t) {
		return Math.sqrt((x - t.x) * (x - t.x) + (y - t.y) * (y - t.y))/(double)v;
	}
}

class Tentacle {
	int x, y, match;
	public Tentacle(int x, int y) {
		this.x = x; this.y = y; match = -1;
	}
}

public class Attack {
	static Scanner sc = new Scanner(System.in);
	int N, K;
	Tentacle[] T;
	Pirate[] P;
	Pirate cap;
	Tentacle head;
	
	public boolean aug(int p) {
		if (P[p].visit) return false;
		P[p].visit = true;
		for (int i = 0; i < P[p].adj.size(); i++) {
			int t = P[p].adj.get(i);
			if (T[t].match == -1 || aug(T[t].match)) {
				T[t].match = p;
				return true;
			}
		}
		return false;
	}
	
	public void run() {
		N = sc.nextInt(); K = sc.nextInt();
		T = new Tentacle[N];
		P = new Pirate[K];
		cap = new Pirate(sc.nextInt(), sc.nextInt(), sc.nextInt());
		for (int i = 0; i < K; i++) P[i] = new Pirate(sc.nextInt(), sc.nextInt(), sc.nextInt());
		head = new Tentacle(sc.nextInt(), sc.nextInt());
		for (int i = 0; i < N; i++) T[i] = new Tentacle(sc.nextInt(), sc.nextInt());
		
		ArrayList<Double> L = new ArrayList<Double>();
		for (int i = 0; i < K; i++) for (int j = 0; j < N; j++) L.add(new Double(P[i].timeTo(T[j])));
		Collections.sort(L);
		int x = -1, y = L.size() - 1;
		while (x + 1 < y) {
			int h = (x+y)/2;
			for (int i = 0; i < K; i++) {
				P[i].adj.clear();
				for (int j = 0; j < N; j++) if (P[i].timeTo(T[j]) <= L.get(h)) P[i].adj.add(new Integer(j));
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
		System.out.println(L.get(y) + cap.timeTo(head));
	}
	
	public static void main(String[] args) {
		int runs = sc.nextInt();
		for (int i = 0; i < runs; i++) new Attack().run();
	}

}


