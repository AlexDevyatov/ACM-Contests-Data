import java.util.*;

public class Antti {
    static int n, m;
    static double[] people;
    static double[] trains;
    static HashMap<Double,Integer> hm1 = new HashMap<Double,Integer>();
    static HashMap<Double,Integer> hm2 = new HashMap<Double,Integer>();
    static int[] capacity;
    static int[] solution;
    static int count;
    static int[] extra;
    static Stack<Integer>[] extraList;

    static int[] findTrains(double x) {
        double best = 1e9;
        int[] result = new int[2];
        for (int j = -1; j <= 1; j++) {
            double goal = x+j*2*Math.PI;
            int k = 0;
            for (int b = m; b >= 1; b /= 2) {
                while (k+b < m && trains[k+b] < goal) k += b;
            }
            double dist = Math.abs(trains[k]-goal);
            if (Math.abs(dist-best) < 1e-15) {
                result[1] = k;
            } else if (dist < best) {
                best = dist;
                result[0] = k;
                result[1] = -1;
            }
            if (k == m-1) continue;
            k++;
            dist = Math.abs(trains[k]-goal);
            if (Math.abs(dist-best) < 1e-15) {
                result[1] = k;
            } else if (dist < best) {
                best = dist;
                result[0] = k;
                result[1] = -1;
            }
        }
        return result;
    }

    static void addPeople(int to, int from, int amount) {
        for (int i = 0; i < amount; i++) {
            solution[extraList[from].pop()] = hm2.get(trains[to]);
        }
    }

    static int[] newcap;
    static int[] newext;
    static int addExtra(int pos, int left, int mode) {
        newcap = capacity.clone();
        newext = extra.clone();
        newext[pos] -= left;
        int u = Math.min(left,newcap[pos]);
        newcap[pos] -= u;
        if (mode == 1) addPeople(pos,pos,u);
        for (int i = 1; i <= m-1; i++) {
            int i1 = pos-i+m;
            int i2 = i1+1+m;
            i1 %= m; i2 %= m;
            u = Math.min(newext[i1],newcap[i2]);
            newcap[i2] -= u;
            newext[i1] -= u;
            if (mode == 1) addPeople(i2,i1,u);
            u = Math.min(newext[i1],newcap[i1]);
            newcap[i1] -= u;
            newext[i1] -= u;
            if (mode == 1) addPeople(i1,i1,u);
        }
        int pos2 = (pos+1)%m;
        u = Math.min(newext[pos],newcap[pos2]);
        newcap[pos2] -= u;
        if (mode == 1) addPeople(pos2,pos,u);
        int count = 0;
        for (int i = 0; i < m; i++) {
            count += capacity[i]-newcap[i];
        }
        return count;
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        n = input.nextInt();
        m = input.nextInt();
        people = new double[n];
        for (int i = 0; i < n; i++) {
            int x = input.nextInt();
            int y = input.nextInt();
            people[i] = Math.atan2(x,y);
        }
        trains = new double[m];
        for (int i = 0; i < m; i++) {
            int x = input.nextInt();
            int y = input.nextInt();
            int c = input.nextInt();
            trains[i] = Math.atan2(x,y);
            hm1.put(trains[i],c);
            hm2.put(trains[i],i);
        }
        Arrays.sort(trains);
        capacity = new int[m];
        for (int i = 0; i < m; i++) {
            capacity[i] = hm1.get(trains[i]);
        }
        solution = new int[n];
        extra = new int[m];
        extraList = new Stack[m];
        for (int i = 0; i < n; i++) {
            solution[i] = -1;
            int[] t = findTrains(people[i]);
            if (t[1] == -1) {
                if (capacity[t[0]] > 0) {
                    solution[i] = hm2.get(trains[t[0]]);
                    capacity[t[0]]--;
                    count++;
                }
            } else {
                if (t[0] > t[1]) {int s = t[0]; t[0] = t[1]; t[1] = s;}
                if (t[0] == 0 && t[1] == m-1) {
                    extra[t[1]]++;
                    if (extraList[t[1]] == null) extraList[t[1]] = new Stack<Integer>();
                    extraList[t[1]].push(i);
                } else {
                    extra[t[0]]++;
                    if (extraList[t[0]] == null) extraList[t[0]] = new Stack<Integer>();
                    extraList[t[0]].push(i);
                }
            }
        }
        int minExtra = n+1, minPos = -1;
        for (int i = 0; i < m; i++) {
            if (extra[i] < minExtra) {
                minExtra = extra[i];
                minPos = i;
            }
        }
        int bestAdded = -1, bestLeft = -1;
        for (int left = 0; left <= extra[minPos]; left++) {
            int added = addExtra(minPos,left,0);
            if (added > bestAdded) {
                bestAdded = added;
                bestLeft = left;
            }
        }
        count += bestAdded;
        addExtra(minPos,bestLeft,1);
        System.out.println(count);
        for (int i = 0; i < n; i++) {
            if (solution[i] == -1) continue;
            System.out.println(i + " " + solution[i]);
        }
    }
}
