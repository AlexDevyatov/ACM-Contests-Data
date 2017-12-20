#include <stdlib.h>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits.h>

using namespace std;

int N, K;

void onerun() {
	cin >> N >> K;
	if (N == 1) cout << (K/2) << endl;
	else if (K - N <= (N+2)/3) cout << (K - N) << endl;
	else cout << ((K - (N-2)/3)/3) << endl;
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}