#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
	freopen("experimental.in", "r", stdin);
	freopen("experimental.out", "w", stdout);
	int n, m;
	cin >> n >> m;
	vector< pair<int, int> > a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i].first >> a[i].second;
	vector<int> b(m);
	for (int i = 0; i < m; i++)
		cin >> b[i];
	for (int i = 0; i < (1 << n); i++)
	{
		vector<int> c(m);
		for (int j = 0; j < n; j++)
			if (i & (1 << j)) c[a[j].first - 1]++;
			else c[a[j].second - 1]++;
		bool f = true;
		for (int j = 0; j < m; j++)
			f &= (b[j] == c[j]);
		if (f)
		{
			for (int j = 0; j < n; j++)
				if (i & (1 << j)) cout << a[j].first << " ";
				else cout << a[j].second << " ";
			return 0;
		}
	}
	cout << "-1\n";
}