import static java.lang.Math.max;
public class brinky_it {


	public static void main(String[] args){
		String[] typeS = new String[130];
		char[] type = new char[130];
		int[] cost = new int[110];
		int[] fac = new int [110];
		
		int[][] tab = new int[110][10101];
		
		int g, c, n;
		java.util.Scanner sc = new java.util.Scanner(System.in);
		g = sc.nextInt();
		c = sc.nextInt();
		n = sc.nextInt();
		for(int i=0; i<n; ++i){
			String tmp;
			tmp = sc.next();
			fac[i] = sc.nextInt();
			cost[i] = sc.nextInt();
			typeS[i] = tmp;
		}
		for(int i=n; i-->0;){
			for(int go=c+1; go-->0;){
				for(int s=10001; s-->0;){
					int res = tab[go][s];
					int r = g - cost[i];
					switch(typeS[i]){
					case "greedy":
						if(s >= cost[i]){
							res = max(res, 1 + tab[go][s-cost[i]]);
						}
						tab[go][s] = res;
						if(go > 0){
							r = r / fac[i] * fac[i];
							res = max(res, 1 + tab[go-1][s+r]);
						}
						break;
					case "honest":
						if(s >= cost[i]){
							res = max(res, 1 + tab[go][s-cost[i]]);
						}
						tab[go][s] = res;
						if(go > 0){
							r = (r + fac[i]/2) / fac[i] * fac[i];
							res = max(res, 1 + tab[go-1][s+r]);
						}
						break;
					case "generous":
						if( s >= cost[i]){
							res = max(res, 1 + tab[go][s-cost[i]]);
						}else if(go > 0){
							r = (r + fac[i] - 1) / fac[i] * fac[i];
							res = max(res, 1 + tab[go-1][s+r]);
						}
						break;
					}
					tab[go][s] = res;
				}
			}
		}
		System.out.println(tab[c][0]);
	}
}
