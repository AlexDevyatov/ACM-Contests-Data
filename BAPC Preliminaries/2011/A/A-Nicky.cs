class Mutiny {
	int N, K;
	
	void runDP() {
		string[] line = System.Console.ReadLine().Split();
		N = int.Parse(line[0]); K = int.Parse(line[1]);
		//int[][][][] Q = new int[N+1,K+1,K+1,K+1]; // ships, pirates, disloyal, buffer
		int[][][][] Q; // ships, pirates, disloyal, buffer
		Q = new int[N+1][][][];
		for (int i = 0; i < N + 1; i++) {
			Q[i] = new int[K+1][][];
			for (int j = 0; j < K+1; j++) {
				Q[i][j] = new int[K+1][];
				for (int k = 0; k < K+1; k++) {
					Q[i][j][k] = new int[K+1];
				}
			}
		}
		for (int i = 0; i <= K; i++) {
			for (int j = 0; j <= K - i; j++) {
				for (int k = 0; k <= K; k++) {
					if (i == 0 || i < j) Q[1][i][j][k] = int.MinValue;
					else Q[1][i][j][k] = System.Math.Min(k, (i - j)/2);
				}
			}
		}
		for (int s = 2; s <= N; s++) {
			for (int i = 0; i <= K; i++) {
				for (int j = 0; j <= K - i; j++) {
					for (int k = 0; k <= K; k++) {
						Q[s][i][j][k] = int.MinValue;
						int maxD = System.Math.Min(k, (i - j)/2);
						for (int d = 0; d <= maxD; d++) {
							int minL = System.Math.Max(1, d+j);
							for (int l = minL; l+d <= i; l++) {
								Q[s][i][j][k] = System.Math.Max(Q[s][i][j][k], d + Q[s-1][i-d-l][d][l-d-j]);
							}
						}
					}
				}
			}
		}
		System.Console.WriteLine(Q[N][K][0][K]);
	}
	
	void run() {
		string[] line = System.Console.ReadLine().Split();
		N = int.Parse(line[0]); K = int.Parse(line[1]);
		if (N == 1) System.Console.WriteLine(K/2);
		else if (K - N <= (N+2)/3) System.Console.WriteLine(K - N);
		else System.Console.WriteLine((K - (N-2)/3)/3);
	}
	
	static void Main() {
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) new Mutiny().runDP();
	}

}

