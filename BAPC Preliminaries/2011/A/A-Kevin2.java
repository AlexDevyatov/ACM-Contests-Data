import java.util.*;

public class Mutiny {
	static Scanner sc = new Scanner(System.in);
	int N, K;
	
	public void runDP() {
		N = sc.nextInt(); K = sc.nextInt();
		int[][][][] Q = new int[N+1][K+1][K+1][K+1]; // ships, pirates, disloyal, buffer
		for (int i = 0; i <= K; i++) {
			for (int j = 0; j <= K - i; j++) {
				for (int k = 0; k <= K; k++) {
					if (i == 0 || i < j) Q[1][i][j][k] = Integer.MIN_VALUE;
					else Q[1][i][j][k] = Math.min(k, (i - j)/2);
				}
			}
		}
		for (int s = 2; s <= N; s++) {
			for (int i = 0; i <= K; i++) {
				for (int j = 0; j <= K - i; j++) {
					for (int k = 0; k <= K; k++) {
						Q[s][i][j][k] = Integer.MIN_VALUE;
						int maxD = Math.min(k, (i - j)/2);
						for (int d = 0; d <= maxD; d++) {
							int minL = Math.max(1, d+j);
							for (int l = minL; l+d <= i; l++) {
								Q[s][i][j][k] = Math.max(Q[s][i][j][k], d + Q[s-1][i-d-l][d][l-d-j]);
							}
						}
					}
				}
			}
		}
		System.out.println(Q[N][K][0][K]);
	}
	
	public void run() {
		N = sc.nextInt(); K = sc.nextInt();
		if (N == 1) System.out.println(K/2);
		else if (K - N <= (N+2)/3) System.out.println(K - N);
		else System.out.println((K - (N-2)/3)/3);
	}
	
	public static void main(String[] args) {
		int runs = sc.nextInt();
		for (int i = 0; i < runs; i++) new Mutiny().runDP();
	}

}

