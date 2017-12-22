#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Angle {
	int x, y;
	int t;
	Angle(int x, int y, int t=0) : x(x), y(y), t(t) {}
	Angle operator-(Angle a) const { return {x-a.x, y-a.y, t}; }
	int quad() const {
		assert(x || y);
		if (y < 0) return (x >= 0) + 2;
		if (y > 0) return (x <= 0);
		return (x <= 0) * 2;
	}
	Angle t90() const { return {-y, x, t + (quad() == 3)}; }
	Angle t180() const { return {-x, -y, t + (quad() >= 2)}; }
	Angle t360() const { return {x, y, t + 1}; }
};
bool operator<(Angle a, Angle b) {
	// add a.dist2() and b.dist2() to also compare distances
	return make_tuple(a.t, a.quad(), a.y * (ll)b.x) <
	       make_tuple(b.t, b.quad(), a.x * (ll)b.y);
}
bool operator>=(Angle a, Angle b) { return !(a < b); }
bool operator>(Angle a, Angle b) { return b < a; }
bool operator<=(Angle a, Angle b) { return !(b < a); }
bool operator==(Angle a, Angle b) { return a.x == b.x && a.y == b.y && a.t == b.t; }

// Given two points, this calculates the smallest angle between
// them, i.e., the angle that covers the defined line segment.
pair<Angle, Angle> segmentAngles(Angle a, Angle b) {
	if (b < a) swap(a, b);
	return (b < a.t180() ?
	        make_pair(a, b) : make_pair(b, a.t360()));
}

Angle operator+(Angle a, Angle b) { // where b is a vector
	Angle r(a.x + b.x, a.y + b.y, a.t);
	if (r > a.t180()) r.t--;
	return r.t180() < a ? r.t360() : r;
}

struct Train {
    int idx;
    int ord;
    int x, y;
    int cap;
    vector<int> persons;
};

struct Person {
    int idx;
    int x, y;
};

vector<Train> trains;
vector<Person> persons;
vector<pii> origPersons;

double tang(Train a, Person b) {
    double aang = atan2(a.y, a.x);
    double bang = atan2(b.y, b.x);
    double res = fmod(abs(bang - aang), 2*M_PI);
    if (res > M_PI) res = 2*M_PI - res;
    return res;
}
double BAminusCB(Train a, Person b, Train c) {
    double aang = atan2(a.y, a.x);
    double bang = atan2(b.y, b.x);
    double cang = atan2(c.y, c.x);

    double ba = fmod(abs(aang - bang), 2*M_PI);
    if (ba > M_PI) ba = 2*M_PI - ba;
    double cb = fmod(abs(cang - bang), 2*M_PI);
    if (cb > M_PI) cb = 2*M_PI - ba;
    return ba - cb;
}

bool equidistant(Train a, Person b, Train c) {
    return fabs(BAminusCB(a, b, c)) < 1e-13;
}

bool AcloserthanB(Train a, Person b, Train c) {
    return BAminusCB(a, b, c) < 0;
}

int S = 800;
void readInput() {
    srand(time(NULL));
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);

    set<Angle> angset;
    rep(i,-S,S+1) {
        rep(j,-S,S+1) {
            if (i || j) {
                angset.emplace(i, j);
            }
        }
    }
    vector<Angle> allangs(all(angset));
    cerr << sz(allangs) << endl;
    while (sz(allangs) > 200000) {
        int r = rand() % sz(allangs);
        swap(allangs.back(), allangs[r]);
        allangs.pop_back();
    }

    set<pii> Q;
    while (Q.size() != 200000) {
        int x = rand() % 1601 - S;
        int y = rand() % 1601 - S;
        if (x || y) Q.emplace(x, y);

    }

    random_shuffle(all(allangs));
    trav(it, allangs) {
        int mx = 1000;
        if (it.x != 0) mx = min(mx, S / abs(it.x));
        if (it.y != 0) mx = min(mx, S / abs(it.y));
        it.x *= mx;
        it.y *= mx;
    }

    int N = sz(Q);
    int M = sz(allangs);
    origPersons = vector<pii>(all(Q));
    trav(it, Q) {
        persons.push_back(Person());
        persons.back().x = it.first;
        persons.back().y = it.second;
        persons.back().idx = sz(persons) - 1;
    }
    trains.resize(M);
    rep(i,0,M) {
        trains[i].x = allangs[i].x;
        trains[i].y = allangs[i].y;
        trains[i].cap = 10;
        trains[i].idx = i;
    }
}

void sortTrains() {
    sort(all(trains), [](const Train& a, const Train& b) {
        return Angle(a.x, a.y) < Angle(b.x, b.y);
    });
    rep(i,0,sz(trains)) trains[i].ord = i;
}

typedef pair<vector<Train>::iterator, vector<Train>::iterator> TrainPair;


