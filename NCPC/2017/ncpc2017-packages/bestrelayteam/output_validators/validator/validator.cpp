#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <cmath>
#include "validate.h"

using namespace std;

const double PREC = 1e-9;

bool almost_same(double d1, double d2) {
  return fabs(d1 - d2) < PREC;
}

void assert_done(istream& is) {
	try {
		string dummy;
		is >> dummy;
		wrong_answer("extraneous data: " + dummy);
	} catch(...) {}
}

int main(int argc, char** argv) {
    init_io(argc, argv);

  int n;
  map<string, double> first, second;
  judge_in >> n;
  for(int i=0;i<n;i++) {
    string s;
    double t1, t2;
    judge_in >> s >> t1 >> t2;
    first[s] = t1;
    second[s] = t2;
  }

  double judge_answer, answer;
  judge_ans >> judge_answer;

  author_out.exceptions(author_out.failbit | author_out.badbit);
  try {
    author_out >> answer;
    if (!almost_same(answer, judge_answer)) {
      wrong_answer("got %lf, expected %lf", answer, judge_answer);
    }

    set<string> used;
    double tm = 0.0;
    for(int i=0;i<4;i++) {
      string s;
      if (!(author_out >> s)) wrong_answer("input ended after reading %d names", i);
      if (used.count(s)) wrong_answer("%s used twice", s.c_str());
      used.insert(s);
      if (first.find(s) == first.end()) wrong_answer("invalid name: %s", s.c_str());
      tm += i == 0 ? first[s] : second[s];
    }

    if (!almost_same(answer, tm)) wrong_answer("Specified runners time %lf doesn't add up to the given time %lf", answer, tm);
    assert_done(author_out);

    accept();
  } catch(...) {
    wrong_answer("IO failure");
  }
}
