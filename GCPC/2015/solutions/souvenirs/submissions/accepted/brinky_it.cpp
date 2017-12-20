#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

char type[130];
int cost[110];
int fac[110];

int tab[110][10101];

int g, c, n;

int main(){
	scanf("%d %d %d", &g, &c, &n);
	for(int i=0; i<n; ++i){
		char tmp[20];
		scanf("%s %d %d", tmp, &fac[i], &cost[i]); 
		switch(tmp[1]){
			case 'r':
				type[i] = 'g';
				break;
			case 'o':
				type[i] = 'h';
				break;
			case 'e':
				type[i] = 'G';
				break;
		}
	}
	for(int i=n; i-->0;){
		for(int go=c+1; go-->0;){
			for(int s=(c+1-go)*g; s-->0;){
				int &res = tab[go][s];
				int r = g - cost[i];
				switch(type[i]){
					case 'g':
						if(s >= cost[i]){
							res = max(res, 1 + tab[go][s-cost[i]]);
						}
						if(go > 0){
							r = r / fac[i] * fac[i];
							res = max(res, 1 + tab[go-1][s+r]);
						}
						break;
					case 'h':
						if(s >= cost[i]){
							res = max(res, 1 + tab[go][s-cost[i]]);
						}
						if(go > 0){
							r = (r + fac[i]/2) / fac[i] * fac[i];
							res = max(res, 1 + tab[go-1][s+r]);
						}
						break;
					case 'G':
						if( s >= cost[i]){
							res = max(res, 1 + tab[go][s-cost[i]]);
						}else if(go > 0){
							r = (r + fac[i] - 1) / fac[i] * fac[i];
							res = max(res, 1 + tab[go-1][s+r]);
						}
						break;
				}
			}
		}
	}
	printf("%d\n", tab[c][0]);
}
