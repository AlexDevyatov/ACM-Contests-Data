#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
 * Author
 *   Robin Lee (hex539)
 *
 * Algorithm
 *   Greedily take the cluster with the largest maximum size
 *
 * Complexity
 *   O(NlogN)
 */

#define MAXN 1000
vector<int> tails[MAXN+1];
int min_size[MAXN];
int max_size[MAXN];
int x[MAXN];

void dfs(int a,int p=-1){
    static bool active[MAXN];
    static int depth[MAXN];
    static int sink[MAXN];

    if (depth[a] and !~p) return;

    active[a]=true;
    int b=x[a];
    sink[a]=a;

    if (active[b]){
        min_size[a]=1+(depth[a]-depth[b]);
    }else{
        if (not depth[b]) depth[b]=depth[a]+1, dfs(b,a);
        sink[a]=sink[b];
    }

    ++max_size[sink[a]];
    active[a]=false;
}

int greedy(vector<pair<int,int>> &v,int k){
    pair<int,int> res;
    for (auto i: v){
      if (res.second+i.second>k) continue;
      res.first+=i.first;
      res.second+=i.second;
    }
    return min(res.first,k);
}

int main(){
    int n,k; cin>>n>>k;
    for (int i=0; i<n; i++) cin>>x[i], --x[i];
    for (int i=n; i--;) dfs(i);

    vector<pair<int,int>> all;
    for (int i=n; i--;) if (max_size[i]) all.emplace_back(max_size[i], min_size[i]);

    int res=0;
    sort(all.begin(),all.end());
    res=max(res,greedy(all,k));
    reverse(all.begin(),all.end());
    res=max(res,greedy(all,k));

    cout<<res<<endl;
}
