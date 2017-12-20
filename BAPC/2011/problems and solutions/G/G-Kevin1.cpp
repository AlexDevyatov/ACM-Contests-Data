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

int k, S;

void onerun(int z) {
	cin >> S >> k;
	if (k%2 == 1) cout << (S%2) << endl;
	else {
		if (S%(k+1) == k) cout << k << endl;
		else cout << ((S%(k+1))%2) << endl;
	}
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	for (int i = 1; i <= runs; i++) onerun(i);
	return 0;
}
