import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;
import java.util.StringTokenizer;

import ru.ifmo.testlib.*;
import ru.ifmo.testlib.Outcome.Type;

public class Check implements ru.ifmo.testlib.Checker {

    ArrayList<Integer>[] g;
    long[] w;
    
    boolean[] used;
    long[] sumInSubTree;
   
    long dfs(int v) {
        used[v] = true;
        sumInSubTree[v] = w[v];
        for (int to : g[v]) {
            if (!used[to]) {
                sumInSubTree[v] += dfs(to);
            }
        }
        return sumInSubTree[v];
    }

    void initSumsFromVertex(int v) {
        used = new boolean[n];
        sumInSubTree = new long[n];
        dfs(v);
    }

    long calculateAnswer(int v) {
        long res = Long.MIN_VALUE;
        for (int to : g[v]) {
            res = Math.max(res, sumInSubTree[to]);
        }
        return res;
    }
    
    int n;
	@Override
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
        n = inf.nextInt();
        w = new long[n];
        g = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            g[i] = new ArrayList<Integer>();
        }
        for (int i = 0; i < n; i++) {
            w[i] = inf.nextInt();
        }
        for (int i = 0; i < n - 1; i++) {
            int a = inf.nextInt() - 1;
            int b = inf.nextInt() - 1;
            g[a].add(b);
            g[b].add(a);
        }

        int juryVertex = ans.nextInt() - 1;
        if (juryVertex < 0 || juryVertex >= n) {
            throw new Outcome(Type.FAIL, "Incorrect vertex #" + (juryVertex + 1));
        }
        int contestantVertex = ouf.nextInt() - 1;
        if (contestantVertex < 0 || contestantVertex >= n) {
            throw new Outcome(Type.WA, "Incorrect vertex #" + (contestantVertex + 1));
        }

        initSumsFromVertex(juryVertex);
        long juryAnswer = calculateAnswer(juryVertex);

        initSumsFromVertex(contestantVertex);
        long contestantAnswer = calculateAnswer(contestantVertex);

        if (juryAnswer == contestantAnswer) {
            throw new Outcome(Type.OK, "OK min max sum = " + contestantAnswer + " , from vertex #" + (contestantVertex + 1));
        } else if (juryAnswer < contestantAnswer) {
            throw new Outcome(Type.WA, "Jury has better solution: found: " + contestantAnswer + ", expected: " + juryAnswer);
        } else {
            throw new Outcome(Type.FAIL, "Ooops! Something gone wrong!");
        }
	}
}
