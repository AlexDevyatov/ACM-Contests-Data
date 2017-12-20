import java.util.*;

public class TreasureMap {
	static Scanner sc = new Scanner(System.in);
	int N;
	
	public void run() {
		N = sc.nextInt();
		if (N%4 == 2) System.out.println("IMPOSSIBLE");
		else {
			int k = (int)Math.ceil(Math.sqrt((double)N));
			while(k > 0) {
				if (N%k == 0 && (N/k + k)%2 == 0) {
					System.out.println((N/k - k)/2 + " " + (N/k + k)/2);
					return;
				}
				k--;
			}
		}
	}
	
	public static void main(String[] args) {
		int runs = sc.nextInt();
		for (int i = 0; i < runs; i++) new TreasureMap().run();
	}

}