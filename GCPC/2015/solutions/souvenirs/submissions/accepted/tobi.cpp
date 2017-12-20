#include <iostream>
#include <string>

using namespace std;

int g, c, n, pac[100], pric[100], dp[101][105*100][100];
string type[100];

int rec(int gold, int silver, int cur) {
	if (cur >= n) return 0;
	if (dp[gold][silver][cur] != 0) return dp[gold][silver][cur] - 1;
	int diff = g-pric[cur];
	int off = 0;
	if (type[cur][1] == 'e') off = pac[cur] - 1;
	else if (type[cur][1] == 'o') off = pac[cur]/2;
	int back = pac[cur]*((diff + off)/pac[cur]);
	if (silver >= pric[cur]) dp[gold][silver][cur] = 1 + rec(gold, silver-pric[cur], cur+1);
	if (gold >= 1 && (silver < pric[cur] || type[cur][1] != 'e')) dp[gold][silver][cur] = max(dp[gold][silver][cur], 1 + rec(gold - 1, silver + back, cur+1)); 
	dp[gold][silver][cur] = max(dp[gold][silver][cur], rec(gold, silver, cur+1)) + 1;
	return dp[gold][silver][cur] - 1;
}

int main() {
	cin >> g >> c >> n;
	for (int i = 0; i < n; i++) cin >> type[i] >> pac[i] >> pric[i];
	cout << rec(c, 0, 0) << endl;
	return 0;
}
