#include <algorithm>
#include <iostream>

using namespace std;

const int oo = 0x3f3f3f3f;

#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int main(){
	int N, M, K, temp, s, t, d;
	cin >> N >> M >> K;
	vector<vector<pair<int,int> > > adjl(N);
	while(K-->0)cin >> temp;
	while(M-->0){
		cin >> s >> t >> d;
		adjl[--s].push_back(make_pair(--t,d));
		adjl[t].push_back(make_pair(s,d));
	}
#if 0
	FOR(i,0,N){
		sort(all(adjl[i])); 
		auto last = unique(all(adjl[i]));
		adjl[i].erase(last, adjl[i].end());
	}
#endif
	vector<bool> multiple_solutions(N, false);
	vector<int> dist(N,oo);
	vector<bool> done(N,false);
	dist[0] = 0;
	while(true){
		int n = -1;
		FOR(i,0,N)if(!done[i])if(n==-1||dist[i]<dist[n])n = i;
		if(n == -1)break;
		if(dist[n] == oo)break;
		for(auto ed: adjl[n]){
			if(dist[ed.first] > dist[n]+ed.second){
				dist[ed.first]=dist[n]+ed.second;
				multiple_solutions[ed.first] = multiple_solutions[n];
			} else if(dist[ed.first] == dist[n] + ed.second){
				multiple_solutions[ed.first] = true;
			}
		}
		done[n] = true;
	}
	cout << (multiple_solutions[N-1]?"yes":"no") << endl;
	return 0;
}
