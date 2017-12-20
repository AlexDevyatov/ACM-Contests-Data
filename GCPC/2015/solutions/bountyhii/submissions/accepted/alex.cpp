#include <algorithm>
#include <iostream>

using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)

bool find_match(vector<vector<int> > & adj, int n, vector<int> & prev, vector<bool> & visited){
	if(n == -1)return true;
	if(visited[n])return false;
	visited[n] = true;
	for(auto to: adj[n])if(find_match(adj, prev[to], prev, visited)){
		prev[to] = n;
		return true;
	}
	return false;
}

int max_matching(vector<vector<int> > & adj, int N){
	vector<int> prev(N, -1);
	int res = 0;
	FOR(n,0,N){
		vector<bool> visited(N, false);
		if(find_match(adj, n, prev, visited))++res;
	}
	return res;
}

int main() {
	int N, K;
	cin >> N;
	vector<vector<int> > adj(N);
	FOR(i,0,N){
		cin >> K;
		adj[i] = vector<int>(K);
		FOR(k,0,K)cin >> adj[i][k];
	}
	cout << N - max_matching(adj, N) << endl;
	return 0;
}
