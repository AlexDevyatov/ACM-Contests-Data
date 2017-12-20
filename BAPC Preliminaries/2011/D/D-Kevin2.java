import java.util.*;

public class Polly {
	static Scanner sc = new Scanner(System.in);
	String S1, S2;
	String[] words, mimic;
	int[][] Q = new int[1005][1005];
	int[][] D = new int[8][8];
	boolean[] matched = new boolean[8];
	
	public int editDist(String S1, String S2) {
		int N1 = S1.length(), N2 = S2.length();
		for (int i = 0; i <= N1; i++) Q[i][0] = i;
		for (int i = 0; i <= N2; i++) Q[0][i] = i;
		for (int i = 1; i <= N1; i++) {
			for (int j = 1; j <= N2; j++) {
				Q[i][j] = Math.min(1 + Math.min(Q[i-1][j], Q[i][j-1]), Q[i-1][j-1] + (S1.charAt(i-1) == S2.charAt(j-1) ? 0 : 1));
			}
		}
		return Q[N1][N2];
	}
	
	public int minErrors(int k) {
		if (k == mimic.length) return 0;
		int minE = Integer.MAX_VALUE;
		for (int i = 0; i < words.length; i++) {
			if (matched[i]) continue;
			matched[i] = true;
			minE = Math.min(minE, D[i][k] + minErrors(k+1));
			matched[i] = false;
		}
		return minE;
	}
	
	public void run() {
		S1 = sc.nextLine(); S2 = sc.nextLine();
		for (int i = 0; i < S1.length() - 1; i++) if (S1.charAt(i) == ' ' && S1.charAt(i+1) == ' ') System.out.println("Double space!");
		for (int i = 0; i < S2.length() - 1; i++) if (S2.charAt(i) == ' ' && S2.charAt(i+1) == ' ') System.out.println("Double space!");
		words = S1.split(" "); mimic = S2.split(" ");
		if (S1.length() > 1000 || S1.length() == 0 || S2.length() > 1000 || S2.length() == 0) System.out.println("Incorrect string length");
		if (words.length > 8 || mimic.length > words.length) System.out.println("Incorrect number of words");
		
		for (int i = 0; i < words.length; i++) for (int j = 0; j < mimic.length; j++) D[i][j] = editDist(words[i], mimic[j]);
		for (int i = 0; i < words.length; i++) matched[i] = false;
		
		System.out.println(minErrors(0));
	}
	
	public static void main(String[] args) {
		int runs = sc.nextInt(); sc.nextLine();
		for (int i = 0; i < runs; i++) new Polly().run();
	}

}


