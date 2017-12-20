import java.util.*;

public class Shuriken {
	static Scanner sc = new Scanner(System.in);
	int S, N, P;
	int[] Q;
	
	public void run() {
		S = sc.nextInt(); N = sc.nextInt(); P = sc.nextInt();
		Q = new int[S+1];
		Q[0] = 0;
		for (int i = 1; i <= S; i++) {
			int move = 0;
			int maxMove = Math.min(N, i);
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
		if (Q[S] >= 0) System.out.println(Q[S] == P ? 0 : Q[S]);
		else {
			for (int i = 1; i <= N; i++) {
				if (i == P) continue;
				if (Q[S-i] == 0 || Q[S-i] == i) {
					System.out.println(i);
					return;
				}
			}
		}
	}
	
	public static void main(String[] args) {
		int runs = sc.nextInt();
		for (int i = 0; i < runs; i++) new Shuriken().run();
	}
}