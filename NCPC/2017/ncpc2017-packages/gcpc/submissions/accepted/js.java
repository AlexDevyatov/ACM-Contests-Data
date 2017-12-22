import java.util.*;
import java.io.*;

public class js {

    public static void main(String... args) {
        Kattio io = new Kattio(System.in);
        int N = io.getInt();
        int M = io.getInt();
        Pair[] cur = new Pair[N];
        for (int i = 0; i < N; ++i) cur[i] = new Pair(0, 0);
        TreeSet<TPair> sc = new TreeSet<>();
        for (int i = 0; i < N; ++i) {
            sc.add(new TPair(new Pair(0, 0), i));
        }
        int rank = 0;
        for (int i = 0; i < M; ++i) {
            int t = io.getInt() - 1;
            int p = io.getInt();
            Pair now = cur[t];
            Pair nx = new Pair(now.first, now.second);
            nx.first--;
            nx.second += p;

            if (t != 0) {
                if (now.ge(cur[0]) && nx.lt(cur[0])) ++rank;
            } else {
                NavigableSet<TPair> better = sc.subSet(new TPair(nx, t), false, new TPair(now, t), false);
                rank -= better.size();
            }

            sc.remove(new TPair(now, t));
            sc.add(new TPair(nx, t));
            cur[t] = nx;
            System.out.println(rank + 1);
        }
    }

    static class TPair implements Comparable<TPair> {
        Pair first;
        int second;
        TPair(Pair first, int second) {
            this.first = first;
            this.second = second;
        }

        @Override
        public int compareTo(TPair ot) {
            int a = first.compareTo(ot.first);
            if (a != 0) return a;
            return second - ot.second;
        }
    }

    static class Pair implements Comparable<Pair> {
        int first;
        int second;
        Pair(int first, int second) {
            this.first = first;
            this.second = second;
        }

        boolean ge(Pair ot) {
            return compareTo(ot) >= 0;
        }

        boolean lt(Pair ot) {
            return compareTo(ot) < 0;
        }

        @Override
        public int compareTo(Pair ot) {
            if (first != ot.first) return first - ot.first;
            return second - ot.second;
        }
    }
}

class Kattio extends PrintWriter {
    public Kattio(InputStream i) {
        super(new BufferedOutputStream(System.out));
        r = new BufferedReader(new InputStreamReader(i));
    }
    public Kattio(InputStream i, OutputStream o) {
        super(new BufferedOutputStream(o));
        r = new BufferedReader(new InputStreamReader(i));
    }

    public boolean hasMoreTokens() {
        return peekToken() != null;
    }

    public int getInt() {
        return Integer.parseInt(nextToken());
    }

    public double getDouble() {
        return Double.parseDouble(nextToken());
    }

    public long getLong() {
        return Long.parseLong(nextToken());
    }

    public String getWord() {
        return nextToken();
    }



    private BufferedReader r;
    private String line;
    private StringTokenizer st;
    private String token;

    private String peekToken() {
        if (token == null)
            try {
                while (st == null || !st.hasMoreTokens()) {
                    line = r.readLine();
                    if (line == null) return null;
                    st = new StringTokenizer(line);
                }
                token = st.nextToken();
            } catch (IOException e) { }
        return token;
    }

    private String nextToken() {
        String ans = peekToken();
        token = null;
        return ans;
    }
}
