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
	char del = ' ';
	for (size_t i = 1; i < s.length(); i++)
	{
		if (s[i] < s[i - 1])
		{
			del = s[i - 1];
			break;
		}
	}
	if (del == ' ') del = s[s.length() - 1];
	for (size_t i = 0; i < s.length(); i++)
		if (s[i] != del) cout << s[i];
	cout << endl;
}