#include <bits/stdc++.h>
using namespace std;

map<string, int> name_idx;
string names[1501];
int dst[1501][1501];
int n;

int lookup(string name) {
    int &res = name_idx[name];
    if (!res) {
        res = name_idx.size();
        names[res-1] = name;
    }
    return res-1;
}

void printpath(int u, int v) {
    for (int i = 0; i < n; ++i)
        if (dst[u][i] == 1 && (dst[i][v] == dst[u][v] - 1 || dst[u][v] == 1)) {
            printf("%s ", names[u].c_str());
            if (dst[u][v] > 1)
                printpath(i, v);
            break;
        }
}

int main(void) {
    string str;
    cin >> n;
    getline(cin, str);
    getline(cin, str);
    memset(dst, 0x1f, sizeof(dst));
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
                dst[u][lookup(str)] = 1;
            }
        }
    }
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                dst[i][j] = min(dst[i][j], dst[i][k] + dst[k][j]);
    int s = 0;
    for (int i = 0; i < n; ++i)
        if (dst[i][i] < dst[s][s])
            s = i;
    if (dst[s][s] <= n)
        printpath(s, s);
    else
        printf("SHIP IT\n");
}
