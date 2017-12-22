import java.util.Scanner;

public class Oskar {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int K = sc.nextInt();
        int sweep[] = new int[101001];
        for (int i = 0; i < N; ++i) {
            int ti = sc.nextInt();
            sweep[ti] += 1;
            sweep[ti + 1000] -= 1;
        }
        int top = 0;
        int accum = 0;
        for (int i = 0; i < 101001; ++i) {
            accum += sweep[i];
            top = accum > top ? accum : top;
        }
        System.out.println((top + K - 1) / K);
    }
}
