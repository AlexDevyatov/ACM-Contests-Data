import java.util.*;

class Range {
	int start, count;
	boolean heavier, lighter, chosen, chL;
	public Range(int s, int c, boolean H, boolean L) {
		start = s; count = c; heavier = H; lighter = L;
		chosen = false; chL = false;
	}
	public String getString() {
		String S = "";
		if (count == 1) S = S + start;
		else S = S + start + "-" + (start + count - 1);
		return S;
	}
}

public class UndercoverPirate {
	static Scanner sc = new Scanner(System.in);
	int A, B, C, D, K;
	ArrayList<Range> Q;

	public UndercoverPirate(int N) {
		Q = new ArrayList<Range>();
		Q.add(new Range(1, N, true, true));
		K = 0;
		int powK = 1;
		while (powK < 2 * N + 3) {
			K++; powK *= 3;
		}
	}
	
	public void merge() {
		for (int i = 0; i < Q.size() - 1; i++) {
			Range R1 = Q.get(i);
			Range R2 = Q.get(i+1);
			if (R1.heavier == R2.heavier && R1.lighter == R2.lighter) {
				R1.count += R2.count;
				Q.remove(i+1);
				i--;
			}
		}
	}
	
	public void countTypes() {
		A = 0; B = 0; C = 0; D = 0;
		for (int i = 0; i < Q.size(); i++) {
			if (Q.get(i).heavier) {
				if (Q.get(i).lighter) A += Q.get(i).count;
				else B += Q.get(i).count;
			}
			else {
				if (Q.get(i).lighter) C += Q.get(i).count;
				else D += Q.get(i).count;
			}
		}
	}
	
	public void addSide(boolean left, boolean H, boolean L, int C) {
		if (C == 0) return;
		for (int i = 0; i < Q.size(); i++) {
			Range R = Q.get(i);
			if (!R.chosen && R.heavier == H && R.lighter == L && R.count >= C) {
				if (R.count - C > 0) Q.add(i+1, new Range(R.start + C, R.count - C, H, L));
				R.chosen = true; R.count = C; R.chL = left;
				break;
			}
		}
	}
	
	public void process() {
		String SL = "";
		String SR = "";
		for (int i = 0; i < Q.size(); i++) {
			Range R = Q.get(i);
			if (R.chosen) {
				if (R.chL) SL = SL + R.getString() + " ";
				else SR = SR + R.getString() + " ";
			}
		}
		System.out.println(SL + "+ " + SR);
		String Res = sc.next();
		for (int i = 0; i < Q.size(); i++) {
			Range R = Q.get(i);
			if (!R.chosen && !Res.equals("E")) {
				R.heavier = false; R.lighter = false;
			}
			if (R.chosen) {
				if (R.chL) {
					if (!Res.equals("R")) R.lighter = false;
					if (!Res.equals("L")) R.heavier = false;
				}
				else {
					if (!Res.equals("R")) R.heavier = false;
					if (!Res.equals("L")) R.lighter = false;
				}
			}
			R.chosen = false;
		}
	}
	
	public void query() {
		int powK = 1;
		for (int i = 0; i < K; i++) powK *= 3;
		
		if (B == 0 && C == 0 && D == 0) {
			int x = Math.min(A/2, (powK/3 - 1)/2);
			addSide(true, true, true, x);
			addSide(false, true, true, x);
		}
		else if (B == 0 && C == 0 && D >= A) {
			int x = Math.min(A, powK/3);
			addSide(true, true, true, x);
			addSide(false, false, false, x);			
		}
		else { // B + C <= powK
			if (B <= 1 && C <= 1) {
				addSide(true, B == 1, B == 0, 1); addSide(false, false, false, 1);
			}
			else if (Math.max(B/2, C/2) < powK/3) {
				int x = Math.max(B/2, C/2);
				int y = Math.min(Math.min(B/2, C/2), powK/3 - x);
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
		for (int i = 0; i < Q.size(); i++) {
			if (Q.get(i).heavier) System.out.println("Ninja " + Q.get(i).start + " is a heavy pirate");
			if (Q.get(i).lighter) System.out.println("Ninja " + Q.get(i).start + " is a light pirate");
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
	
	public static void main(String[] args) {
		int runs = sc.nextInt();
		for (int i = 0; i < runs; i++) new UndercoverPirate(sc.nextInt()).run();
	}

}
