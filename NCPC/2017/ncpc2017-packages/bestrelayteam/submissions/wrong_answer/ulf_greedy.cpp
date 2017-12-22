#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<pair<pair<double, double>, string> > a(n);
	int first = 0;
	for (int i = 0; i < n; ++i) {
		cin >> a[i].second >> a[i].first.second >> a[i].first.first;
		if (a[i].first.second < a[first].first.second)
			first = i;
	}
	sort(a.begin(), a.end());
	double t = a[first].first.second;
	for (int j = 0, jj = 0; j < 3; ++j, ++jj) {
		if (jj == first)
			++jj;
		t += a[jj].first.first;
	}
	cout << t << endl << a[first].second << endl;
	for (int j = 0, jj = 0; j < 3; ++j, ++jj) {
		if (jj == first)
			++jj;
		cout << a[jj].second << endl;
	}
}