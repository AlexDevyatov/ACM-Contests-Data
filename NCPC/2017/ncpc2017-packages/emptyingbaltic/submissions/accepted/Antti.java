import java.util.*;

public class Antti {
    static int h, w;
    static int[][] map, res;

    static class Node implements Comparable<Node> {
        int y, x;
        int d;

        Node(int y, int x, int d) {
            this.y = y; this.x = x; this.d = d;
        }

        public int compareTo(Node other) {
            return this.d-other.d;
        }
    }

    static PriorityQueue<Node> q = new PriorityQueue<Node>();

    static void add(int y, int x, int c) {
	if (y < 0 || y >= h || x < 0 || x >= w) return;
        c = Math.max(c,map[y][x]);
        if (c >= res[y][x] || c >= 0) return;
        res[y][x] = c;
        q.add(new Node(y,x,c));
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        h = input.nextInt();
        w = input.nextInt();
        map = new int[h][w];
        res = new int[h][w];
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                map[i][j] = input.nextInt();
            }
        }
        int y = input.nextInt()-1;
        int x = input.nextInt()-1;
        add(y,x,map[y][x]);
        while (q.size() > 0) {
            Node cur = q.poll();
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    add(cur.y+i,cur.x+j,cur.d);
                }
            }
        }
        long water = 0;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                water += -res[i][j];
            }
        }
        System.out.println(water);
    }
}
