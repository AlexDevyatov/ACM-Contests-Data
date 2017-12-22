#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
typedef pair<int, int> pii;

const int oo = 0x1f1f1f1f;
int t;
int w, e;
pii driver[2][300];

int mint[2][251][251][251];

int MinT(int w, int e, int last, int irr) {
	if (irr < 0) return oo;
	if (w == 0 && e == 0) return -oo;
	int &r = mint[last][w][e][irr];
	if (r == -1) {
		r = oo;
		if (last == 0 && w > 0) {
			r = max(min(MinT(w-1, e, 0, irr) + 3,
						MinT(w-1, e, 1, irr) + t),
					driver[0][w-1].first);
			if (r > driver[0][w-1].first+driver[0][w-1].second)
				r = max(min(MinT(w-1, e, 0, irr-1) + 3,
							MinT(w-1, e, 1, irr-1) + t),
						driver[0][w-1].first);
		} else if (last == 1 && e > 0) {
			r = max(min(MinT(w, e-1, 1, irr) + 3,
						MinT(w, e-1, 0, irr) + t),
					driver[1][e-1].first);
			if (r > driver[1][e-1].first+driver[1][e-1].second)
				r = max(min(MinT(w, e-1, 1, irr-1) + 3,
							MinT(w, e-1, 0, irr-1) + t),
						driver[1][e-1].first);
		}
		//		if (r < oo)	printf("MinT %d %d %d %d = %d\n",  w,e,last, irr, r);
	}
	return r;
}

int main(void) {
	int n;
	scanf("%d%d", &t, &n);
	for (int i = 0; i < n; ++i) {
		char foo[10];
		int a, r;
		scanf("%s%d%d", foo, &a, &r);
		if (*foo == 'W') driver[0][w++] = pii(a, r);
		else driver[1][e++] = pii(a,r);
	}
	memset(mint, -1, sizeof(mint));
	for (int irr = 0; irr <= n; ++irr)
		if (MinT(w, e, 0, irr) < oo ||
			MinT(w, e, 1, irr) < oo) {
			printf("%d\n", irr);
			break;
		}
	return 0;
}
