#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <stdio.h>
#include <assert.h>

using namespace std;

struct StackSum 
{
	StackSum()
	{
		st = vector<long long>();
		sum = vector<long long>();
		st.push_back(0);
		sum.push_back(0);
	}

	void push(long long x)
	{
		st.push_back(x);
		sum.push_back(sum.back() + x);
	}

	long long pop() 
	{
		sum.pop_back();
		long long res = st.back();
		st.pop_back();
		return res;
	}

	long long get(int k)
	{
		return sum[sum.size() - 1] - sum[sum.size() - k - 1];
	}

	int size()
	{
		assert(sum.size() == st.size());
		return st.size();
	}

	vector<long long> st;
	vector<long long> sum;
};


int main()
{
	freopen("hemoglobin.in", "r", stdin);
	ofstream out("hemoglobin.out");

	int n;
	scanf("%d\n", &n);
	assert(n > 0 && n < 100001);

	StackSum ss = StackSum();
	char oper;
	int x;
	int k;

	for (int i = 0; i < n; i++) 
	{
		scanf("%c", &oper);
		if (oper == '+')
		{
			scanf("%d\n", &x);
			ss.push(x);
			assert(x > 0 && x < 1000000001);
		} else
		if (oper == '-') 
		{
			scanf("\n");
			out << ss.pop() << '\n';
		}
		else
		if (oper == '?')
		{
			scanf("%d\n", &k);
			out << ss.get(k) << '\n';
			assert(k < ss.size());
		} else
		{
			assert(false);
		}
	}

	return 0;
}
