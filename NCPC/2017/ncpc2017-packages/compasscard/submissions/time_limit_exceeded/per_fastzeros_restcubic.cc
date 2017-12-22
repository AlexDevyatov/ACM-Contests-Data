/* This solution quickly processes cards of zero uniqueness, and then
 * solves the rest (there are at most 3*360 cards left then) in cubic
 * time.  Ideally this should time out, but this implementation will
 * end up somewhere around the time limit in running time, and whether
 * or not it times out will depend on the precise hardware/compiler used.
 *
 * If it causes trouble, just remove it.
 */
#include <bits/stdc++.h>
using namespace std;

struct Card {
    int angle[3], ID;
};

int main(void) {
    int n;
    scanf("%d", &n);
    vector<Card> cards(n);
    for (auto &C: cards)
        scanf("%d%d%d%d", &C.angle[0], &C.angle[1], &C.angle[2], &C.ID);

    set<int> by_angle[3][360];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < 3; ++j)
            by_angle[j][cards[i].angle[j]].insert(i);

    set<pair<int, int>> zeros;
    for (int i = 0; i < n; ++i) {
        bool zero = true;
        for (int j = 0; j < 3; ++j)
            zero &= by_angle[j][cards[i].angle[j]].size() > 1;
        if (zero)
            zeros.insert(make_pair(-cards[i].ID, i));
    }

    while (!zeros.empty()) {
        int i, ID;
        tie(ID, i) = *zeros.begin();
        zeros.erase(zeros.begin());
        printf("%d\n", -ID);
        for (int j = 0; j < 3; ++j) {
            int a = cards[i].angle[j];
            by_angle[j][a].erase(i);
            if (by_angle[j][a].size() == 1) {
                int i = *by_angle[j][a].begin();
                zeros.erase(make_pair(-cards[i].ID, i));
            }
        }
    }

    vector<Card> left;
    for (int a = 0; a < 360; ++a)
        for (auto i: by_angle[0][a])
            left.push_back(cards[i]);

    while (!left.empty()) {
        int n = left.size();
        vector<int> uniq(n);
        for (int j = 0; j < 3; ++j) {
            for (int i = 0; i < n; ++i) {
                int nxt = i, next_val = 360;
                int prv = i, prev_val = 360;
                for (int k = 0; k < n; ++k) {
                    int nv = (left[k].angle[j] - left[i].angle[j] + 360) % 360;
                    int pv = (left[i].angle[j] - left[k].angle[j] + 360) % 360;
                    if (i != k && nv < next_val)
                        nxt = k, next_val = nv;
                    if (i != k && pv < prev_val)
                        prv = k, prev_val = pv;
                }
                uniq[i] += next_val + prev_val;
            }
        }
        int best = 0;
        for (int i = 0; i < n; ++i) {
            if (uniq[i] < uniq[best] || uniq[i] == uniq[best] && left[i].ID > left[best].ID)
                best = i;
        }
        printf("%d\n", left[best].ID);
        left.erase(left.begin() + best);
    }

    return 0;
}
