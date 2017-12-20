import java.util.*;
import java.math.*;

public class Thorsten {
    public static int W;
    public static int H;
    public static int c;
    public static int[] a = new int[9];
    public static int[] w = new int[9];
    public static int[] h = new int[9];

    public static boolean[][] buf = new boolean[101][]; // whether occupied by carpet

    public static boolean tryFill(int x, int y) {
        while (true) {
            // do this...
            if (x >= W) { // go to next row
                x = 0;
                y++;
            }
            if (y >= H) {
                return true;
            }
            // until we find a free cell
            if (buf[x][y] == false) break;
            x++;
        }
        // try all the carpets
        for (int i = 0; i < c; i++) {
            if (a[i] <= 0) continue;
            // does it fit at all?
            int wi = w[i], hi = h[i];
            for (int xyz = 0; xyz < 2; xyz++) {
                int tmp = wi;
                wi = hi;
                hi = tmp;
                if (x + wi > W) continue;
                if (y + hi > H) continue;
                boolean allfree = true;
                // we only need to check the [dx + x][y] points. because if so,
                // any [dx + x][y + dy] will be free as well.
                for (int dx = 0; dx < wi; dx++) {
                    if (buf[dx + x][y] == true) {
                        allfree = false;
                        break;
                    }
                }
                if (!allfree) {
                    continue;
                }
                // there's enough space => try it.
                for (int dx = 0; dx < wi; dx++) {
                    for (int dy = 0; dy < hi; dy++) {
                        buf[dx + x][dy + y] = true;
                    }
                }
                a[i]--;
                if (tryFill(x + wi, y)) {
                    return true;
                }
                for (int dx = 0; dx < wi; dx++) {
                    for (int dy = 0; dy < hi; dy++) {
                        buf[dx + x][dy + y] = false;
                    }
                }
                a[i]++;

            }
        }
        return false;
    }

    public static void main(String[] args) {
        for (int i = 0; i < 101; i++) {
            buf[i] = new boolean[101];
            for (int j = 0; j < 101; j++) {
                buf[i][j] = false;
            }
        }
        Scanner scan = new Scanner(System.in);
        W = scan.nextInt();
        H = scan.nextInt();
        c = scan.nextInt();
        long totalArea = 0;
        for (int i = 0; i < c; i++) {
            a[i] = scan.nextInt();
            w[i] = scan.nextInt();
            h[i] = scan.nextInt();
            totalArea += a[i]*w[i] * h[i];
        }
        if (totalArea >= W*H && tryFill(0,0)) {
            System.out.println("yes");
        } else {
            System.out.println("no");
        }
    }
}
