#include <bits/stdc++.h>
using namespace std;

int dp[101][10001], p[100], c[100], generous[100];

int main() {
	int G, g0, n; cin >> G >> g0 >> n;
	for (int i = 0; i < n; i++) {
		string type; int pack;
		cin >> type >> pack >> p[i];
		int m = type == "greedy" ? 0 : type == "honest" ? pack/2 : pack-1;
		generous[i] = type == "generous";
		c[i] = (G - p[i] + m) / pack * pack;
	}
	for (int i = n-1; i >= 0; i--)
		for (int g = g0; g >= 0; g--) for (int s = G*g0; s >= 0; s--) {
			if (s >= p[i])  dp[g][s] = max(dp[g][s],1+dp[g][s-p[i]]);
			if (g > 0 && s+c[i] <= G*g0 && (!generous[i] || s < p[i]))
				dp[g][s] = max(dp[g][s],1+dp[g-1][s+c[i]]);
		}
	cout << dp[g0][0] << endl;
}
	
