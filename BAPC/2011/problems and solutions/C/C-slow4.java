import java.util.*;

class Island {
	long x, y;
	public Island(long x, long y) {
		this.x = x; this.y = y;
	}
}

class View {
	long A, B, C; // Ax + By + C = 0
	public View(Island i1, Island i2) {
		A = i2.y - i1.y; B = i1.x - i2.x; C = -A * i1.x - B * i1.y;  
	}
}

public class FindTreasureNaive {
	static Scanner sc = new Scanner(System.in);
	int N, M;
	Island[] L;
	View[] V;
	
	public void run() {
		N = sc.nextInt();
		L = new Island[N];
		for (int i = 0; i < N; i++) {
			L[i] = new Island(sc.nextLong(), sc.nextLong());
		}
		int K = sc.nextInt();
		for (int k = 0; k < K; k++) {
			M = sc.nextInt();
			V = new View[M];
			for (int i = 0; i < M; i++) {
				V[i] = new View(L[sc.nextInt() - 1], L[sc.nextInt() - 1]);
			}
			for (int i = 0; i < N; i++) {
				boolean good = true;
				for (int j = 0; j < M; j++) {
					if (V[j].A * L[i].x + V[j].B * L[i].y + V[j].C <= 0) {
						good = false; break;
					}
				}
				if (good) System.out.println(i+1);
			}
			System.out.println("0");
		}
	}
	
	public static void main(String[] args) {
		int runs = sc.nextInt();
		for (int i = 0; i < runs; i++) new FindTreasureNaive().run();
	}

}

