#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

typedef vector<int> vi;

vi adj[300000];
int val[300000];
bool ok;

void prop(int v, int c) {
	if (val[v] != -1) {
		ok &= val[v] == c;
		return;
	}
	val[v] = c;
	for (auto w: adj[v]) {
		prop(w, val[v]^1);
	}
}

void setit(int v, int c) {
	if (val[v] != -1 && val[v] != c) ok = false;
	val[v] = c;
}

int main(void) {
	int n, m;
	scanf("%d%d", &n, &m);
	memset(val, -1, sizeof(val));
	ok = true;
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		if (c == 2) { 
			setit(a, 1); 
			setit (b, 1);
		}
		else if (c == 0) {
			setit(a, 0);
			setit(b, 0);
		}
		else { 
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
	}
	for (int i = 1; ok && i <= n; ++i)
		if (val[i] != -1) 
			for (auto w: adj[i])
				prop(w, val[i]^1);
	int cmp = 2;
	for (int i = 1; ok && i <= n; ++i)
		if (val[i] == -1) {
			prop(i, cmp);
			cmp += 2;
		}
	if (!ok) {
		printf("impossible\n");
	} else {
		int cnt[cmp];
		memset(cnt, 0, sizeof(int)*cmp);
		for (int i = 1; i <= n; ++i) {
			++cnt[val[i]];
		}
		int res = cnt[1];
		for (int t = 2; t < cmp; t += 2)
			res += min(val[t], val[t+1]);
		printf("%d\n", res);
	}
	return 0;
}
