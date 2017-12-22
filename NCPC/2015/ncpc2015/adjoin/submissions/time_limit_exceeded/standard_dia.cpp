#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>

using namespace std;

vector<int> find_component(const int& source,
        const vector< vector<int> >& graph, vector<int>& marked) {
    vector<int> component(0);
    queue<int> next;
    next.push(source);

    marked[source] = source;
    while(!next.empty()) {
        int v = next.front();
        next.pop();
        component.push_back(v);

        for(int i = 0; i < graph[v].size(); ++i) {
            int nghbr = graph[v][i];
            if(marked[nghbr] != source) {
                marked[nghbr] = source;
                next.push(nghbr);
            }
        }
    }

    return component;
}

int find_max_distance(const int& source,
        const vector< vector<int> >& graph) {

    map<int, int> dist;
    queue<int> next;
    next.push(source);
    dist[source] = 0;

    int max_dist = 0;
    while(!next.empty()) {
        int v = next.front();
        next.pop();

        for(int i = 0; i < graph[v].size(); ++i) {
            if(dist.find(graph[v][i]) == dist.end()) {
                dist[graph[v][i]] = dist[v]+1;
                next.push(graph[v][i]);
                max_dist = max(max_dist, dist[graph[v][i]]);
            }
        }
    }

    return max_dist;
}

int find_dia(const vector<int>& component,
        const vector< vector<int> >& graph) {
    int largest_dist = 0;
    for(int i = 0; i < component.size(); ++i)
        largest_dist = max(largest_dist,
                find_max_distance(component[i], graph));

    return largest_dist;
}


int main()
{
    int N, M;
    //cin >> N >> M;
    scanf("%d %d", &N, &M);

    vector< vector<int> > graph(N, vector<int>());
    for(int i = 0; i < M; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        //cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int max_dia = 0;
    vector<int> max_radii(3, 0);
    vector<int> marked(N, -1);

    for(int v = 0; v < N; ++v) {
        if(marked[v] < 0) {
            vector<int> component = find_component(v, graph, marked);
            int dia = find_dia(component, graph);
            max_dia = max(max_dia, dia);

            int radius = dia/2 + dia%2;
            if(radius > max_radii[2]) {
                max_radii[2] = radius;
                for(int i = 2; i > 0; --i)
                    if(max_radii[i] > max_radii[i-1])
                        swap(max_radii[i], max_radii[i-1]);
            }
        }
    }

    cout << max(max_dia, max(
                max_radii[0]+max_radii[1]+1,
                max_radii[1]+max_radii[2]+2)) << endl;
    return 0;
}
