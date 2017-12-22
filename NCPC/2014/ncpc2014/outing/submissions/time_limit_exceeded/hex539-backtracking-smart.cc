#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
 * Author
 *   Robin Lee (hex539)
 *
 * Algorithm
 *   Backtracking with some workarounds to avoid pathological cases. Copes with
 *   N=100 due to these optimisations, but chokes on N=1000.
 *
 * Complexity
 *   O(2^sqrt(N))
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

    if (not depth[a]) depth[a]=1;
    else if (!~p) return;

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

int solve(int n,int m,int slack=0){
    if (n<=0){
        return max(0, m-slack);
    }

    int res=m;
    for (int i=0; i<=tails[n].size(); i++){
        if (i) slack+=tails[n][i-1];
        if (m-i*n>=0){
            res=min(res,solve(n-1,m-i*n,slack));
        }
    }
    return res;
}

int main(){
    // read in participants, make connectivity clusters using depth-first search
    int n,m; cin>>n>>m;
    for (int i=0; i<n; i++) cin>>x[i], --x[i];
    for (int i=n; i--;) dfs(i);
    for (int i=n; i--;) if (max_size[i]) tails[min_size[i]].push_back(max_size[i]-min_size[i]);
    for (int i=n+1; i--;) sort(tails[i].rbegin(),tails[i].rend());

    cout<<m-solve(n,m)<<endl;
}
