#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vector<vector<pii>> children;
vector<pair<int, int>> leaves;
int N;
int K;
ll offset;
int LLIM;

void readTree() {
    cin >> N;
    children.resize(N);
    rep(i,1,N) {
        int par;
        cin >> par;
        children[par].emplace_back(i, 1);
    }
    cin >> K;
}

void findLeaves() {
    int cnt = 0;
    function<void(int)> rec = [&](int at) {
        if (children[at].empty()) {
            leaves.emplace_back(at, cnt);
        } else  {
            ++cnt;
            trav(it, children[at]) rec(it.first);
        }
    };
    rec(0);

    if (sz(leaves) == 1) LLIM = 1;
    else LLIM = (int)ceil(40 / log2(sz(leaves)) + 1);
}

void compressTree() {
    int lengthTo = 0;
    int at = 0;
    while (!children[at].empty()) {
        lengthTo++;
        at = children[at][0].first;
    }
    cerr << "length to is " << lengthTo << endl;
    cerr << "K is " << K << " llim is " << LLIM << endl;
    ll jmp = max(0, K - LLIM);
    offset += jmp * lengthTo;
    K -= jmp;
}

vector<ll> pows;

void makePows() {
    pows.resize(sz(leaves) + 1);
    pows[0] = 1;
    rep(i,1,sz(leaves)+1) {
        pows[i] = pows[i - 1] * sz(leaves);
    }
}

vector<int> findPath(int x) {
    //cerr << "finding node " << x << endl;
    vi path;
    while (true) {
        if (sz(path) == K) {
            //cerr << "pushing final " << x << endl;
            path.push_back(x);
            break;
        }

        int lo = 0;
        int hi = sz(leaves);
        while (hi - lo > 1) {
            int mid = (lo + hi) / 2;
            //cerr << mid << " " << sz(leaves) << " " << K - sz(path) << " " << sz(pows) << endl;
            if ((mid + 1) * pows[K - sz(path)] + leaves[mid].second < x+1) {
                lo = mid;
            } else {
                hi = mid;
            }
        }
        x -= lo * N * pows[K - sz(path) - 1];
        //cerr << "leaf was " << lo << " new x " << x << endl;
        if (x < leaves[lo].second) {
            //cerr << "pushing tail " << x << endl;
            path.push_back(x);
            break;
        } else {
            x -= leaves[lo].second;
            //cerr << "pushing leaf " << lo << endl;
            path.push_back(lo);
        }
    }
    return path;
}

int lastNode(const vector<int>& path) {
    //cerr << sz(path) << endl;
    //cerr << path.back() << endl;
    return path.size() == 1 ? path.back() : leaves[path.back()].first;
}

typedef vector<pii> vpi;
typedef vector<vpi> graph;
const pii inf(1 << 29, -1);

template <class T>
struct RMQ {
	vector<vector<T>> jmp;

	RMQ(const vector<T>& V) {
		int N = sz(V), on = 1, depth = 1;
		while (on < sz(V)) on *= 2, depth++;
		jmp.assign(depth, V);
		rep(i,0,depth-1) rep(j,0,N)
			jmp[i+1][j] = min(jmp[i][j],
			jmp[i][min(N - 1, j + (1 << i))]);
	}

	T query(int a, int b) {
		if (b <= a) return inf;
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA {
	vi time;
	vector<ll> dist;
	RMQ<pii> rmq;

	LCA(graph& C) : time(sz(C), -99), dist(sz(C)), rmq(dfs(C)) {}

	vpi dfs(graph& C) {
		vector<tuple<int, int, int, ll> > q(1);
		vpi ret;
		int T = 0, v, p, d; ll di;
		while (!q.empty()) {
			tie(v, p, d, di) = q.back();
			q.pop_back();
			if (d) ret.emplace_back(d, p);
			time[v] = T++;
			dist[v] = di;
			trav(e, C[v]) if (e.first != p)
				q.emplace_back(e.first, v, d+1, di + e.second);
		}
		return ret;
	}

	int query(int a, int b) {
		if (a == b) return a;
		a = time[a], b = time[b];
		return rmq.query(min(a, b), max(a, b)).second;
	}
	ll distance(int a, int b) {
		int lca = query(a, b);
		return dist[a] + dist[b] - 2 * dist[lca];
	}
};

LCA *lca;
void makeLCA() {
    lca = new LCA(children);
}

int nodeDistance(int a, int b) {
    return lca->distance(a, b);
}

ll pathDistance(const vi& path) {
    if (path.empty()) return 0;
    ll ans = 0;
    rep(i,0,sz(path)) {
        int nod = path[i];
        //cerr << "pre " << nod << endl;
        if (i != sz(path) - 1) {
            nod = leaves[nod].first;
        }
        //cerr << "nod " << nod << endl;
        ans += lca->distance(0, nod);
    }
    return ans;
}

int solve(int a, int b) {
    vector<int> apath = findPath(a);
    vector<int> bpath = findPath(b);
    reverse(all(apath));
    reverse(all(bpath));
    while (apath.size() > 1 && bpath.size() > 1) {
        if (apath.back() == bpath.back()) {
            apath.pop_back();
            bpath.pop_back();
        } else break;
    }
    ll ans = nodeDistance(lastNode(apath), lastNode(bpath));
    apath.pop_back();
    bpath.pop_back();
    reverse(all(apath));
    reverse(all(bpath));
    ans += pathDistance(apath);
    ans += pathDistance(bpath);
    return ans;
}

void readQueries() {
    int Q;
    cin >> Q;
    rep(i,0,Q) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        cerr << "offset " << offset << endl;
        if (a <= offset && b <= offset) {
            cout << abs(a - b) << endl;
        } else {
            int addition = 0;
            if (a <= offset) addition += offset - a, a = offset;
            if (b <= offset) addition += offset - b, b = offset;
            a -= offset;
            b -= offset;
            int ret = (solve(a, b) + addition);
            //cerr << "ANS: ";
            cout << ret << endl;
        }
    }
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
    readTree();
    findLeaves();
    makePows();
    compressTree();
    makeLCA();
    readQueries();
}
