#include <iostream>
#include <unordered_map>
using namespace std;

namespace kdtree {
  struct pt {
    int x[2];
    pt (int x, int y) : x{x,y} {}
    pt () : x{0,0} {}
    pt operator + (const pt & p) const { return pt(x[0]+p.x[0],x[1]+p.x[1]); }
    pt operator - (const pt & p) const { return pt(x[0]-p.x[0],x[1]-p.x[1]); }
    bool operator == (const pt & p) const { return x[0]==p.x[0] and x[1]==p.x[1]; }
    int mod2() const { return x[0]*x[0] + x[1]*x[1]; }
  };
  istream& operator >> (istream& i, pt& p) {
    return i >> p.x[0] >> p.x[1];
  }
  ostream& operator << (ostream& o, const pt& p) {
    return o << p.x[0] << ' ' << p.x[1];
  }

  int level;
  pt p;
  int r2;
  pt bl,ur;

  bool operator < (const pt& p, const pt& q) {
    return p.x[level&1] < q.x[level&1] + (1<<(13-level/2));
  }

  struct node {
  private:
    node* children[2];
    pt x;
    int n;
  public:
    node (const pt& x) : children{nullptr,nullptr}, x(x), n(0) {}
    void insert() {
      ++n;
      if (level==28) return;
      bool lt = p < x;
      node*& child = children[not lt];
      if (child==nullptr) {
        child = new node(x);
        if (not lt) child->x.x[level&1]+=(1<<(13-level/2));
      }
      ++level;
      child->insert();
    }
    int cleanchild(int i) {
      node*& child = children[i];
      level++;
      int ret = child->clean();
      level--;
      if (child->n==0) child=nullptr;
      return ret;
    }
    int clean() {
      if (level==28) {
        if ((x-p).mod2()<=r2) {
          int ret=n;
          n=0;
          return ret;
        }
        return 0;
      }
      int ret=0;
      if (children[0] and bl < x) ret += cleanchild(0);
      if (children[1] and not (ur < x)) ret += cleanchild(1);
      n-=ret;
      return ret;
    }
  };
  node root({});

  void insert(const pt& p) {
    level=0;
    kdtree::p = p;
    root.insert();
  }
  int clean(const pt& p, int r) {
    level = 0;
    kdtree::p = p;
    r2 = r*r;
    bl = p-pt(r,r);
    ur = p+pt(r,r);
    return root.clean();
  }
};
namespace std {
template<> struct hash<kdtree::pt> {
  size_t operator () (kdtree::pt p) const { return p.x[0]*10000+p.x[1]; }
};
};

int main() {
  int g;
  cin >> g;
  for (int i=0; i<g; ++i) {
    kdtree::pt p;
    cin >> p;
    kdtree::insert(p);
  }
  int m;
  cin >> m;
  int cleaned = 0;
  unordered_map<kdtree::pt,int> sprinklers;
  for (int i=0; i<m; ++i) {
    kdtree::pt p;
    cin >> p;
    int r;
    cin >> r;
    int& q = sprinklers[p];
    q = max(q,r);
  }
  for (auto it : sprinklers) {
    cleaned += kdtree::clean(it.first,it.second);
  }
  cout << g - cleaned << endl;
}
