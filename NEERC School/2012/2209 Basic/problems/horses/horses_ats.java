import java.util.*;
import java.io.*;

/**
 * Created with IntelliJ IDEA.
 * User: Alexey
 * Date: 21.09.12
 * Time: 10:27
 * To change this template use File | Settings | File Templates.
 */
public class horses_ats implements Runnable {
    StringTokenizer st;
    PrintWriter out;
    BufferedReader br;

    public static void main(String[] args) {
        new horses_ats().run();
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
        int[] cnt = new int[n + 1];
        Arrays.fill(cnt, Integer.MAX_VALUE);
        Arrays.fill(t, Integer.MAX_VALUE);
        t[0] = 1;
        cnt[0] = -1;
        for (int i = 0; i < n; i++) {
            if (t[i] <= a[i]) {
                for (int j = i + 1; j < n; j++) {
                    int newTime = a[i] + (j - i) * (j - i + 1) / 2;
                    if (a[j] >= newTime && cnt[j] > cnt[i] + 1) {
                        t[j] = newTime;
                        cnt[j] = cnt[i] + 1;
                    }
                }
                int newAns = a[i] + (n - i) * (n - i + 1) / 2;
                if (newAns < t[n] || (newAns == t[n] && cnt[n] > cnt[i] + 1)) {
                    t[n] = newAns;
                    cnt[n] = cnt[i] + 1;
                }
            }
        }
        out.println(t[n] + " " + cnt[n]);
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
