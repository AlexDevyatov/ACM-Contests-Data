#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<pair<pair<double, double>, string> > a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i].second >> a[i].first.second >> a[i].first.first;
	}
	sort(a.begin(), a.end());
	int first = 0;
	double btime = 1e100;
	for (int i = 0; i < n; ++i) {
		double t = a[i].first.second;
		for (int j = 0, jj = 0; j < 3; ++j, ++jj) {
			if (jj == i)
				++jj;
			t += a[jj].first.first;
		}
		if (t < btime) {
			btime = t;
			first = i;
		}
	}
	cout << btime << endl << a[first].second << endl;
	for (int j = 0, jj = 0; j < 3; ++j, ++jj) {
		if (jj == first)
			++jj;
		cout << a[jj].second << endl;
	}
}