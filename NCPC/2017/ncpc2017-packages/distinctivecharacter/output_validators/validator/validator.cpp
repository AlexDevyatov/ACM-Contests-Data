// usage: ./a.out input_file correct_output output_dir < contestants_output

#include <iostream>
#include <fstream>
#include <vector>
#include "validate.h"

using namespace std;

int n, k;
vector<string> v;

int calc(string x) {
    int r = k;
    for (auto u : v) {
        int d = 0;
        for (int i = 0; i < k; i++) {
            if (u[i] != x[i]) d++;
        }
        r = min(r,d);
    }
    return r;
}

int main(int argc, char **argv) {
    init_io(argc, argv);
    judge_in >> n >> k;
    v.resize(n);
    for (int i = 0; i < n; i++) judge_in >> v[i];
    string s1, s2;
    judge_ans >> s1;
    author_out >> s2;
    if (s1.size() != s2.size()) {
        wrong_answer("Invalid output size\n");
    }
    string extra;
    author_out >> extra;
    if (extra != "") {
        wrong_answer("Output contains extra data\n");
        return 43;
    }
    for (int i = 0; i < k; i++) {
        if (s2[i] != '0' && s2[i] != '1') {
            wrong_answer("Wrong character '%c' in output\n", s2[i]);
        }
    }
    int judge_dist = calc(s1);
    int team_dist = calc(s2);
    if (team_dist > judge_dist) {
        judge_error("Team answer (dist %d) better than judge answer (dist %d)", team_dist, judge_dist);
    }
    if (team_dist < judge_dist) {
        wrong_answer("Team answer (dist %d) worse than judge answer (dist %d)", team_dist, judge_dist);
    }
    accept();
}
