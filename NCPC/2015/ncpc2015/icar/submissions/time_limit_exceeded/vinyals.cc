#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <queue>
using namespace std;

#if defined VIZ
#include <map>
#include <boost/format.hpp>
#endif

typedef vector<int> VI;

const double EPS=1e-9;
const double INF=numeric_limits<double>::infinity();

template<typename T> T sq(T x) { return x*x; }

// time <= 6\sqrt(2000) + \sum(red) < 520
// #parabolas ~ 1200
const int TMAX = 520;

int n;
vector<double> Ti,g0,gi;

vector<VI> green;
vector<VI> red;

bool isitgreen(int i, double t) {
  t+=EPS;
  t-=g0[i];
  t=fmod(t,Ti[i]);
  t+=Ti[i];
  t=fmod(t,Ti[i]);
  t-=2*EPS;
  return t<gi[i];
}

class parabola {
 private:
  int crash() const {
    for (int i=1;i<n;++i) {
      if (i*1000 < xstart + EPS) continue;
      if (isitgreen(i,t(i*1000))) continue;
      return i;
    }
    return n;
  }
  int carefulcrash() const {
    for (int i=1;i<n;++i) {
      if (i*1000 < xstart - EPS) continue;
      if (isitgreen(i,t(i*1000))) continue;
      return i;
    }
    return n;
  }
public:
  double xstart;
  double tstart;
  int iend;
  bool feasible;
  parabola(int igreen, int tgreen, int istart) :
    xstart(istart*1000)
  {
    double dx=igreen*1000-xstart;
    double dt=sqrt(2*dx);
    tstart = tgreen-dt;
    if (tstart<-EPS) { feasible = false; return; }
    iend = crash();
    feasible = iend>=igreen;
#if defined DEBUG
    if (feasible) {
      cerr << "Considering start from " << istart << " green " << igreen << " at " << tgreen << endl;
      cerr << "  Would start at " << tstart << endl;
      cerr << "  Would go to " << iend << endl;
      cerr << "  Would arrive at " << t(iend*1000) << endl;
    }
#endif
  }
  parabola(int igreen, int tgreen, int ired, int tred)  {
    double dx=(igreen-ired)*1000;
    double dt=tgreen-tred;
    tstart = (2*dx+sq(tred)-sq(tgreen))/(-2*dt);
    if (tstart<-EPS) { feasible = false; return; }
    dt = tgreen-tstart;
    xstart = igreen*1000-dt*dt/2;
    if (xstart<-EPS) { feasible = false; return; }
    iend = crash();
    feasible = iend>=igreen;
#if defined DEBUG
    if (feasible) {
      cerr << "Considering red " << ired << " at " << tred << " green " << igreen << " at " << tgreen << endl;
      cerr << "  Would start at " << tstart << endl;
      cerr << "  Would start from " << xstart << endl;
      cerr << "  Would go to " << iend << endl;
      cerr << "  Would arrive at " << t(iend*1000) << endl;
    }
#endif
  }
  parabola(int igreen, int tgreen, const parabola& start) {
    double dx=(igreen*1000-start.xstart);
    double dt=(tgreen-start.tstart);
    double delta = 4*dx-sq(dt);
    if (delta<EPS) { feasible = false; return; }
    tstart = (tgreen+start.tstart+sqrt(delta))/2;
    if (tstart<-EPS) { feasible = false; return; }
    dt = tgreen-tstart;
    xstart = igreen*1000-dt*dt/2;
    if (xstart<-EPS) { feasible = false; return; }
    iend = carefulcrash();
    feasible = iend>=igreen;
#if defined DEBUG
    if (feasible) {
      cerr << "Considering extra from " << start.xstart << " at " << start.tstart << " green " << igreen << " at " << tgreen << endl;
      cerr << "  Would start at " << tstart << endl;
      cerr << "  Would start from " << xstart << endl;
      cerr << "  Would go to " << iend << endl;
      cerr << "  Would arrive at " << t(iend*1000) << endl;
    }
#endif
}
  bool canitgothere(double x) const {
    return xstart < x + EPS and x - EPS < iend*1000;
  }
  double t(double x) const {
    double dx=x-xstart;
    double dt=sqrt(2*dx);
    return tstart+dt;
  }
  bool canstartfrom(const parabola& p) {
    if (not p.canitgothere(xstart)) return false;
    double tp=p.t(xstart);
    return tp-EPS<tstart;
  }
};

