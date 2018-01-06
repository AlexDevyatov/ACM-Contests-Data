#include <cstdio>
#include <iostream>
#include <vector>
#include <queue> 

using namespace std;

struct edge
{
	int first;
	int second;
	long long cap;
	long long flow;
};

const long long INF = 1e18;

int s, t;

vector<edge> e;
vector<int> g[4000];
vector<long long> ans[40010];
int number = 0;

vector<int> d, ptr;


void addEdge(int first, int second, int cap)
{
	edge e1 = {first, second, cap, 0};
	edge e2 ={second, first, 0, 0};

	g[first].push_back((int) e.size());
	e.push_back(e1);

	g[second].push_back((int) e.size());
	e.push_back(e2);
}

bool bfs(int n)
{
	queue<int> q;
	q.push(s);
	
	d.assign(n + 1, -1);

	d[s] = 0;

	while(q.size() && d[t] == -1)
	{
		int v = q.front();
		q.pop();

		vector<int>::iterator iter = g[v].begin();
		for(; iter != g[v].end(); ++iter)
		{
			int to = e[*iter].second;
			if(d[to] == -1 && e[*iter].flow < e[*iter].cap)
			{
				q.push(to);
				d[to] = d[v] + 1;
			}
		}
	}

	return d[t] != -1;
}

long long dfs(int v, long long f)
{
	if(!f)
		return 0;
	if(v == t)
		return f;

	for(; ptr[v] < (int)g[v].size(); ++ptr[v])
	{
		int id = g[v][ptr[v]];
		int	to = e[id].second;

		if(d[to] != d[v] + 1)
			continue;

		long long MIN = min(f, e[id].cap - e[id].flow);
		long long pushed = dfs(to, MIN);

		if(pushed)
		{
			e[id].flow += pushed;
			e[id ^ 1].flow -= pushed;
			ans[number].push_back(id / 2 + 1);
			return pushed;
		}
	}
	return 0;
}

long long dinic(int n)
{
	long long res = 0;

	for(;;)
	{
		if(!bfs(n))
			break;
		
		ptr.assign(n + 1, 0);

		while(long long flow = dfs(s, INF))
		{
			ans[number].push_back(flow);
			++number;

			res += flow;
		}
		ans[number].clear();
	}

	return res;
}

int main()
{
    freopen("experimental.in", "r", stdin);
	freopen("experimental.out", "w", stdout);
	int n, m;
	cin >> n >> m;
    vector< vector<int> > b(n, vector<int>(2));
    for (int i = 0; i < n; i++)
        cin >> b[i][0] >> b[i][1];
    
    for (int i = 0; i < n; i++)
	    b[i][0], b[i][1];
    vector<int> end(m);
    for (int i = 0; i < m; i++)
        cin >> end[i];

    int last = n + m + 1;

    for (int i = 1; i <= n; i++) 
	   addEdge(0, i, 1);
	
    for (int i = 1; i <= n; i++) 
    {
	   addEdge(i, b[i - 1][0] + n, 1);
	   addEdge(i, b[i - 1][1] + n, 1);
	}

	for (int i = n + 1; i <= n + m; i++)
	   addEdge(i, last, end[i - n - 1]);

	d.resize(last + 1);
	ptr.resize(last + 1);
	s = 0, t = last;
	long long res = dinic(last + 1);
    if (res != n) cout << "-1\n"; 
	else
	{
		vector<int> ans(n);
		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j < g[i].size(); j++)
			{
				edge ed = e[g[i][j]];
				if (ed.second != 0 && ed.flow == ed.cap)
					ans[i - 1] = ed.second - n;  
			}
		}
		for (int i = 0; i < n; i++)
			cout << ans[i] << " ";
	}
}