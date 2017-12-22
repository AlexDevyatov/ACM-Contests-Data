#include <iostream>
#include <algorithm>
#include <vector>
#define Cout if(DBG) cout
using namespace std;
typedef vector<int> vi;
typedef vector<vi> order;
const int DBG = 1;

order all[10];

ostream& operator<<(ostream& os, const vi& v) {
	for(int i = 0; i < v.size(); ++i)
		os << v[i] << ' ';
	return os;
}

vi ins(vi& u, int k) {
	int n = u.size() + 1;
	vi v(n);
	for(int l = 0; l < n; ++l) 
		if(l < k) v[l] = u[l]; 
		else if(l == k) v[l] = n; 
		else if(l > k) v[l] = u[l-1];
	return v;
}

int main() {
    all[1].push_back(vi(1, 1));
	vi u;u.push_back(1);u.push_back(2);
	all[2].push_back(u);
	reverse(u.begin(), u.end());
	all[2].push_back(u);
	
	int n_in;
    scanf("%d", &n_in);
	for(int n = 3; n <= n_in; ++n) {
		order prev = all[n-1];
		int t = 0;
		while(t < prev.size()) {
			for(int k = n-1; k >= 0; --k) { //put n at position k and prev[t] around it
				vi v = ins(prev[t], k);
				all[n].push_back(v);
				//Cout << "u = " << u << " and k = " << k << " give v = " << v << endl;
			}
			++t;
			for(int k = 0; k < n; ++k) {
				vi v = ins(prev[t], k);
				all[n].push_back(v);
			}
			++t;
		}
	}
	for(int k = 0; k < all[n_in].size(); ++k)
		cout << all[n_in][k] << endl;
}
