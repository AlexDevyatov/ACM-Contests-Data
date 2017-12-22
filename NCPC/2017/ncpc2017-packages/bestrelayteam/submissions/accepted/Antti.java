import java.util.*;

public class Antti {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        String[] name = new String[n];
        double[] time1 = new double[n];
        double[] time2 = new double[n];
        for (int i = 0; i < n; i++) {
            name[i] = input.next();
            time1[i] = input.nextDouble();
            time2[i] = input.nextDouble();
        }
        double best = 1e9;
        String[] result = new String[4];
        for (int i = 0; i < n; i++) {
            String[] names = new String[3];
            double[] times = {1e9,1e9,1e9};
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (time2[j] < times[0]) {
                    times[2] = times[1];
                    times[1] = times[0];
                    times[0] = time2[j];
                    names[2] = names[1];
                    names[1] = names[0];
                    names[0] = name[j];
                } else if (time2[j] < times[1]) {
                    times[2] = times[1];
                    times[1] = time2[j];
                    names[2] = names[1];
                    names[1] = name[j];
                } else if (time2[j] < times[2]) {
                    times[2] = time2[j];
                    names[2] = name[j];
                }
            }
            double total = time1[i]+times[0]+times[1]+times[2];
            if (total < best) {
                best = total;
                result[0] = name[i];
                result[1] = names[0];
                result[2] = names[1];
                result[3] = names[2];
            }
        }
        System.out.println(best);
        System.out.println(result[0]);
        System.out.println(result[1]);
        System.out.println(result[2]);
        System.out.println(result[3]);
    }
}
