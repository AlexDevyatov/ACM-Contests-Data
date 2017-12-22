import java.util.*;
import java.io.*;
import java.math.*;

/**
 * A Java version of the Set Solution by Lukas
 */
public class Markus {
    public static void main(String[] args) {
        // Read input
        Kattio io = new Kattio(System.in);
        int n = io.getInt();
        int k = io.getInt();

        Interval[] intervals = new Interval[n];
        for(int i = 0; i < n; ++i)
            intervals[i] = new Interval(io.getInt(), io.getInt());

        // Sort intervals by endpoint
        Arrays.sort(intervals, new Comparator<Interval>() {
            public int compare(Interval a, Interval b) {
                return a.end - b.end; 
            }
        });

        // Maintain a multi set of the intervals limiting further action
        TreeSet<UniqueInteger> limits = new TreeSet<UniqueInteger>(
                new Comparator<UniqueInteger>() {
                    public int compare(UniqueInteger a, UniqueInteger b) {
                        return a.value == b.value ? a.id - b.id : a.value - b.value;
                    }
                });

        // Insert initial bounds
        for(int i = 0; i < k; ++i)
            limits.add(new UniqueInteger(0));

        // Compute solution
        int shows = 0;
        for(int i = 0; i < n; ++i) {
            UniqueInteger floor = limits.floor(
                    new UniqueInteger(intervals[i].start));
            if(floor != null) {
                limits.remove(floor);
                limits.add(new UniqueInteger(intervals[i].end));
                ++shows;
            }
        }

        System.out.println(shows);
    }
}

/**
 * To turn the TreeSet into a multi set
 */
class UniqueInteger {

    private static int idCounter = 0;
    int value;
    int id;

    public UniqueInteger(int value) {

        this.value = value;
        id = idCounter++;
    } 
}

class Interval {

    int start, end;

    public Interval(int start, int end) {
        this.start = start;
        this.end = end;
    }
}

/** Simple yet moderately fast I/O routines.
 *
 * Example usage:
 *
 * Kattio io = new Kattio(System.in, System.out);
 *
 * while (io.hasMoreTokens()) {
 *    int n = io.getInt();
 *    double d = io.getDouble();
 *    double ans = d*n;
 *
 *    io.println("Answer: " + ans);
 * }
 *
 * io.close();
 *
 *
 * Some notes:
 *
 * - When done, you should always do io.close() or io.flush() on the
 *   Kattio-instance, otherwise, you may lose output.
 *
 * - The getInt(), getDouble(), and getLong() methods will throw an
 *   exception if there is no more data in the input, so it is generally
 *   a good idea to use hasMoreTokens() to check for end-of-file.
 *
 * @author: Kattis
 */

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
