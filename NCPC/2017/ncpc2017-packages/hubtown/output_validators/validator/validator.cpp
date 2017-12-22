// usage: ./a.out input_file correct_output output_dir < contestants_output

#include <bits/stdc++.h>
#include "validate.h"
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(it, v) for(auto& it : v)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long ll;


void assert_done(istream& is) {
	try {
		string dummy;
		is >> dummy;
		wrong_answer("extraneous data");
	} catch(...) {}
}

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
	return make_tuple(a.t, a.quad(), a.y * (ll)b.x) <
	       make_tuple(b.t, b.quad(), a.x * (ll)b.y);
}
bool operator==(Angle a, Angle b) {
    return !(a < b) && !(b < a);
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

typedef pair<vector<Train>::iterator, vector<Train>::iterator> TrainPair;

void sortTrains() {
    sort(all(trains), [](const Train& a, const Train& b) {
        return Angle(a.x, a.y) < Angle(b.x, b.y);
    });
    rep(i,0,sz(trains)) trains[i].ord = i;
}

TrainPair getClosest(Person& p) {
    auto it = upper_bound(all(trains), p, [](const Person& p, const Train& t) {
        return Angle(p.x, p.y) < Angle(t.x, t.y);
    });
    if (it == trains.end()) it = trains.begin();
    auto it2 = (it == trains.begin() ? trains.end() : it);
    --it2;
    return make_pair(it2, it);
}

double tang(Train a, Person b) {
    double aang = atan2(a.y, a.x);
    double bang = atan2(b.y, b.x);
    double res = fmod(abs(bang - aang), 2*M_PI);
    if (res > M_PI) res = 2*M_PI - res;
    return res;
}

vector<int> tidx;
bool optimal(int p, int t) {
    TrainPair tp = getClosest(persons[p]);
    double aang = tang(*tp.first, persons[p]);
    double bang = tang(*tp.second, persons[p]);
    double closest = min(aang, bang);


    double claim = tang(trains[tidx[t]], persons[p]);
    return claim < closest || fabs(claim - closest) < 1e-13;
}

int main(int argc, char** argv) {
    init_io(argc, argv);

    int N, M;
    judge_in >> N >> M;
    persons.resize(N);
    rep(i,0,N) {
        judge_in >> persons[i].x >> persons[i].y;
        persons[i].idx = i;
    }
    trains.resize(M);
    rep(i,0,M) {
        judge_in >> trains[i].x >> trains[i].y >> trains[i].cap;
        trains[i].idx = i;
    }
    judge_in.close();
    sortTrains();
    tidx.resize(M);
    rep(i,0,M) tidx[trains[i].idx] = i;

    int judgeAns;
	judge_ans >> judgeAns;
	judge_ans.close();

	try {
        author_out.exceptions(author_out.failbit | author_out.badbit);

        int teamAns;
        if (!(author_out >> teamAns)) {
            wrong_answer("Could not read team answer");
        }
        if (teamAns < 0 || teamAns > N) {
            wrong_answer("Number of people given (%d) out of range", teamAns);
        }
        set<int> placedPersons;
        rep(i,0,teamAns) {
            int p, t;
            if (!(author_out >> p >> t)) wrong_answer("Could not read assignments");
            cerr << "person " << p << " train " << t << endl;
            if (!(0 <= p && p < N)) wrong_answer("Person out of range");
            if (!(0 <= t && t < M)) wrong_answer("train out of range");
            if (trains[tidx[t]].cap == 0) wrong_answer("Overloading a train");
            if (!optimal(p, t)) wrong_answer("Person is too far away from train");
            if (placedPersons.find(p) != placedPersons.end()) wrong_answer("Person is already placed");
            --trains[tidx[t]].cap;
            placedPersons.insert(p);
        }
        if (teamAns > judgeAns) {
            judge_error("Team presented a valid solution that is better than jury???");
        }
        if (teamAns != judgeAns) {
            wrong_answer("Incorrect number of civilians");
        }
	} catch(...) {
		wrong_answer("IO failure");
	}
    accept();
}
