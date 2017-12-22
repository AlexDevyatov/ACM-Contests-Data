#include <bits/stdc++.h>
using namespace std;

struct Card {
    int angle[3], ID, uniqueness, idx;
    bool operator<(const Card &C) const {
        if (uniqueness != C.uniqueness) return uniqueness < C.uniqueness;
        return ID > C.ID;
    }
};

vector<Card> cards;
set<Card> cur;
set<pair<int, int>> by_angle[3];

void Update(int idx) {
    cur.erase(cards[idx]);

    int u = 0;
    const Card &C = cards[idx];
    for (int j = 0; j < 3; ++j) {
        int v = cards[idx].angle[j];
        auto jt = by_angle[j].find(make_pair(v, idx));
        auto it = jt++;
        if (it == by_angle[j].begin()) it = by_angle[j].end();
        if (jt == by_angle[j].end()) jt = by_angle[j].begin();
        --it;
        if (it->first != v && jt->first != v)
            u += 1 + (jt->first - it->first + 359) % 360;
    }
    cards[idx].uniqueness = u;

    cur.insert(cards[idx]);
}


int main(void) {
    int n;
    scanf("%d", &n);
    cards.resize(n);
    for (auto &C: cards)
        scanf("%d%d%d%d", &C.angle[0], &C.angle[1], &C.angle[2], &C.ID);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < 3; ++j)
            by_angle[j].insert(make_pair(cards[i].angle[j], i));

    for (int i = 0; i < n; ++i) {
        cards[i].idx = i;
        Update(i);
    }
    for (int i = 0; i < n; ++i) {
        Card C = *cur.begin();
        cur.erase(cur.begin());
        printf("%d\n", C.ID);
        if (i == n-1) break;
        for (int j = 0; j < 3; ++j) {
            auto it = by_angle[j].find(make_pair(C.angle[j], C.idx));
            by_angle[j].erase(it++);
            auto jt = it == by_angle[j].end() ? by_angle[j].begin() : it;
            if (it == by_angle[j].begin()) it = by_angle[j].end();
            --it;
            Update(it->second);
            Update(jt->second);
        }
    }
    return 0;
}
