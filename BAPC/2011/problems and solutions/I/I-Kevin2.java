import java.util.*;

class Pirate {
	int x, L;
	public Pirate(int x, int L) {
		this.x = x; this.L = L;
	}
}

class compHouse implements Comparator<Pirate> {
	public int compare(Pirate arg0, Pirate arg1) {
		return (arg0.x - arg1.x);
	}	
}

class compShip implements Comparator<Pirate> {
	public int compare(Pirate arg0, Pirate arg1) {
		if (arg0.L == arg1.L) return (arg0.x - arg1.x);
		else return (arg0.L - arg1.L);
	}	
}

public class ParkingShips {
	static Scanner sc = new Scanner(System.in);
	int N;
	Pirate cap;
	PriorityQueue<Pirate> Qx1, Qx2, QL1, QL2;
	
	public void run() {
		N = sc.nextInt();
		cap = new Pirate(sc.nextInt(), sc.nextInt());
		if (cap.L%2 == 1) cap.L++;
		Qx1 = new PriorityQueue<Pirate>(N, new compHouse());
		Qx2 = new PriorityQueue<Pirate>(N, new compHouse());
		QL1 = new PriorityQueue<Pirate>(N, new compShip());
		QL2 = new PriorityQueue<Pirate>(N, new compShip());
		for (int i = 1; i < N; i++) {
			Pirate P = new Pirate(sc.nextInt(), sc.nextInt());
			if (P.x < cap.x) Qx1.add(P);
			else Qx2.add(P);
		}
		
		int k = 0;
		int left = Integer.MIN_VALUE;
		while (!Qx1.isEmpty() || !QL1.isEmpty()) {
			if (Qx1.isEmpty()) {
				Pirate P = QL1.poll();
				if (P.x < left) continue;
				if (left + P.L > cap.x - cap.L/2) break;
				left += P.L; k++;
			}
			else if (QL1.isEmpty()) {
				Pirate P = Qx1.poll();
				if (P.x < left) continue;
				if (P.x > cap.x - cap.L/2) break;
				if (P.x - P.L < left) {
					QL1.add(P); continue;
				}
				left = P.x; k++;
			}
			else {
				Pirate P1 = Qx1.peek();
				Pirate P2 = QL1.peek();
				if (P1.x < left + P2.L || (P1.x == left + P2.L && P1.x < P2.x)) {
					Pirate P = Qx1.poll();
					if (P.x < left) continue;
					if (P.x > cap.x - cap.L/2) break;
					if (P.x - P.L < left) {
						QL1.add(P); continue;
					}
					left = P.x; k++;					
				}
				else {
					Pirate P = QL1.poll();
					if (P.x < left) continue;
					if (left + P.L > cap.x - cap.L/2) break;
					left += P.L; k++;
				}
			}
		}
		
		k++;
		
		left = cap.x + cap.L/2;
		while (!Qx2.isEmpty() || !QL2.isEmpty()) {
			if (Qx2.isEmpty()) {
				Pirate P = QL2.poll();
				if (P.x < left) continue;
				left += P.L; k++;
			}
			else if (QL2.isEmpty()) {
				Pirate P = Qx2.poll();
				if (P.x < left) continue;
				if (P.x - P.L < left) {
					QL2.add(P); continue;
				}
				left = P.x; k++;
			}
			else {
				Pirate P1 = Qx2.peek();
				Pirate P2 = QL2.peek();
				if (P1.x < left + P2.L || (P1.x == left + P2.L && P1.x < P2.x)) {
					Pirate P = Qx2.poll();
					if (P.x < left) continue;
					if (P.x - P.L < left) {
						QL2.add(P); continue;
					}
					left = P.x; k++;					
				}
				else {
					Pirate P = QL2.poll();
					if (P.x < left) continue;
					left += P.L; k++;
				}
			}
		}
		
		System.out.println(k);
	}
	
	public static void main(String[] args) {
		int runs = sc.nextInt();
		for (int i = 0; i < runs; i++) new ParkingShips().run();
	}

}
