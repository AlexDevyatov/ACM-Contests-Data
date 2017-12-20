
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>
#include <numeric>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <fstream>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> pii;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)

#define ROTATION_ALLOWED 1
#define DEBUG 0

int W, H;
int AVAILABLE_AREA;

map<vector<pair<int,int> >, bool> can_finish_list;
bool can_finish(vector<pair<int, int> > carpets){
	sort(all(carpets));
	if(can_finish_list.find(carpets) == can_finish_list.end()){
		int a = 0;
		for(auto c: carpets)a += c.first * c.second;
		if(a == AVAILABLE_AREA - W * H)
			return can_finish_list[carpets] = true;
		if(carpets.empty())
			return can_finish_list[carpets] = false;
		vector<pair<int,int> > new_carpets = carpets;
		pair<int, int> tmp = carpets[sz(carpets)-1];
		new_carpets.pop_back();
		if(can_finish(new_carpets))
			return can_finish_list[carpets] = true;
		FOR(i,0,sz(new_carpets)){
			swap(tmp, new_carpets[i]);
			if(can_finish(new_carpets))
				return can_finish_list[carpets] = true;
		}
		return can_finish_list[carpets] = false;
	}
	return can_finish_list[carpets];
}

bool can_fill(vector<vector<bool> > & filled, int w, int h, vector<pair<int,int> > available_carpets){
	sort(all(available_carpets));
#if DEBUG
	FOR(w,0,W){
		FOR(h,0,H)cout << filled[w][h];
		cout << endl;
	}
	cout << w <<  " "<< h << endl;
	for(auto it: available_carpets)cout << "(" << it.first << " " << it.second << ")";
	cout << endl;
#endif
	if(!can_finish(available_carpets))return false;
	while(filled[w][h]){
		++w;
		if(w == W){
			++h;
			w = 0;
			if(h == H)return true;
		}
	}
	int space_w = 0, space_h = H - h;
	while(w + space_w < W && !filled[w + space_w][h])++space_w;
	int last_w = -1, last_h = -1;
	int A = sz(available_carpets);
	FORD(i,0,A){
		int w_cur = available_carpets[i].first;
		int h_cur = available_carpets[i].second;
#if DEBUG
		cout << "w_cur = " << w_cur << " h_cur = " << h_cur << endl;
#endif
		if(last_w == w_cur && last_h == h_cur)continue;
		last_w = w_cur;
		last_h = h_cur;
#if ROTATION_ALLOWED
		swap(w_cur, h_cur);
		FOR(ii,0,2){
			swap(w_cur, h_cur);
#endif
			if(w_cur > space_w)continue;
			if(h_cur > space_h)continue;
			FOR(ww,0,w_cur)FOR(hh,0,h_cur)assert(filled[w+ww][h+hh] == false);
			FOR(ww,0,w_cur)FOR(hh,0,h_cur)filled[w+ww][h+hh]=true;
			vector<pair<int,int> > new_available_carpets = available_carpets;
			swap(new_available_carpets[i], new_available_carpets[A-1]);
			new_available_carpets.pop_back();
			if(can_fill(filled, w, h, new_available_carpets))return true;
			FOR(ww,0,w_cur)FOR(hh,0,h_cur)filled[w+ww][h+hh]=false;
#if ROTATION_ALLOWED
		}
#endif
	}
	return false;
}

int main() {
	int C;
	cin >> W >> H >> C;
	vector<pair<int,int> > available_carpets;
	AVAILABLE_AREA = 0;
	FOR(c,0,C){
		int a, w, h;
		cin >> a >> w >> h;
		AVAILABLE_AREA += a * w * h;
#if ROTATION_ALLOWED
		if(w < h)swap(w,h);
#endif
		FOR(i,0,a)available_carpets.push_back(make_pair(w,h));
	}
	vector<vector<bool> > filled(W, vector<bool>(H,false));
	if(can_fill(filled, 0, 0, available_carpets))
		cout << "yes\n";
	else
		cout << "no\n";
	return 0;
}
