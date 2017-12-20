import java.util.*;

public class tobi {
	public static int N, from, to, numP, r, dp[] = new int[1000];
	public static ArrayList<Integer> adjList[] = new ArrayList[1000];
	public static HashMap<String, Integer> nameToInt = new HashMap<>();
	public static boolean isProgram[] = new boolean[1000], visited[] = new boolean[1000];

	public static int getName(String s) {
		if (nameToInt.get(s) == null) {
			nameToInt.put(s, nameToInt.size());
			isProgram[nameToInt.get(s)] = s.endsWith("::PROGRAM");
		}
		return nameToInt.get(s);
	}

	public static boolean dfs(int node) {
		if (visited[node]) return false;
		visited[node] = true;
		for (int next : adjList[node]) if (dfs(next)) return true;
		return false;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		for (int i = 0; i < N; i++) adjList[i] = new ArrayList<>();
		for (int i = 0; i < N; i++) {
			from = getName(sc.next());
			numP = sc.nextInt();
			for (int j = 0; j < numP; j++) {
				to = getName(sc.next());
				adjList[to].add(from);
			}
		}
		for (int i = 0; i < N; i++) if (isProgram[i]) dfs(i);
		for (int i = 0; i < N; i++) if (visited[i]) r++;
		System.out.println(N-r);
	}
}
