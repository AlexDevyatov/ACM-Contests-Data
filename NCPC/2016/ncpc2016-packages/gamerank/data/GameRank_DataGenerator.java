import java.util.Random;

public class GameRank_DataGenerator {
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        double p = Double.parseDouble(args[1]);
        StringBuilder sb = new StringBuilder();
        Random random = new Random();
        for (int i = 0; i < n; i++) {
            sb.append(random.nextDouble() < p ? 'W' : 'L');
        }
        System.out.println(sb.toString());
    }
}
