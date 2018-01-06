import java.util.*;
import java.io.*;

public class wordTestGen implements Runnable {

    private int done = 0;
    private final int MAXLEN = (int) 1e6;
    private final String ALL = "abcdefghijklmnopqrstuvwxyz";
    private ArrayList<Character> data;
    private int dataCnt;

    private void print() throws IOException {
        String filename = (done + 1) + "";
        if (done + 1 < 10) {
            filename = "0" + filename;
        }

        File outFile = new File("..\\tests\\" + filename);
        System.out.println(done + 1);
        PrintWriter out = new PrintWriter(outFile);
        for (int i = 0; i < dataCnt; i++) {
            for (int j = 0; j < data.size(); j++) {
                out.print(data.get(j));
            }
        }
        data.clear();
        out.println();
        out.close();
        done++;
    }

    public static void main(String[] args) {
        new wordTestGen().run();
    }

    private void genSample() throws IOException {
        data.add('a');
        data.add('b');
        data.add('c');
        dataCnt = 2;
        print();
    }

    private ArrayList<Character> genSinglePattern(char c, int num) {
        ArrayList<Character> ans = new ArrayList<Character>();
        for (int i = 0; i < num; i++) {
            ans.add(c);
        }
        return ans;
    }

    private void genPattern(ArrayList<Character> pattern) throws IOException {
        data = pattern;
        dataCnt = MAXLEN / pattern.size();
        print();
    }

    private void genPattern(String s) throws IOException {
        ArrayList<Character> t = new ArrayList<Character>();
        for (int i = 0; i < s.length(); i++) {
            t.add(s.charAt(i));
        }
        genPattern(t);
    }

    private boolean checkValid(String s) {
        int[] cnt = new int[26];
        for (int i = 0; i < s.length(); i++) {
            cnt[(int) (s.charAt(i) - 'a')]++;
            if (cnt[(int) (s.charAt(i) - 'a')] > 1) {
                return false;
            }
        }
        return true;
    }

    private void genRand(int period, String toUse) throws IOException {
        if (!checkValid(toUse)) {
            throw new RuntimeException("PANIC!!!!!");
        }
        ArrayList<Character> pt = new ArrayList<Character>();
        for (int i = 0; i < period; i++) {
            pt.add(toUse.charAt((rnd.nextInt() % toUse.length() + toUse.length()) % toUse.length()));
        }
        genPattern(pt);
    }

    private ArrayList<Character> merge(ArrayList<Character> a, ArrayList<Character> b) {
        a.addAll(b);
        return a;
    }

    public void run() {
        try {
            File testDir = new File("..\\tests");
            if (!testDir.exists()) {
                testDir.mkdir();
            }
            data = new ArrayList<Character>();
            rnd = new Random(98547);

            genSample();
            genPattern(merge(genSinglePattern('a', MAXLEN - 1), genSinglePattern('x', 1)));
            genPattern(merge(genSinglePattern('a', 10), genSinglePattern('z', 10)));
            genPattern(merge(merge(genSinglePattern('g', MAXLEN / 9), genSinglePattern('k', MAXLEN / 9)),
                    merge(genSinglePattern('s', MAXLEN / 9), genSinglePattern('t', MAXLEN / 9))));
            genPattern("abacaba");
            genPattern("zxyxz");
            genPattern("a");

            genRand(10, ALL);
            genRand(20, ALL);
            genRand(50, ALL);
            genRand(MAXLEN, ALL);
            genRand(1000, ALL);

            genRand(1000, "abcdefghijkl");
            genRand(1000, "abclmnopq");
            genRand(1000, "bdfhjlnprtvwyz");


        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    Random rnd;
}
