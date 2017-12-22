import java.util.*;
import java.io.*;
import java.math.*;

/**
 * Nasty hack to get the TreeSet to work as I want. I need the UniqueInteger
 * to make it a multiset. However, it depends on the fact that objects I'm
 * looking for is created later than the ones inserted originally (hence their
 * id's are larger. I'll try to come up with a nicer fix.
 */
public class Markus {

    static int MAX_VALUE = 10000;

    public static void main(String[] args) {
        Kattio io = new Kattio(System.in);
        int G = io.getInt();

        ArrayList<TreeSet<UniqueInteger>> goblins =
            new ArrayList<TreeSet<UniqueInteger>>();

        for(int i = 0; i <= MAX_VALUE; ++i)
            goblins.add(new TreeSet<UniqueInteger>(new Comparator<UniqueInteger>(){
                public int compare(UniqueInteger a, UniqueInteger b) {
                    return a.value == b.value ? b.id - a.id : a.value - b.value;
                }
            }));

        for(int i = 0; i < G; ++i) {
            int x = io.getInt();
            int y = io.getInt();
            goblins.get(x).add(new UniqueInteger(y));
        }

        int M = io.getInt();
        for(int i = 0; i < M; ++i) {
            int sx = io.getInt();
            int sy = io.getInt();
            int sr = io.getInt();

            for(int x = Math.max(0, sx-sr); x <= Math.min(MAX_VALUE, sx+sr); ++x) {
                double delta_y = Math.sqrt(sr*sr-(sx-x)*(sx-x));
                int min_y = (int)Math.ceil(sy-delta_y);
                int max_y = (int)Math.floor(sy+delta_y);

                TreeSet<UniqueInteger> rel_goblins = goblins.get(x);
                while(!rel_goblins.isEmpty()) {
                    UniqueInteger goblin_y =
                        rel_goblins.ceiling(new UniqueInteger(min_y));

                    if(goblin_y != null && goblin_y.value <= max_y)
                        rel_goblins.remove(goblin_y);
                    else
                        break;
                }
            }
        }

        int goblins_left = 0;
        for(int i = 0; i <= MAX_VALUE; ++i)
            goblins_left += goblins.get(i).size();

        System.out.println(goblins_left);
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
