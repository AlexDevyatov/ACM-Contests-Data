#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int N, from, to, numP, r;
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
	vector<int> todo;
	todo.push_back(node);
	unsigned int cur = 0;
	while (cur < todo.size()) {
		node = todo[cur++];
		if (isProgram[node]) return true;
		for (int next : adjList[node]) if (!visited[next]) {
			visited[next] = true;
			todo.push_back(next);
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> N;
	FOR(i, 0, N) {
		string fromS, toS;
		cin >> fromS >> numP;
		from = getName(fromS);
		FOR(j, 0, numP) {
			cin >> toS;
			to = getName(toS);
			adjList[from].push_back(to);
		}
	}
	FOR(i, 0, N) {
		fill_n(visited, N, false);
		if (dfs(i)) r++;
	}
	cout << N-r << endl;

	return 0;
}
