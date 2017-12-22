// Solution by Markus Dregi
// Runs the 5^k n algorithm up to some threshold and then concludes with
// whatever it has found so far.

#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cmath>

#define IN 0
#define OUT 1
#define FREE 2

using namespace std;

vector< vector<int> > graph;
vector< vector<bool> > adjacent;
vector<int> degree;
vector<int> status;

int k, n;

int counter = 0;
int CUTOFF = 1000000;

int branch(const int& next, const vector<int>& branch_vertices, const int& target);
int solve(int bv, const int& target);

int branch(const int& next, const vector<int>& branch_vertices, const int& target)
{
    // Locate the free neighbours of the branching vertex
    vector<int> new_outs;

    for(int i = 0; i < branch_vertices.size(); ++i)
        for(int j = 0; j < graph[branch_vertices[i]].size(); ++j)
            if(status[graph[branch_vertices[i]][j]] == FREE)
                new_outs.push_back(graph[branch_vertices[i]][j]);

    // Update status
    for(int i = 0; i < new_outs.size(); ++i)
        status[new_outs[i]] = OUT;
    for(int i = 0; i  < branch_vertices.size(); ++i)
        status[branch_vertices[i]] = IN;

    // Recurse
    int size = branch_vertices.size();
    size += solve(next, target-size);

    // Reset status
    for(int i = 0; i < new_outs.size(); ++i)
        status[new_outs[i]] = FREE;
    for(int i = 0; i  < branch_vertices.size(); ++i)
        status[branch_vertices[i]] = FREE;

    return size;
}

int solve(int bv, const int& target)
{
    if(++counter > CUTOFF)
        return 0;

    if(target <= 0)
        return 0;

    while(bv < n && status[bv] != FREE)
        ++bv;

    if(bv == n)
        return 0;

    vector<int> branch_set(1, bv);
    int best = branch(bv+1, branch_set, target);

    for(int i = 0; i < graph[bv].size() && best < target; ++i) {
        if(status[graph[bv][i]] == FREE) {
            branch_set[0] = graph[bv][i];
            best = max(best, branch(bv+1, branch_set, target));
        }
    }

    return best;
}

int main()
{
    // Read Input
    cin >> k >> n;

    if(n >= 5*k-4) {
        cout << "possible" << endl;
        return 0;
    }

    graph = vector< vector<int> >(n);
    adjacent = vector< vector<bool> >(n, vector<bool>(n, false));
    degree = vector<int>(n);
    status = vector<int>(n, FREE);

    for(int i = 0; i < n; ++i) {
        cin >> degree[i];

        for(int j = 0; j < degree[i]; ++j) {
            int nghbr;
            cin >> nghbr;
            graph[i].push_back(nghbr-1);
            adjacent[i][nghbr-1] = true;
        }
    }

    // Output
    cout << (solve(0, k) >= k ? "possible" : "impossible") << endl;

    return 0;
}
