// Solution by Markus Dregi

#include<iostream>
#include<vector>

#define UNDECIDED 1<<20

using namespace std;

bool propagate(int pos,
        const vector< vector<int> >& graph,
        const vector< vector<int> >& req,
        vector<int>& guards)
{
    for(int i = 0; i < graph[pos].size(); ++i) {
        int nbr = graph[pos][i];
        int r = req[pos][i];

        if(guards[pos] > r || guards[pos]+1 < r)
            return false;
        if(guards[nbr] != UNDECIDED && guards[nbr] + guards[pos] != r)
            return false;

        if(guards[nbr] != UNDECIDED)
            continue;

        guards[nbr] = r-guards[pos];

        if(!propagate(nbr, graph, req, guards))
            return false;
    }

    return true;
}

bool find_coloring(int pos,
        const int& pos_col,
        const vector< vector<int> >& graph,
        vector<int>& color,
        vector<int>& color_counter)
{
    if(color[pos] != UNDECIDED)
        return color[pos] == pos_col;

    color[pos] = pos_col;
    ++color_counter[pos_col];

    for(int i = 0; i < graph[pos].size(); ++i)
        if(!find_coloring(graph[pos][i], (pos_col+1)%2,
                    graph, color, color_counter))
            return false;

    return true;
}

int main()
{
    // Read input
    int n,m;
    cin >> n >> m;

    vector< vector<int> > graph(n);
    vector< vector<int> > req(n);

    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;

        graph[a-1].push_back(b-1);
        graph[b-1].push_back(a-1);

        req[a-1].push_back(c);
        req[b-1].push_back(c);
    }

    // Propagate
    vector<int> guards(n, UNDECIDED);
    bool valid = true;

    for(int v = 0; v < graph.size() && valid; ++v) {
        for(int i = 0; i < graph[v].size() && valid; ++i) {
            int nbr = graph[v][i];
            int r = req[v][i];

            if(guards[v]+guards[nbr] != r && r != 1) {
                guards[v] = r/2;
                valid &= propagate(v, graph, req, guards);
            }
        }
    }

    int sol = 0;
    for(int i = 0; i < guards.size(); ++i)
        if(guards[i] != UNDECIDED)
            sol += guards[i];

    // Color
    vector<int> color = guards;

    for(int i = 0; i < color.size() && valid; ++i) {
        if(color[i] == UNDECIDED) {
            vector<int> color_counter(2);
            valid &= find_coloring(i, 0, graph, color, color_counter);
            sol += min(color_counter[0], color_counter[1]);
        }
    }

    if(valid)
        cout << sol << endl;
    else
        cout << "impossible" << endl;

    return 0;
}
