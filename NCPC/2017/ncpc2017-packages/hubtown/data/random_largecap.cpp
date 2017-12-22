#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Angle {
	int x, y;
	int t;
	Angle(int x, int y, int t=0) : x(x), y(y), t(t) {}
	Angle operator-(Angle a) const { return {x-a.x, y-a.y, t}; }
	int quad() const {
		assert(x || y);
		if (y < 0) return (x >= 0) + 2;
		if (y > 0) return (x <= 0);
		return (x <= 0) * 2;
	}
	Angle t90() const { return {-y, x, t + (quad() == 3)}; }
	Angle t180() const { return {-x, -y, t + (quad() >= 2)}; }
	Angle t360() const { return {x, y, t + 1}; }
};
bool operator<(Angle a, Angle b) {
	// add a.dist2() and b.dist2() to also compare distances
	return make_tuple(a.t, a.quad(), a.y * (ll)b.x) <
	       make_tuple(b.t, b.quad(), a.x * (ll)b.y);
}
bool operator>=(Angle a, Angle b) { return !(a < b); }
bool operator>(Angle a, Angle b) { return b < a; }
bool operator<=(Angle a, Angle b) { return !(b < a); }

// Given two points, this calculates the smallest angle between
// them, i.e., the angle that covers the defined line segment.
pair<Angle, Angle> segmentAngles(Angle a, Angle b) {
	if (b < a) swap(a, b);
	return (b < a.t180() ?
	        make_pair(a, b) : make_pair(b, a.t360()));
}

Angle operator+(Angle a, Angle b) { // where b is a vector
	Angle r(a.x + b.x, a.y + b.y, a.t);
	if (r > a.t180()) r.t--;
	return r.t180() < a ? r.t360() : r;
}

int S = 800;

int main() {
    srand(time(NULL));
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);

    set<Angle> angset;
    rep(i,-S,S+1) {
        rep(j,-S,S+1) {
            if (i || j) {
                angset.emplace(i, j);
            }
        }
    }
    vector<Angle> allangs(all(angset));
    cerr << sz(allangs) << endl;
    while (sz(allangs) > 200000) {
        int r = rand() % sz(allangs);
        swap(allangs.back(), allangs[r]);
        allangs.pop_back();
    }

    set<pii> Q;
    while (Q.size() != 200000) {
        int x = rand() % 1601 - S;
        int y = rand() % 1601 - S;
        if (x || y) Q.emplace(x, y);
    }
    cout << sz(Q) << " " << sz(allangs) << endl;
    trav(it, Q) {
        cout << it.first << " " << it.second << endl;
    }

    random_shuffle(all(allangs));
    trav(it, allangs) {
        int mx = 1000;
        if (it.x != 0) mx = min(mx, S / abs(it.x));
        if (it.y != 0) mx = min(mx, S / abs(it.y));
        int m = rand() % mx + 1;
        cout << it.x * m << " " << it.y * m << " " << 1000 << endl;
    }
}
