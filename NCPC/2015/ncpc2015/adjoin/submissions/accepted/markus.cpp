#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>

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

vector<int> degree;
int find_dia(const vector<int>& component,
        const vector< vector<int> >& graph) {

    vector<int> leafs(0);
    for(int i = 0; i < component.size(); ++i)
        if(degree[component[i]] < 2)
            leafs.push_back(component[i]);

    int layers = 0;
    int explored = leafs.size();
    while(explored < component.size()) {
        ++layers;
        vector<int> new_leafs(0);

        for(int i = 0; i < leafs.size(); ++i) {
            for(int k = 0; k < graph[leafs[i]].size(); ++k) {
                int nghbr = graph[leafs[i]][k];
                --degree[nghbr];
                if(degree[nghbr] == 1)
                    new_leafs.push_back(nghbr);
            }
        }

        leafs = new_leafs;
        explored += leafs.size();
    }

    return 2*layers + (leafs.size() == 2 ? 1 : 0);
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

    degree = vector<int>(N);
    for(int i = 0; i < N; ++i)
        degree[i] = graph[i].size();

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
