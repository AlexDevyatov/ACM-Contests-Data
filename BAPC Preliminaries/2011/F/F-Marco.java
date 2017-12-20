import java.io.*;
import java.util.*;


public class DividingTheLoot {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws IOException{
		Scanner sc = new Scanner(System.in);
		int casenr = 0;
		int cases = sc.nextInt();
		while(cases-- > 0){
			casenr++;
			solve(sc);
		}
		
	}

	private static void solve(Scanner s) throws IOException{				
		int pirates = s.nextInt();
		int[] items = new int[s.nextInt()];

		
		
		for(int i = 0; i < items.length; i++){
			items[i] = s.nextInt();
		}
		
		Arrays.sort(items);
		
		int myShare = items.length/(pirates+1);
		
		int myValue = 0;
		for(int i = items.length-(myShare); i < items.length; i++){
			myValue += items[i];
		}
		
		System.out.println(myValue);
	}

}
