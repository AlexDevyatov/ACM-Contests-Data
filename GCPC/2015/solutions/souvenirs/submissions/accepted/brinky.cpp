#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

char type[130];
int cost[110];
int fac[110];

int tab[110][110][10100];

int g, c, n;

int rek(int i, int go, int s){
	if(i == n){
		return 0;
	}
	if(tab[i][go][s] != -1)
		return tab[i][go][s];
	int &res = tab[i][go][s];
	res = rek(i+1, go, s);
	int r = g - cost[i];
	switch(type[i]){
		case 'g':
			if(s >= cost[i]){
				res = max(res, 1 + rek(i+1, go, s-cost[i]));
			}
			if(go > 0){
				r = r / fac[i] * fac[i];
				res = max(res, 1 + rek(i+1, go-1, s+r));
			}
			break;
		case 'h':
			if(s >= cost[i]){
				res = max(res, 1 + rek(i+1, go, s-cost[i]));
			}
			if(go > 0){
				r = (r + fac[i]/2) / fac[i] * fac[i];
				res = max(res, 1 + rek(i+1, go-1, s+r));
			}
			break;
		case 'G':
			if( s >= cost[i]){
				res = max(res, 1 + rek(i+1, go, s-cost[i]));
			}else if(go > 0){
				r = (r + fac[i] - 1) / fac[i] * fac[i];
				res = max(res, 1 + rek(i+1, go-1, s+r));
			}
			break;
	}
	return res;
}

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
	memset(tab, -1, sizeof(tab));
	int res = rek(0, c, 0);
	printf("%d\n", res);
}
