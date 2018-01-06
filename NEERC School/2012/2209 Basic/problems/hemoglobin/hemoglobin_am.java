import java.io.*;
import java.util.*;

public class hemoglobin_am {
    public class StackSum {
        StackSum() {
            st = new ArrayList<Long>();
            sum = new ArrayList<Long>();
            st.add(new Long(0));
            sum.add(new Long(0));
        }

        void push(Long x) {
            st.add(x);
            sum.add(x + sum.get(sum.size() - 1));
        }

        Long pop() {
            sum.remove(sum.size() - 1);
            return st.remove(st.size() - 1);
        }

        Long sum(int k) {
            Long result = new Long(0);
            result = sum.get(sum.size() - 1) - sum.get(sum.size() - k - 1);
            return result;
        }

        int size() {
            assert(st.size() == sum.size());
            return st.size();
        }

        ArrayList<Long> st;
        ArrayList<Long> sum;
    }

    public void solve() throws IOException {
        StackSum ss = new StackSum();
        int n = in.nextInt();
        assert(0 < n && n < 100001);
        for (int i = 0; i < n; i++) {
            String s = in.nextToken();
            char oper = s.charAt(0);
            if (oper == '+') {
                Long x = Long.parseLong(s.substring(1, s.length()));
                assert(0 < x && x < 1000000001);
                ss.push(x);
            }
            else if (oper == '-') {
                out.println(ss.pop());
            }
            else if (oper == '?') {
                int k = Integer.parseInt(s.substring(1, s.length()));
                assert(0 < k && k < ss.size());
                out.println(ss.sum(k));
            } else {
                throw new AssertionError();
            }
        }
    }

    static MyScanner in;
    static PrintWriter out;

    public static void main(String[] args) throws IOException {
        in = new MyScanner(new FileReader(new File("hemoglobin.in")));
        out = new PrintWriter(new File("hemoglobin.out"));
        new hemoglobin_am().solve();
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