#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

ll gcd(ll a,ll b) {return b? gcd(b,a%b): a;}

/*
 * Author
 *   Robin Lee (hex539)
 *
 * Algorithm
 *   Put each line into a hash table keyed against gradient. Compute all-pairs
 *   distances for each key and take the product of these distance histograms
 *   against the corresponding histogram for the set with an orthogonal
 *   gradient.
 *
 * Complexity
 *   O(N^2 log N)
 */


struct Vec{
  ll x,y;
  ll cross(Vec const &a) const {return y*a.x-x*a.y;}
  ll dot(Vec const &a) const {return x*a.x+y*a.y;}
  Vec operator-(Vec const &a) const {return {x-a.x,y-a.y};}
  Vec operator/(ll const a) const {return {x/a,y/a};}
  Vec normalise() const {return (*this)/(max(1ll,gcd(abs(x),abs(y)))*(x<0 or x==0 and y<0? -1: +1));}
};

struct Line{
  Vec o,v;
  Line(ll a,ll b,ll c,ll d) {o=(Vec{a,b}), v=(Vec{c,d}-o).normalise();}
  Line transverse() const {return Line(o.x,o.y,o.x-v.y,o.y+v.x);}
  ll dist(Line const &a) const {return abs(Vec{-v.y,v.x}.dot(a.o-o));}
  bool operator<(Line const &a) const {return v.cross(a.v)<0;}
};

int main(){
  int n; cin>>n;
  map<Line,vector<Line>> lines;
  for (int i=0; i<n; i++){
    ll a,b,c,d; cin>>a>>b>>c>>d; Line l(a,b,c,d); lines[l].emplace_back(l);
  }

  ll res=0;
  for (auto const &a: lines){
    if (not lines.count(a.first.transverse())) continue;
    auto const &b=lines[a.first.transverse()];

    map<ll,ll> have;
    for (int i=a.second.size(); i--;) for (int j=i; j--;) ++have[a.second[i].dist(a.second[j])];
    for (int i=b.size(); i--;) for (int j=i; j--;) res+=have[b[i].dist(b[j])];
  }

  cout<<res/2ll<<endl;
}
