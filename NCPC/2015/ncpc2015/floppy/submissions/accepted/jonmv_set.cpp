#include <iostream>
#include <set>

using namespace std;

int main() {
	int f; cin >> f;
	set<int> ok, dok;
	while (f--) {
		int t, n; cin >> t >> n;
		ok.clear();
		for (auto i = 0; i <= t; i++)
			ok.insert(i);
 		while (n--) {
			int s, e; cin >> s >> e;
			dok.clear();
			for (auto i : ok) {
				if (i - e + s >= 0)
					dok.insert(i - e + s);
				if (i + e - s <= t)
					dok.insert(i + e - s);
			}
			if (dok.empty()) {
				cout << "impossible\n";
				return 0;
			}
			swap(ok, dok);
		}
	}
	cout << "possible\n";
	return 0;
}