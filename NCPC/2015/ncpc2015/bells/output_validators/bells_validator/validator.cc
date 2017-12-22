#include <utility>
#include <string>
#include <cassert>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include "streamcorr.h"

#include <sstream>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;

bool author_messages = false;

/* Wrapper for author message printing so that they are only printed in
 * case the author_messages option was given.  If the validator should
 * always print author messages, you can just call
 * report_feedback(authormessage, ...) directly.
 */
void author_message(const char *s) {
    if (author_messages) {
        report_feedback(authormessage, s);
    }
}

bool check(int p, vi &a, vi &b)
{
    if (a[p] == b[p]) return true;
    if (p > 0 && a[p] == b[p - 1]) return true;
    if (p + 1 < (int)a.size() && a[p] == b[p + 1]) return true;
    return false;
}

int encode(vi &p)
{
    if (p.size() == 1) return 0;
    int pos = find(p.begin(), p.end(), p.size()) - p.begin();
    int sz = p.size();
    p.erase(p.begin() + pos);
    return pos + encode(p) * sz;
}

/* Check one test case. */
void check_case() {
    int n;
    judge_in >> n;

    vector<vi> perm;
    int fact = 1;
    for (int i = 2; i <= n; i++) fact *= i;

    for (int i = 0; i < fact; i++)
    {
        vi x(n);
        vector<bool> seen(n, false);
        for (int j = 0; j < n; j++)
        {
            if (!(author_out >> x[j]))
                report_error("Wrong output format");
            if (x[j] < 1 || x[j] > n)
                report_error("Output out of range");
            if (seen[x[j] - 1])
                report_error("Not a permutation");
            seen[x[j] - 1] = true;
        }

        perm.push_back(x);
    }

    for (int j = 0; j < n; j++)
        if (perm[0][j] != j + 1)
            report_error("The first line is not the identical permutation");

    for (int i = 1; i < fact; i++)
    {
        for (int j = 0; j < n; j++)
            if (!check(j, perm[i], perm[i - 1]))
                report_error("Permutations are not 1 step away from each other");
    }

    vector<bool> seen(fact, false);
    for (int i = 0; i < fact; i++)
        seen[encode(perm[i])] = true;
    if (count(seen.begin(), seen.end(), false) > 0)
        report_error("Some permutations are missing");

}

int main(int argc, char **argv) {
    init_io(argc, argv);
    /* Check if the author_messages option is given. */
    for (int i = 4; i < argc; ++i)
        if (!strcmp(argv[i], "author_messages"))
            author_messages = true;

    check_case();

    /* Check for trailing output in author file. */
    string trash;
    if (author_out >> trash) {
        author_message("Trailing output after last test case");
        report_error("Trailing output");
    }

    /* Yay! */
    author_message("Thank you for your great code. It was fantastic.");
    accept();
}
