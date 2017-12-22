#include <iostream>
#include <set>
#include <cstdio>
#include <algorithm>
#define MP(x,y) make_pair(x,y)
#define FI(x) (x).first
#define SE(x) (x).second
#define rep(i,a,b) for(int i=a;i<b;++i)
#define trav(it,v) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
#define Cout if(DBG) cout
using namespace std;
typedef pair<int, int> pii;
pii shows[100000+10];
const int DBG = 0;

struct cmp {
	bool operator()(int a, int b) {return a > b;}
};

ostream& operator<<(ostream& os, const multiset<int>& x) {
	for(set<int>::const_iterator it = x.begin(); it != x.end(); ++it)
		os << (*it) << ' ';
	return os;
}

int main() {
	int n,k;
	scanf("%d%d", &n, &k);
	rep(i,0,n) {
		int x,y;
		scanf("%d%d", &x, &y);
		shows[i] = MP(y, x);
	}
	sort(shows, shows+n);
	//rep(i,0,n) cout << shows[i] << " :::"<<endl;
	multiset<int, cmp> s;
	rep(i,0,k) s.insert(0);
	int score = 0;
	rep(i,0,n) {
		Cout << endl << "processing ["<<SE(shows[i]) << ", " << FI(shows[i]) << ")" << endl;
		if (DBG) {
			multiset<int> ful(s.begin(), s.end());
			Cout << "endpoint set is " << ful << endl;
		}
		multiset<int>::iterator it = s.lower_bound(SE(shows[i]));
		if(it != s.end()) {
			Cout << "use band ending at " << (*it) << endl;
			s.erase(it);
			s.insert(FI(shows[i]));
			++score;
		} else Cout << "no available band" << endl;
	}
	printf("%d\n", score);
	return 0;
}
