// Solution by Markus Dregi
//
// If it finds a simplicial vertex, it adds it to the solution. Otherwise it
// finds a lowest degree neighbour and branches on it.
//
// Complexity: <= 5^k n


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

// Finds a good vertex to branch on. Either a simplicial vertex or a low-degree
void search(int& bv, bool& simplicial)
{
    simplicial = false;
    bv = -10;
    int min_deg = 10;

    for(int i = 0; i < n; ++i) {
        if(status[i] != FREE)
            continue;

        bool s = true;
        int d = 0;
        for(int j = 0; j < graph[i].size(); ++j) {
            if(status[graph[i][j]] != FREE)
                continue;
            ++d;

            for(int k = j+1; k < graph[i].size() && s; ++k)
                s &= (status[graph[i][k]] != FREE ||
                        adjacent[graph[i][j]][graph[i][k]]);

        }

        if(s) {
            bv = i;
            simplicial = true;
            return;
        } else if(d < min_deg) {
            bv = i;
            min_deg = d;
        }
    }
}

int branch(const vector<int>& branch_vertices, const int& target);
int solve(const int& target);

// Adds branch_vertices to the solution and searches for a solution of size
// target.
int branch(const vector<int>& branch_vertices, const int& target)
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
    size += solve(target-size);

    // Reset status
    for(int i = 0; i < new_outs.size(); ++i)
        status[new_outs[i]] = FREE;
    for(int i = 0; i  < branch_vertices.size(); ++i)
        status[branch_vertices[i]] = FREE;

    return size;
}

// Searches for a solution of size target
int solve(const int& target)
{
    if(target <= 0)
        return 0;

    bool simplicial;
    int bv;
    search(bv, simplicial);

    if(bv < 0)
        return 0;

    vector<int> branch_set(1, bv);
    int best = branch(branch_set, target);

    if(!simplicial) {
        for(int i = 0; i < graph[bv].size() && best < target; ++i) {
            if(status[graph[bv][i]] == FREE) {
                branch_set[0] = graph[bv][i];
                best = max(best, branch(branch_set, target));
            }
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
    cout << (solve(k) >= k ? "possible" : "impossible") << endl;

    return 0;
}
