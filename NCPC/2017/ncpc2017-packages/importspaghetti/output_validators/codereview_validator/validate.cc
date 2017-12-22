#include <vector>
#include <map>
#include <set>
#include "validate.h"

using namespace std;

const int MAX_NAME_LENGTH = 8;
const int MAX_FILE_COUNT = 1000; // auto-reject answers longer than this
typedef map<string, set<string>> graph;

void read_import_line(istream &in, set<string> &res) {
    string line, token;
    getline(in, line);
    istringstream tokenizer(line);
    tokenizer >> token; // skip "import"
    while (tokenizer >> token) {
        if (token.back() == ',') token.pop_back();
        res.insert(token);
    }
}

graph read_input(istream &in) {
    graph res;
    int n;
    string line;
    in >> n;
    for (int i = 0; i < n; ++i) {
        in >> line;
        res[line] = set<string>();
    }
    getline(in, line); // eat rest of line containing list of names
    for (int i = 0; i < n; ++i) {
        string name;
        int k;
        in >> name >> k;
        getline(in, line); // eat rest of header line
        set<string> &dest = res[name];
        for (int i = 0; i < k; ++i)
            read_import_line(in, dest);
    }
    return res;
}

vector<string> read_solution(istream &in, feedback_function feedback) {
    vector<string> res;
    string name;
    while (in >> name) {
        if (name.length() > MAX_NAME_LENGTH) {
            feedback("Invalid file name '%s'\n", name.c_str());
        }
        res.push_back(name);
        if (res.size() > MAX_FILE_COUNT) {
            feedback("Too long answer (more than %d items)\n", MAX_FILE_COUNT);
        }
    }
    return res;
}

// Returns -1 if "SHIP IT", otherwise length of cycle
// Calls feedback on any error
int check_solution(const graph &G, vector<string> tokens, feedback_function feedback) {
    if (tokens.size() == 2 && tokens[0] == "SHIP" && tokens[1] == "IT") {
        return -1;
    }
    if (tokens.size() == 0) {
        feedback("Empty output?");
    }
    int size = tokens.size();
    tokens.push_back(tokens.front());
    for (int i = 0; i < size; ++i) {
        auto adj = G.find(tokens[i]);
        if (adj == G.end()) {
            feedback("Output contains file '%s' that does not exist", tokens[i].c_str());
        }
        if (adj->second.find(tokens[i+1]) == adj->second.end()) {
            feedback("Missing edge: %s does not import %s", tokens[i].c_str(), tokens[i+1].c_str());
        }
    }
    return size;
}

int main(int argc, char **argv) {
    init_io(argc, argv);

    graph G = read_input(judge_in);

    vector<string> Out = read_solution(cin, wrong_answer);
    vector<string> Ans = read_solution(judge_ans, judge_error);

    int OutVal = check_solution(G, Out, wrong_answer);
    int AnsVal = check_solution(G, Ans, judge_error);

    if (OutVal == -1 && AnsVal != -1) {
        wrong_answer("Output claims no cycle but there is a cycle");
    } else if (OutVal != -1 && AnsVal == -1) {
        judge_error("Answer claims no cycle, but output found a cycle");
    } else if (OutVal < AnsVal) {
        judge_error("Output found shorter cycle (length %d) than judge answer (length %d)", OutVal, AnsVal);
    } else if (OutVal > AnsVal) {
        wrong_answer("Output had cycle of length %d, shortest cycle is %d", OutVal, AnsVal);
    }

    accept();
}
