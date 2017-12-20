import java.util.*;

public class BadWiring {
	static Scanner sc = new Scanner(System.in);
	int N, D;
	int[][] M;
	int[][] NV;
	int[] A, B;
	ArrayList<Integer> L;
	
	public int findMin(int x) {
		if (x == L.size()) {
			int q = 0;
			for (int i = 0; i < N; i++) q += A[i];
			return q;
		}
		else {
			int q = findMin(x+1);
			for (int i = 0; i < N; i++) A[i] = (A[i] + NV[x][i])%2;
			q = Math.min(q, findMin(x+1));
			for (int i = 0; i < N; i++) A[i] = (A[i] + NV[x][i])%2;
			return q;
		}
	}
	
	public void run() {
		N = sc.nextInt(); D = sc.nextInt();
		M = new int[N][N+1];
		A = new int[N]; B = new int[N];
		L = new ArrayList<Integer>();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				M[i][j] = ((Math.abs(j - i) <= D) ? 1 : 0);
			}
			M[i][N] = sc.nextInt();
			A[i] = -1;
		}
		
		int r = 0, c = 0;
		while (c < N) {
			// pivot
			for (int k = r; k < N; k++) {
				if (M[k][c] > M[r][c]) {
					int[] h = M[r]; M[r] = M[k]; M[k] = h;
				}
			}
			if (M[r][c] == 1) {
				B[r] = c;
				for (int k = 0; k < N; k++) {
					if (k == r) continue;
					if (M[k][c] == 1) {
						for (int j = c; j <= N; j++) M[k][j] ^= M[r][j];
					}
				}
				r++;
			}
			else {
				L.add(c); A[c] = 0;
			}
			c++;
		}
		for (int k = r; k < N; k++) {
			if (M[k][N] == 1) {
				System.out.println("impossible");
				return;
			}
		}
		
		// null space
		NV = new int[L.size()][N];
		for (int i = 0; i < L.size(); i++) {
			for (int j = 0; j < N; j++) {
				NV[i][j] = (j == L.get(i) ? 1 : 0);
			}
			for (int j = 0; j < r; j++) NV[i][B[j]] = M[j][L.get(i)]; 
		}
		
		// solution
		for (int k = r - 1; k >= 0; k--) {
			int x = M[k][N];
			c = N-1;
			while (A[c] != -1) {
				x = (x + M[k][c] * A[c])%2;
				c--;
			}
			A[c] = x;
		}
		
		// all solutions
		System.out.println(findMin(0));
	}
	
	public static void main(String[] args) {
		int runs = sc.nextInt();
		for (int i = 0; i < runs; i++) new BadWiring().run();
	}

}
