import java.io.IOException;

public class Gamerank_jmv {

	public static void main(String[] args) throws IOException {
		java.util.Scanner in = new java.util.Scanner(System.in);
		String l = in.next();
		int s = 0, w = 0;
		char c;
		boolean b = false;
		for (int i = 0; i < l.length(); i++) {
			c = l.charAt(i);
			if (c == 'W') {
				if (++w >= 3 && s <= 70) s++;
				if (++s > 95) {
					System.out.println("Legend");
					in.close();
					return;
				}
				b = true;
			}
			else {
				w = 0;
				if (s > 10) {
					s--;
					b = false;
				}
			}
		}
		int r = 0, q = 2;
		while (s >= q) {
			s -= q;
			r++;
			if (r % 5 == 0 && r <= 20) q++; 
		}
		if (s == 0 && b) r--;
		System.out.println(25 - r);
		
		in.close();
	}
}
