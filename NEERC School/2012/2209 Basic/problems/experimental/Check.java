import java.util.*;

import ru.ifmo.testlib.*;
import ru.ifmo.testlib.Outcome.Type;

public class Check implements Checker {
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		int n = inf.nextInt();
		int m = inf.nextInt();
		int[][] a = new int[n][2];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 2; j++) {
				a[i][j] = inf.nextInt();
			}
		}
		int[] b = new int[m];
		for (int i = 0; i < m; i++) {
			b[i] = inf.nextInt();
		}
		for (int i = 0; i < n; i++) {
			int k = ouf.nextInt();
			if (i == 0 && k == -1) {
				int t = ans.nextInt();
				if (t == -1) {
					return new Outcome(Type.OK, "");
				}
			}
			if (a[i][0] != k && a[i][1] != k) {
				return new Outcome(Type.WA, "Bad pillow");
			}
			b[k - 1]--;
		}
		for (int i = 0; i < m; i++) {
			if (b[i] != 0) {
				return new Outcome(Type.WA, "Bad count");
			}
		}
		int t = ans.nextInt();
		if (t == -1) {
			return new Outcome(Type.FAIL, "Panic");
		}
		return new Outcome(Type.OK, "");
	}
}