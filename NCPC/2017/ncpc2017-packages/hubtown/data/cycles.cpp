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

double adist(Angle a, Angle b) {
    double aang = atan2(a.y, a.x);
    double bang = atan2(b.y, b.x);

    double ba = fmod(abs(aang - bang), 2*M_PI);
    if (ba > M_PI) ba = 2*M_PI - ba;
    return ba;
}

double adist(double aang, double bang) {
    double ba = fmod(abs(aang - bang), 2*M_PI);
    if (ba > M_PI) ba = 2*M_PI - ba;
    return ba;
}

int S = 1000;

bool inside(int l, int mid, int r, int N) {
    if (l > r) r += N;
    if (l > mid) mid += N;
    return l < mid && mid < r;
}

int main() {
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
    int N = sz(allangs);
    rep(i,0,N) {
        allangs.push_back(allangs[i].t360());
    }
    rep(i,N,2*N) {
        allangs.push_back(allangs[i].t360());
    }
    vector<vector<pii>> mvs(N);
    vector<double> angs(sz(allangs));
    rep(i,0,sz(allangs)) angs[i] = atan2(allangs[i].y, allangs[i].x);
    auto start = std::chrono::steady_clock::now();
    rep(i,N,2*N) {
        ll duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count()/ (i - N + 1) * (2*N - i) / 1000;
        ll hours = duration / 3600;
        ll minutes = (duration / 60) % 60;
        ll seconds = duration % 60;
        cerr << "at " << (i-N+1) << "/" << N << " remaining time " << hours << " " << minutes << " " << seconds << endl;
        Angle x = allangs[i];
        Angle mx = x.t180();
        Angle mn = mx; mn.t--;

        int j = i + 1;
        int at = i - 1;
        while (allangs[j] < mx) {
            while (allangs[at] > mn) {
                double diff = adist(angs[j], angs[i]) - adist(angs[i], angs[at]);
                if (fabs(diff) < 1e-13) {
                    //cerr << x.x << " " << x.y << " neighbours " << allangs[j].x << " " << allangs[j].y << " and " << allangs[at].x << " " << allangs[at].y << endl;
                    mvs[at%N].emplace_back(j%N, i%N);
                    break;
                }
                if (diff < 0) break;
                --at;
            }
            ++j;
        }
    }
    int largest = 0;
    vector<pii> bestsol;
    rep(i,0,N) {
        cerr << "at " << i << "/" << N << endl;
        vector<pair<int, pii>> mlen(N + 1, make_pair(-100000, pii(-1, -1)));
        mlen[0].first = 0;
        rep(j,0,N) {
            if (mlen[j].first < 0) continue;
            int real = (j + i) % N;
            trav(it, mvs[real]) {
                int nx = (it.first - i + N) % N;
                if (inside(j, 0, nx, N)) continue;
                if (mlen[j].first + 1 > mlen[nx].first) {
                    mlen[nx] = make_pair(mlen[j].first + 1, pii(j, it.second));
                }
            }
        }
        if (mlen[0].first > 0) {
            if (largest < mlen[0].first) {
                cerr << allangs[i].x << "," << allangs[i].y << " gives " << mlen[0].first << endl;
                bestsol.clear();
                largest = mlen[0].first;

                int at = 0;
                rep(_,0,mlen[0].first) {
                    int real = (at + i) % N;
                    cerr << allangs[real].x << " " << allangs[real].y << " (" << mlen[at].first << ")" << endl;
                    bestsol.emplace_back(allangs[real].x, allangs[real].y);
                    int mv = mlen[at].second.second;
                    cerr << allangs[mv].x << " " << allangs[mv].y << " (mid)" << endl;
                    bestsol.emplace_back(allangs[mv].x, allangs[mv].y);
                    assert(mlen[at].first == mlen[0].first - _);
                    at = mlen[at].second.first;
                }
            }
        }
    }
    cerr << "largest " << largest << endl;
    cout << sz(bestsol) << endl;
    trav(it, bestsol) {
        cout << it.first << " " << it.second << endl;
    }
}
