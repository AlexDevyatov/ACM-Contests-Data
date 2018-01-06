import java.util.*;
import java.io.*;

public class word_ats implements Runnable {
    private StringTokenizer st;
    private BufferedReader br;
    private PrintWriter out;

    private final int MAXLEN = (int) 1e6;

    public static void main(String[] args) {
        new word_ats().run();
    }

    private void solve() throws IOException {
        String s = nextToken();
        assert (s.length() <= MAXLEN);
        for (int i = 0; i < s.length(); i++) {
            assert ('a' <= s.charAt(i) && s.charAt(i) <= 'z');
        }

        boolean[] have = new boolean[26];
        for (int i = 0; i < s.length(); i++) {
            have[(int) (s.charAt(i) - 'a')] = true;
        }

        int[] maxDif = new int[26];
        Arrays.fill(maxDif, 0);
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                if (have[j] && have[i]) {
                    maxDif[i] = Math.max(maxDif[i], Math.abs(i - j));
                }
            }
        }
        s = "#" + s;
        int[] pref = new int[s.length()];

        pref[0] = -1;
        pref[1] = 0;

        for (int i = 1; i < s.length(); i++) {
            int pos = i - 1;
            while (pos != -1 && s.charAt(i) != s.charAt(pref[pos] + 1)) {
                pos = pref[pos];
            }
            if (pos != -1) {
                pref[i] = pref[pos] + 1;
            }
        }
        int per = s.length() - 1;
        if ((s.length() - 1) % ((s.length() - 1) - pref[s.length() - 1]) == 0) {
            per = s.length() - 1 - pref[s.length() - 1];
        }
        int cnt = 0;
        int ans = Integer.MAX_VALUE / 2;
        int last = s.length() - 1;
        for (int i = 1; i <= per; i++) {
            int val = maxDif[(int) (s.charAt(i) - 'a')] + maxDif[(int) (s.charAt(last) - 'a')];
            if (ans > val) {
                ans = val;
                cnt = 1;
            } else if (ans == val) {
                cnt++;
            }
            last = (last + 1) % s.length();
            if (last == 0) {
                last++;
            }
        }
        out.println(ans + " " + cnt);
    }

    public void run() {
        try {
            br = new BufferedReader(new FileReader("word.in"));
            out = new PrintWriter("word.out");

            solve();

            br.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
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
}
