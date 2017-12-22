import java.util.*;

public class Antti {
    static double totalLength;
    static double slowSpeed, fastSpeed;
    static double waitTime, drinkTime;
    static double oneCoffee;
    static int n;
    static double[] carts;
    static double[] minimumTime;
    static int[] nextCart;

    static double calcTime(int curPos, int nextPos) {
        double distance = carts[nextPos]-carts[curPos];
        double time = minimumTime[nextPos];
        if (waitTime*slowSpeed >= distance) {
            time += distance/slowSpeed;
        } else {
            time += waitTime;
            distance -= waitTime*slowSpeed;
            if (drinkTime*fastSpeed >= distance) {
                time += distance/fastSpeed;
            } else {
                time += drinkTime;
                distance -= drinkTime*fastSpeed;
                time += distance/slowSpeed;
            }
        }
        return time;
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        totalLength = input.nextLong();
        slowSpeed = input.nextInt();
        fastSpeed = input.nextInt();
        waitTime = input.nextInt();
        drinkTime = input.nextInt();
        oneCoffee = waitTime*slowSpeed+drinkTime*fastSpeed;
        n = input.nextInt();
        carts = new double[n+1];
        for (int i = 0; i < n; i++) carts[i] = input.nextLong();
        carts[n] = totalLength;
        minimumTime = new double[n+1];
        nextCart = new int[n+1];
        for (int i = n-1; i >= 0; i--) {
            minimumTime[i] = (totalLength-carts[i])/slowSpeed;
            nextCart[i] = n;
            int k = i+1;
            for (int b = n; b >= 1; b /= 2) {
                while (k+b <= n && carts[k+b]-carts[i] <= oneCoffee) k += b;
            }
            for (int j = k; j <= n && j <= k+1; j++) {
                double time = calcTime(i,j);
                if (time < minimumTime[i]) {
                    minimumTime[i] = time;
                    nextCart[i] = j;
                }
            }
        }
        int count = 0;
        int pos = 0;
        while (pos < n) {
            count++;
            pos = nextCart[pos];
        }
        System.out.println(count);
        pos = 0;
        while (pos < n) {
            System.out.print(pos + " ");
            pos = nextCart[pos];
        }
    }
}
