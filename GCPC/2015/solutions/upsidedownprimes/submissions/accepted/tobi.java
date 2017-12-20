import java.util.*;
import java.math.*;
import java.io.*;

public class tobi {
	public static boolean prime(String s) {
		BigInteger n = new BigInteger(s);
		return n.isProbablePrime(50);
	}

	public static String translate(String s) {
		String ret = "";
		for (char c : s.toCharArray()) {
			if (c == '6') c = '9';
			else if (c == '9') c = '6';
			ret = c + ret;
		}
		return ret;
	}

	public static boolean check(String num) {
		for (char c : num.toCharArray()) {
			if (c == '3' || c == '4' || c == '7') return false;
		}
		return prime(num) && prime(translate(num));
	}
	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		String num = sc.next();
		System.out.println(check(num) ? "yes" : "no");
	}
}
