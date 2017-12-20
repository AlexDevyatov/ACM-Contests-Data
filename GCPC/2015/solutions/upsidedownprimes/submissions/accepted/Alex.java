import java.util.*;
import java.math.*;

public class Alex{
	public static void main(String[] args){
		Scanner scan = new Scanner(System.in);
		String input = scan.next();
		BigInteger a = new BigInteger(input);
		boolean success = true;
		if(!a.isProbablePrime(20)) success = false;
		String[] forbidden = {"3", "4", "7"};
		for(String s: forbidden)
			if(input.contains(s)) success = false;
		char maps_to[] = {'0', '1', '2', '3', '4', '5', '9', '7', '8', '6'};
		char input_c[] = input.toCharArray();
		char reverse[] = new char[input_c.length];
		for(int i = 0; i < input_c.length; i++)
			reverse[i] = maps_to[ input_c[ input_c.length - i - 1 ] - '0' ];
		String reverse_string = new String(reverse);
		a = new BigInteger(reverse_string);
		if(!a.isProbablePrime(20)) success = false;
		if(success) System.out.println("yes");
		else System.out.println("no");
	}
}
