import java.util.*;
import java.io.*;

public class tobi_bufread_sb {
	public static void main(String args[]) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer strtok = new StringTokenizer(br.readLine());
		int W = Integer.parseInt(strtok.nextToken());
		int S = Integer.parseInt(strtok.nextToken());
		strtok = new StringTokenizer(br.readLine());
		int X = Integer.parseInt(strtok.nextToken());
		int Y = Integer.parseInt(strtok.nextToken());

		int Ws[][] = new int[W][X];
		for (int i = 0; i < W; i++) {
			strtok = new StringTokenizer(br.readLine());
			for (int j = 0; j < X; j++) {
				Ws[i][j] = Integer.parseInt(strtok.nextToken());
			}
		}

		int M[] = new int[X]; // initialized with 0
		for (int i = 0; i < S; i++) {
			strtok = new StringTokenizer(br.readLine());
			for (int j = 0; j < X; j++) {
				M[j] = Math.max(M[j], Integer.parseInt(strtok.nextToken()));
			}
		}

		StringBuilder sb = new StringBuilder(W*500);
		for (int i = 0; i < W; i++) {
			for (int j = 0; j < X; j++) {
				Ws[i][j] = Math.min(Ws[i][j], Y-M[j]);
				if (j != 0) {
					sb.append(" ");
				}
				sb.append(Ws[i][j]);
			}
			sb.append("\n");
		}
		System.out.print(sb.toString());
	}
}
