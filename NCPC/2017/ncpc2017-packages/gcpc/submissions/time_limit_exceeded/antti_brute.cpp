#include <iostream>

using namespace std;

int n, m;
int count[101010];
int penalty[101010];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int t, p;
        cin >> t >> p;
        count[t]++;
        penalty[t] += p;
        int rank = 1;
        for (int j = 2; j <= n; j++) {
            if (count[j] < count[1]) continue;
            if (count[j] == count[1] && penalty[j] >= penalty[1]) continue;
            rank++;
        }
        cout << rank << "\n";
    }
}
