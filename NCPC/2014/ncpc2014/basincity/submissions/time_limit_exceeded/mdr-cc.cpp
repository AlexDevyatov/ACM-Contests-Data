// Brute force solution by Markus Dregi
// Splits into connected components, applies special rule on leaves
// and then does brute force.

#include<iostream>
#include<queue>
#include<vector>
#include<string>

#define IN 0
#define OUT 1
#define FREE 2

using namespace std;

vector< vector<int> > graph;
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

int solve(int pos, int target)
{
    if(target == 0)
        return 0;

    // Finds the lowest degree vertex and the size of the free
    // component of pos 
    int cc_size, min_deg;
    search(pos, cc_size, min_deg);

    // If component is large, we are done
    if(cc_size >= 6+4*(target-2)) {
        return target;
    }

    // Vertices to branch on. If min_deg is at most 1, we can pick the vertex
    // greadily
    vector<int> branch_set(1, pos);
    if(min_deg >= 2) {
        for(int i = 0; i < graph[pos].size(); ++i)
            if(status[graph[pos][i]] == FREE)
                branch_set.push_back(graph[pos][i]);
    }

    // Branch on each vertex in the branch set
    int best = 0;
    for(int i = 0; i < branch_set.size(); ++i) {
        int branch_vertex = branch_set[i];
        int fresh = seen;

        // Locate the free neighbours of the branching vertex
        vector<int> new_outs;

        for(int j = 0; j < graph[branch_vertex].size(); ++j)
            if(status[graph[branch_vertex][j]] == FREE)
                new_outs.push_back(graph[branch_vertex][j]);

        // Update status
        for(int j = 0; j < new_outs.size(); ++j)
            status[new_outs[j]] = OUT;
        status[branch_vertex] = IN;

        int size = 1;

        // Vertices to start from
        vector<int> starting_points;
        for(int j = 0; j < new_outs.size(); ++j)
            for(int k = 0; k < graph[new_outs[j]].size(); ++k)
                if(status[graph[new_outs[j]][k]] == FREE)
                    starting_points.push_back(graph[new_outs[j]][k]);

        // Solve
        for(int j = 0; j < starting_points.size(); ++j)
            if(visited[starting_points[j]] <= fresh)
                size += solve(starting_points[j], target-size);

        // Reset status
        for(int j = 0; j < new_outs.size(); ++j)
            status[new_outs[j]] = FREE;
        status[branch_vertex] = FREE;                    

        if(best < size)
            best = size;

        if(best >= target)
            break;
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
    degree = vector<int>(n);
    status = vector<int>(n, FREE);
    visited = vector<int>(n, 0);

    for(int i = 0; i < n; ++i) {
        cin >> degree[i];

        for(int j = 0; j < degree[i]; ++j) {
            int nghbr;
            cin >> nghbr;
            graph[i].push_back(nghbr-1);
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
