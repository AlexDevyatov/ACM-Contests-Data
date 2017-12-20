import java.util.*;

public class RNG {
	static Scanner sc = new Scanner(System.in);
	long Y, A, B, C, N, N2;
	
	public boolean check(long x) {
		long Z = A;
		Z = (Z * x + B)%N2; Z = (Z * x + C)%N2;
		return (Z%N2 == Y%N2);
	}
	
	public void run() {
		Y = sc.nextInt(); A = sc.nextInt(); B = sc.nextInt(); C = sc.nextInt(); N = sc.nextInt();
		N2 = 1;
		long x = 0;
		for (int n = 1; n <= N; n++) {
			N2 *= 2;
			boolean c1 = check(x);
			boolean c2 = check(x + N2/2);
			if (!c1 && c2) x += N2/2;
			else if (c1 == c2) {
				System.out.println("No unique solution");
				return;
			}
		}
		System.out.println(x);
	}
	
	public static void main(String[] args) {
		int runs = sc.nextInt();
		for (int i = 0; i < runs; i++) new RNG().run();
	}

}

