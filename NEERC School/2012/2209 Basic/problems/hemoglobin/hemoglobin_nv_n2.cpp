#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>

using namespace std;

int main()
{
	freopen("hemoglobin.in", "r", stdin);
	freopen("hemoglobin.out", "w", stdout);
	int n;
	scanf("%d\n", &n);
	vector<long long> a(n + 1);
	int si = 0;
	for (int i = 0; i < n; i++)
	{
		char c;
		scanf("%c", &c);
		if (c == '+')
		{
			int x;
			scanf("%d\n", &x);
			a[si++] = x;
		}
		if (c == '-')
		{
			scanf("\n");
            printf("%lld\n", a[--si]);
		}
		if (c == '?')
		{
			int k;
			scanf("%d\n", &k);
			long long ans = 0;
			for (int i = 0; i < k; i++)
				ans += a[si - i - 1];
			printf("%lld\n", ans);
		}
	}
}
