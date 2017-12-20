
public class TreasureMap {
	int N;
	
	public void run() {
		N = int.Parse(System.Console.ReadLine());
		if (N%4 == 2) System.Console.WriteLine("IMPOSSIBLE");
		else {
			int k = (int)System.Math.Ceiling(System.Math.Sqrt((double)N));
			while(k > 0) {
				if (N%k == 0 && (N/k + k)%2 == 0) {
					System.Console.WriteLine((N/k - k)/2 + " " + (N/k + k)/2);
					return;
				}
				k--;
			}
		}
	}
	
	public static void Main() {
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) new TreasureMap().run();
	}

}