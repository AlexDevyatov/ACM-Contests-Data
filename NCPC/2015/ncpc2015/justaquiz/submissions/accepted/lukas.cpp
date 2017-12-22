//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

struct Node {
    unordered_map<string, int> next;
    unordered_map<string, int> answers;
    double probability; // probability of being right if picking the most common answer in the subtree
    int total_answers;
};
vector<Node> nodes(1, Node());
double traverse(int j, vector<double>::iterator it, int left)
{
    if (left == 0) return 0;
    double now = nodes[j].probability + *it; // answer now and move to the next question
    double move = 0;
    for (auto& w : nodes[j].next) // wait for the next word
        move += traverse(w.second, it + 1, left - 1) * nodes[w.second].total_answers;

    return max(now, move / nodes[j].total_answers);
}

int main()
{
    int t, n; scanf("%d %d", &t, &n);
    string s; getline(cin, s);
    rep(i,0,n)
    {
        getline(cin, s);
        stringstream w(s);
        vector<string> words;
        while (w >> s) words.push_back(s);

        string answer = words.back();
        words.pop_back();
        nodes[0].answers[answer]++;

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
            ma = max(ma, w.second);
        }
        node.probability = ma / double(s);
        node.total_answers = s;
    }

    vector<double> best(t + 1);
    for (int i = t - 1; i >= 0; i--)
        best[i] = traverse(0, best.begin() + i + 1, t - i);

    printf("%.10lf\n", best[0]);
}
