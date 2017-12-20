import java.util.*;

class State implements Comparable<State> {
	int x, y, dist;
	public State(int x, int y, int dist) {
		this.x = x; this.y = y; this.dist = dist;
	}
	public int compareTo(State arg0) {
		return dist - arg0.dist;
	}
}

public class QuickHarbour {
	static Scanner sc = new Scanner(System.in);
	int H, W, D;
	int[][] maze;
	int[][] dist;
	State start;
	PriorityQueue<State> Q;
	
	public void run() {
		H = sc.nextInt(); W = sc.nextInt(); D = sc.nextInt(); sc.nextLine();
		maze = new int[W][H];
		dist = new int[W][H];
		for (int i = 0; i < H; i++) {
			String S = sc.nextLine();
			for (int j = 0; j < W; j++) {
				switch(S.charAt(j)) {
					case 'S': start = new State(j, i, 0);
					case '.': maze[j][i] = 0; break;
					case '@': maze[j][i] = 1; break;
					case '#': maze[j][i] = -1; break;
				}
				dist[j][i] = Integer.MAX_VALUE;
			}
		}
		dist[start.x][start.y] = 0;
		
		Q = new PriorityQueue<State>();
		Q.add(start);
		
		State[] L = new State[4];
		while (!Q.isEmpty()) {
			State S = Q.poll();
			if (S.x == W-1 || S.x == 0 || S.y == H-1 || S.y == 0) {
				System.out.println(S.dist+1);
				return;
			}
			L[0] = new State(S.x-1, S.y, S.dist);
			L[1] = new State(S.x+1, S.y, S.dist);
			L[2] = new State(S.x, S.y+1, S.dist);
			L[3] = new State(S.x, S.y-1, S.dist);
			for (int i = 0; i < 4; i++) {
				if (maze[L[i].x][L[i].y] == -1) continue;
				L[i].dist += 1 + maze[L[i].x][L[i].y] * D;
				if (L[i].dist < dist[L[i].x][L[i].y]) {
					dist[L[i].x][L[i].y] = L[i].dist;
					Q.add(L[i]);
				}
			}
		}
	}
	
	public static void main(String[] args) {
		int runs = sc.nextInt();
		for (int i = 0; i < runs; i++) new QuickHarbour().run();
	}

}
