#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>
#include <map>
#include <climits>
#include <cstdio>
#include <set>
#include <bitset>
using namespace std;
#define db(a) (cout << (#a) << " = " << (a) << endl)
typedef long long ll;

/** Dijkstra - Mark multiple paths
		AdjList because duplicate edges are allowed.
**/

#define INF (INT_MAX/2)

int N,M,K;
vector<pair<int, int>> A[10001];
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
int dist[10001];
int counter[10001];


int main()
{  
	cin>>N>>M>>K;
	int a,b,c;
	for(int i=0;i<K;i++) cin>>a;
	for(int i=0;i<N;i++) A[i].clear();
	for(int i=0;i<N;i++) dist[i] = INF;
	for(int i=0;i<N;i++) counter[i] = 0;	
	for(int i=0;i<M;i++)
	{
		cin>>a>>b>>c;
		a--; b--;
		A[a].push_back(pair<int,int>(b, c));
		A[b].push_back(pair<int,int>(a, c));
	}
	dist[0] = 0;
	counter[0] = 1;
	pq.push(pair<int,int>(0, 0));
	while(!pq.empty())
	{
		int v = pq.top().second;
		int curDist = pq.top().first;
		pq.pop();
		if(curDist > dist[v]) continue;
		for(int j=0;j<(int)A[v].size();j++)
		{
			int u = A[v][j].first;
			int w = A[v][j].second;						
			int newDist = curDist + w;			
			if(newDist == dist[u]) counter[u] = max(2, counter[u] + counter[v]);
			else if(newDist < dist[u])
			{
				dist[u] = newDist;
				counter[u] = counter[v];								
				pq.push(pair<int,int>(newDist, u));
			}				
		}
	}	
	if(counter[N-1] > 1) cout << "yes\n";
	else cout << "no\n";
	return 0;
}


