import java.util.*;
import java.io.*;
 
public class football_bm {
    FastScanner in;
    PrintWriter out;
 
    int x, y;
     
    boolean win(int a, int b) {
        if (x == b && y == a) return false;
        if (x + a > y + b) return true;
        if (x + a < y + b) return false;
        if (a > y) return true;
        return false;
    }
 
    public void solve() throws IOException {
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            String s = in.next();
            x = Integer.parseInt(s.split(":")[0]);
            y = Integer.parseInt(s.split(":")[1]);
            int sum = 0;
            for (int a = 0; a < 10; a++)
                for (int b = 0; b < 10; b++)
                    if (win(a, b)) sum++;
            out.println(sum + " " + (99 - sum));
        }
             
    }
 
    public void run() {
        try {
            in = new FastScanner(new File("football.in"));
            out = new PrintWriter(new File("football.out"));
 
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
        new football_bm().run();
    }
}