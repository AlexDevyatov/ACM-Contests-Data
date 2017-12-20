#include <stdlib.h>
#include <vector>
#include <queue>
#include <set>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits.h>

typedef long long int lli;

using namespace std;

struct Sol {
	int north, east, south, west;
	bool operator<(const Sol& r) const {
		if (north != r.north) return (north < r.north);
		if (east != r.east) return (east < r.east); 
		if (south != r.south) return (south < r.south); 
		return (west < r.west); 
	}
};

Sol makeSol(int n, int e, int s, int w) {
	Sol S; S.north = n; S.east = e; S.south = s; S.west = w;
	return S;
}

lli L, W, B;
lli Sx, Sy;
lli fx, fy;

void onerun() {
	cin >> L >> W >> B;
	cin >> Sx >> Sy;
	cin >> fx >> fy;

	if (L < 3 || L > 100 || W < 3 || W > 100 || B < 0 || B > 100000) cout << "ERROR" << endl;
	if (Sx < 1 || Sx >= L || Sy < 1 || Sy >= W || fx < 1 || fx >= L || fy < 1 || fy >= W) cout << "ERROR" << endl;
	if (Sx == fx && Sy == fy) cout << "ERROR" << endl;

	set<Sol> Q;
	lli minD = LLONG_MAX;

	for (lli i = -B; i <= B; i++) {
		lli j1 = B - (i >= 0 ? i : -i);
		lli j2 = (i >= 0 ? i : -i) - B;
		lli rx = (i >= 0 ? (((i+1)/2) * 2 * L + (i%2 == 0 ? fx : -fx)) : ((i/2) * 2 * L + (i%2 == 0 ? fx : -fx)));
		lli ry1 = ((j1+1)/2) * 2 * W + (j1%2 == 0 ? fy : -fy);
		lli ry2 = (j2/2) * 2 * W + (j2%2 == 0 ? fy : -fy);
		lli D1 = (Sx - rx) * (Sx - rx) + (Sy - ry1) * (Sy - ry1);
		lli D2 = (Sx - rx) * (Sx - rx) + (Sy - ry2) * (Sy - ry2);
		if (D1 <= minD) {
			if (D1 < minD) Q.clear();
			minD = D1;
			Q.insert(makeSol((j1+1)/2, (i >= 0 ? (i+1)/2 : (-i)/2), j1/2, (i < 0 ? (-i+1)/2 : i/2)));
		}
		if (D2 <= minD) {
			if (D2 < minD) Q.clear();
			minD = D2;
			Q.insert(makeSol((-j2)/2, (i >= 0 ? (i+1)/2 : (-i)/2), (-j2+1)/2, (i < 0 ? (-i+1)/2 : i/2)));
		}
	}

	for (set<Sol>::iterator it = Q.begin(); it != Q.end(); it++) cout << it->north << " " << it->east << " " << it->south << " " << it->west << endl;
	cout << "0" << endl;
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}