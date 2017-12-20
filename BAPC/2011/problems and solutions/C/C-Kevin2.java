import java.util.*;

class Island {
	int x, y;
	public Island(int x, int y) {
		this.x = x; this.y = y;
	}
}

class View implements Comparable<View> {
	int i, j;
	double a, b;
	public View(int i, int j, Island i1, Island i2) {
		this.i = i; this.j = j;
		a = (double)(i2.y - i1.y) / (double)(i2.x - i1.x);
		b = a * i1.x - i1.y;
	}
	public int compareTo(View o) {
		return Double.compare(a, o.a);
	}
}

public class FindTreasure {
	static Scanner sc = new Scanner(System.in);
	int N, M;
	Island[] L;
	ArrayList<View> V1, V2;
	
	public double getTurn(View v1, View v2, View v3) { // right < 0, left > 0
		return ((v2.a - v1.a) * (v3.b - v2.b) - (v2.b - v1.b) * (v3.a - v2.a));
	}
	
	public void run() {
		N = sc.nextInt();
		L = new Island[N];
		for (int i = 0; i < N; i++) {
			L[i] = new Island(sc.nextInt(), sc.nextInt());
		}
		int K = sc.nextInt();
		for (int k = 0; k < K; k++) {
			M = sc.nextInt();
			V1 = new ArrayList<View>(); V2 = new ArrayList<View>();
			for (int i = 0; i < M; i++) {
				int l = sc.nextInt(); l--;
				int r = sc.nextInt(); r--;
				View v = new View(l, r, L[l], L[r]);
				if (L[l].x < L[r].x) V1.add(v);
				else V2.add(v);
			}
			Collections.sort(V1); Collections.sort(V2);
			
			// bottom
			ArrayList<View> Q1 = new ArrayList<View>();
			if (V1.size() > 0) Q1.add(V1.get(0));
			if (V1.size() > 1) Q1.add(V1.get(1));
			for (int i = 2; i < V1.size(); i++) {
				while (Q1.size() >= 2 && getTurn(Q1.get(Q1.size() - 2), Q1.get(Q1.size() - 1), V1.get(i)) > 0.0) Q1.remove(Q1.size() - 1);
				Q1.add(V1.get(i));
			}
			// top
			ArrayList<View> Q2 = new ArrayList<View>();
			if (V2.size() > 0) Q2.add(V2.get(0));
			if (V2.size() > 1) Q2.add(V2.get(1));
			for (int i = 2; i < V2.size(); i++) {
				while (Q2.size() >= 2 && getTurn(Q2.get(Q2.size() - 2), Q2.get(Q2.size() - 1), V2.get(i)) < 0.0) Q2.remove(Q2.size() - 1);
				Q2.add(V2.get(i));
			}
			
			for (int i = 0; i < N; i++) {
				double A = L[i].x;
				double B = -L[i].y;
				if (Q1.size() > 0) {
					int x = -1, y = Q1.size() - 1;
					while (x + 1 < y) {
						int h = (x+y)/2;
						if ((Q1.get(h+1).b - Q1.get(h).b) >= A * (Q1.get(h+1).a - Q1.get(h).a)) x = h;
						else y = h;
					}
					if (A * Q1.get(y).a + B <= Q1.get(y).b || Q1.get(y).i == i || Q1.get(y).j == i) continue;
				}
				if (Q2.size() > 0) {
					int x = -1, y = Q2.size() - 1;
					while (x + 1 < y) {
						int h = (x+y)/2;
						if ((Q2.get(h+1).b - Q2.get(h).b) <= A * (Q2.get(h+1).a - Q2.get(h).a)) x = h;
						else y = h;
					}
					if (A * Q2.get(y).a + B >= Q2.get(y).b || Q2.get(y).i == i || Q2.get(y).j == i) continue;
				}
				System.out.println(i+1);
			}
			System.out.println("0");
		}
	}
	
	public static void main(String[] args) {
		int runs = sc.nextInt();
		for (int i = 0; i < runs; i++) new FindTreasure().run();
	}

}
