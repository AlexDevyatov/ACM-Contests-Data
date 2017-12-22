import java.util.*;
import java.io.*;

public class Antti {
    static int n;
    static ArrayList<Integer>[] tree;
    static int k;
    static int nodeCount, leafCount, firstPath;
    static int[] nodePos, nodeDepth;
    static ArrayList<Integer> leafPos = new ArrayList<Integer>();
    static int[][] nodeUp;
    
    static void checkTree(int s, int d) {
        if (leafCount == 0) firstPath++;
        if (tree[s].size() == 0) {
            leafCount++;
            leafPos.add(nodeCount);
        }
        nodeDepth[s] = d;
        nodePos[nodeCount++] = s;
        for (int u : tree[s]) checkTree(u,d+1);
    }
    
    static long[] levelCount = new long[50];
    static ArrayList<Long>[] rangeStart, rangeEnd;
    static long longPath;
    
    static void createLevel(int s, int f) {
        if (tree[s].size() == 0) {
            if (f == 0) {
                levelCount[f]++;
            } else {
                rangeStart[f].add(levelCount[f]);
                rangeEnd[f].add(levelCount[f]+levelCount[f-1]-1);
                levelCount[f] += levelCount[f-1];
            }
            return;
        }
        levelCount[f]++;
        for (int u : tree[s]) createLevel(u, f);
    }
    
    static Stack<Long> bases = new Stack<Long>();
    static Stack<Integer> leaves = new Stack<Integer>();
    
    static long[] findNode(int f, long id, long base) {
        bases.push(base);
        if (f == 0) {
            return new long[] {0,id,base};
        }
        int k = -1;
        for (int b = leafCount; b >= 1; b /= 2) {
            while (k+b < leafCount && rangeStart[f].get(k+b) <= id) k += b;
        }
        if (k == -1) {
            return new long[] {f,id,base};
        } else if (rangeEnd[f].get(k) >= id) {
            leaves.push(k);
            return findNode(f-1,id-rangeStart[f].get(k),base+rangeStart[f].get(k));
        } else {
            return new long[] {f,leafPos.get(k)+id-rangeEnd[f].get(k),base};
        }
    }

    static long distance(long[] a, long[] b, Stack<Long> z1, Stack<Long> z2, Stack<Integer> w1, Stack<Integer> w2) {
        long result = 0;
        while (true) {
            if (a[2] == b[2]) {
                int x = nodePos[(int)a[1]];
                int y = nodePos[(int)b[1]];
                if (nodeDepth[x] > nodeDepth[y]) {
                    int t = x; x = y; y = t;
                }
                for (int i = 19; i >= 0; i--) {
                    if (nodeDepth[y]-(1<<i) >= nodeDepth[x]) {
                        result += (1<<i);
                        y = nodeUp[y][i];
                    }
                }
                for (int i = 19; i >= 0; i--) {
                    if (nodeUp[x][i] != nodeUp[y][i]) {
                        x = nodeUp[x][i];
                        y = nodeUp[y][i];
                        result += 2*(1<<i);
                    }
                }
                if (x != y) result += 2;
                break;
            }
            if (b[0] > a[0]) {
                if (a[1] != 0) {
                    result += nodeDepth[nodePos[(int)a[1]]];
                    a[1] = 0;
                    continue;
                }
                z1.pop();
                a[0]++;
                a[1] = leafPos.get(w1.peek());
                a[2] = z1.peek();
                w1.pop();
            } else {
                if (b[1] != 0) {
                    result += nodeDepth[nodePos[(int)b[1]]];
                    b[1] = 0;
                    continue;
                }
                z2.pop();
                b[0]++;
                b[1] = leafPos.get(w2.peek());
                b[2] = z2.peek();
                w2.pop();
            }
        }
        return result;
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        n = input.nextInt();
        tree = new ArrayList[n];
        nodePos = new int[n];
        nodeDepth = new int[n];
        nodeUp = new int[n][20];
        for (int i = 0; i < n; i++) tree[i] = new ArrayList<Integer>();
        for (int i = 1; i < n; i++) {
            int p = input.nextInt();
            nodeUp[i][0] = p;
            tree[p].add(i);
        }
        for (int d = 1; d < 20; d++) {
            for (int i = 0; i < n; i++) {
                nodeUp[i][d] = nodeUp[nodeUp[i][d-1]][d-1];
            }
        }
        checkTree(0,0);
        k = input.nextInt();
        rangeStart = new ArrayList[50];
        rangeEnd = new ArrayList[50];
        if (leafCount > 1) {
            int newK = 0;
            for (int i = 0; i <= k; i++) {
                rangeStart[i] = new ArrayList<Long>();
                rangeEnd[i] = new ArrayList<Long>();
                createLevel(0,i);
                newK = i;
                if (levelCount[i] > (1<<30)) {
                    longPath = (long)(k-i)*(firstPath-1);
                    break;
                }
            }
            k = newK;
        }
        int q = input.nextInt();
        for (int i = 0; i < q; i++) {
            int a = input.nextInt()-1;
            int b = input.nextInt()-1;
            if (leafCount == 1 || (a < longPath && b < longPath)) {
                System.out.println(Math.abs(a-b));
                continue;
            }
            a -= (int)longPath;
            b -= (int)longPath;
            long bonus = 0;
            if (a < 0) {bonus -= a; a = 0;}
            if (b < 0) {bonus -= b; b = 0;}
            bases.clear();
            leaves.clear();
            long[] x = findNode(k,a,0);
            Stack<Long> z1 = (Stack<Long>)bases.clone();
            Stack<Integer> w1 = (Stack<Integer>)leaves.clone();
            bases.clear();
            leaves.clear();
            long[] y = findNode(k,b,0);
            Stack<Long> z2 = (Stack<Long>)bases.clone();
            Stack<Integer> w2 = (Stack<Integer>)leaves.clone();
            System.out.println(distance(x,y,z1,z2,w1,w2)+bonus);
        }
    }
}
