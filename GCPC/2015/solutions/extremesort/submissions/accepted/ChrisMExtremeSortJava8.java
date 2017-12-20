import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * @author Christian Müller, TU Munich
 */
public class ChrisMExtremeSortJava8 {

	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			int n = sc.nextInt();
			
			// Just to test Java 8 stuff
			List<Integer> list = Stream.generate(() -> sc.nextInt()).limit(n).collect(Collectors.toList());
			
			int x = 0;
			boolean sorted = true;
			for (int y : list) {
				if (x > y) {
					sorted = false;
				}
				x = y;
			}
			System.out.println(sorted? "yes" : "no");
		}
	}
}
