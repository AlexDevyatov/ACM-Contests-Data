#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int N, from, to, numP, r, dp[1000];
vector<int> adjList[1000];
map<string,int> nameToInt;
bool isProgram[1000], visited[1000];

int getName(string s) {
	if (nameToInt.find(s) == nameToInt.end()) {
		nameToInt[s] = nameToInt.size() - 1;
		isProgram[nameToInt[s]] = (s.length() >= 10 && s.rfind("::PROGRAM") == s.size() - 9);
	}
	return nameToInt[s];
}

bool dfs(int node) {
	if (visited[node]) return false;
	visited[node] = true;
	for (int next : adjList[node]) if (dfs(next)) return true;
	return false;
}

int main() {
	cin >> N;
	FOR(i, 0, N) {
		string fromS, toS;
		cin >> fromS >> numP;
		from = getName(fromS);
		FOR(j, 0, numP) {
			cin >> toS;
			to = getName(toS);
			adjList[to].push_back(from);
		}
	}
	FOR(i, 0, N) if (isProgram[i]) dfs(i);
	FOR(i, 0, N) if (visited[i]) r++;
	cout << N-r << endl;
	
	return 0;
}
