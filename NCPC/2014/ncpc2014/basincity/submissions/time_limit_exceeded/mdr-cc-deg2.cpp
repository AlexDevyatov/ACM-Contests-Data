// Solution by Markus Dregi
// Splits into connected components, applies special rule on vertices of degree
// at most 2. Always branches on lowest degree vertex.
// Complexity: 5^k n

#include<iostream>
#include<queue>
#include<vector>
#include<string>

#define IN 0
#define OUT 1
#define FREE 2

using namespace std;

vector< vector<int> > graph;
vector< vector<bool> > adjacent;
vector<int> degree;
vector<int> status;
vector<int> visited;
int seen = 0;

int k, n;

int get_degree(const int& v)
{
    int dv = 0;
    for(int i = 0; i < graph[v].size(); ++i)
        if(status[graph[v][i]] == FREE)
            ++dv;

    return dv;
}

// Finds a low degree vertex in the component of pos induced by only FREE
// vertices
void search(int& pos, int& cc_size, int& min_deg)
{
    ++seen;

    queue<int> next;
    next.push(pos); 
    visited[pos] = seen;

    min_deg = get_degree(pos);
    cc_size = 0;
    while(!next.empty()) {
        int v = next.front();
        next.pop();
        int dv = get_degree(v);
        ++cc_size;

        if(dv < min_deg) {
            pos = v;
            min_deg = dv;
        }

        for(int i = 0; i < graph[v].size(); ++i) {
            int nghbr = graph[v][i];
            if(status[nghbr] == FREE && visited[nghbr] != seen) {
                visited[nghbr] = seen;
                next.push(nghbr);
            }
        }
    }
}

int branch(const vector<int>& branch_vertices, const int& target);
int solve(int pos, int target);

int branch(const vector<int>& branch_vertices, const int& target)
{
    int fresh = seen;

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
    for(int j = 0; j < new_outs.size() && size < target; ++j) {
        for(int k = 0; k < graph[new_outs[j]].size() && size < target; ++k) {
            int next = graph[new_outs[j]][k];
            if(status[next] == FREE && visited[next] <= fresh)
                size += solve(next, target-size);
        }
    }

    // Reset status
    for(int i = 0; i < new_outs.size(); ++i)
        status[new_outs[i]] = FREE;
    for(int i = 0; i  < branch_vertices.size(); ++i)
        status[branch_vertices[i]] = FREE;

    return size;
}

int solve(int pos, int target)
{
    if(target <= 0)
        return 0;

    // Finds the lowest degree vertex and the size of the free
    // component of pos 
    int cc_size, min_deg;
    search(pos, cc_size, min_deg);

    // If component is large, we are done
    if(cc_size >= 6+4*(target-2)) {
        return target;
    }

    if(min_deg <= 1) {
        return branch(vector<int>(1, pos), target);
    } else {
        vector< vector<int> > branch_set(1, vector<int>(1, pos));

        if(min_deg == 2) {
            branch_set.push_back(vector<int>());
            for(int i = 0; i < graph[pos].size(); ++i)
                if(status[graph[pos][i]] == FREE)
                    branch_set[1].push_back(graph[pos][i]);

            if(adjacent[branch_set[1][0]][branch_set[1][1]])
                return branch(branch_set[0], target);
        } else {
            for(int i = 0; i < graph[pos].size(); ++i)
                if(status[graph[pos][i]] == FREE)
                    branch_set.push_back(vector<int>(1, graph[pos][i]));
        }

        int best = 0;
        for(int i = 0; i < branch_set.size(); ++i) {
            int size = branch(branch_set[i], target);

            if(best < size)
                best = size;

            if(best >= target)
                break;
        }    

        return best;
    }
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
    visited = vector<int>(n, 0);

    for(int i = 0; i < n; ++i) {
        cin >> degree[i];

        for(int j = 0; j < degree[i]; ++j) {
            int nghbr;
            cin >> nghbr;
            graph[i].push_back(nghbr-1);
            adjacent[i][nghbr-1] = true;
        }
    }

    // Solve
    int ans = 0;
    for(int i = 0; i < n; ++i) {
        if(visited[i] == 0) {
            ans += solve(i, k-ans);
        }
        if(ans >= k)
            break;
    }

    // Output
    cout << (ans >= k ? "possible" : "impossible") << endl;

    return 0;
}
