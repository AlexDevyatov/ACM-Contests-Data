import java.io.*;
import java.util.*;

public class fence_am {
    public class point {
        double x;
        double y;

        public point(double a, double b){
            x = a;
            y = b;
        }
    }

    double area(point a, point b, point c){
        point p1 = new point(a.x - c.x, a.y - c.y);
        point p2 = new point(b.x - c.x, b.y - c.y);
        return Math.abs(p1.x * p2.y - p2.x * p1.y);
    }

    public void solve() throws IOException {
        int n = in.nextInt();
        point[] p = new point[n + 1];
        for (int i = 1; i <=n; i++){
            p[i] = new point(in.nextInt(), in.nextInt());
        }
        p[0] = p[n];
        point c = new point(in.nextInt(), in.nextInt());
        double mn = Double.MAX_VALUE;
        for (int i = 0 ; i<n ; i++){
            if (area(c, p[i], p[i+1])< mn){
                mn = area(c, p[i], p[i+1]);
            }
        }
        out.println(n+1);
        for (int i = 0 ; i<n ; i++){
            out.println((int) p[i].x+ " "+ (int) p[i].y);
            if (area(c, p[i], p[i+1]) == mn){
                mn = -1;
                out.println((int) c.x+ " "+ (int) c.y);
            }
        }

    }

    static MyScanner in;
    static PrintWriter out;

    public static void main(String[] args) throws IOException {
        in = new MyScanner(new FileReader(new File("fence.in")));
        out = new PrintWriter(new File("fence.out"));
        new fence_am().solve();
        out.close();
    }

    static class MyScanner {
        private StringTokenizer st;
        private BufferedReader br;

        public MyScanner(Reader r) {
            br = new BufferedReader(r);
        }

        public String nextToken() throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            return st.nextToken();
        }

        public int nextInt() throws IOException {
            return Integer.parseInt(nextToken());
        }
    }

}
