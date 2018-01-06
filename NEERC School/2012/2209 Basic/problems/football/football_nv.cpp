#include <cstdio>
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

int main()
{
    freopen("football.in", "r", stdin);
    freopen("football.out", "w", stdout);
    int n;
    cin >> n;
    assert(0 <= n && n <= 100);
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        assert(s.length() == 3);
        assert(s[1] == ':');
        assert(isdigit(s[0]) && isdigit(s[2]));
        int x = s[0] - '0';
        int y = s[2] - '0';
        int ans1 = 0, ans2 = 0;
        for (int j = 0; j < 10; j++)
            for (int k = 0; k < 10; k++)
                if (x + j < y + k) ans2++;
                else
                    if (x + j > y + k) ans1++;
                    else
                        if (y > j) ans2++;
                        else
                            if (j > y) ans1++;
        assert(ans1 + ans2 == 99);
        cout << ans1 << " " << ans2 << endl;
    }
}