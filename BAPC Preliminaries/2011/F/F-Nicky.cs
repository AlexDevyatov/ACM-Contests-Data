class DividingTheLoot {

	/**
	 * @param args
	 */
	static void Main() {
		int casenr = 0;
		int cases = int.Parse(System.Console.ReadLine());
		while(cases-- > 0){
			casenr++;
			solve();
		}
		
	}

	static void solve() {				
		string[] line = System.Console.ReadLine().Split();
		int pirates = int.Parse(line[0]);
		int[] items = new int[int.Parse(line[1])];

		
		line = System.Console.ReadLine().Split();
		for(int i = 0; i < items.Length; i++){
			items[i] = int.Parse(line[i]);
		}
		
		System.Array.Sort(items);
		
		int myShare = items.Length/(pirates+1);
		
		int myValue = 0;
		for(int i = items.Length-(myShare); i < items.Length; i++){
			myValue += items[i];
		}
		
		System.Console.WriteLine(myValue);
	}

}
