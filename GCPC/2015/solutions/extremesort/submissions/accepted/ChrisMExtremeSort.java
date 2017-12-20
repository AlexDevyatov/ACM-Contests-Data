import java.util.Scanner;

/**
 * @author Christian Müller, TU Munich
 */
public class ChrisMExtremeSort {

	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			int n = sc.nextInt();
			
			boolean sorted = true;
			int x = sc.nextInt();
			for (int i = 0; i < n - 1; i++) {
				int y = sc.nextInt();
				if (x > y) {
					sorted = false;
				}
				x = y;
			}
			System.out.println(sorted? "yes" : "no");
		}
	}
}
