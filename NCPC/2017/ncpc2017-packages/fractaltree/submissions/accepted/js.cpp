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
vector<vector<pii>> nchildren;
vector<pair<int, int>> leaves;
vi excludeleaf;
int N;
int K;
ll offset;
int LLIM;

//#define D(x) x
#define D(x)

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
    vi renumbering(N);
    int s = 0;
    function<void(int)> rec = [&](int at) {
        renumbering[at] = s++;
        if (children[at].empty()) {
            leaves.emplace_back(at, cnt);
        } else  {
            excludeleaf.push_back(at);
            ++cnt;
            trav(it, children[at]) rec(it.first);
        }
    };
    rec(0);

    trav(it, excludeleaf) it = renumbering[it];
    if (sz(leaves) == 1) LLIM = 0;
    else LLIM = (int)ceil(40 / log2(sz(leaves)) + 1);
    trav(it, leaves) it.first = renumbering[it.first];
    D(trav(it, leaves) {
        cerr << "leaf at node " << it.first << endl;
    })
    nchildren.resize(N);
    rep(i,0,N) {
        trav(it, children[i]) {
            nchildren[renumbering[i]].emplace_back(renumbering[it.first], it.second);
            D(cerr << "add " << renumbering[i] << " to " << renumbering[it.first] << endl;)
        }
    }
}

void compressTree() {
    int lengthTo = 0;
    int at = 0;
    while (!children[at].empty()) {
        lengthTo++;
        at = children[at][0].first;
    }
    D(cerr << "length to is " << lengthTo << endl;)
    D(cerr << "K is " << K << " llim is " << LLIM << endl;)
    ll jmp = max(0, K - LLIM);
    offset += jmp * lengthTo;
    K -= jmp;
}

vector<ll> pows;

void makePows() {
    pows.resize(K + 2);
    pows[1] = N;
    rep(i,2,K+2) {
        if ((ll(pows[i - 1]) - 1) * sz(leaves) + N > 1LL<<30) {
            pows[i] = 1LL<<30;
        } else pows[i] = (pows[i - 1] - 1) * sz(leaves) + N;
    }
}

vector<int> findPath(int x) {
    D(cerr << "finding node " << x << endl;)
    vi path;
    while (true) {
        if (sz(path) == K) {
            D(cerr << "pushing final " << x << endl;)
            path.push_back(-x);
            break;
        }
        int lo = -1;
        int hi = sz(leaves)-1;
        while (hi - lo > 1) {
            int mid = (lo + hi) / 2;
            D(cerr << mid << " " << sz(leaves) << " " << K - sz(path) << " " << pows[K - sz(path)] << endl;)
            if (ll(mid + 1) * pows[K - sz(path)] + leaves[mid].second >= x+1) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        int leaf = hi;
        x -= leaf * pows[K - sz(path)];
        D(cerr << "leaf was " << leaf << " new x " << x << endl;)
        if (x < leaves[leaf].second) {
            D(cerr << "pushing tail " << x << endl;)
            path.push_back(x);
            break;
        } else {
            x -= leaves[leaf].second;
            D(cerr << "pushing leaf " << leaf << endl;)
            path.push_back(leaf);
        }
    }
    return path;
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
    lca = new LCA(nchildren);
}

int nodeDistance(int a, int b) {
    D(cerr << "node distance between " << a << " and " << b << endl;)
    return lca->distance(a, b);
}

int lastNode(const vector<int>& path) {
    D(cerr << sz(path) << endl;)
    D(cerr << path.back() << endl;)
    int ret = path.size() == 1 ? (path.back() < 0 ? -path.back() : excludeleaf[path.back()]) : leaves[path.back()].first;
    D(cerr << "last nod " << ret << endl;)
    return ret;
}

ll pathDistance(const vi& path) {
    if (path.empty()) return 0;
    ll ans = 0;
    rep(i,0,sz(path)) {
        int nod = path[i];
        D(cerr << "pre " << nod << endl;)
        if (i != sz(path) - 1) {
            nod = leaves[nod].first;
        } else {
            if (nod < 0) nod = -nod;
            else nod = excludeleaf[nod];
        }
        D(cerr << "nod " << nod << endl;)
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
        D(cerr << "offset " << offset << endl;)
        if (a <= offset && b <= offset) {
            cout << abs(a - b) << endl;
        } else {
            int addition = 0;
            if (a <= offset) addition += offset - a, a = offset;
            if (b <= offset) addition += offset - b, b = offset;
            a -= offset;
            b -= offset;
            int ret = (solve(a, b) + addition);
            D(cerr << "ANS: ";)
            cout << ret << endl;
        }
    }
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
    readTree();
    findLeaves();
    compressTree();
    makePows();
    makeLCA();
    readQueries();
}
