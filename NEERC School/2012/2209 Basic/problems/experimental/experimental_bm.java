import java.util.*;
import java.io.*;
 
public class experimental_bm {
    FastScanner in;
    PrintWriter out;
 
    int n, m;
    boolean[] was;
    ArrayList<Edge>[] g;
 
    class Edge {
        int fr, to, flow;
        Edge back;
 
        Edge(int fr, int to, int flow) {
            this.fr = fr;
            this.to = to;
            this.flow = flow;
        }
    }
 
    void addEdge(int fr, int to, int flow) {
        Edge e1 = new Edge(fr, to, flow);
        Edge e2 = new Edge(to, fr, 0);
        e1.back = e2;
        e2.back = e1;
        g[fr].add(e1);
        g[to].add(e2);
    }
 
    boolean dfs(int v) {
        was[v] = true;
        if (v == n + m + 1)
            return true;
        for (Edge e : g[v]) {
            if (e.flow > 0 && !was[e.to]) {
                if (dfs(e.to)) {
                    e.flow--;
                    e.back.flow++;
                    return true;
                }
            }
        }
        return false;
    }
 
    public void solve() throws IOException {
        n = in.nextInt();
        m = in.nextInt();
        int[][] a = new int[n][2];
        int[] max = new int[m];
        for (int i = 0; i < n; i++) {
            a[i][0] = in.nextInt();
            a[i][1] = in.nextInt();
        }
        for (int i = 0; i < m; i++)
            max[i] = in.nextInt();
        g = new ArrayList[n + m + 2];
        for (int i = 0; i < n + m + 2; i++)
            g[i] = new ArrayList<Edge>();
        was = new boolean[n + m + 2];
        for (int i = 1; i <= n; i++)
            addEdge(0, i, 1);
        for (int i = 1; i <= n; i++) {
            addEdge(i, a[i - 1][0] + n, 1);
            addEdge(i, a[i - 1][1] + n, 1);
        }
        for (int i = n + 1; i <= n + m; i++)
            addEdge(i, n + m + 1, max[i - n - 1]);
        while (dfs(0)) {
            Arrays.fill(was, false);
        }
        int[] res = new int[n];
        for (int i = 1; i <= n; i++) {
            for (Edge e : g[i]) {
                if (e.to != 0 && e.flow == 0)
                    res[i - 1] = e.to - n;
            }
        }
        boolean ok = true;
        for (int i = 0; i < n; i++)
            if (res[i] == 0)
                ok = false;
        if (!ok) {
            out.println(-1);
        } else {
            for (int i = 0; i < n; i++)
                out.print(res[i] + " ");
        }
             
    }
 
    public void run() {
        try {
            in = new FastScanner(new File("experimental.in"));
            out = new PrintWriter(new File("experimental.out"));
 
            solve();
 
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
 
    class FastScanner {
        BufferedReader br;
        StringTokenizer st;
 
        FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }
 
        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
 
        int nextInt() {
            return Integer.parseInt(next());
        }
 
        long nextLong() {
            return Long.parseLong(next());
        }
 
        double nextDouble() {
            return Double.parseDouble(next());
        }
 
    }
 
    public static void main(String[] arg) {
        new experimental_bm().run();
    }
}