import java.util.*;
import java.math.*;

public class tobi {
	public static long N, ret = 1;
	public static void factors(long fact) {
		long facCnt = 0;
		while (N % fact == 0) {
			N /= fact;
			facCnt++;
		}
		ret *= (facCnt + 1);
	}
	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextLong();
		factors(2);
		for (long i = 3; i <= 1000000; i += 2) factors(i);
		long root = (long) Math.sqrt(N);
		BigInteger bigN = new BigInteger("" + N);
		if (bigN.isProbablePrime(50)) ret *= 2;
		else if (N != 1 && root*root == N) ret *= 3;
		else if (N != 1) ret *= 4;
		System.out.println(ret);
	}
}
