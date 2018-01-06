import java.util.*;
import java.io.*;

/**
 * Created with IntelliJ IDEA.
 * User: Alexey
 * Date: 21.09.12
 * Time: 10:27
 * To change this template use File | Settings | File Templates.
 */
public class horses_ats_wa implements Runnable {
    StringTokenizer st;
    PrintWriter out;
    BufferedReader br;

    public static void main(String[] args) {
        new horses_ats_wa().run();
    }

    private String nextToken() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }

    private int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    private long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    private double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }

    private void solve() throws IOException {
        int n = nextInt();
        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = nextInt();
        }
        int[] t = new int[n + 1];
        int[] prev = new int[n + 1];
        Arrays.fill(prev, -1);
        Arrays.fill(t, Integer.MAX_VALUE);
        t[0] = 1;
        for (int i = 0; i < n; i++) {
            if (t[i] <= a[i]) {
                for (int j = i + 1; j <= n; j++) {
                    if (t[j] > a[i] + (j - i) * (j - i + 1) / 2) {
                        t[j] = a[i] + (j - i) * (j - i + 1) / 2;
                        prev[j] = i;
                    }
                }
            }
        }
        System.out.println(Arrays.toString(t));
        int cnt = -1;
        int pos = n;
        while (pos != 0) {
            cnt++;
            pos = prev[pos];
        }
        out.println(t[n] + " " + cnt);
    }

    public void run() {
        try {
            br = new BufferedReader(new FileReader("horses.in"));
            out = new PrintWriter("horses.out");

            solve();

            br.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}
