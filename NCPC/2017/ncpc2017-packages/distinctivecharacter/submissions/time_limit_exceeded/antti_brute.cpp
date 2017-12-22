#include <iostream>
#include <vector>

using namespace std;

int n, k;
vector<int> v;

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int x = 0;
        for (int j = 0; j < k; j++) {
            x += (1<<j)*(s[j]-'0');
        }
        v.push_back(x);
    }
    int p = -1, c;
    for (int b = 0; b < (1<<k); b++) {
        int u = k;
        for (int i = 0; i < n; i++) {
            u = min(u,__builtin_popcount(v[i]^b));
        }
        if (u > p) {
            p = u;
            c = b;
        }
    }
    for (int j = 0; j < k; j++) {
        if (c&(1<<j)) cout << "1";
        else cout << "0";
    }
    cout << "\n";
}
