import java.util.*;
import java.io.*;
import java.math.*;

public class Markus {

    public static ArrayList<Integer> findComponent(int source,
            ArrayList<ArrayList<Integer>> graph, int[] marked) {

        ArrayList<Integer> component = new ArrayList<Integer>();
        Queue<Integer> queue = new LinkedList<Integer>();
        queue.add(source);

        marked[source] = source;
        while(!queue.isEmpty()) {
            int v = queue.poll();
            component.add(v);

            for(int nghbr: graph.get(v)) {
                if(marked[nghbr] != source) {
                    marked[nghbr] = source;
                    queue.add(nghbr);
                }
            }
        }

        return component;
    }

    public static int findDia(ArrayList<Integer> component,
            ArrayList<ArrayList<Integer>> graph) {

        HashMap<Integer, Integer> degree = new HashMap<Integer, Integer>();
        ArrayList<Integer> leafs = new ArrayList<Integer>();
        for(int v: component) {
            degree.put(v, graph.get(v).size());
            if(degree.get(v) < 2)
                leafs.add(v);
        }

        int layers = 0;
        int explored = leafs.size();
        while(explored < component.size()) {
            ++layers;

            ArrayList<Integer> new_leafs = new ArrayList<Integer>();
            for(int v: leafs) {
                for(int nghbr: graph.get(v)) {
                    degree.put(nghbr, degree.get(nghbr)-1);
                    if(degree.get(nghbr) == 1)
                        new_leafs.add(nghbr);
                }
            }

            leafs = new_leafs;
            explored += leafs.size();
        }

        return 2*layers + (leafs.size() == 2 ? 1 : 0);
    }

    public static void main(String[] args) {
        Kattio io = new Kattio(System.in);
        int N = io.getInt();
        int M = io.getInt();

        ArrayList<ArrayList<Integer>> graph = new ArrayList<ArrayList<Integer>>();
        for(int i = 0; i < N; ++i)
            graph.add(new ArrayList<Integer>());

        for(int i = 0; i < M; ++i) {
            int a = io.getInt();
            int b = io.getInt();
            graph.get(a).add(b);
            graph.get(b).add(a);
        }

        int max_dia = 0;
        PriorityQueue<Integer> radii = new PriorityQueue<Integer>();
        int[] marked = new int[N];
        for(int i = 0; i < N; ++i)
            marked[i] = -1;

        for(int v = 0; v < N; ++v) {
            if(marked[v] < 0) {
                ArrayList<Integer> component = findComponent(v, graph, marked);
                int dia = findDia(component, graph);
                max_dia = Math.max(max_dia, dia);

                radii.add(dia/2 + dia%2);
                while(radii.size() > 3)
                    radii.poll();
            }
        }

        while(radii.size() < 3)
            radii.add(0);

        int small = radii.poll();
        int medium = radii.poll();
        int large = radii.poll();

        System.out.println(Math.max(max_dia,
                    Math.max(large+medium+1,
                        medium+small+2)));
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
