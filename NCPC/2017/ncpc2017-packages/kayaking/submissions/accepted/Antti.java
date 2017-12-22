import java.util.*;

public class Antti {
    static int[] count = new int[3];
    static int[] strength = new int[3];
    static int m;
    static int[] factor;

    static boolean ok(int[] left, int speed) {
        boolean[] chosen = new boolean[m];
        for (int a = 0; a < 3; a++) {
            for (int b = a; b < 3; b++) {
                for (int i = 0; i < m; i++) {
                    if (chosen[i]) continue;
                    if (a == b && left[a] < 2) continue;
                    if (left[a] < 1 || left[b] < 1) continue;
                    if (factor[i]*(strength[a]+strength[b]) < speed) continue;
                    chosen[i] = true;
                    left[a]--; left[b]--;
                }
            }
        }
        return left[0] == 0 && left[1] == 0 && left[2] == 0;
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        for (int i = 0; i < 3; i++) count[i] = input.nextInt();
        for (int i = 0; i < 3; i++) strength[i] = input.nextInt();
        m = (count[0]+count[1]+count[2])/2;
        factor = new int[m];
        for (int i = 0; i < m; i++) {
            factor[i] = input.nextInt();
        }
        Arrays.sort(factor);
        int k = 0;
        for (int u = 5000000; u >= 1; u /= 2) {
            while (ok(new int[] {count[0],count[1],count[2]},k+u)) k += u;
        }
        System.out.println(k);
    }
}

