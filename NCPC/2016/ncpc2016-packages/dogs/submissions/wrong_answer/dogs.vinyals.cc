#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

typedef long long ll;

const double INF = numeric_limits<double>::infinity();
const double EPS = 1e-10;

bool EQ(double x, double y) { return abs(x-y)<EPS; }

struct pt {
  double x,y;
  pt operator + (const pt& p) const { return {x+p.x,y+p.y}; }
  pt operator - (const pt& p) const { return {x-p.x,y-p.y}; }
  pt operator * (double k) const { return {x*k,y*k}; }
  double operator * (const pt& p) const { return x*p.x + y*p.y; }
  double mod() const { return hypot(x,y); }
};

ostream& operator << (ostream& o, const pt& p) {
  return o << p.x << ' ' << p.y;
}

template<typename T>
ostream& operator << (ostream& o, const vector<T>& v) {
  for (const auto& x : v) o << x << ' ';
  return o;
}

double dist(const pt& p, const pt&q ) {
  return (p-q).mod();
}

void parse(int& n, vector<pt>& v, vector<double>& t) {
  cin >> n;
  v.resize(n);
  for (pt& p : v) cin >> p.x >> p.y;
  t.resize(n);
  t[0]=0;
  for (int i=1;i<n;++i) {
    t[i]=t[i-1]+dist(v[i-1],v[i]);
  }
}

pt getnext(const pt& start, const pt& end, double d) {
  pt v=end-start;
  return start+v*(d/v.mod());
}

double opt(const pt& p, const pt& pp, const pt& q, const pt& qq) {
  pt v=pp-p;
  pt w=qq-q;
  pt dp=p-q;
  pt dv=w-v;
  if (EQ(dv*dv,0)) return INF;
  double lambda=(dp*dv)/(dv*dv);
  if (lambda<0 or lambda>1) return INF;
  double ret= dist(p+v*lambda,q+w*lambda);
  //cerr << lambda << ' ' << ret << endl;
  return ret;
}

int main() {
  int n1,n2;
  vector<pt> v1,v2;
  vector<double> t1,t2;
  parse(n1,v1,t1);
  parse(n2,v2,t2);
  //cerr << t1 << endl;
  //cerr << t2 << endl;
  int i1=0,i2=0;
  pt p1=v1[0], p2=v2[0];
  double d=dist(v1[0],v2[0]);
  double t=0;
  while(i1+1<n1 and i2+1<n2) {
    //cerr << " at " << p1 << ' ' << p2 << endl;
    double nt;
    pt np1,np2;
    if (t1[i1+1]<t2[i2+1]) {
      // advance dog 1
      i1++;
      nt=t1[i1];
      np1=v1[i1];
      np2=getnext(p2,v2[i2+1],nt-t);
      d=min(d,opt(p1,np1,p2,np2));
    }
    else {
      // advance dog 2
      i2++;
      nt=t2[i2];
      np2=v2[i2];
      np1=getnext(p1,v1[i1+1],nt-t);
      d=min(d,opt(p1,np1,p2,np2));
    }
    t=nt;
    p1=np1;
    p2=np2;
    d=min(d,dist(p1,p2));
  }
  printf("%.10f\n",d);
}
