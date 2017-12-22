import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class pvr_pgd {
	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		int n = s.nextInt();
		int k = s.nextInt();

		if (k >= n) {
			System.out.println(k);
			s.close();
			return;
		}

		ArrayList<Interval> lst = new ArrayList<>();

		for (int i = 0; i < n; i++) {
			int l = s.nextInt();
			int r = s.nextInt();

			lst.add(new Interval(l, r));
		}
		s.close();

		int solution = 0; // the shit we print

		Collections.sort(lst);

		Queue<Interval> q = new LinkedList<>();

		for (int i = 0; i < k; i++) {
			q.add(lst.get(i));
			//System.out.println("Add " + lst.get(i));
			solution++;
		}

		
		for (int i = k; i < n; i++) {
			Interval first = q.peek();
			
			Interval current = lst.get(i);
			if (first.right <= current.left) {
				solution++;
				q.remove();
				q.add(current);
				//System.out.println("Add " + current);
			}			
		}

		System.out.println(solution);
	}

	static class Interval implements Comparable<Interval> {
		int left, right;

		public Interval(int l, int r) {
			this.left = l;
			this.right = r;
		}

		@Override
		public int compareTo(Interval o) {
			return Integer.compare(right, o.right);
		}

		@Override
		public String toString() {
			return "(" + left + "," + right + ").";
		}
	}
}

