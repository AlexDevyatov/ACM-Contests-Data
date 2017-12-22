import java.util.*;

public class Antti {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        HashMap<String,Integer> map = new HashMap<String,Integer>();
        ArrayList<String> names = new ArrayList<String>();
        int n = input.nextInt();
        for (int i = 0; i < n; i++) {
            String name = input.next();
            names.add(name);
            map.put(name,i);
            map.put(name+",",i);
        }
        int[][] dist = new int[n][n];
        int[][] path = new int[n][n];
        int INF = 999999999;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = INF;
            }
        }
        for (int i = 0; i < n; i++) {
            String name = input.next();
            int from = map.get(name);
            int count = input.nextInt();
            for (int j = 0; j < count; j++) {
                name = input.next();
                while (true) {
                    name = input.next();
                    int to = map.get(name);
                    dist[from][to] = 1;
                    if (!name.endsWith(",")) break;
                }
            }
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    int d1 = dist[i][j];
                    int d2 = dist[i][k]+dist[k][j];
                    if (d2 < d1) {
                        dist[i][j] = d2;
                        path[i][j] = k;
                    }
                }
            }
        }
        int minDist = INF;
        int first = -1;
        for (int i = 0; i < n; i++) {
            if (dist[i][i] < minDist) {
                minDist = dist[i][i];
                first = i;
            }
            minDist = Math.min(minDist,dist[i][i]);
        }
        if (minDist == INF) {
            System.out.println("SHIP IT");
        } else {
            int node = first;
            for (int step = 0; step < minDist; step++) {
                System.out.print(names.get(node) + " ");
                for (int next = 0; next < n; next++) {
                    if (dist[node][next] == 1 &&
                        dist[node][first] > dist[next][first]) {
                        node = next;
                        break;
                    }
                }
            }
            System.out.println();
        }
    }
}
