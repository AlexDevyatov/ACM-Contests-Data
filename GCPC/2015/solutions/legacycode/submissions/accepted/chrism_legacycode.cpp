#include <vector>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <cstring>

using namespace std;


/*
 * Author: Christian Müller, TU Munich
 */
struct node {
	vector<int> edges;
};

int nextindex = 0;
int getIndex(string& id, unordered_map<string, int>& ids) {
	unordered_map<string, int>::iterator it=ids.find(id);
	if (it == ids.end()) {
		ids[id] = nextindex;
		nextindex++;
		return nextindex - 1;
	}
	return it->second;
}

int main(int argc, char **argv) {

	int n;

	ios_base::sync_with_stdio(false);
	cin >> n;

	unordered_map<string, int> ids;
	vector<int> starting;
	node nodes[n];

	for (int i = 0; i < n; i++) {
		string id;
		int k;
		cin >> id >> k;

		int to = getIndex(id, ids);

		if (id.substr(id.find("::") + 2, id.length()) == "PROGRAM") {
			starting.push_back(to);
		}

		for (int j = 0; j < k; j++) {
			string id2;
			cin >> id2;
			int from = getIndex(id2, ids);
			nodes[from].edges.push_back(to);
		}
	}

	// bfs
	bool visited[n];
        memset( visited, 0, n*sizeof(bool) );

	queue<int> q;
	for (int idx : starting) {
		q.push(idx);
		visited[idx]=true;
	}
	while (!q.empty()) {
		int idx = q.front();
		q.pop();
		for (int to : nodes[idx].edges) {
			if (!visited[to]) {
				q.push(to);
				visited[to]=true;
			}
		}
	}

	int result = 0;
	for (auto& vis : visited) {
		if (!vis) {
			result++;
		}
	}

	cout << result;
}
