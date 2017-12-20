import java.util.*;

public class Doubloon {
	static Scanner sc = new Scanner(System.in);
	int S, k;
	
	public void run() {
		S = sc.nextInt(); k = sc.nextInt();
		System.out.println((S%(k+1))%2 + k * ((k+1)%2) * ((S%(k+1))/k));
	}
	
	public static void main(String[] args) {
		int runs = sc.nextInt();
		for (int i = 0; i < runs; i++) new Doubloon().run();
	}

}


