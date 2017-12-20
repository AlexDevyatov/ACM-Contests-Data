import java.util.*;

class Sol implements Comparable<Sol> {
	int N, E, S, W;
	public Sol(int N, int E, int S, int W) {
		this.N = N; this.E = E; this.S = S; this.W = W;
	}
	public int compareTo(Sol arg0) {
		if (N != arg0.N) return (N - arg0.N);
		if (E != arg0.E) return (E - arg0.E);
		if (S != arg0.S) return (S - arg0.S);
		return (W - arg0.W);
	}
	public void print() {
		System.out.println(N + " " + E + " " + S + " " + W);
	}
}

public class UFS {
	static Scanner sc = new Scanner(System.in);
	long L, W, B;
	long sx, sy, fx, fy;
	TreeSet<Sol> Q;
	
	public void run() {
		L = sc.nextLong(); W = sc.nextLong(); B = sc.nextLong();
		sx = sc.nextLong(); sy = sc.nextLong(); fx = sc.nextLong(); fy = sc.nextLong();
		Q = new TreeSet<Sol>();
		long minDist = Long.MAX_VALUE;
		long curx = (B%2 == 0 ? fx : L-fx), cury = fy;
		long Bx = -B, By = 0;
		while (Bx <= B) {
			long dx = sx - (Bx * L + curx), dy1 = sy - (By * W + cury), dy2 = sy - (cury - By * W);
			long d1 = dx * dx + dy1 * dy1;
			long d2 = dx * dx + dy2 * dy2;
			if (d1 <= minDist) {
				if (d1 < minDist) {
					minDist = d1; Q.clear();
				}
				Q.add(new Sol((int)(By+1)/2, (int)(Bx > 0 ? (Bx+1)/2 : -Bx/2), (int)By/2, (int)(Bx > 0 ? Bx/2 : (-Bx+1)/2)));
			}
			if (d2 <= minDist) {
				if (d2 < minDist) {
					minDist = d2; Q.clear();
				}
				Q.add(new Sol((int)By/2, (int)(Bx > 0 ? (Bx+1)/2 : -Bx/2), (int)(By+1)/2, (int)(Bx > 0 ? Bx/2 : (-Bx+1)/2)));
			}
			if (Bx >= 0) By--;
			else By++;
			Bx++;
			curx = L - curx; cury = W - cury;
		}
		
		while (!Q.isEmpty()) {
			Q.pollFirst().print();
		}
		System.out.println("0");
	}
	
	public static void main(String[] args) {
		int runs = sc.nextInt();
		for (int i = 0; i < runs; i++) new UFS().run();
	}

}


