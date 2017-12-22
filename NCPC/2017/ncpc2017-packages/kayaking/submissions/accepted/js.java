import java.util.*;
import java.io.*;

public class js {
    public static void main(String... args) {
        Kattio io = new Kattio(System.in);
        int b = io.getInt();
        int n = io.getInt();
        int e = io.getInt();
        int sb = io.getInt();
        int sn = io.getInt();
        int se = io.getInt();
        int N = (b + n + e) / 2;
        int[] canoes = new int[N];
        for (int i = 0; i < N; ++i) canoes[i] = io.getInt();
        Arrays.sort(canoes);
        int lo = 1;
        int hi = 300000000;
        while (hi - lo > 1) {
            int mid = (lo + hi) / 2;
            if (can(mid, b, n, e, sb, sn, se, canoes)) lo = mid;
            else hi = mid;
        }
        System.out.println(lo);
    }

    static boolean can(int minspeed, int b, int n, int e, int sb, int sn, int se, int[] canoes) {
        ArrayList<Integer> left = new ArrayList<>();
        // Pass 1: assign bb/bn when possible, assign ee/ne where required
        for (int c : canoes) {
            int required = (minspeed + c - 1) / c;
            if (required > se + se) {
                return false;
            }
            if (sb + sb >= required) {
                if (b >= 2) {
                    b -= 2;
                    continue;
                }
            }
            if (sb + sn >= required) {
                if (b >= 1 && n >= 1) {
                    b -= 1;
                    n -= 1;
                    continue;
                }
            }
            if (required > sn + se) {
                if (e >= 2) {
                    e -= 2;
                    continue;
                }
                return false;
            }
            if (required > Math.max(sn + sn, sb + se)) {
                if (e >= 1 && n >= 1) {
                    e -= 1;
                    n -= 1;
                    continue;
                } else if (e >= 2) {
                    e -= 2;
                    continue;
                }
                return false;
            }
            left.add(c);
        }
        ArrayList<Integer> nleft = new ArrayList<>();
        for (int c : left) {
            int required = (minspeed + c - 1) / c;
            if (sb + sn >= required) {
                assert b <= 1 && (b == 0 || n == 0);

                if (b == 0) {
                    if (n >= 2) {
                        n -= 2;
                        continue;
                    }
                    if (n >= 1 && e >= 1) {
                        n -= 1;
                        e -= 1;
                        continue;
                    }
                    if (e >= 2) {
                        e -= 2;
                        continue;
                    }
                    return false;
                }

                if (n == 0) {
                    if (b >= 1 && e >= 1) {
                        b -= 1;
                        e -= 1;
                        continue;
                    }
                    if (e >= 2) {
                        e -= 2;
                        continue;
                    }
                    return false;
                }

                assert false;
            }
            nleft.add(c);
        }
        for (int c : nleft) {
            int required = (minspeed + c - 1) / c;

            if (se + sb < sn + sn) {
                if (se + sb >= required && e >= 1 && b >= 1) {
                    b -= 1;
                    e -= 1;
                    continue;
                }
                if (sn + sn >= required && n >= 2) {
                    n -= 2;
                    continue;
                }
            } else {
                if (se + sb >= required && e >= 1 && b >= 1) {
                    b -= 1;
                    e -= 1;
                    continue;
                }
                if (sn + sn >= required && n >= 2) {
                    n -= 2;
                    continue;
                }
            }

            if (sn + se >= required && e >= 1 && n >= 1) {
                n -= 1;
                e -= 1;
                continue;
            }
            if (se + se >= required && e >= 2) {
                e -= 2;
                continue;
            }
            return false;
        }
        return true;
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
