#include <iostream>
#include <set>

using namespace std;

int n, m;
pair<int,int> score[101010];
multiset<pair<int,int>> better;

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int t, p;
        cin >> t >> p;
        auto old = score[t];
        score[t].first++;
        score[t].second -= p;
        if (t == 1) {
            while (better.size()) {
                auto first = better.begin();
                if (*first <= score[1]) {
                    better.erase(first);
                } else {
                    break;
                }
            }
        } else {
            if (old <= score[1] && score[t] > score[1]) {
                better.insert(score[t]);
            } else if (score[t] > score[1]) {
                better.erase(better.find(old));
                better.insert(score[t]);
            }
        }
        cout << better.size()+1 << "\n";
    }
}
