#include <iostream>
#include <string>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

int main()
{
    string t = "PER";
    string s; cin >> s;
    int res = 0;
    rep(i,0,s.size())
        res += s[i] != t[i % 3];

    cout << res << endl;
}
