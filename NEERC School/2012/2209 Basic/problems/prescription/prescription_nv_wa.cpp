#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

int main()
{
	freopen("prescription.in", "r", stdin);
	freopen("prescription.out", "w", stdout);
	string s;
	cin >> s;
	string ans = s;
	for (char c = 'a'; c <= 'z'; c++)
	{
		string tmp = "";
		for (size_t i = 0; i < s.length(); i++)
			if (s[i] != c) tmp += s[i];
		ans = min(ans, tmp);
	}
	cout << ans;
}