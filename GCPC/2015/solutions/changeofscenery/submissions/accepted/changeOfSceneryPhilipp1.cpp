#include <queue>
#include <stdio.h>

using namespace std;
const int INF = 2000000000;
typedef pair<int,int> PII;

int main(){
	
	int N, M, K;
	scanf ("%d%d%d", &N, &M, &K);
	vector<vector<PII> > edges(N);
	vector<int> shortest(K);
	for (int i = 0; i < K; i++) {
		scanf("%d", &shortest[i]);
	}

	for (int i = 0; i < M; i++){
		int start, end, dist;
		scanf ("%d%d%d", &start, &end, &dist);
		start--;
		end--;
		edges[start].push_back (make_pair (dist, end)); // note order of arguments here
		edges[end].push_back (make_pair (dist, start));
	}
	
	// use priority queue in which top element has the "smallest" priority
	priority_queue<PII, vector<PII>, greater<PII> > Q;
	vector<int> dist(N, INF);
	vector<bool> multiple(N, false);
	vector<bool> finished(N, false);
	Q.push (make_pair (0, 0));
	dist[0] = 0;
	while (!Q.empty()){
		PII p = Q.top();
		Q.pop();
		if (finished[p.second]) continue;
		finished[p.second] = true;
		if (p.second == N - 1) break;
		
		int here = p.second;
		for (vector<PII>::iterator it=edges[here].begin(); it!=edges[here].end(); it++){
			if (dist[here] + it->first < dist[it->second]){
				dist[it->second] = dist[here] + it->first;
				multiple[it->second] = multiple[here];
				Q.push (make_pair (dist[it->second], it->second));
			} else if (dist[here] + it->first == dist[it->second]) {
				multiple[it->second] = true;
			}
		}
	}
	
	if (multiple[N-1]) {
		printf("yes\n");
	} else {
		printf("no\n");
	}
		
	return 0;
}
