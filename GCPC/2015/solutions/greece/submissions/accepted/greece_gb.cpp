#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cfloat>
#include <climits>
#include <numeric>
#include <iomanip>

using namespace std;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const double PI = 2.0 * acos(0.0);


typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORS(i,a,b,s) for (int i = (a); i < (b); i=i+(s))
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)

#define MAXN 1000000
#define SMALLN 21

int N,T;
vi adj[MAXN];
vi w[MAXN];
vi sites;
map<int,int> toSite;

int sDist[SMALLN][SMALLN];

int esti[MAXN];

void dijk(int start){
	FOR(i,0,sz(sites)) sDist[toSite[start]][i] = sDist[i][toSite[start]] = -1;
	
	priority_queue<pii> queue;
	queue.push(make_pair(0,start));
	
	FOR(i,0,N) esti[i] = -oo;
	esti[start] = 0;
	
	while (queue.size()){
		pii v = queue.top();
		queue.pop();
		
		if (esti[v.second] != v.first) continue;
		if (toSite.count(v.second)) {
			sDist[toSite[start]][toSite[v.second]] = -v.first;
			sDist[toSite[v.second]][toSite[start]] = -v.first;
		}
		
		FOR(n,0,sz(adj[v.second])) {
			int nei = adj[v.second][n];
			int nd = v.first - w[v.second][n];
			if (nd > esti[nei]) {
				queue.push(make_pair(nd,nei));
				esti[nei] = nd;
			}
		}
	}
}

int dp[2<<SMALLN][SMALLN][2]; // last dimension says whether the taxis was used or not

int play(int n, int S, int s, int tx){
	//cout << "P " << n << " " << S << " " << s << " " << tx << endl;
	if (S==(1<<s)) return dp[S][s][tx] = sDist[s][0];
	int& v=dp[S][s][tx];
	if (v>=0) return v;
	v=oo;
	
	FOR(i,0,n) if (i!=s) if (S&(1<<i)) {
		v = min(v,sDist[s][i]+play(n,S-(1<<s),i,tx));
		if (tx) v = min(v,T+play(n,S-(1<<s),i,0));
	}
	
	return v;
}

void tsp(int n){
	memset(dp,-1,sizeof(dp));
	play(n,(1<<n)-1,0,1);
	play(n,(1<<n)-1,0,0);
}

int main(){
		int P,M,G;
		cin >> N >> P >> M >> G >> T;
		sites.clear();
		sites.push_back(0);
		toSite.clear();
		toSite[0] = 0;
		FOR(i,0,P){
			int s, _t; cin >> s >> _t;
			G -= _t;
			if (s) sites.push_back(s), toSite[s] = sz(sites) - 1;
		}
		FOR(i,0,N) adj[i].clear(), w[i].clear();
		FOR(i,0,M){
			int s,d,t;
			cin >> s >> d >> t;
			adj[s].push_back(d);
			w[s].push_back(t);
			adj[d].push_back(s);
			w[d].push_back(t);
		}
		// run dijkstra for every node
		FOR(i,0,sz(sites))
			dijk(sites[i]);
		
		int nS = sz(toSite); 
		
		/*FOR(i,0,nS) {
			FOR(j,0,nS)
				cout << sDist[i][j] << " ";
			cout << endl;
		}*/
		
		tsp(nS);
		//cout << "G " << G << endl;
		//cout << "R " << dp[(1<<nS)-1][0][0] << " " << dp[(1<<nS)-1][0][1] << endl; 
		
		if (dp[(1<<nS)-1][0][1] > G) cout << "impossible" << endl;
		else if (dp[(1<<nS)-1][0][0] <= G) cout << "possible without taxi" << endl;
		else cout << "possible with taxi" << endl;
}
