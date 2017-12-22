import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.*;

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

import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.OutputStream;

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


public class Jimmy_BadHeuristic {

    private final int noHouses, c1, c2;
    private final boolean[] covered; // covered[x] = true if talk covered by "endpoint solution"
    private final ArrayList<Talk> talks;
    private final List<List<Talk>> talksByHouse;

    public Jimmy_BadHeuristic(int noHouses, ArrayList<Talk> talks, int c1, int c2) {
        this.noHouses = noHouses;
        this.talks = talks;
        this.c1 = c1;
        this.c2 = c2;
        this.covered = new boolean[talks.size()+1];
        this.talksByHouse = new ArrayList<>(talks.size()+1);
        for (int i = 0; i <= noHouses; i++) talksByHouse.add(new ArrayList<>());
    }

    public static class Pair {
        public int a,b;
        public Pair(int a, int b) { this.a = a; this.b = b; }

        @Override
        public String toString() {
            return String.format("<%d,%d>", a, b);
        }
    }

    public static class Talk {
        public int a,b,c,ix; // a < b
        public boolean isSameSide() { return c < 0; }
        public Talk(int a, int b, int c, int ix) {
            this.a = Math.min(a,b);
            this.b = Math.max(a,b);
            this.c = c;
            this.ix = ix;
        }
    }

    public void solveEndpoint(int ep, int c, int step, List<Pair> devices) {
        HashSet<Talk> active = new HashSet<>(), started = new HashSet<>();
        for (int i = ep;; i+=step) {
            for (Talk talk : talksByHouse.get(i)) {
                if (active.contains(talk)) {
                    devices.add(new Pair(i-step, i));
                    for (Talk at : active) {
                        covered[at.ix] = true;
                    }
                    active.clear();
                }
            }
            if (i == c) break;
            for (Talk talk : talksByHouse.get(i)) {
                if (!started.contains(talk)) {
                    started.add(talk);
                    active.add(talk);
                }
            }
        }

    }

    private boolean isUpperLeft(int h) { return h % 2 == 1 && h < c1; }
    private boolean isLowerLeft(int h) { return h % 2 == 0 && h < c1+1; }
    private boolean isUpperRight(int h) { return h % 2 == 1 && h > c2; }
    private boolean isLowerRight(int h) { return h % 2 == 0 && h > c2+1; }

    private int withinBounds(int h) {
        // Converts a house position to the closest position in middle area
        if (isUpperLeft(h)) return c1;
        if (isLowerLeft(h)) return c1+1;
        if (isUpperRight(h)) return c2;
        if (isLowerRight(h)) return c2+1;
        return h;
    }

    private int convert(int h) {
        // Converts a house position in the middle area to the circular enumeration
        // starting at c1 (0) to c2 to c2+1 to c1+1 and back.
        assert h % 2 == 0 || (h >= c1 && h <= c2);
        assert h % 2 == 1 || (h >= c1+1 && h <= c2+1);
        return h % 2 == 1 ? (h - c1) / 2 : c2 - c1 + 1 - (h - c1 - 1) / 2;
    }

    private int deconvert(int c) {
        // Converts in the other direction
        return c <= (c2 - c1) / 2 ? c1 + c * 2 : (c2 - c1 + 1 - c) * 2 + c1 + 1;
    }

    private List<Pair> solve() {
        for (Talk talk : talks) {
            talksByHouse.get(talk.a).add(talk);
            talksByHouse.get(talk.b).add(talk);
        }

        ArrayList<Pair> solution = new ArrayList<>();
        solveEndpoint(1, c1, 2, solution);
        solveEndpoint(2, c1+1, 2, solution);
        solveEndpoint(noHouses -1, c2, -2, solution);
        solveEndpoint(noHouses, c2+1, -2, solution);

        ArrayList<Pair> bestSubSolution = null;

        for (int mask = 0; mask < 16; mask++) {
            if ((mask & 3) == 3) continue;
            if ((mask & 12) == 12) continue;

            ArrayList<Pair> circular = new ArrayList<>(talks.size());
            ArrayList<Pair> subSolution = new ArrayList<>();
            if ((mask & 1) > 0) subSolution.add(new Pair(c1 - 2, c1));
            if ((mask & 2) > 0) subSolution.add(new Pair(c1 - 1, c1 + 1));
            if ((mask & 4) > 0) subSolution.add(new Pair(c2, c2 + 2));
            if ((mask & 8) > 0) subSolution.add(new Pair(c2 + 1, c2 + 3));

            for (Talk talk : talks) {
                if (covered[talk.ix]) continue;
                if ((mask & 1) > 0 && (isUpperLeft(talk.a) ^ isUpperLeft(talk.b))) continue;
                if ((mask & 2) > 0 && (isLowerLeft(talk.a) ^ isLowerLeft(talk.b))) continue;
                if ((mask & 4) > 0 && (isUpperRight(talk.b) ^ isUpperRight(talk.a))) continue;
                if ((mask & 8) > 0 && (isLowerRight(talk.b) ^ isLowerRight(talk.a))) continue;

                int a = convert(withinBounds(talk.a)), b = convert(withinBounds(talk.b));
                if ((talk.isSameSide() && talk.a % 2 == 1) || (!talk.isSameSide() && (talk.a % 2 == 1 ^ talk.c == c1))) {
                    circular.add(new Pair(a, b));
                } else {
                    circular.add(new Pair(b, a));
                }
            }

            int length = c2 - c1 + 2;
            List<Integer> circularSolution1 = solveCircular(circular, length);

            for (int i = 0; i < circular.size(); i++) {
                Pair pair = circular.get(i);
                circular.set(i, new Pair(length - 1 - pair.b, length - 1 - pair.a));
            }
            List<Integer> circularSolution2 = solveCircular(circular, length);

            if (circularSolution1.size() <= circularSolution2.size()) {
                for (Integer node : circularSolution1) {
                    subSolution.add(new Pair(deconvert(node), deconvert((node + 1) % length)));
                }

            } else {
                for (Integer node : circularSolution2) {
                    int t = length - 1 - node;
                    subSolution.add(new Pair(deconvert(t), deconvert((t+length-1)%length)));
                }
            }

            if (bestSubSolution == null || subSolution.size() < bestSubSolution.size()) {
                bestSubSolution = subSolution;
            }
        }

        solution.addAll(bestSubSolution);

        return solution;
    }

