#include <iostream>
#include <iomanip>
#include <cassert>
#include <sstream>
#include <cstdio>
#include <vector>
#include <map>
#define rep(i,a,b) for(int i=a;i<b;++i)
#define MP(x,y) make_pair(x,y)
#define FI(x) (x).first
#define SE(x) (x).second
#define trav(it,v) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef double fl;

fl Dp[1000000+10]; //NOT SPECIFIED
	int t,n;

vector<pair<vi, int> > questions;
vector<string> words;
map<string, int> uid;


fl DP(int x) {
	if(x <= 0) return 0;
	return Dp[x];
}


template<typename t>
ostream& operator<<(ostream& os, const vector<t>&v) {
	rep(i,0,v.size())
		os << v[i] << ' ';
	return os;
}

int Uid(string s) {
	map<string,int>::iterator it = uid.find(s);
	if(it == uid.end()) {
		uid[s] = words.size();
		words.push_back(s);
		return uid[s];
	} else return it->second;
}

struct node {
	node(int _ans = -1) :ans(_ans), w(-1) {}
	map<int, node*> children;
	fl prob;
	int ans;
	map<int, int> compute();	
	fl dp(int);
	void debug(vi);
	int w; //number of questions (=leaves) contained in subtree
	int weight();
};

int node::weight() {
	if(w == -1) {
		if(ans != -1) w = 1;
		else {
			w = 0;
			trav(it, children)
				w += it->second->weight();
		}
	}
	return w;
}

void node::debug(vi u) {
	rep(i,0,u.size()) cout << words[u[i]] << ' '; cout << " : prob = "<<prob<<endl;
	if(ans != -1) cout << "answer is " << words[ans] << endl;
	cout << "weight of node is " << weight() << endl;
	trav(it, children) {
		u.push_back(it->first);
		it->second->debug(u);
		u.pop_back();
	}
}

fl node::dp(int t) {
	if(t == 0) return 0;
	//option 1: answer directly.
	fl M = prob + DP(t-1);
	//option i: wait at least one more word, and use optimal strategy from there
	//there is a probability distribution for next word
	
	fl alt = 0;
	trav(it, children) {
		alt += fl(it->second->weight())/fl(weight()) * fl(it->second->dp(t-1));
	} 
	return max(M, alt);
}

map<int, int> node::compute() {
	map<int, int> rt;
	if(ans != -1) {
		rt[ans] = 1;
	} else {
		trav(it, children) {
			map<int, int> tmp = it->second->compute();
			trav(jt, tmp) rt[jt->first] += jt->second;
		}
	}
	int M = 0, sz = 0;
	trav(it, rt) { M = max(M,it->second); sz += it->second; }
	prob = fl(M) / fl(sz);
	return rt;
}

int main() {
	string s;
	{getline(cin, s);
	istringstream ss(s);
	ss >> t >> n;}
	cout<<setprecision(10);
	rep(i,0,n) {
		getline(cin, s);
		istringstream ss(s);
		vector<string> v;
		string w;
		while(ss >> w) v.push_back(w);
		int ans = Uid(v.back()); v.pop_back();			
		vi q;
		rep(i,0,v.size()) q.push_back(Uid(v[i]));
		questions.push_back(MP(q, ans));
	}	

	node *root = new node;
	rep(i,0,questions.size()) {
		node *cur = root;
		vi q = FI(questions[i]);
		rep(j,0,q.size()) {
			map<int, node*>::iterator it = cur->children.find(q[j]);
			if(it == cur->children.end()) {
				cur = (cur->children[q[j]] = new node);
			} else cur = it->second;
		}
		cur->ans = SE(questions[i]);
	}
	root->compute(); root->weight();
//	vi u;	root->debug(u);
	for(int tp = 0; tp <= t; ++tp) {
		Dp[tp] = root->dp(tp);	
//		cout << tp << " : " << Dp[tp] << endl;
	}
	cout << DP(t) << endl;
	return 0;
}
