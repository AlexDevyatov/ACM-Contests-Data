#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#define rep(i,a,b) for(int i=(a);i<(b);++i)
using namespace std;
typedef double fl;

string wordnr(int k) {
	ostringstream os;
	os << "word_"<<k;
	return os.str();
}

struct node {
	vector<node*> children;
	~node();
	int q_word;
	int ans;
	void Print(vector<int>&);
	void print() {vector<int> u; Print(u);}
	int size();
};

int node::size() {
	int rt = 1;
	if(ans == -1)
		rep(i,0,children.size())
			rt += children[i]->size();
	return rt;
}

void node::Print(vector<int>& u) {
	if(ans != -1) {
		rep(i,0,children.size()) {
			u.push_back(q_word);
			children[i]->Print(u);
			u.pop_back();
		}
	} else {
		rep(i,0,u.size()) {
			cout << wordnr(u[i]);
			if(i == u.size()-1) cout << "? "; else cout << " "; 
		}
		cout << wordnr(ans) << endl;
	}
}

node::~node() {
	rep(i,0,children.size())
		delete children[i];
}

node *new_rnd_tree(fl m, int a, int A) { //generate random tree, where the offspring distribution is supported on {0, a} and has mean m. The value of m better be < 1! (and a >= 1). Each leaf has one of A possible answers, chosen uniformly at random
	fl p0, p1;
	p1 = m / fl(a), p0 = 1 - p1;
	node *c = new node;
	cout << "p1 = " << p1 << endl;
	if(rand() < p1 * RAND_MAX) {
		c->children.resize(a);
		c->ans = -1;
		rep(i,0,a) {
			c->children[i] = new_rnd_tree(m,a,A);
			c->children[i]->q_word = i;
		}
	} else {
		c->ans = rand()%A;
	}
	return c;	
}

int main() {
	srand(time(0));
	node *c = new_rnd_tree(0.99, 5, 10);
	cout << c->size() << " nodes" << endl;
	c->print();
	
	return 0;
}
