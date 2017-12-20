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

lli N;

void onerun() {
	cin >> N;
	lli solX = -1, solY = -1;
	for (lli i = 1; i * i <= N; i++) {
		if (N%i != 0) continue;
		lli j = N/i;
		if ((i+j)%2 == 1) continue;
		solX = (j-i)/2;
		solY = (i+j)/2;
	}
	if (solX == -1) cout << "IMPOSSIBLE" << endl;
	else cout << solX << " " << solY << endl;
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}