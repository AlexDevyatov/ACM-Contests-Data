using System.Collections.Generic;

class Range {
	public int start, count;
	public bool heavier, lighter, chosen, chL;
	public Range(int s, int c, bool H, bool L) {
		start = s; count = c; heavier = H; lighter = L;
		chosen = false; chL = false;
	}
	public string getString() {
		string S = "";
		if (count == 1) S = S + start;
		else S = S + start + "-" + (start + count - 1);
		return S;
	}
}

public class UndercoverPirate {
	int A, B, C, D, K;
	List<Range> Q;

	public UndercoverPirate(int N) {
		Q = new List<Range>();
		Q.Add(new Range(1, N, true, true));
		K = 0;
		int powK = 1;
		while (powK < 2 * N + 3) {
			K++; powK *= 3;
		}
	}
	
	public void merge() {
		for (int i = 0; i < Q.Count - 1; i++) {
			Range R1 = Q[i];
			Range R2 = Q[i+1];
			if (R1.heavier == R2.heavier && R1.lighter == R2.lighter) {
				R1.count += R2.count;
				Q.RemoveAt(i+1);
				i--;
			}
		}
	}
	
	public void countTypes() {
		A = 0; B = 0; C = 0; D = 0;
		for (int i = 0; i < Q.Count; i++) {
			if (Q[i].heavier) {
				if (Q[i].lighter) A += Q[i].count;
				else B += Q[i].count;
			}
			else {
				if (Q[i].lighter) C += Q[i].count;
				else D += Q[i].count;
			}
		}
	}
	
	public void addSide(bool left, bool H, bool L, int C) {
		if (C == 0) return;
		for (int i = 0; i < Q.Count; i++) {
			Range R = Q[i];
			if (!R.chosen && R.heavier == H && R.lighter == L && R.count >= C) {
				if (R.count - C > 0) Q.Insert(i+1, new Range(R.start + C, R.count - C, H, L));
				R.chosen = true; R.count = C; R.chL = left;
				break;
			}
		}
	}
	
	public void process() {
		string SL = "";
		string SR = "";
		for (int i = 0; i < Q.Count; i++) {
			Range R = Q[i];
			if (R.chosen) {
				if (R.chL) SL = SL + R.getString() + " ";
				else SR = SR + R.getString() + " ";
			}
		}
		System.Console.WriteLine(SL + "+ " + SR);
		string Res = System.Console.ReadLine();
		for (int i = 0; i < Q.Count; i++) {
			Range R = Q[i];
			if (!R.chosen && !Res.Equals("E")) {
				R.heavier = false; R.lighter = false;
			}
			if (R.chosen) {
				if (R.chL) {
					if (!Res.Equals("R")) R.lighter = false;
					if (!Res.Equals("L")) R.heavier = false;
				}
				else {
					if (!Res.Equals("R")) R.heavier = false;
					if (!Res.Equals("L")) R.lighter = false;
				}
			}
			R.chosen = false;
		}
	}
	
	public void query() {
		int powK = 1;
		for (int i = 0; i < K; i++) powK *= 3;
		
		if (B == 0 && C == 0 && D == 0) {
			int x = System.Math.Min(A/2, (powK/3 - 1)/2);
			addSide(true, true, true, x);
			addSide(false, true, true, x);
		}
		else if (B == 0 && C == 0 && D >= A) {
			int x = System.Math.Min(A, powK/3);
			addSide(true, true, true, x);
			addSide(false, false, false, x);			
		}
		else { // B + C <= powK
			if (B <= 1 && C <= 1) {
				addSide(true, B == 1, B == 0, 1); addSide(false, false, false, 1);
			}
			else if (System.Math.Max(B/2, C/2) < powK/3) {
				int x = System.Math.Max(B/2, C/2);
				int y = System.Math.Min(System.Math.Min(B/2, C/2), powK/3 - x);
				addSide(true, B >= C, B < C, x); addSide(true, B < C, B >= C, y);
				addSide(false, B >= C, B < C, x); addSide(false, B < C, B >= C, y);
			}
			else {
				addSide(true, B >= C, B < C, powK/3); addSide(false, B >= C, B < C, powK/3);
			}
		}
		process();
	}
	
	public void outputAnswer() {
		for (int i = 0; i < Q.Count; i++) {
			if (Q[i].heavier) System.Console.WriteLine("Ninja " + Q[i].start + " is a heavy pirate");
			if (Q[i].lighter) System.Console.WriteLine("Ninja " + Q[i].start + " is a light pirate");
		}
	}
	
	public void run() {
		countTypes();
		while (2 * A + B + C > 1) {
			query();
			K--;
			merge();
			countTypes();
		}
		outputAnswer();
	}
	
	public static void Main() {
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) new UndercoverPirate(int.Parse(System.Console.ReadLine())).run();
	}

}
