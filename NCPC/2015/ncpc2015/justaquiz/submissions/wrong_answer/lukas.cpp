//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef vector<double> vd;
struct Node {
    unordered_map<string, int> next;
    unordered_map<string, int> answers;
    double probability;
    int total_answers;
};
vector<Node> nodes;
template <typename T>
void improveMax(T &a, T b)
{
    a = max(a, b);
}
double traverse(int j, vd::iterator it, int left)
{
    if (left == 0) return 0;
    double now = nodes[j].probability + *it;
    double move = 0;
    for (auto& w : nodes[j].next)
        move += traverse(w.second, it + 1, left - 1) * nodes[w.second].answers.size();

    return max(now, move / nodes[j].answers.size());
}

int main()
{
    nodes.push_back(Node());

    int t, n; scanf("%d %d", &t, &n);
    string s; getline(cin, s);
    rep(i,0,n)
    {
        getline(cin, s);
        stringstream w(s);
        vector<string> words;
        while (w >> s) words.push_back(s);
        words[words.size() - 2].pop_back();

        string answer = words.back();
        nodes[0].answers[answer]++;
        words.pop_back();

        int index = 0;
        for (string &cur : words)
        {
            if (!nodes[index].next.count(cur))
            {
                nodes[index].next[cur] = nodes.size();
                nodes.push_back(Node());
            }
            index = nodes[index].next[cur];
            nodes[index].answers[answer]++;
        }
    }

    for (Node &node : nodes)
    {
        int s = 0, ma = 0;
        for (auto& w : node.answers)
        {
            s += w.second;
            improveMax(ma, w.second);
        }
        node.probability = ma / double(s);
        node.total_answers = s;
    }

    vector<double> best(t + 1);
    for (int i = t - 1; i >= 0; i--)
        best[i] = traverse(0, best.begin() + i + 1, t - i);

    printf("%.10lf\n", best[0]);
}
