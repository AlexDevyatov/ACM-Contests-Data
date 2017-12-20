#include <queue>
#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int N, U = 0, K;

unordered_map<string,int> s_to_id;
int get_id(string s){
	if(s_to_id.find(s) == s_to_id.end())
		s_to_id[s] = U++;
	return s_to_id[s];
}

bool is_program(string s){
	return s.find("::PROGRAM") == s.size() - 9 && s.size() != 8;
}

int main() {
	cin >> N;
	vector<vector<int> > adj(N);
	queue<int> q;
	vector<bool> in_use(N,false);
	FOR(ii,0,N){
		string name;
		cin >> name >> K;
		int id = get_id(name);
		if(is_program(name)){
			q.push(id);
			in_use[id] = true;
		}
		while(K-->0){
			cin >> name;
			adj[get_id(name)].push_back(id);
		}
	}
	while(!q.empty()){
		int n = q.front();
		q.pop();
		for(auto to: adj[n])if(!in_use[to]){
			in_use[to] = true;
			q.push(to);
		}
	}
	cout << count(all(in_use), false) << endl;
	return 0;
}
