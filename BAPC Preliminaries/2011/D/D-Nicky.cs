class Polly {
	string S1, S2;
	string[] words, mimic;
	int[,] Q = new int[1005,1005];
	int[,] D = new int[8,8];
	bool[] matched = new bool[8];
	
	public int editDist(string S1, string S2) {
		int N1 = S1.Length, N2 = S2.Length;
		for (int i = 0; i <= N1; i++) Q[i,0] = i;
		for (int i = 0; i <= N2; i++) Q[0,i] = i;
		for (int i = 1; i <= N1; i++) {
			for (int j = 1; j <= N2; j++) {
				Q[i,j] = System.Math.Min(1 + System.Math.Min(Q[i-1,j], Q[i,j-1]), Q[i-1,j-1] + (S1[i-1] == S2[j-1] ? 0 : 1));
			}
		}
		return Q[N1,N2];
	}
	
	public int minErrors(int k) {
		if (k == mimic.Length) return 0;
		int minE = int.MaxValue;
		for (int i = 0; i < words.Length; i++) {
			if (matched[i]) continue;
			matched[i] = true;
			minE = System.Math.Min(minE, D[i,k] + minErrors(k+1));
			matched[i] = false;
		}
		return minE;
	}
	
	public void run() {
		S1 = System.Console.ReadLine(); S2 = System.Console.ReadLine();
		for (int i = 0; i < S1.Length - 1; i++) if (S1[i] == ' ' && S1[i+1] == ' ') System.Console.WriteLine("Double space!");
		for (int i = 0; i < S2.Length - 1; i++) if (S2[i] == ' ' && S2[i+1] == ' ') System.Console.WriteLine("Double space!");
		words = S1.Split(' '); mimic = S2.Split(' ');
		if (S1.Length > 1000 || S1.Length == 0 || S2.Length > 1000 || S2.Length == 0) System.Console.WriteLine("Incorrect string length");
		if (words.Length > 8 || mimic.Length > words.Length) System.Console.WriteLine("Incorrect number of words");
		
		for (int i = 0; i < words.Length; i++) for (int j = 0; j < mimic.Length; j++) D[i,j] = editDist(words[i], mimic[j]);
		for (int i = 0; i < words.Length; i++) matched[i] = false;
		
		System.Console.WriteLine(minErrors(0));
	}
	
	static void Main() {
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) new Polly().run();
	}

}


