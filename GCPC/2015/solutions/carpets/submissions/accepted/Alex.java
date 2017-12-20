import java.util.*;

public class Alex{
	static int W, H, C;
	static boolean DEBUG = false;
	static boolean can_fill(boolean[][] filled, int w, int h, int[][] available_carpets, int N){
		boolean sorted = true;
		do{
			sorted = true;
			for(int i = 0; i < N - 1; i++){
				if(available_carpets[i][0] > available_carpets[i+1][0] ||
					(available_carpets[i][0] == available_carpets[i+1][0] &&
						available_carpets[i][1] > available_carpets[i+1][1])){
					int [] tmp = available_carpets[i];
					available_carpets[i] = available_carpets[i+1];
					available_carpets[i+1] = tmp;
					sorted = false;
				}
			}
		} while(!sorted);
		if (DEBUG){
			for(int ww = 0; ww < W; ww++){
				for(int hh = 0; hh < H; hh++)System.out.print(filled[ww][hh]);
				System.out.println();
			}
			System.out.println(w + " " + h);
			for(int i = 0; i < N; i++)System.out.print("(" + available_carpets[i][0] + " " + available_carpets[i][1] + ")");
			System.out.println();
		}
		while(filled[w][h]){
			++w;
			if(w == W){
				++h;
				w = 0;
				if(h == H)return true;
			}
		}
		if(N == 0)return false;
		int space_w = 0, space_h = H - h;
		while(w + space_w < W && !filled[w + space_w][h])++space_w;
		int last_w = -1, last_h = -1;
		for(int i = N-1; i >= 0; i--){
			int w_cur = available_carpets[i][0];
			int h_cur = available_carpets[i][1];
			if(DEBUG){
				System.out.println("w_cur = " + w_cur + " h_cur = " + h_cur);
			}
			if(last_w == w_cur && last_h == h_cur)continue;
			last_w = w_cur;
			last_h = h_cur;
			for(int ii = 0; ii < 2; ii++){
				int tmp = w_cur;
				w_cur = h_cur;
				h_cur = tmp;
				if(w_cur > space_w)continue;
				if(h_cur > space_h)continue;
				for(int ww = 0; ww < w_cur; ww++)for(int hh = 0; hh < h_cur; hh++)filled[w+ww][h+hh]=true;
				int[][] new_available_carpets = new int[N-1][2];
				for(int i1 = 0; i1 < N - 1; i1++)for(int i2 = 0; i2 < 2; i2++){
					new_available_carpets[i1][i2] = available_carpets[i1 + (i1 >= i?1:0)][i2];
				}
				if(can_fill(filled, w, h, new_available_carpets, N-1))return true;
				for(int ww = 0; ww < w_cur; ww++)for(int hh = 0; hh < h_cur; hh++)filled[w+ww][h+hh]=false;
			}
		}
		return false;
	}

	public static void main(String[] args){
		Scanner scan = new Scanner(System.in);
		W = scan.nextInt();
		H = scan.nextInt();
		C = scan.nextInt();
		int N = 0;
		int[][] available_carpets = new int[8][2];
		for(int c = 0; c < C; c++){
			int a, w, h;
			a = scan.nextInt();
			w = scan.nextInt();
			h = scan.nextInt();
			if(w < h){
				int tmp = w;
				w = h;
				h = tmp;
			}
			for(int i = 0; i < a; i++){
				available_carpets[N][0] = w;
				available_carpets[N++][1] = h;
			}
		}
		boolean filled[][] = new boolean[W][H];
		if(can_fill(filled, 0, 0, available_carpets, N))
			System.out.println("yes");
		else
			System.out.println("no");
		System.exit(0);
	}
}
