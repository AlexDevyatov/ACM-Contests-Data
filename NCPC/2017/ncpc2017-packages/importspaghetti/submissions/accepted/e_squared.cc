#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;


map<string, int> name_idx;
string names[1501];
vector<int> adj[1501];
int n;

int lookup(string name) {
    int &res = name_idx[name];
    if (!res) {
        res = name_idx.size();
        names[res-1] = name;
    }
    return res-1;
}

int bfs(int u, int v, bool print = false) {
    int q[1501], qh = 0, qt = 0;
    int d[1501], b[1501];
    q[qh++] = u;
    memset(d, 0x1f, sizeof(d));
    memset(b, -1, sizeof(b));
    d[u] = 0;
    //    printf("bfs %d %d\n", u, v);
    while (d[v] > n && qh > qt) {
        int x = q[qt++];
        //        printf("  vis %d dst %d\n", x, d[x]);
        for (int y: adj[x]) {
            if (d[y] > d[x] + 1) {
                d[y] = d[x] + 1;
                q[qh++] = y;
                b[y] = x;
            }
        }
    }
    if (print) {
        int x = v;
        while (b[x] != -1) {
            printf("%s ", names[x].c_str());
            x = b[x];
        }
        printf("%s\n", names[x].c_str());
    }
    return d[v];
}

int main(void) {
    string str;
    cin >> n;
    getline(cin, str);
    getline(cin, str);
    int m = 0;
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> str >> k;
        int u = lookup(str);
        getline(cin, str);
        for (int i = 0; i < k; ++i) {
            getline(cin, str);
            istringstream in(str);
            in >> str;
            while (in >> str) {
                if (str.back() == ',') str.pop_back();
                adj[lookup(str)].push_back(u);
                ++m;
            }
        }
    }
    fprintf(stderr, "%d edges\n", m);
    int bu = -1, bv = -1, bd = 2*n;
    for (int u = 0; u < n; ++u)
        for (int v: adj[u]) {
            int val = bfs(v, u);
            if (val < bd) {
                bu = u;
                bv = v;
                bd = val;
            }
        }
    if (bu != -1) {
        bfs(bv, bu, true);
    } else
        printf("SHIP IT\n");
}
