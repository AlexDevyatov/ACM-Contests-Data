import java.io.*;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class hospital_ak {

    static class Edge {
        int from, to;
        Edge reverse;

        Edge(int from, int to) {
            this.from = from;
            this.to = to;
        }

        Long w;
    }

    ArrayList<Edge>[] g;
    long[] w;
    long sumInAllVertices;

    void addEdge(int a, int b) {
        Edge e1 = new Edge(a, b);
        Edge e2 = new Edge(b, a);
        e1.reverse = e2;
        e2.reverse = e1;
        g[a].add(e1);
        g[b].add(e2);
    }

    boolean[] used;

    long dfs(int v) {
        used[v] = true;
        long res = w[v];
        for (Edge e : g[v]) {
            if (used[e.to]) {
                continue;
            }
            long now = dfs(e.to);
            e.w = now;
            e.reverse.w = sumInAllVertices - e.w;
            res += now;
        }
        return res;
    }

    void solve() throws IOException {
        int n = in.nextInt();
        assert 1 <= n && n <= 100000;
        g = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            g[i] = new ArrayList<Edge>();
        }
        w = new long[n];
        sumInAllVertices = 0;
        for (int i = 0; i < n; i++) {
            w[i] = in.nextInt();
            assert 0 <= w[i] && w[i] <= 1000000000;
            sumInAllVertices += w[i];
        }
        for (int i = 0; i < n - 1; i++) {
            int a = in.nextInt() - 1;
            int b = in.nextInt() - 1;
            assert a != b;
            assert 0 <= a && a < n;
            assert 0 <= b && b < n;
            addEdge(a, b);
        }
        used = new boolean[n];
        dfs(0);
        for (boolean b : used) {
            assert b; // ^_^
        }
        long min = Long.MAX_VALUE;
        int argMin = -1;
        for (int i = 0; i < n; i++) {
            long currentMax = -1;            
            for (Edge e : g[i]) {
                currentMax = Math.max(currentMax, e.w);
            }
            if (currentMax < min) {
                min = currentMax;
                argMin = i;
            }
        }
        out.println(argMin + 1);
    }

    static MyScanner in;
    static PrintWriter out;

    public static void main(String[] args) throws IOException {
        in = new MyScanner(new FileReader("hospital.in"));
        out = new PrintWriter("hospital.out");
        new hospital_ak().solve();
        out.close();
    }

    static class MyScanner {
        BufferedReader br;
        StringTokenizer st;

        MyScanner(Reader r) {
            br = new BufferedReader(r);
        }

        String nextToken() throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            return st.nextToken();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(nextToken());
        }
        
    }
}
