class Shuriken {
	int S, N, P;
	int[] Q;
	
	public void run() {
		string[] line = System.Console.ReadLine().Split();
		S = int.Parse(line[0]); N = int.Parse(line[1]); P = int.Parse(line[2]);
		Q = new int[S+1];
		Q[0] = 0;
		for (int i = 1; i <= S; i++) {
			int move = 0;
			int maxMove = System.Math.Min(N, i);
			for (int j = 1; j <= maxMove; j++) {
				if (Q[i-j] == 0 || Q[i-j] == j) {
					if (move == 0) move = j;
					else {
						move = -1;
						break;
					}
				}
			}
			Q[i] = move;
		}
		if (Q[S] >= 0) System.Console.WriteLine(Q[S] == P ? 0 : Q[S]);
		else {
			for (int i = 1; i <= N; i++) {
				if (i == P) continue;
				if (Q[S-i] == 0 || Q[S-i] == i) {
					System.Console.WriteLine(i);
					return;
				}
			}
		}
	}
	
	static void Main() {
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) new Shuriken().run();
	}
}