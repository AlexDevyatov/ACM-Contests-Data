#include <iostream>
#include <iomanip>
#include <cmath>
#define rep(i,a,b) for(int i=a;i<b;++i)
#define Cout if(DEBUG) cout
using namespace std;
typedef double fl;

const bool DEBUG = false;

fl dp[8]; //dp[i]: earliest time one can be standing still just behind light number i. We start just behind light 0, and light n is always green.

int t[10], g[10], r[10];
int n;

bool is_green(int i, fl T) {
	if(i == n) return true;
	int t0 = int(T);
	if(t0 < t[i]) return false; //REALLY?
	t0 -= t[i];
	t0 %= (r[i] + g[i]);
	return t0 < g[i];
}

bool is_fine(int i, int j, fl T) { //is it possible to travel from i to j with one button press starting at time T?
	for(int u = i+1; u <= j; ++u) {
		//would we violate light nr u?
		//we would pass that light at time sqrt(2*1000*(u-l))
		fl t = T+sqrt(2000 * (u-i));
		if(!is_green(u, t)) {
			Cout << "cannot go from " << i << " to " << j << " starting at " << T << "; would violate light " << u << " (t = " << t << ")" << endl;
			return false;
		}
	}
	return true;
}

int main() {
	cin >> n;
	rep(i,1,n) 
		cin >> t[i] >> g[i] >> r[i];
	cout << setprecision(10);
	dp[0] = 0;
	dp[1] = dp[2] = dp[3] = dp[4] = dp[5] = dp[6] = 10000000;//FIX	
	for(int m = 1; m <= n; ++m) {
		for(int l = m-1; l >= 0; --l) {
			Cout << "trying " << l << " -> " << m << endl;
			//try to start at l and go to m
			//is it possible directly?
			bool possible = is_fine(l, m, dp[l]);
			if(possible) {
				Cout << "can go directly!" << endl;
				dp[m] = dp[l] + sqrt(2000*(m-l));
			} else {
				Cout << "cannot go directly"<<endl;
			//if not, then move (adjusting the starting time from l) so as to pass light nr u just as it turns green
			for(int u = l+1; u < m; ++u) {
				//go through green times p at light u
				int p = t[u];
				fl t0;
				do {
					//when would we have to start at light l? Put answer in t0
					t0 = fl(p) - sqrt(2*1000*(u-l));
					Cout << "try to pass light nr "<< u << " at time " << p << ". Have to start at " << t0 << " in that case." << endl;
					if(is_fine(l, m, t0)) {
						Cout << "IS FINE" << endl;
						dp[m] = min(dp[m], t0 + sqrt(2000*(m-l)));
						break;
					}
					p += (r[u] + g[u]);	
				} while(t0 < dp[m]);
			}
			}
		}
	}
	cout << dp[n] << endl;
	return 0;
}