#if defined VIZ
ostream& operator << (ostream& o, const parabola& p) {
  return o << boost::format(
      "pair f(real t) { return (%2% + (t-%1%)**2/2,t); }"
      "path g = graph(f,%1%,%3%, Hermite);"
      "draw(g,p=blue);") % p.tstart % p.xstart % p.t(p.iend*1000);
}
#endif

vector<parabola> parabolas;

double best;
#if defined VIZ
VI parent;
int besti;
#endif
void bfs() {
  best=INF;
  VI seen(parabolas.size(),false);
#if defined VIZ
  parent.resize(parabolas.size());
#endif
  queue<int> q;
  q.push(0);
  seen[0]=true;
  while(not q.empty()) {
    int v = q.front(); q.pop();
    const parabola& p = parabolas[v];
#if defined DEBUG
    cerr << "Visiting " << p.xstart << ' ' << p.tstart << " -> " << p.iend*1000 << ' ' << p.t(p.iend*1000) << endl;
#endif
    if (p.iend==n) {
      double tstop=p.t(n*1000);
#if defined VIZ
      if (tstop<best) besti=v;
#endif
      best=min(best,tstop);
    }
    for (int u=0;u<parabolas.size();++u) {
      if (seen[u]) continue;
      if (parabolas[u].canstartfrom(p)) {
#if defined VIZ
        parent[u]=v;
#endif
        q.push(u);
        seen[u]=true;
      }
    }
  }
}
  
int main() {
  cin >> n;
  green.resize(n);
  red.resize(n);
  Ti.resize(n);
  g0.resize(n);
  gi.resize(n);
  green[0].push_back(0);
  for (int i=1;i<n;++i) {
    int firstgreen,firstred,Tgreen,Tred,T;
    cin >> firstgreen >> Tgreen >> Tred;
    T=Tgreen+Tred;
    g0[i]=firstgreen;
    gi[i]=Tgreen;
    Ti[i]=T;
    firstred=firstgreen+Tgreen;
    firstred%=T;
    for (int t=firstgreen;t<=TMAX;t+=T) green[i].push_back(t);
    for (int t=firstred;t<=TMAX;t+=T) red[i].push_back(t);
  }
  for (int igreen=0;igreen<n;++igreen) {
    for (int tgreen : green[igreen]) {
      for (int istart=0;istart<=igreen;++istart) {
        parabola p(igreen,tgreen,istart);
        if (p.feasible) parabolas.push_back(p);
      }
      for (int ired=0;ired<igreen;++ired) {
        for (int tred : red[ired]) {
          if (tred>=tgreen) break;
          parabola p(igreen,tgreen,ired,tred);
          if (p.feasible) parabolas.push_back(p);
        }
      }
    }
  }
  for (int igreen=0;igreen<n;++igreen) {
    vector<parabola> extraparabolas;
    for (int tgreen : green[igreen]) {
      for (const parabola& p : parabolas) {
        parabola q(igreen,tgreen,p);
        if (q.feasible) extraparabolas.push_back(q);
      }
    }
    parabolas.insert(parabolas.end(), extraparabolas.begin(), extraparabolas.end());
  }
  bfs();
#if defined VIZ
  cout << "import graph;" << endl;
  cout << "defaultpen(1);" << endl; // for PNG
  cout << boost::format("draw((0,%2%) -- (0,0) -- (%1%,0) -- (%1%,%2%));") % (n*1000) % best << endl;
  for (int i=0;i<n;++i) {
    map<double,int> events;
    for (auto y : green[i]) events[y]=1;
    for (auto y : red[i]) events[y]=-1;
    if (events.find(0)==events.end())
      events.insert(make_pair(0.,-events.begin()->second));
    events[best]=0;
    for (auto it = events.begin();it->first<best;) {
      if (it->second!=-1) {++it; continue;}
      cout << boost::format("draw((%1%,%2%) -- (%1%,%3%),p=red+2);") % (i*1000) % it->first % (it++)->first << endl;
    }
  }
  while(true) {
    cout << parabolas[besti] << endl;
    if (parabolas[besti].xstart==0) break;
    cout << boost::format("draw((%1%,%2%) -- (%1%,%3%),p=blue+dotted);") % parabolas[besti].xstart % parabolas[besti].tstart % parabolas[parent[besti]].t(parabolas[besti].xstart) << endl;
    besti=parent[besti];
  }
  cout << "currentpicture = scale(0.125,1.5)*currentpicture;" << endl;
#else
  cout.precision(10);
  cout << best << endl;
#endif
}
