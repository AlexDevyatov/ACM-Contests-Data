#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

bool check(int n, int C) {
	long long cur = 0;
	for (int i = 0; i < n; ++i) {
		int l, e, w;
		scanf("%d%d%d", &l, &e, &w);
		if (cur-l < 0) return false;
		cur = cur-l+e;
		if (cur > C) return false;
		if (w > 0 && cur < C) return false;
	}
	if (cur != 0) return false;
	return true;
}

int main(void) {
	int C, n;
	scanf("%d%d", &C, &n);
	printf("%spossible\n", check(n, C) ? "" : "im");
	return 0;
}
