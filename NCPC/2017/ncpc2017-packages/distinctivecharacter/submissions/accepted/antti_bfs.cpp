#include <iostream>
#include <vector>

using namespace std;

int n, k;
int dist[1<<20];
vector<int> q;

int main() {
    cin >> n >> k;
    for (int b = 0; b < (1<<k); b++) {
        dist[b] = 999999999;
    }
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int u = 0;
        for (int j = 0; j < k; j++) {
            u += (1<<j)*(s[j]-'0');
        }
        dist[u] = 0;
        q.push_back(u);
    }
    int best;
    for (int i = 0; i < q.size(); i++) {
        int a = q[i];
        best = a;
        for (int j = 0; j < k; j++) {
            int b = a^(1<<j);
            if (dist[a]+1 < dist[b]) {
                dist[b] = dist[a]+1;
                q.push_back(b);
            }
        }
    }
    for (int j = 0; j < k; j++) {
        if (best&(1<<j)) cout << "1";
        else cout << "0";
    }
    cout << "\n";
}
