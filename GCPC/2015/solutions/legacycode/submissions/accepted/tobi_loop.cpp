#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int N, from, to, numP, r, dp[1000];
vector<int> adjList[1000];
unordered_map<string,int> nameToInt;
bool isProgram[1000], visited[1000];

int getName(string s) {
	if (nameToInt.find(s) == nameToInt.end()) {
		nameToInt[s] = nameToInt.size() - 1;
		isProgram[nameToInt[s]] = (s.length() >= 10 && s.rfind("::PROGRAM") == s.size() - 9);
	}
	return nameToInt[s];
}

void dfs(int node) {
	vector<int> todo;
	todo.push_back(node);
	unsigned int cur = 0;
	while (cur < todo.size()) {
		node = todo[cur++];
		for (int next : adjList[node]) if (!visited[next]) {
			visited[next] = true;
			todo.push_back(next);
		}
	}
}

int main() {
	scanf("%d", &N);
	FOR(i, 0, N) {
		char fromS[100], toS[100];
		scanf("%s %d", fromS, &numP);
		from = getName(fromS);
		FOR(j, 0, numP) {
			scanf("%s", toS);
			to = getName(toS);
			adjList[to].push_back(from);
		}
	}
	FOR(i, 0, N) if (isProgram[i] && !visited[i]) dfs(i);
	FOR(i, 0, N) if (visited[i] || isProgram[i]) r++;
	printf("%d\n", N-r);
	
	return 0;
}
