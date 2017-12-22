#include <vector>
#include "validate.h"
using namespace std;

struct Call {
  int a, b, c;
};

int n, c1, c2;
vector<Call> calls;

void read_input(istream &in) {
  int m;
  assert(in >> n >> m >> c1 >> c2);
  calls.resize(m);
  for (int i = 0; i < m; ++i) {
    assert(in >> calls[i].a >> calls[i].b);
    if (calls[i].a % 2 != calls[i].b % 2) {
      assert(in >> calls[i].c);
      if (calls[i].b % 2)
	swap(calls[i].a, calls[i].b);
    } else {
      if (calls[i].a > calls[i].b)
	swap(calls[i].a, calls[i].b);
    }
  }
}

int read_solution(istream &in, feedback_function error) {
  int sol_size;
  if (!(in >> sol_size)) {
    error("Could not read solution size");
  }
  if (sol_size < 0) {
    error("Negative solution size, can't be right...");
  }
  if (sol_size > calls.size()) {
    error("sol_size > #calls, can't be right...");    
  }

  bool has_c1 = false, has_c2 = false;
  vector<int> next_block[2];
  next_block[0].resize(n, 1<<25);
  next_block[1].resize(n, 1<<25);
  for (int i = 0; i < sol_size; ++i) {
    int a, b;
    if (!(in >> a >> b)) {
      error("failed to read item %d/%d in solution, expected two integers", i+1, sol_size);
    }
    if (a < 1 || a > n || b < 1 || b > n) {
      error("sol item %d/%d has invalid street numbers %d %d (outside [1..%d])\n",
	    i+1, sol_size, a, b, n);
    }
    if (a > b) swap(a, b);
    if (a % 2 == b % 2) {
      // along sides
      if (b != a+2) {
	error("sol item %d/%d invalid edge %d %d (non-adjacent)\n", i+1, sol_size, a, b);
      }
      next_block[a%2][a] = a;
    } else {
      // take a crossing
      if (!(b == a+1 && (a == c1 || a == c2))) {
	error("sol item %d/%d invalid crossing %d %d (must be %d %d or %d %d)\n",
	      i+1, sol_size, a, b, c1, c1+1, c2, c2+1);
      }
      (a == c1 ? has_c1 : has_c2) = true;
    }
  }
  for (int i = n-2; i >= 0; --i) {
    next_block[0][i] = min(next_block[0][i], next_block[0][i+1]);
    next_block[1][i] = min(next_block[1][i], next_block[1][i+1]);
  }

  for (auto call: calls) {
    if (call.a % 2 == call.b % 2) {
      assert(call.a < call.b);
      if (next_block[call.a%2][call.a] >= call.b) {
	error("call %d %d is not blocked", call.a, call.b);
      }
    } else {
      assert(call.a % 2 == 1);
      assert(call.b % 2 == 0);
      if (!(call.c == c1 ? has_c1 : has_c2) &&
	  next_block[1][min(call.a, call.c)] >= max(call.a, call.c) &&
	  next_block[0][min(call.b, call.c+1)] >= max(call.b, call.c+1)) {
	error("call %d %d %d is not blocked", call.a, call.b, call.c);
      }
    }
  }

  return sol_size;
}


int main(int argc, char **argv) {
  init_io(argc, argv);

  read_input(judge_in);

  int judge_value = read_solution(judge_ans, judge_error);
  int submission_value = read_solution(author_out, wrong_answer);
  if (submission_value > judge_value)
    wrong_answer("suboptimal solution using %d devices, opt = %d\n", submission_value, judge_value);
  else if (submission_value < judge_value)
    judge_error("solution produced better solution than judge (value %d, judge %d)\n",
		submission_value, judge_value);

  accept();
}
