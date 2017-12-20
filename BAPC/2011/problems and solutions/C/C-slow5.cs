using System;
using System.Collections;
using System.Collections.Generic;

class Island {
	public long x, y;
	public Island(long x, long y) {
		this.x = x; this.y = y;
	}
}

class View {
	public long A, B, C; // Ax + By + C = 0
	public View(Island i1, Island i2) {
		A = i2.y - i1.y; B = i1.x - i2.x; C = -A * i1.x - B * i1.y;  
	}
}

public class FindTreasureNaive {
	int N, M;
	Island[] L;
	View[] V;
	
	public void run() {
		N = int.Parse(System.Console.ReadLine());
		L = new Island[N];
		for (int i = 0; i < N; i++) {
			string[] line = System.Console.ReadLine().Split();
			L[i] = new Island(int.Parse(line[0]), int.Parse(line[1]));
		}
		int K = int.Parse(System.Console.ReadLine());
		for (int k = 0; k < K; k++) {
			M = int.Parse(System.Console.ReadLine());
			V = new View[M];
			for (int i = 0; i < M; i++) {
				string[] line = System.Console.ReadLine().Split();
				V[i] = new View(L[int.Parse(line[0]) - 1], L[int.Parse(line[1])- 1]);
			}
			for (int i = 0; i < N; i++) {
				bool good = true;
				for (int j = 0; j < M; j++) {
					if (V[j].A * L[i].x + V[j].B * L[i].y + V[j].C <= 0) {
						good = false; break;
					}
				}
				if (good) System.Console.WriteLine(i+1);
			}
			System.Console.WriteLine("0");
		}
	}
	
	public static void Main() {
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) new FindTreasureNaive().run();
	}

}

