#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int h[200000];

int main(void) {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", h+i);
	sort(h, h+n);
	int r = n;
	for (int i = 0; i < n; ++i)
		r = min(r, h[i]+n-i-1);
	printf("%d\n", r);
	return 0;
}
