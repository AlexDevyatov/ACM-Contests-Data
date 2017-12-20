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

int P, N;
int A[1005];

void onerun() {
	cin >> P >> N;
	for (int i = 0; i < N; i++) cin >> A[i];
	sort(A, A+N);
	int S = 0;
	for (int i = 1; i <= N/(P+1); i++) S += A[N-i];
	cout << S << endl;
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}