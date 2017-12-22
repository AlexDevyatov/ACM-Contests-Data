// Solution for NCPC/UKIEPC 2014 problem "squares"
// Written by Jaap Eldering
// Creates sets of parallel lines and then iterates over these sets
// and the orthogonal sets to find total number of squares.

#include <cstdlib>
#include <iostream>
#include <map>
#include <set>

using namespace std;

template<class T> T gcd(T a, T b) { return a==0 ? b : gcd(b%a,a); }

struct point {
	int x, y;

	point() {}
	point(int x_, int y_): x(x_), y(y_) {}

	// Make direction vector unique, for use as map key:
	point normalize()
	{
		int g = gcd(abs(x),abs(y));
		x /= g;
		y /= g;

		if ( x<0 ) {
			x = -x;
			y = -y;
		}
		if ( x==0 && y<0 ) y = -y;

		return *this;
	}

	point orthogonal() const
	{
		return point(y,-x).normalize();
	}
};


point operator -(const point& a, const point& b) { return point(a.x-b.x,a.y-b.y); }
int   operator *(const point& a, const point& b) { return a.x*b.x + a.y*b.y; }

int   operator <(const point& a, const point& b)
{
	if ( a.x!=b.x ) return a.x<b.x;
	return a.y<b.y;
}

void finddists(set<int> s, map<int,int>& d)
{
	for(auto i1=s.begin(); i1!=s.end(); i1++) {
		for(auto i2=s.begin(); i2!=i1; i2++) {
			d[abs(*i1 - *i2)]++;
		}
	}
}

int main()
{
	int n;
	cin >> n;

	// Store lines as "normalized direction -> distance from origin"
	map<point,set<int> > lines;

	for(int i=0; i<n; i++) {
		point p1, p2, dir;
		cin >> p1.x >> p1.y >> p2.x >> p2.y;
		dir = (p2 - p1).normalize();
		lines[dir].insert(p1*dir.orthogonal());
	}

	int res = 0;

	for(auto it=lines.begin(); it!=lines.end(); it++) {
		if ( it->second.empty() ) continue;
		// count #distances between pairs of parallel lines:
		map<int,int> dist1, dist2;
		point dir = it->first.orthogonal();
		finddists(it->second,dist1);
		finddists(lines[dir],dist2);

		for(auto id=dist1.begin(); id!=dist1.end(); id++) {
			if ( dist2.count(id->first)!=0 ) {
				res += id->second * dist2[id->first];
			}
		}

		// To make sure we don't count this pair of sets of orthogonal
		// lines again:
		lines[dir].clear();
	}

	cout << res << endl;

	return 0;
}