TrainPair getClosest(Person& p) {
    auto it = upper_bound(all(trains), p, [](const Person& p, const Train& t) {
        return Angle(p.x, p.y) < Angle(t.x, t.y);
    });
    if (it == trains.end()) it = trains.begin();
    auto it2 = (it == trains.begin() ? trains.end() : it);
    --it2;
    return make_pair(it2, it);
}
bool optimal(int p, int t) {
    TrainPair tp = getClosest(persons[p]);
    double aang = tang(*tp.first, persons[p]);
    double bang = tang(*tp.second, persons[p]);
    double closest = min(aang, bang);
    double claim = tang(trains[t], persons[p]);

    if (p == 499683 && t == 401868) {
        cerr << claim << " " << closest << " " << tp.first->idx << " " << tp.second->idx << endl;
    }
    return claim < closest || fabs(claim - closest) < 1e-13;
}

void placePerson(Train& train, Person& p) {
    //assert(optimal(p.idx, train.idx));
    if (train.cap) {
        train.persons.push_back(p.idx);
        --train.cap;
    }
}

void removeUniquePersons() {
    vector<Person> rem;
    trav(p, persons) {
        TrainPair tp = getClosest(p);
        Train &a = *tp.first, &b = *tp.second;
        assert((a.ord + 1) % sz(trains) == b.ord);
        if (Angle(p.x, p.y) == Angle(a.x, a.y)) {
            placePerson(a, p);
        } else if (Angle(p.x, p.y) == Angle(b.x, b.y)) {
            placePerson(b, p);
        } else if (AcloserthanB(a, p, b)) {
            placePerson(a, p);
        } else if (AcloserthanB(b, p, a)) {
            placePerson(b, p);
        } else {
            rem.push_back(p);
        }
    }
    persons = rem;
}

void addTo(Train& t, int cnt, vi& p) {
    while (cnt--) {
        assert(!p.empty());
        assert(t.cap >= 0);
        t.persons.push_back(p.back());
        t.cap--;
        p.pop_back();
    }
}

template<class T> T edmondsKarp(vector<map<int, T> >& graph, int source, int sink) {
	if(source == sink) return numeric_limits<T>::max();
	T flow = 0;
	vi prev(sz(graph)), bfs = prev;

	for (;;) {
		fill(all(prev), -1);
		int bfsEnd = 0;
		prev[source] = -2;
		bfs[bfsEnd++] = source;

		for(int i = 0; i < bfsEnd && prev[sink] == -1; ++i) {
			int x = bfs[i];
			trav(e, graph[x]) {
				if(prev[e.first] == -1 && e.second > 0) {
					prev[e.first] = x;
					bfs[bfsEnd++] = e.first;
				}
			}
		}

		if(prev[sink] == -1) break;
		T incrFlow = numeric_limits<T>::max();
		for(int y = sink; prev[y] != -2; y = prev[y])
			incrFlow = min(incrFlow, graph[prev[y]][y]);

		flow += incrFlow;
		for(int y = sink; prev[y] != -2; y = prev[y]) {
			int x = prev[y];
			if((graph[x][y] -= incrFlow) <= 0) graph[x].erase(y);
			graph[y][x] += incrFlow;
		}
	}
	return flow;
}

void solveAmbiguous() {
    vector<vi> ambigs(sz(trains));
    trav(p, persons) {
        ambigs[(getClosest(p).first->ord + 1)%sz(trains)].push_back(p.idx);
    }
    vi fwd(sz(ambigs)), bwd(sz(ambigs));
#define SOURCE 0
#define SINK 1
#define TRAIN(x) (SINK + 1 + (x))
#define PERSON(x) (TRAIN(sz(trains)) + x)
    vector<map<int, int>> G(PERSON(sz(ambigs)));
    rep(i,0,sz(trains)) {
        G[SOURCE][TRAIN(i)] = trains[i].cap;
        G[TRAIN(i)][PERSON(i)] = 10000000;
        G[TRAIN(i)][PERSON((i + 1)%sz(ambigs))] = 10000000;
        G[PERSON(i)][SINK] = sz(ambigs[i]);
    }
    edmondsKarp(G, SOURCE, SINK);
    rep(i,0,sz(trains)) {
        bwd[i] = 10000000 - G[TRAIN(i)][PERSON(i)];
        fwd[i] = 10000000 - G[TRAIN(i)][PERSON((i + 1)%sz(ambigs))];
    }

    rep(i,0,sz(trains)) {
        vi& b = ambigs[i];
        vi& f = ambigs[(i + 1) % sz(ambigs)];
        assert(trains[i].cap >= fwd[i] + bwd[i]);
        addTo(trains[i], bwd[i], b);
        addTo(trains[i], fwd[i], f);
    }
}

void printResults() {
    int oktrains = 0;
    trav(t, trains) {
        oktrains += !t.persons.empty();
    }
    cout << sz(origPersons) << " " << oktrains << endl;
    trav(it, origPersons) cout << it.first << " " << it.second << endl;
    trav(it, trains) {
        if (!it.persons.empty()) {
            int ot = sz(it.persons);
            if (ot > 1 && rand() % 25 == 0) --ot;
            cout << it.x << " " << it.y << " " << ot << endl;
        }
    }
}

int main() {
    srand(time(NULL));
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);

    readInput();
    sortTrains();
    removeUniquePersons();
    solveAmbiguous();
    printResults();
}