    private static class SegmentEndpoint {
        private int p, ix;
        private boolean start;

        public SegmentEndpoint(int p, int ix, boolean start) {
            this.p = p;
            this.ix = ix;
            this.start = start;
        }

        @Override
        public String toString() {
            return String.format("%s at %d [%d]", start ? "Start" : "End", p, ix);
        }
    }

    private List<Integer> solveCircular(ArrayList<Pair> segments, int n) {
        if (segments.size() == 0) return new ArrayList<>();

        List<Integer> bestSol = null;

        ArrayList<SegmentEndpoint> endpoints = new ArrayList<>(segments.size() * 2);
        for (int i = 0; i < segments.size(); i++) {
            Pair segment = segments.get(i);
            SegmentEndpoint epa = new SegmentEndpoint(segment.a, i, true);
            SegmentEndpoint epb = new SegmentEndpoint(segment.b, i, false);
            endpoints.add(epa);
            endpoints.add(epb);
        }
        endpoints.sort((o1, o2) -> {
            if (o1.p != o2.p) return o1.p - o2.p;
            if (o1.start != o2.start) return o1.start ? 1 : -1; // ends should come before start
            return 0;
        });

        /*
        for (SegmentEndpoint ep : endpoints) {
            System.out.println(String.format("%s at %d [%d]", ep.start ? "Start" : "End", ep.p, ep.ix));
        }
        System.out.println();
        */

        int best[] = new int[endpoints.size()];
        int lastStartPos = -1;
        for (int start = 0; start < endpoints.size(); start++) {
            // There must not be points on the same coord before and after start
            ArrayList<Integer> sol = new ArrayList<>();
            boolean[] done = new boolean[segments.size()];
            TreeSet<Integer> active = new TreeSet<>();

            int startPos = endpoints.get(start).p;
            if (startPos == lastStartPos) continue;
            lastStartPos = startPos;

            // Find segments that are already active
            for (int i = 0; i < segments.size(); i++) {
                Pair segment = segments.get(i);
                if (segment.a < segment.b) {
                    if (segment.a < startPos && segment.b >= startPos) {
                        active.add(i);
                    }
                } else {
                    if (segment.a < startPos || segment.b >= startPos) {
                        active.add(i);
                    }
                }
            }

            boolean noImprovement = false;
            for (int i = 0; i < endpoints.size(); i++) {
                int index = (i + start) % endpoints.size();
                SegmentEndpoint endpoint = endpoints.get(index);
                if (endpoint.start) {
                    if (active.contains(endpoint.ix)) throw new RuntimeException();
                    if (!done[endpoint.ix]) {
                        active.add(endpoint.ix);
                    }
                } else {
                    if (!done[endpoint.ix]) {
                        sol.add((endpoint.p + n - 1)%n);
                        for (int a : active) {
                            done[a] = true;
                        }
                        active.clear();
                        if (best[index] > 0 && sol.size() >= best[index]) {
                            noImprovement = true;
//                            break;
                        }
                        best[index] = sol.size();
                    }
                }
            }
            if (noImprovement) continue;
            if (active.size() > 0) throw new RuntimeException();


            /*
            System.out.println("Fixed " + fixed);
            for (Integer device : sol) {
                System.out.println(device);
            }
            System.out.println();
            */

            if (bestSol == null) {
                bestSol = sol;
            } else if (sol.size() < bestSol.size()) {
                // A solution can be at most 1 better than any other, so if we find a better, return it!
                return sol;
            }
            break;
        }

        return bestSol;
    }

    public static void main(String[] args) throws FileNotFoundException {
//        Kattio io = new Kattio(new FileInputStream("surveillance.in"), System.out);
        Kattio io = new Kattio(System.in, System.out);
        int n = io.getInt(), m = io.getInt(), c1 = io.getInt(), c2 = io.getInt();
        ArrayList<Talk> talks = new ArrayList<>();
        for (int i = 0; i < m; i++) {
            int a = io.getInt(), b = io.getInt();
            if (a%2 != b%2) {
                int c = io.getInt();
                talks.add(new Talk(a,b,c,i));
            } else {
                talks.add(new Talk(a,b,-1,i));
            }
        }

        List<Pair> solution = new Jimmy_BadHeuristic(n, talks, c1, c2).solve();

        io.println(solution.size());
        for (Pair device : solution) {
            io.println(device.a + " " + device.b);
        }


        io.close();
    }
}
