import java.util.*;

public class AnttiOverflow {
    static int h, w;
    static int[][] map, res;

    static void dfs(int y, int x, int c) {
	if (y < 0 || y >= h || x < 0 || x >= w) return;
        c = Math.max(c,map[y][x]);
        if (c >= res[y][x] || c >= 0) return;
        res[y][x] = c;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                dfs(y+i,x+j,c);
            }
        }
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
        dfs(y,x,map[y][x]);
        int water = 0;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                water += -res[i][j];
            }
        }
        System.out.println(water);
    }
}
