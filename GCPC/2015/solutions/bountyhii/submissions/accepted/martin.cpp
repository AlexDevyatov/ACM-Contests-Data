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

/** Vertex-Disjoint Min Path Cover on DAG
		
		Given a DAG find the minimum number of vertex-disjoint paths to cover each vertex.
		
		Solution idea: Construct bipartite Graph from DAG. Set Vout contains all vertices
		with their outgoing edges, set Vin contains all vertices with their incoming edges.
		Compute maximal matching M on bipartite Graph with augmenting paths.
		Number of needed paths is then N - M.
		Accepted solutions should be in O(V * E).
**/

#define MAX_V (2*1001)

vector<int> adjList[MAX_V];
int visited[MAX_V];
int match[MAX_V];
int N;

int augment(int v)
{
	if(visited[v] == 1) return 0;
	visited[v] = 1;
	for(int i=0;i<(int)adjList[v].size();i++)
	{
		int u = adjList[v][i];
		if(match[u] == -1 || augment(match[u]) == 1)
		{
			match[u] = v;
			return 1;
		}
	}
	return 0;
}

int mcbm()
{
	int erg = 0;
	for(int j=0;j<MAX_V;j++) match[j] = -1;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<MAX_V;j++) visited[j] = 0;
		erg += augment(i);
	}
	return erg;
}

int main()
{  
 	cin>>N;
	for(int i=0;i<MAX_V;i++) adjList[i].clear();
	for(int i=0;i<N;i++)
	{
		int K;
		cin>>K;
		// Construct bipartite graph with sets Vin and Vout.
		for(int j=0;j<K;j++)
		{
			int P;
			cin>>P;
			adjList[i].push_back(P+N);
		}
	}
	// Solution is number of nodes minus the maximal matching of the bipartite graph.
	cout << N - mcbm() << "\n";

  return 0;
}


