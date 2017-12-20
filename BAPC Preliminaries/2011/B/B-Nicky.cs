class RNG {
	long Y, A, B, C, N, N2;
	
	bool check(long x) {
		long Z = A;
		Z = (Z * x + B)%N2; Z = (Z * x + C)%N2;
		return (Z%N2 == Y%N2);
	}
	
	void run() {
		string[] line = System.Console.ReadLine().Split();
		Y = long.Parse(line[0]); A = long.Parse(line[1]); B = long.Parse(line[2]); C = long.Parse(line[3]); N = long.Parse(line[4]);
		N2 = 1;
		long x = 0;
		for (int n = 1; n <= N; n++) {
			N2 *= 2;
			bool c1 = check(x);
			bool c2 = check(x + N2/2);
			if (!c1 && c2) x += N2/2;
			else if (c1 == c2) {
				System.Console.WriteLine("No unique solution");
				return;
			}
		}
		System.Console.WriteLine(x);
	}
	
	static void Main() {
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) new RNG().run();
	}

}

