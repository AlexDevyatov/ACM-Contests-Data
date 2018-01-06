#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

int main()
{
	freopen("viruses.in", "r", stdin);
	freopen("viruses.out", "w", stdout);
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	int ans = n - 1;
	for (int k = 1; k < n; k++)
	{
		bool f = true;
		for (int i = 0; i < n; i++)
		{
			for (int j = 1; j <= k; j++)
				if (i * k + j >= n) break;
				else
					if (a[i] < a[i * k + j]) 
					{
						f = false;
						break;
					}
		}
		if (f) 
		{
			cout << k;
            return 0;
		}
	}
	cout << 0;
}