import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class GenTests {

    static Random rnd = new Random(3);
    
    static class Edge {
        int a, b;

        Edge(int a, int b) {
            this.a = a;
            this.b = b;
        }

        @Override
        public String toString() {
            return "(" + a + ", " + b + ")";
        }
    }

    static long[] randomArray(int n, int m) {
        long[] res = new long[n];
        for (int i = 0; i < n; i++) {
            res[i] = rnd.nextInt(m) + 1;
        }
        return res;
    }

    static long[] range(int n) {
        long[] res = new long[n];
        for (int i = 0; i < n; i++)
            res[i] = i + 1;
        return res;
    }
    
    static long[] range2(int n) {
        long[] res = new long[n];
        for (int i = 0; i < n; i++) {
            res[i] = n - i;
        }
        return res;
    }

    static class Tree {
        int size;
        List<Edge> edges;

        Tree() {
            size = 1;
            edges = new ArrayList<Edge>();
        }

        Tree(int n) {
            size = n;
            edges = new ArrayList<Edge>();
        }

        void addEdge(int a, int b) {
            edges.add(new Edge(a, b));
        }

        void addToAllIndices(int a) {
            for (Edge e : edges) {
                e.a += a;
                e.b += a;
            }
        }

        void mergeWithWithRandomEdge(Tree t) {
            t.addToAllIndices(size);
            int v1 = rnd.nextInt(size);
            int v2 = rnd.nextInt(t.size);
            edges.add(new Edge(v1, size + v2));
            edges.addAll(t.edges);
            size += t.size;
            t.edges = null;
        }

        void shuffleEdges() {
            Collections.shuffle(edges, rnd);
        }

        void randomlyReenumerateVertices() {
            ArrayList<Integer> perm = new ArrayList<Integer>();
            for (int i = 0; i < size; i++) {
                perm.add(i);
            }
            Collections.shuffle(perm, rnd);
            for (Edge e : edges) {
                e.a = perm.get(e.a);
                e.b = perm.get(e.b);
                if (rnd.nextBoolean()) {
                    int tmp = e.a;
                    e.a = e.b; 
                    e.b = tmp;
                }
            }
            shuffleEdges();
        }

        @Override
        public String toString() {
            return "[Size: " + size + ", edges: " + edges + "]";
        }
    }

    static Tree randomTree(int n) {
        Tree t = new Tree();
        for (int i = 0; i < n - 1; i++) {
            t.mergeWithWithRandomEdge(new Tree());
        }
        t.randomlyReenumerateVertices();
        return t;
    }
    
    static Tree chain(int n) {
        Tree t = new Tree(n);
        for (int i = 0; i < n - 1; i++) {
            t.addEdge(i, i + 1);
        }
        return t;
    }
    
    static Tree binaryTree(int n) {
        Tree t = new Tree(n);
        for (int i = 1; i < n; i++) {
            t.addEdge(i, i / 2);
        }
        return t;
    }

    static Tree star(int n) {
        Tree t = new Tree(n);
        for (int i = 1; i < n; i++) {
            t.addEdge(i, 0);
        }
        return t;
    }

    static Tree kAryTree(int n, int k) {
        Tree t = new Tree(n);
        for (int i = 1; i < n; i++) {
            t.addEdge(i, i / k);
        }
        return t;
    }

    static Test randomTest(int n, int m) {
        Tree t = randomTree(n);
        t.randomlyReenumerateVertices();
        long[] w = randomArray(n, m);
        return new Test(t, w);
    }

    static class Test {
        
        static int test = 1;
        
        Tree t;
        long[] w;

        Test(Tree t, long[] w) {
            this.t = t;
            this.w = w;
        }

        void out() throws FileNotFoundException {
            PrintWriter out = new PrintWriter("../tests/" + String.format("%02d", test++));
            out.println(t.size);
            for (int i = 0; i < t.size; i++) {
                out.print(w[i]);
                if (i < t.size - 1) {
                    out.print(" ");
                } else {
                    out.println();
                }
            }
            for (Edge e : t.edges) {
                out.println((e.a + 1) + " " + (e.b + 1));
            }            
            System.err.println(test - 1);
            out.close();
        }
    }

    
    static Test sample() {
        Tree t = new Tree(5);
        t.addEdge(0, 1);
        t.addEdge(1, 2);
        t.addEdge(1, 3);
        t.addEdge(3, 4);
        long[] w = new long[]{3, 3, 2, 5, 1};
        return new Test(t, w);
    }
    
    public static void main(String[] args) throws FileNotFoundException {
        sample().out();
        for (int i = 3; i < 16; i += 3) {
            randomTest(i, i).out();
        }
        int MAXN = 100000;
        int MAXM = 1000000000;
        Tree t = binaryTree(MAXN);
        new Test(t, range(MAXN)).out();
        new Test(t, range2(MAXN)).out();
        new Test(t, randomArray(MAXN, MAXM)).out();
        t.randomlyReenumerateVertices();
        new Test(t, range(MAXN));

        t = chain(MAXN);
        new Test(t, range(MAXN)).out();
        t.randomlyReenumerateVertices();
        new Test(t, range(MAXN)).out();
        new Test(t, randomArray(MAXN, MAXM)).out();
        
        for (int k = 3; k < 100; k += 10) {
            new Test(kAryTree(MAXN, k), randomArray(MAXN, MAXM)).out();
        }

        new Test(star(MAXN), range(MAXN)).out();
        new Test(star(MAXN), randomArray(MAXN, MAXM)).out();
        for (int i = 0; i < 10; i++) {
            new Test(randomTree(MAXN), randomArray(MAXN, MAXM)).out();
        }
    }


}
