import java.util.*;

class Interval implements Comparable<Interval> {
	double ang1, ang2;
	public Interval(int x, int y, int r) {
		double mid = Math.atan2(y, x);
		double dist = Math.sqrt(x * x + y * y);
		double dif = Math.asin((double)r / dist);
		ang1 = mid - dif;
		if (ang1 < -Math.PI) ang1 += 2.0 * Math.PI;
		ang2 = mid + dif;
		if (ang2 >= Math.PI) ang2 -= 2.0 * Math.PI;		
	}
	public boolean contains(double ang) {
		if (ang1 <= ang2) return (ang1 <= ang && ang <= ang2);
		else return (ang1 <= ang || ang <= ang2);
	}
	public int compareTo(Interval arg0) {
		return Double.compare(ang2, arg0.ang2);
	}
}

public class Popping {
	static Scanner sc = new Scanner(System.in);
	int N;
	ArrayList<Interval> I = new ArrayList<Interval>();
	
	public void run() {
		N = sc.nextInt();
		for (int i = 0; i < N; i++) {
			I.add(new Interval(sc.nextInt(), sc.nextInt(), sc.nextInt()));
		}
		Collections.sort(I);
		
		int opt = N;
		for (int i = 0; i < N; i++) {
			int count = 1;
			double ang = I.get(i).ang2;
			for (int j = (i+1)%N; j != i; j = (j+1)%N) {
				if (!I.get(j).contains(ang)) {
					count++; ang = I.get(j).ang2;
				}
			}
			opt = Math.min(opt, count);
		}
		System.out.println(opt);
	}
	
	public static void main(String[] args) {
		int runs = sc.nextInt();
		for (int i = 0; i < runs; i++) new Popping().run();
	}

}



