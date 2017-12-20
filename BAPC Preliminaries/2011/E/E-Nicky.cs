class Dice {
	int up = 1, left = 3, right = 4, front = 2, back = 5;
	long x, y; // just to be sure
	
	public void rotateX(long k) {
		x += k;
		k = k%4; 
		if (k < 0) k += 4;
		for (int i = 0; i < k; i++) {
			right = up; up = left; left = 7 - right;
		}
	}
	
	public void rotateY(long k) {
		y += k;
		k = k%4; 
		if (k < 0) k += 4;
		for (int i = 0; i < k; i++) {
			back = up; up = front; front = 7 - back;
		}
	}	
	
	public void run() {
		string S = System.Console.ReadLine();
		int dir = 1, num = 0;
		x = 0; y = 0;
		for (int i = 0; i < S.Length; i++) {
			char c = S[i];
			if (c >= '0' && c <= '9') num = 10 * num + (c - '0');
			else {
				switch(c) {
				case '+': dir *= -1; break;
				case '-': dir *= -1; break;
				case 'X': num = dir * (num > 0 ? num : 1); rotateX(num); num = 0; break;
				case 'Y': num = dir * (num > 0 ? num : 1); rotateY(num); num = 0; break;
				}
			}
		}
		System.Console.WriteLine("position (" + x + "," + y + "), " + up + " dots");
	}
	
	static void Main() {
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) new Dice().run();
	}

}

