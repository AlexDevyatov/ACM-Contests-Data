import java.util.*;

class Pirate implements Comparable<Pirate> {
	long[] t = new long[4];
	long arrive;
	int side;
	public Pirate(long t1, long t2, long t3, long t4, long arrive, int side) {
		t[0] = t1; t[1] = t2; t[2] = t3; t[3] = t4; this.arrive = arrive; this.side = side;
	}
	public int compareTo(Pirate arg0) {
		if (arrive < arg0.arrive) return -1;
		else if (arrive > arg0.arrive) return 1;
		else return ((int)arg0.t[3 - 2 * side] - (int)t[3 - 2 * side]);
	}
}

public class WalkThePlank {
	static Scanner sc = new Scanner(System.in);
	long N, P, T;
	PriorityQueue<Pirate> Q1, Q2;
	
	public void run() {
		N = sc.nextLong(); P = sc.nextLong(); T = 0;
		Q1 = new PriorityQueue<Pirate>(); Q2 = new PriorityQueue<Pirate>();
		for (int i = 0; i < P; i++) {
			Q1.add(new Pirate(sc.nextLong(), sc.nextLong(), sc.nextLong(), sc.nextLong(), i - P, 0));
		}
		
		while (!Q1.isEmpty() || !Q2.isEmpty()) {
			Pirate P1 = Q1.peek(), P2 = Q2.peek();
			if (P2 == null || (P1 != null && P2.arrive > T && P1.arrive < P2.arrive)) {
				Q1.poll(); 
				if (N - Q2.size() > 0) {
					T = Math.max(T, P1.arrive) + P1.t[0];
					P1.arrive = T + P1.t[1]; P1.side = 1;
					Q2.add(P1);
				}
			}
			else {
				T = Math.max(T, P2.arrive) + P2.t[2];
				Q2.poll(); P2.arrive = T + P2.t[3]; P2.side = 0; 
				Q1.add(P2);
				N--;
				if (N == 0) {
					System.out.println(T);
					return;
				}
			}
		}
	}
	
	public static void main(String[] args) {
		int runs = sc.nextInt();
		for (int i = 0; i < runs; i++) new WalkThePlank().run();
	}

}