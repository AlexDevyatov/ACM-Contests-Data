//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <NTL/RR.h>
using namespace std;

NTL_CLIENT

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

template <class T>
struct Point {
    typedef T coordType;
    typedef Point P;
    typedef const P & R;
    T x, y;
    explicit Point(T x=T(), T y=T()) : x( x), y( y) { }
    bool operator==(R p) const { return x==p.x && y==p.y; }
    P operator+(R p) const { return P(x+p.x, y+p.y); }
    P operator-(R p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(R p) const { return x*p.x + y*p.y; }
    T dist2() const { return x*x + y*y; } //distance^2
    T dist() const { return sqrt(dist2()); } //length
    P unit() const {
        if (dist() < 1e-9) return *this;
        return *this/(T)dist();
    } //makes dist()=1
};
template <class T>
ostream & operator<<(ostream & os, const Point<T> & p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
}
template <class T>
istream & operator>>(istream & is, Point<T> & p) {
    is >> p.x >> p.y;
    return is;
}
template <class P>
RR segDist(const P& s, const P& e, const P& p) {
    if (s==e) return (p-s).dist();
    typedef typename P::coordType T;
    T d = (e-s).dist2(), t = min(d,max(T(0),(p-s).dot(e-s)));
    return ((p-s)*d-(e-s)*t).dist()/d;
}

int main() {
    RR::SetPrecision(300);

    int n; cin >> n;
    vector<Point<RR>> a(n);
    rep(i,0,n) cin >> a[i];
    a.push_back(a.back());
    int m; cin >> m;
    vector<Point<RR>> b(m);
    rep(i,0,m) cin >> b[i];
    b.push_back(b.back());

    Point<RR> cura = a[0], curb = b[0];
    RR ma = (cura - curb).dist();
    RR noll; noll = 0;
    int nexta = 1, nextb = 1;
    while (nexta < n && nextb < m) { // Stop when one of them reaches home
        Point<RR> mova = a[nexta] - cura;
        Point<RR> movb = b[nextb] - curb;

        RR lena = mova.dist();
        RR lenb = movb.dist();
        RR len = min(lena, lenb);
        Point<RR> diff = cura - curb;
        cura = cura + mova.unit() * len;
        curb = curb + movb.unit() * len;

        RR distance = segDist(diff, cura - curb, Point<RR>(noll, noll));
        ma = min(ma, distance);

        if (lena <= lenb) {
            // assign for better precision. the value of cura is almost the same as a[nexta] already
            cura = a[nexta];
            nexta++;
        }
        else {
            curb = b[nextb];
            nextb++;
        }
    }

    RR::SetOutputPrecision(30);
    cout << ma << endl;
}
