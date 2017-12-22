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

void assert_done(istream& is) {
	try {
		string dummy;
		is >> dummy;
		wrong_answer("extraneous data");
	} catch(...) {}
}

const double PREC = 1e-9;

double computeTime(vector<double>& P, double l, double a, double b, double T, double r, vi seq) {
    int n = sz(P);
#define BEGIN -1
#define BUY_COFFEE(i) (3*i)
#define START_RUN(i) (3*i + 1)
#define END_RUN(i) (3*i + 2)
#define END (END_RUN(n - 1) + 1)
#define IS_BEGIN(x) ((x) == BEGIN)
#define IS_END(x) ((x) == END)
#define IS_BUY(x) ((x)%3 == 0)
#define IS_STARTRUN(x) ((x)%3 == 1)
#define IS_ENDRUN(x) ((x)%3 == 2)
    vector<pair<double, int>> events;
    events.emplace_back(0, BEGIN);
    trav(j, seq) {
        events.emplace_back(P[j], BUY_COFFEE(j));
        events.emplace_back(P[j] + a * T, START_RUN(j));
        events.emplace_back(P[j] + a * T + b * r, END_RUN(j));
    }
    events.emplace_back(l, END);
    sort(all(events));
    double t = 0;
    int lastBuy = -1;
    int isRunning = -1;
    double currentPos = 0;
    trav(it, events) {
        double newPos = it.first;
        t += (newPos - currentPos) / ((isRunning >= 0) ? b : a);
        if (IS_BEGIN(it.second)) {}
        else if (IS_END(it.second)) { break; }
        else if (IS_BUY(it.second)) { isRunning = -1; lastBuy = it.second / 3; }
        else if (IS_STARTRUN(it.second) && it.second / 3 == lastBuy) { isRunning = lastBuy; }
        else if (IS_ENDRUN(it.second) && it.second / 3 == isRunning) { isRunning = -1; }
        currentPos = newPos;
    }
    return t;
}

int main(int argc, char** argv) {
    init_io(argc, argv);

    double l, a, b, t, r;
    judge_in >> l >> a >> b >> t >> r;
    int n;
    judge_in >> n;
    vector<double> P(n);
    trav(it, P) judge_in >> it;

	int judgen;
	judge_ans >> judgen;
    vector<int> judgeSeq(judgen);
    trav(it, judgeSeq) judge_ans >> it;

	try {
        author_out.exceptions(author_out.failbit | author_out.badbit);

        int teamn;
        author_out >> teamn;
        if (teamn < 0 || teamn > n) {
            wrong_answer("Invalid number of coffee carts (%d) used", teamn);
        }
        vector<int> teamSeq(teamn);
        trav(it, teamSeq) author_out >> it;
        assert_done(author_out);

        sort(all(teamSeq));
        if (unique(all(teamSeq)) != teamSeq.end()) {
            wrong_answer("Indexes were not unique");
        }
        trav(it, teamSeq) {
            if (!(0 <= it && it < n)) wrong_answer("Index is out of range");
        }
        double judgeAns = computeTime(P, l, a, b, t, r, judgeSeq);
        double teamAns = computeTime(P, l, a, b, t, r, teamSeq);
        if (fabs(judgeAns - teamAns) < PREC) accept();
        if (fabs(teamAns - judgeAns) / judgeAns < PREC) accept();
        wrong_answer("Expected value %lf, got value %lf.  Abs error %lf, rel error %lf",
                     judgeAns, teamAns, fabs(judgeAns - teamAns), fabs(teamAns - judgeAns) / judgeAns);
	} catch(...) {
		wrong_answer("IO failure");
	}
}
