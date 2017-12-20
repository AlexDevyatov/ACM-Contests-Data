import java.math.*;
import java.util.*;
import java.io.*;

public class SolutionWithBigIntegerProbablePrime{
	static PrintStream out;
	static InputStream in;
	// precalculate all primes < 10^6 with sieve of Eratosthenes
	// store primes in array primes - the number of stored primes is P
	static final int MAXP = 1000000; // = 10^6
	static int primes[] = new int[MAXP / 10];
	static int P;
	static boolean sieve[] = new boolean[MAXP];

	static void init(){
		P = 0;
		for(int p = 2; p < MAXP; p++){
			if(sieve[p])continue;
			primes[P++] = p;
			if(MAXP / p >= p){
				for(int i = p * p; i < MAXP; i+=p){
					sieve[i] = true;
				}
			}
		}
	}

	static boolean isPrime(long val){
		return BigInteger.valueOf(val).isProbablePrime(100);
	}

	// checks whether val is a square with binary search, val >= 1
	static boolean isSquare(long val){
		long lo = 1, hi = val;
		while(lo <= hi){
			long mid = lo + (hi - lo) / 2;
			long tmp = (val / mid) / mid;
			if(tmp == 0)hi = mid - 1;
			else if(mid * mid == val)return true;
			else if(mid * mid < val)lo = mid + 1;
		}
		return false;
	}


	// calculates the number of positive divisors of val
	static long calc(long val){
		long res = 1;
		for(int i = 0; i < P; i++){
			if(val == 1)break;
			int p = primes[i];
			if(val % p == 0){ // checks whether p is a divisor of val
				int num = 0;
				while(val % p == 0){
					val /= p;
					++num;
				}
				// p^num divides initial val but p^(num + 1) does not divide initial val
				// => p can be taken 0 to num times => num + 1 possibilities!!
				res *= num + 1;
			}
		}
		// val has no divisors less or equal than 10^6 and val <= 10^18
		// => this leads to the following 3 cases
		// val is either 1
		// or val = p with p prime
		// or val = p * q with p and q prime
		if(val == 1)return res; // first case
		else if(isPrime(val))return res * 2; // second case
		else if(isSquare(val))return res * 3; // third case but with p == q
		else return res * 4; // third case with p != q
	}

	// reading input and writing output:
	public static void main(String[] args){
		if(args.length == 2){
			try{
				in = new FileInputStream(args[0]);
				out = new PrintStream(args[1]);
			} catch (Exception ex){
				out = System.out;
				in = System.in;
			}				
		} else {
			out = System.out;
			in = System.in;
		}
		init();
		Scanner scan = new Scanner(in);
		while(scan.hasNext()){
			long next = scan.nextLong();
			out.println(calc(next));
		}
		System.exit(0);
	}
}
