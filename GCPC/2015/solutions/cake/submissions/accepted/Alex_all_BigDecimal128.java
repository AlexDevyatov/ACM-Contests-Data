import java.util.*;
import java.math.*;

public class Alex_all_BigDecimal128{
	static MathContext mc = new MathContext(128);

	static long x[][] = new long[128][2];
	static int N;

	public static BigDecimal sqrt(BigDecimal v){
		BigDecimal allowed_error = BigDecimal.valueOf(1e-300);
		BigDecimal approximation = BigDecimal.ONE;
		BigDecimal two = BigDecimal.valueOf(2);
		BigDecimal last_change = null;
		while(true){
			BigDecimal inverse = v.divide(approximation, mc);
			// exact solution is between in the interval with borders approximation and inverse
			BigDecimal diff = approximation.subtract(inverse).abs();
			if(last_change != null && last_change.compareTo(diff) <= 0)break;
			if(diff.compareTo(allowed_error) <= 0)break;
			last_change = diff;
			approximation = approximation.add(inverse, mc).divide(two);
		}
		return approximation;
	}

	public static void main(String[] args){
		Scanner scan = new Scanner(System.in);
		BigDecimal a = new BigDecimal(scan.next());
		N = scan.nextInt();
		for(int i = 0; i < N; i++)
			for(int j = 0; j < 2; j++)
				x[i][j] = scan.nextLong();
		BigDecimal A = BigDecimal.valueOf(0.0), PARTS = BigDecimal.valueOf(0.0);
		for(int i = 1; i <= N; i++)
			A = A.add(BigDecimal.valueOf( x[i-1][0]).multiply(BigDecimal.valueOf(x[i%N][1]))).subtract(BigDecimal.valueOf(x[i%N][0]).multiply(BigDecimal.valueOf(x[i-1][1])));
		for(int i = 0; i < N ; i++){
			for(int j = 1; j <= 3; j++){
				PARTS = PARTS.add(BigDecimal.valueOf(x[(i+j-1)%N][0]).multiply(BigDecimal.valueOf(x[(i+(j%3))%N][1]))).subtract(BigDecimal.valueOf(x[(i+j-1)%N][1]).multiply(BigDecimal.valueOf(x[(i+(j%3))%N][0])));
			}
		}
		BigDecimal square_result = PARTS.divide((BigDecimal.ONE.subtract(a)).multiply(A), mc);
		BigDecimal result = sqrt(square_result);
		System.out.println(result);
		System.exit(0);
	}
}
