#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <iostream>

using namespace std;
typedef long long ll;

int gcd(ll a, ll b) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	if (b == 0) return a;
	return gcd(b, a % b);
}

struct rat {
	ll n, d;
	rat(ll n=0, ll d=1): n(n), d(d) {
		norm();
	}
	void norm() {
		ll D = gcd(n, d);
		n /= D;
		d /= D;
		if (d < 0 || d == 0 && n < 0) d = -d, n = -n;
	}

	bool operator<(const rat p) const {
		if (d != p.d) return d > p.d;
		return n > p.n;
	}
};

struct point {
	ll x, y;
	point(ll x=0, ll y=0): x(x), y(y) {}
	ll dist2() const { return x*x+y*y; }
	ll dot(const point &p) const { return x*p.x+y*p.y; }
	point operator+(const point &p) const { return point(x+p.x, y+p.y); }
	point operator-(const point &p) const { return point(x-p.x, y-p.y); }
	point operator*(ll k) const { return point(k*x, k*y); }
};



rat ldist(point p, point q, rat dir) {
	// project p onto (q, q+dir)
	point dp(dir.n, dir.d);
	point qp = q-p;
	ll proj = dp.dot(qp);
	point diff = qp*dp.dist2() - dp*proj;
	return rat(diff.dist2(), dp.dist2()*dp.dist2());
}

int main(void) {
	map<rat, vector<point> > lines;
	map<rat, map<rat, long long> > linedists;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		lines[rat(x2-x1, y2-y1)].push_back(point(x1, y1));
	}
	long long tot = 0;
	for (auto l: lines) {
		int N = l.second.size();
		//		printf("process dir %lf, %lf\n", (double)l.first.n, (double)l.first.d);
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < i; ++j) {
				rat dst = ldist(l.second[i], l.second[j], l.first);
				//				printf("pt (%lf,%lf) to (%lf,%lf) = %lf/%lf\n", (double)l.second[i].x, (double) l.second[i].y,   (double)l.second[j].x,  (double)l.second[j].y,   (double)dst.n,  (double)dst.d);
				++linedists[l.first][ldist(l.second[i], l.second[j], l.first)];
			}
	}
	for (auto ld: linedists) {
		rat perp = rat(-ld.first.d, ld.first.n);
		for (auto d: ld.second)
			tot += d.second * linedists[perp][d.first];
	}
	printf("%lld\n", tot/2);
	return 0;
}
