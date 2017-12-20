public class Doubloon {
	int S, k;
	
	public void run() {
		string[] line = System.Console.ReadLine().Split();
		S = int.Parse(line[0]); k = int.Parse(line[1]);
		System.Console.WriteLine((S%(k+1))%2 + k * ((k+1)%2) * ((S%(k+1))/k));
	}
	
	public static void Main() {
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) new Doubloon().run();
	}

}


