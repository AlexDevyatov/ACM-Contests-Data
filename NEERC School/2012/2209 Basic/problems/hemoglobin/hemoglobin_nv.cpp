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
	vector<long long> sum(n + 1);
	stack<long long> a;
	for (int i = 0; i < n; i++)
	{
		char c;
		scanf("%c", &c);
		if (c == '+')
		{
			int x;
			scanf("%d\n", &x);
			a.push(x);
			sum[a.size()] = sum[(int)a.size() - 1] + a.top();
		}
		if (c == '-')
		{
			scanf("\n");
            printf("%lld\n", a.top());
			a.pop();
		}
		if (c == '?')
		{
			int k;
			scanf("%d\n", &k);
			printf("%lld\n", sum[a.size()] - sum[a.size() - k]);
		}
	}
}
