#include <stdlib.h>
#include <vector>
#include <queue>
#include <set>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits.h>

using namespace std;

struct Vec {
	double x, y;
	bool operator<(const Vec& r) const {
		if (x == r.x) return (y < r.y);
		else return (x < r.x);
	}
	void normalize() {
		double L = sqrt(x * x + y * y);
		if (L == 0.0) return;
		x /= L; y /= L;
	}
	double distToVec(const Vec& r) const {return sqrt((r.x - x) * (r.x - x) + (r.y - y) * (r.y - y));}
	Vec perpVec() {
		Vec r; r.x = -y; r.y = x;
		return r;
	}
};

Vec operator+(const Vec& a, const Vec& b) {
	Vec r; r.x = a.x + b.x; r.y = a.y + b.y;
	return r;
}

Vec operator-(const Vec& a, const Vec& b) {
	Vec r; r.x = a.x - b.x; r.y = a.y - b.y;
	return r;
}

Vec operator*(double a, const Vec& b) {
	Vec r; r.x = a * b.x; r.y = a * b.y;
	return r;
}

Vec makeVec(double x, double y) {
	Vec r; r.x = x; r.y = y;
	return r;
}

struct Line {
	Vec start, end;
	bool bounded;
	bool intersectLine(const Line& L, Vec* r = NULL) const {
		Vec dif1 = end - start, dif2 = L.end - L.start;
		Vec dS = L.start - start;
		double D = dif2.x * dif1.y - dif1.x * dif2.y;
		if (D == 0) return false;
		double u1 = (dS.y * dif2.x - dS.x * dif2.y)/D;
		double u2 = (dS.y * dif1.x - dS.x * dif1.y)/D;
		if (r != NULL) *r = start + u1 * dif1;
		return ((!bounded || (0 <= u1 && u1 <= 1)) && (!L.bounded || (0 <= u2 && u2 <= 1))); // includes endpoints
	}
};

Line makeLine(Vec start, Vec end, bool bounded = true) {
	Line L; L.start = start; L.end = end; L.bounded = bounded;
	return L;
}

double pointToLineDist(const Vec& p, const Line& L) {
	Vec dif = L.end - L.start;
	double u = ((p.x - L.start.x) * dif.x + (p.y - L.start.y) * dif.y) / (dif.x * dif.x + dif.y * dif.y);
	if (L.bounded) u = max(min(u, 1.0), 0.0);
	return p.distToVec(L.start + u * dif);
}

struct QuadrForm { // Ax^2 + By^2 + Cxy + Dx + Ey + F = 0
	double A, B, C, D, E, F;
};

QuadrForm makeQuad(double A, double B, double C, double D, double E, double F) {
	QuadrForm Q; Q.A = A; Q.B = B; Q.C = C; Q.D = D; Q.E = E; Q.F = F;
	return Q;
}

Line getBisector(const Vec& p1, const Vec& p2) {
	Vec mid = 0.5 * p1 + 0.5 * p2;
	return makeLine(mid, mid + (p2 - p1).perpVec(), false);
}

Line getBisector(const Line& L1, const Line& L2) {
	Vec dif1 = L1.start - L1.end, dif2 = L2.end - L2.start; dif1.normalize(); dif2.normalize();
	Vec dif = 0.5 * (dif1 + dif2);
	Vec p;
	if (L1.intersectLine(L2, &p)) return makeLine(p, p + dif, false);
	else {
		double u = ((L1.start.x - L2.start.x) * dif2.x + (L1.start.y - L2.start.y) * dif2.y) / (dif2.x * dif2.x + dif2.y * dif2.y);
		p = L2.start + u * dif2; dif1 = 0.5 * (p - L1.start);
		return makeLine(L1.start + dif1, L1.end + dif1);
	}
}

QuadrForm getBisector(const Vec& p, const Line& L) {
	Vec dif = L.end - L.start; dif.normalize(); dif = dif.perpVec();
	double C = -dif.x * L.start.x - dif.y * L.start.y; // dif.x * x + dif.y * y + C = 0
	return makeQuad(1.0 - dif.x * dif.x, 1.0 - dif.y * dif.y, -2.0 * dif.x * dif.y, -2.0 * (p.x + dif.x * C), -2.0 * (p.y + dif.y * C), p.x * p.x + p.y * p.y - C * C);
}

