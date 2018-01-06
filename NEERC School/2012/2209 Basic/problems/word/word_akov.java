import java.io.*;
import java.util.*;
 
public class word_akov {
    public static void main(String[] args) {
        new word_akov().run();
    }
 
    PrintWriter out;
    BufferedReader br;
    StringTokenizer st;
 
    String nextToken() throws IOException {
        while ((st == null) || (!st.hasMoreTokens()))
            st = new StringTokenizer(br.readLine());
        return st.nextToken();
    }
 
    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }
 
    public long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }
 
    public double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }
 
    final long P = 3;  
    long[] h, p;
    int[] cnt;
     
     
    public void solve() throws IOException {
        char[] c = nextToken().toCharArray();
        int n = c.length;
        h = new long[n];
        h[0] = c[0] - 'a' + 1;
        for (int i = 1; i < n; i++) {
            h[i] = h[i - 1] * P + c[i] - 'a' + 1;
        }
        p = new long[n];
        p[0] = 1;
        for (int i = 1; i < n; i++) {
            p[i] = p[i - 1] * P;
        }
        cnt = new int[26];
        for (int i = 0; i < n; i++) {
            cnt[c[i] - 'a']++;
        }
        int ans = -1;
        int cntans = 0;
        for (int i = 0; i < n; i++) {
            long hash = h[n - 1];
            if (i != 0) {
                hash -= p[n - i] * h[i - 1];
                hash *= p[i];
                hash += h[i - 1];
            }
            if (hash == h[n - 1] && i != 0) {
                break;
            }
            int max1 = 0;
            int max2 = 0;
            int first = i;
            int last = (i + n - 1) % n;
            for (int j = 0; j < 26; j++) {
                if (cnt[j] >= 1 && Math.abs(c[i] - 'a' - j) > max1) {
                    max1 = Math.abs(c[i] - 'a' - j);
                }
                if (cnt[j] >= 1 && Math.abs(c[last] - 'a' - j) > max2) {
                    max2 = Math.abs(c[last] - 'a' - j);
                }
            }
            int cur = max1 + max2;
            if (ans == -1 || cur < ans) {
                ans = cur;
                cntans = 1;
            } else if (ans == cur) {
                cntans++;
            }
        }
        out.println(ans + " " + cntans);
    }
 
    public void run() {
        try {
            br = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
 
            br = new BufferedReader(new FileReader("word.in"));
            out = new PrintWriter("word.out");
 
            solve();
 
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
 
}