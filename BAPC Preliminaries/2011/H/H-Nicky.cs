using System.Collections;

class State {
	public int x, y, t;
	public State(int x, int y, int t) {
		this.x = x; this.y = y; this.t = t;
	}
}

public class Stealth {
	static bool[,,] cell;
	static bool[,,] done;
	int N, K, W, H;
	ArrayList Q = new ArrayList();
	
	public void run() {
		string[] line = System.Console.ReadLine().Split();
		N = int.Parse(line[0]);
		K = int.Parse(line[1]);
		W = 2 * N + 1; H = 2 * N + 3;
		cell = new bool[W,H,8];
		done = new bool[W,H,8];
		for (int i = 0; i < W; i++) {
			for (int j = 0; j < H; j++) {
				for (int t = 0; t < 8; t++) {
					if (i == 0 || i == W-1 || j == 0 || j == H-1 || (i%2 == 0 && j%2 == 1)) cell[i,j,t] = true;
				}
			}
		}
		
		for (int k = 0; k < K; k++) {
			string S = System.Console.ReadLine();
			string[] L = S.Split();
			int r = int.Parse(L[0]); r++;
			int c = int.Parse(L[1]);
			int dir = 0;
			switch(L[2][0]) {
				case 'B': dir = 6; break;
				case 'R': dir = 4; break;
				case 'F': dir = 2; break;
			}
			for (int i = 1; i <= c; i++) {
				cell[i,r,dir] = true; cell[i,r,dir+1] = true;
			}
			for (int i = c; i < 2*N; i++) {
				cell[i,r,(dir+4)%8] = true; cell[i,r,(dir+5)%8] = true;
			}
			for (int i = 2; i <= r; i++) {
				cell[c,i,(dir+6)%8] = true; cell[c,i,(dir+7)%8] = true;
			}
			for (int i = r; i <= 2*N; i++) {
				cell[c,i,(dir+2)%8] = true; cell[c,i,(dir+3)%8] = true;
			}		
		}
		
		for (int i = 1; i < W; i += 2) {
			Q.Add(new State(i, 1, 0)); done[i,1,0] = true;
		}
		int y = 0;
		State[] neighbors = new State[5];
		while (y < Q.Count) {
			State s = (State)Q[y];
			if (s.y == H - 2) {
				System.Console.WriteLine("succeeds");
				return;
			}
			neighbors[0] = new State(s.x-1,s.y,(s.t+1)%8);
			neighbors[1] = new State(s.x+1,s.y,(s.t+1)%8);
			neighbors[2] = new State(s.x,s.y-1,(s.t+1)%8);
			neighbors[3] = new State(s.x,s.y+1,(s.t+1)%8);
			neighbors[4] = new State(s.x,s.y,(s.t+1)%8);
			for (int i = 0; i < 5; i++) {
				State s2 = neighbors[i];
				if (!cell[s2.x,s2.y,s2.t] && !done[s2.x,s2.y,s2.t]) {
					done[s2.x,s2.y,s2.t] = true;
					Q.Add(s2);
				}
			}
			y++;
		}
		System.Console.WriteLine("fails");
	}
	
	static void Main() {
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) new Stealth().run();
	}
}


