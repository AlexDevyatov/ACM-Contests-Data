import java.util.*;

public class Antti {
    static int n;
    static int[][] angle;
    static int[] id;
    static TreeSet<Integer>[][] cards;
    static int[] value;
    static TreeSet<Integer>[] order;
    static TreeMap<Integer,Integer> map;

    static int uniqueness(int k) {
        int result = 0;
        for (int c = 0; c < 3; c++) {
            int a = angle[c][k];
            if (cards[c][a].size() != 1) continue;
            for (int i = 1; i <= 360; i++) {
                if (cards[c][(a+i)%360].size() != 0) {
                    result += i;
                    break;
                }
            }
            for (int i = 1; i <= 360; i++) {
                if (cards[c][(a-i+360)%360].size() != 0) {
                    result += i;
                    break;
                }
            }
        }
        return result;
    }

    static void update(int id) {
        int k = map.get(id);
        order[value[k]].remove(id);
        value[k] = uniqueness(k);
        order[value[k]].add(id);
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        n = input.nextInt();
        angle = new int[3][n];
        id = new int[n];
        cards = new TreeSet[3][360];
        for (int c = 0; c < 3; c++) {
            for (int i = 0; i < 360; i++) {
                cards[c][i] = new TreeSet<Integer>();
            }
        }
        map = new TreeMap<Integer,Integer>();
        for (int i = 0; i < n; i++) {
            for (int c = 0; c < 3; c++) {
                angle[c][i] = input.nextInt();
            }
            id[i] = input.nextInt();
            map.put(id[i],i);
            for (int c = 0; c < 3; c++) {
                cards[c][angle[c][i]].add(id[i]);
            }
        }
        value = new int[n];
        order = new TreeSet[2200];
        for (int i = 0; i < 2200; i++) {
            order[i] = new TreeSet<Integer>();
        }
        for (int i = 0; i < n; i++) {
            value[i] = uniqueness(i);
            order[value[i]].add(id[i]);
        }
        for (int z = 0; z < 2200; z++) {
            while (order[z].size() > 0) {
                int id = order[z].last();
                System.out.println(id);
                order[z].remove(id);
                int k = map.get(id);
                for (int c = 0; c < 3; c++) {
                    int a = angle[c][k];
                    cards[c][a].remove(id);
                    if (cards[c][a].size() == 0) {
                        for (int i = 1; i <= 360; i++) {
                            if (cards[c][(a+i)%360].size() == 1) {
                                update(cards[c][(a+i)%360].first());
                                break;
                            }
                        }
                        for (int i = 1; i <= 360; i++) {
                            if (cards[c][(a-i+360)%360].size() == 1) {
                                update(cards[c][(a-i+360)%360].first());
                                break;
                            }
                        }
                    }
                    if (cards[c][a].size() == 1) {
                        update(cards[c][a].first());
                    }
                }
            }
        }
    }
}
