#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int T1[300000], T2[300000];
int Hay[500000], Needle[300000];


bool find(int H, int N) {
	int fail[300000];
	
	fail[0] = -1;
	for (int i = 1; i < N; ++i) {
		int k = fail[i-1];
		while (k >= 0 & Needle[k+1] != Needle[i])
			k = fail[k];
		if (Needle[k+1] == Needle[i])
			fail[i] = k+1;
		else
			fail[i] = -1;
	}

	int j = -1;
	for (int i = 0; i < H; ++i) {
		while (j != -1 && Needle[j+1] != Hay[i])
			j = fail[j];
		if (Needle[j+1] == Hay[i])
			++j;
		if (j == N-1)
			return true;
	}
	return false;
}

int main(void) {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", T1+i);
	for (int i = 0; i < n; ++i)
		scanf("%d", T2+i);
	sort(T1, T1+n);
	sort(T2, T2+n);

	for (int i = 1; i < 2*n; ++i)
		Hay[i-1] = (T1[i % n]-T1[(i-1)%n] + 360000) % 360000;
	for (int i = 1; i < n; ++i)
		Needle[i-1] = T2[i]-T2[i-1];

	printf("%spossible\n", find(2*n-1, n-1) ? "" : "im");
	
}