vector<Vec> intersect(const Line& L, const QuadrForm& Q) {
	vector<Vec> V;
	Vec dif = L.end - L.start; dif.normalize();
	double A = Q.A * dif.x * dif.x + Q.B * dif.y * dif.y + Q.C * dif.x * dif.y;
	double B = 2.0 * (Q.A * L.start.x * dif.x + Q.B * L.start.y * dif.y) + Q.C * (L.start.x * dif.y + L.start.y * dif.x) + Q.D * dif.x + Q.E * dif.y;
	double C = Q.A * L.start.x * L.start.x + Q.B * L.start.y * L.start.y + Q.C * L.start.x * L.start.y + Q.D * L.start.x + Q.E * L.start.y + Q.F;
	if (A == 0) {
		if (B != 0.0) {
			double u = -C/B;
			V.push_back(L.start + u * dif);
		}
		return V;
	}
	double D = B * B - 4.0 * A * C;
	if (D < 0.0) return V;
	D = sqrt(D);
	double u1 = (-B + D)/(2.0 * A);
	double u2 = (-B - D)/(2.0 * A);
	V.push_back(L.start + u1 * dif); V.push_back(L.start + u2 * dif);
	return V;
}

struct Circle {
	Vec center;
	double r;
	bool containsPoint(const Vec& p) {return ((p.x - center.x) * (p.x - center.x) + (p.y - center.y) * (p.y - center.y) <= r * r);}
};

Circle makeCircle(double x, double y, double r) {
	Circle c; c.center.x = x; c.center.y = y; c.r = r;
	return c;
}

vector<Vec> intersectCircles(const Circle& c1, const Circle& c2) {
	vector<Vec> V;
	double D = c1.center.distToVec(c2.center);
	if (D == 0) return V;
	double x = (D * D - c2.r * c2.r + c1.r * c1.r)/(2.0 * D);
	double y = c1.r * c1.r - x * x;
	if (y < 0.0) return V;
	y = sqrt(y);
	Vec dif = c2.center - c1.center; dif.normalize();
	Vec dif2 = dif.perpVec();
	V.push_back(c1.center + x * dif + y * dif2);
	V.push_back(c1.center + x * dif - y * dif2);
	return V;
}

int N;
Vec P[25];
double maxR;

bool pointInPoly(const Vec& p) {
	int c = 0;
	for (int i = 0; i < N; i++) {
		int i2 = (i+1)%N;
		Vec A = P[i], B = P[i2];
		if (P[i].y > P[i2].y) {
			A = P[i2]; B = P[i];
		}
		if (p.y >= A.y && p.y < B.y && (B.y - A.y) * (p.x - A.x) - (B.x - A.x) * (p.y - A.y) >= 0) c++;
	}
	return (c%2 == 1);
}

double fitCircle(const Vec& p) {
	if (!pointInPoly(p)) return 0.0;
	double R = 1000000;
	for (int i = 0; i < N; i++) {
		int j = (i+1)%N;
		R = min(R, pointToLineDist(p, makeLine(P[i], P[j])));
	}
	return R;
}

void check(const Vec& p1, const Vec& p2, const Vec& p3) {
	Vec r;
	if (getBisector(p1, p2).intersectLine(getBisector(p2, p3), &r)) maxR = max(maxR, fitCircle(r));
}

void check(const Vec& p1, const Vec& p2, const Line& L) {
	vector<Vec> V = intersect(getBisector(p1, p2), getBisector(p1, L));
	for (int i = 0; i < V.size(); i++) maxR = max(maxR, fitCircle(V[i]));
}

void check(const Vec& p, const Line& L1, const Line& L2) {
	vector<Vec> V = intersect(getBisector(L1, L2), getBisector(p, L1));
	for (int i = 0; i < V.size(); i++) maxR = max(maxR, fitCircle(V[i]));
}

void check(const Line& L1, const Line& L2, const Line& L3) {
	Vec r;
	if (getBisector(L1, L2).intersectLine(getBisector(L2, L3), &r)) maxR = max(maxR, fitCircle(r));
}

void onerun() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> P[i].x >> P[i].y;

	maxR = 0.0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			for (int k = 0; k < N; k++) {
				if (k == i || k == j) continue;
				int i2 = (i+1)%N, j2 = (j+1)%N, k2 = (k+1)%N;
				check(P[i], P[j], P[k]);
				if (k2 != i && k2 != j) check(P[i], P[j], makeLine(P[k], P[k2], false));
				if (k2 != i && j2 != i) check(P[i], makeLine(P[j], P[j2], false), makeLine(P[k], P[k2], false));
				check(makeLine(P[i], P[i2], false), makeLine(P[j], P[j2], false), makeLine(P[k], P[k2], false));
			}
		}
	}

	cout << setprecision(12) << maxR << endl;
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}