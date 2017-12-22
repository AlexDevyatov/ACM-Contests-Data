#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

typedef pair<int,int> pii;

int x[2000];
int cid[2000];

int steps(int s, int t, int id) {
	cid[s] = id;
	if (s == t) return 0;
	return 1 + steps(x[s], t, id);
}

int main(void) {
	int k, n;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) 
		scanf("%d", x+i);
	vector<pii> cycles;
	memset(cid, -1, sizeof(cid));
	for (int i = 1; i <= n; ++i) {
		//		printf("follow %d\n", i);
		int at = i;
		int seen[2000] = {0};
		while (!seen[at]) {
			seen[at] = true;
			at = x[at];
		}
		if (cid[at] != -1) continue;
		int l = 1 + steps(x[at], at, cycles.size());
		//		printf("reach %d, cyclen %d\n", at, l);
		cycles.push_back(pii(l, 0));
	}
	for (int i = 1; i <= n; ++i)
		if (cid[i] == -1) {
			int at = i;
			while (cid[at] == -1)
				at = x[at];
			++cycles[cid[at]].second;
		}

	int cando[2000];
	memset(cando, 0, sizeof(cando));
	cando[0] = true;
	for (auto p: cycles) {
		for (int v = k-1; v >= 0; --v) {
			if (cando[v])
				for (int x = p.first; x <= k && x <= p.first+p.second; ++x)
					cando[v+x] = true;
		}
	}
	for (int x = k; x>= 0; --x)
		if (cando[x]) {
			printf("%d\n", x);
			break;
		}
	return 0;
}
